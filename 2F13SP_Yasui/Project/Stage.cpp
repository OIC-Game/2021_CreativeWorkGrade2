#include "Stage.h"
#include "GlobalDefine.h"


CStage::CStage() :
	stage_ChipTexture(),
	stage_BackTexture(),
	stage_ChipSize(0),
	stage_XCount(0),
	stage_YCount(0),
	stage_pChipData(NULL),
	stage_Scroll(0.0f, 0.0f),
	stage_EnemyTextureCount(0),
	stage_pEnemyTexture(NULL),
	stage_EnemyCount(0),
	stage_ItemTextureCount(0),
	stage_pItemTexture(NULL),
	stage_ItemCount(0),
	stage_ChipMove(0.0f),
	stage_chipUp(false),
	stage_break(false),
	stage_tmpChipX(0),
	stage_tmpChipY(0),
	stage_BlockAttackSE(),
	stage_NowStage(0),
	stage_BlockDestroy(false),
	stage_BlockDestroyWait(0),
	stage_BlockDestroySE(),
	stage_BlockChange(false),
	stage_FixScroll(false)
{
}

CStage::~CStage()
{
}

bool CStage::Load(char* pName)
{

	FILE* fp = fopen(pName, "rt");
	if (fp == NULL) {
		return false;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	//ファイルサイズ分だけメモリを確保する
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけメモリ確保
	char* buffer = (char*)malloc(fSize + 1);
	//ファイルをすべてバッファに読み込む
	fSize = fread(buffer, 1, fSize, fp);
	buffer[fSize] = '\0';
	char* pstr;

	//テクスチャの読み込み
	pstr = strtok(buffer, ",");
	if (!stage_BackTexture.Load(pstr)) {
		return false;
	}
	pstr = strtok(NULL, ",");
	if (!stage_ChipTexture.Load(pstr)) {
		return false;
	}

	//チップサイズ
	stage_ChipSize = atof(strtok(NULL, ","));
	//マップのチップ数
	stage_XCount = atoi(strtok(NULL, ","));
	stage_YCount = atoi(strtok(NULL, ","));

	//マップチップ用のメモリ確保
	stage_pChipData = (char*)malloc(stage_XCount * stage_YCount);
	stage_gap = new float[stage_XCount * stage_YCount];
	stage_gapMove = new float[stage_XCount * stage_YCount];

	//チップデータの読み込み
	for (int y = 0; y < stage_YCount; y++) {
		for (int x = 0; x < stage_XCount; x++) {
			stage_pChipData[y * stage_XCount + x] = atoi(strtok(NULL, ","));
		}
	}


	//敵のテクスチャの読み込み
	pstr = strtok(NULL, ",");
	stage_EnemyTextureCount = atoi(pstr);
	stage_pEnemyTexture = new CTexture[stage_EnemyTextureCount];
	for (int i = 0; i < stage_EnemyTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!stage_pEnemyTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//敵配置データの読み込み
	stage_pEnemyData = (char*)malloc(stage_XCount * stage_YCount);
	stage_EnemyCount = 0;
	for (int y = 0; y < stage_YCount; y++)
	{
		for (int x = 0; x < stage_XCount; x++)
		{
			stage_pEnemyData[y * stage_XCount + x] = atoi(strtok(NULL, ","));
			if (stage_pEnemyData[y * stage_XCount + x] > 0)
			{
				stage_EnemyCount++;
			}
		}
	}

	//アイテムのテクスチャ読み込み
	pstr = strtok(NULL, ",");
	stage_ItemTextureCount = atoi(pstr);
	stage_pItemTexture = new CTexture[stage_ItemTextureCount];
	for (int i = 0; i < stage_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!stage_pItemTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//アイテム配置データの読み込み
	stage_pItemData = (char*)malloc(stage_XCount * stage_YCount);
	stage_ItemCount = 0;
	for (int y = 0; y < stage_YCount; y++)
	{
		for (int x = 0; x < stage_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			stage_pItemData[y * stage_XCount + x] = atoi(pstr);
			if (stage_pItemData[y * stage_XCount + x] > 0)
			{
				stage_ItemCount++;
			}
		}
	}



	//ファイルを閉じる
	fclose(fp);
	free(buffer);



	//SEロード
	if (!stage_BlockAttackSE.Load("BlockAttack.mp3"))
	{
		return false;
	}
	if (!stage_BlockDestroySE.Load("BlockDestroy.mp3"))
	{
		return false;
	}
	//敵弾テクスチャロード
	if (!stage_EnemyShotTexture.Load("EnemyShot_Skeleton.png"))
	{
		return false;
	}
	if (!stage_EnemyFireTexture.Load("Mario_Fire.png"))
	{
		return false;
	}

	return true;

}

void CStage::Initialize(CEnemy* pEnemy, CItem* pItem)
{
	stage_Scroll = Vector2(0, 0);
	stage_ChipMove = 0.0f;
	stage_chipUp = false;
	stage_break = false;
	stage_tmpChipX = 0;
	stage_tmpChipY = 0;
	int n = 0;
	stage_BlockDestroy = false;
	stage_BlockDestroyWait = 0;
	stage_BlockChange = false;
	stage_FixScroll = false;

	//敵初期化
	for (int y = 0; y < stage_YCount; y++)
	{

		for (int x = 0; x < stage_XCount; x++)
		{
			//配置番号
			//0は配置しない
			char on = stage_pEnemyData[y * stage_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			if (on == ENEMY_MARIO)
			{
				pEnemy[n].SetTexture(&stage_pEnemyTexture[on], &stage_EnemyFireTexture);
			}
			else
			{
				pEnemy[n].SetTexture(&stage_pEnemyTexture[on],  & stage_EnemyShotTexture);
			}
			pEnemy[n++].Initialize(x * stage_ChipSize, y * stage_ChipSize, on);
		}
	}
	n = 0;
	//アイテム初期化
	for (int y = 0; y < stage_YCount; y++)
	{
		for (int x = 0; x < stage_XCount; x++)
		{
			//配置番号
			//番号０は配置しない
			char on = stage_pItemData[y * stage_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pItem[n].SetTexture(&stage_pItemTexture[on]);
			pItem[n++].Initialize(x * stage_ChipSize, y * stage_ChipSize, on);
		}
	}

	//ブロック移動の位置と速度を初期化
	for (int y = 0; y < stage_YCount; y++) {
		for (int x = 0; x < stage_XCount; x++) {
			stage_gap[y * stage_XCount + x] = 0;
			stage_gapMove[y * stage_XCount + x] = 0;
		}
	}
}

void CStage::Update(CPlayer& pl)
{

	//プレイヤーの矩形取得
	CRectangle prect = pl.GetRectPlayer();
	//スクリーンの幅
	float sw = g_pGraphics->GetTargetWidth();
	//ステージ全体の幅
	float stgw = stage_ChipSize * stage_XCount;

	//座標が画面端によっている(角端から200pixel)場合スクロールを行って補正する。
	if (pl.Getplayer_PositionX() < 5270 && !pl.GetWarpFlg())
	{
		if (prect.Left - stage_Scroll.x < 400) {
			stage_Scroll.x -= 400 - (prect.Left - stage_Scroll.x);
			if (stage_Scroll.x <= 0) {
				stage_Scroll.x = 0;
			}
		}
		else if (prect.Right - stage_Scroll.x > sw - 400) {
			stage_Scroll.x += (prect.Right - stage_Scroll.x) - (sw - 400);
			if (stage_Scroll.x >= stgw - sw) {
				stage_Scroll.x = stgw - sw;
			}
		}
	}
	else if (pl.GetWarpFlg() && !stage_FixScroll)
	{

		stage_Scroll.x = 6175;//(prect.Right - stage_Scroll.x) - (sw - 400);

			stage_FixScroll = true;
	}

	if (pl.GetMarioDead())
	{
		if (prect.Left - stage_Scroll.x < 400) {
			stage_Scroll.x -= 400 - (prect.Left - stage_Scroll.x);
			if (stage_Scroll.x <= 0) {
				stage_Scroll.x = 0;
			}
		}
		else if (prect.Right - stage_Scroll.x > sw - 400) {
			stage_Scroll.x += (prect.Right - stage_Scroll.x) - (sw - 400);
			if (stage_Scroll.x >= stgw - sw) {
				stage_Scroll.x = stgw - sw;
			}
		}
	}
	


	//ブロック動き処理
	for (int y = 0; y < stage_YCount; y++) {
		for (int x = 0; x < stage_XCount; x++) {
			stage_gap[y * stage_XCount + x] = stage_gapMove[y * stage_XCount + x];

			if (stage_gapMove[y * stage_XCount + x] > 0)
			{
				stage_gapMove[y * stage_XCount + x] -= 0.5;
			}
		}
	}
	if (stage_chipUp && pl.Getplayer_DeadFlg() == false)
	{
		stage_gapMove[stage_tmpChipY * stage_XCount + stage_tmpChipX] = 5;
		stage_BlockAttackSE.Stop();
		stage_BlockAttackSE.Play();
		stage_chipUp = false;
	}

	//ブロック破壊処理
	if (stage_BlockDestroy && pl.Getplayer_BigFlg() && pl.Getplayer_DeadFlg() == false)
	{
		if (stage_BlockDestroyWait > 4)
		{
			stage_BlockDestroySE.Play();
		}
		stage_BlockDestroyWait--;
		if (stage_BlockDestroyWait <= 0)
		{
			if (stage_pChipData[stage_tmpChipY * stage_XCount + stage_tmpChipX] == CHIP_BLOCK)
			{
				//非表示
				stage_pChipData[stage_tmpChipY * stage_XCount + stage_tmpChipX] = 0;
				stage_BlockDestroy = false;
			}

		}
	}
	//ブロック変化処理
	if (stage_BlockChange && pl.Getplayer_DeadFlg() == false)
	{
			if (stage_pChipData[stage_tmpChipY * stage_XCount + stage_tmpChipX] == CHIP_QUESTION)
			{

				stage_pChipData[stage_tmpChipY * stage_XCount + stage_tmpChipX] = CHIP_HARDBLOCK;
				stage_BlockChange = false;
			}
	}

	if (pl.GetMarioDead())
	{

		int x = 223;
		for (int y = 12; y < 16; y++)
		{
			stage_pChipData[y * stage_XCount + x] = 0;
		}
	}


}

void CStage::Render(void)
{

	//遠景の描画
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	float bScale = sch / (float)stage_BackTexture.GetHeight();
	int bw = (int)(stage_BackTexture.GetWidth() * bScale);
	int bh = (int)(stage_BackTexture.GetHeight() * bScale);
	for (float y = ((int)-stage_Scroll.y % bh) - bh; y < sch; y += bh) {
		for (float x = ((int)-stage_Scroll.x / 4 % bw) - bw; x < scw; x += bw) {
			stage_BackTexture.Render(x, y);
		}
	}

	//テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = stage_ChipTexture.GetWidth() / stage_ChipSize;
	//マップチップの描画
	for (int y = 0; y < stage_YCount; y++)
	{
		//描画するチップ番号
		//チップ番号0は描画しない
		for (int x = 0; x < stage_XCount; x++)
		{
			char cn = stage_pChipData[y * stage_XCount + x] - 1;
			if (cn < 0) {
				continue;
			}

			//マップチップの矩形
			CRectangle cr(stage_ChipSize * (cn % tcx), stage_ChipSize * (cn / tcx), stage_ChipSize * (cn % tcx + 1), stage_ChipSize * (cn / tcx + 1));
			//マップチップの描画
			stage_ChipTexture.Render(-stage_Scroll.x + x * stage_ChipSize, -stage_Scroll.y + y * stage_ChipSize - stage_gap[y * stage_XCount + x], cr);
		}
	}


}

void CStage::RenderDebug(void)
{

}

void CStage::Release(void)
{
	//チップ解放
	stage_ChipTexture.Release();
	stage_BackTexture.Release();
	if (stage_pChipData) {
		free(stage_pChipData);
		stage_pChipData = NULL;
	}
	//敵解放
	if (stage_pEnemyData)
	{
		free(stage_pEnemyData);
		stage_pEnemyData = NULL;
	}
	if (stage_pEnemyTexture)
	{
		delete[] stage_pEnemyTexture;
		stage_pEnemyTexture = NULL;
	}
	//アイテム解放
	if (stage_pItemData)
	{
		free(stage_pItemData);
		stage_pItemData = NULL;
	}
	if (stage_pItemTexture)
	{
		delete[] stage_pItemTexture;
		stage_pItemTexture = NULL;
	}
	//アイテム解放
	if (stage_gap)
	{
		delete[] stage_gap;
		stage_gap = NULL;
	}
	//アイテム解放
	if (stage_gapMove)
	{
		delete[] stage_gapMove;
		stage_gapMove = NULL;
	}


	//SE解放
	stage_BlockAttackSE.Release();
	stage_BlockDestroySE.Release();
	
	//敵弾テクスチャ解放
	stage_EnemyShotTexture.Release();
	stage_EnemyFireTexture.Release();

}






bool CStage::Collision(CRectangle r, float& ox, float& oy, bool& og, bool& dead, bool& jump, CPlayer& pl,bool& magma)
{
	bool re = false;
	int	 wait = 10;
	//当たり判定する矩形の左上と右下のチップ位置を求める
	int lc = r.Left / stage_ChipSize;
	int rc = r.Right / stage_ChipSize;
	int tc = r.Top / stage_ChipSize;
	int bc = r.Bottom / stage_ChipSize;

	//ステージの範囲外にならないようにする
	if (lc < 0) lc = 0;
	if (tc < 0) tc = 0;
	if (rc >= stage_XCount) rc = stage_XCount - 1;
	if (bc >= stage_YCount) bc = stage_YCount - 1;
	//当たり判定をする矩形の左上から右下の範囲のみ当たり判定を行う
	//それ以外の番号は当たることがないので判定は必要ない
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			char cn = stage_pChipData[y * stage_XCount + x] - 1;
			//チップ番号0は当たり判定しない
			if (cn < 0) {
				continue;
			}
			//ゴールフラッグも当たり判定をしない
			else if (cn == CHIP_GOALFLAG_L - 1 || cn == CHIP_GOALFLAG_R - 1)
			{
				continue;
			}
			//クリアしたとき、ゴールフラッグの球と棒の当たり判定をしない
			if (pl.Getplayer_ClearFlg() && (cn == CHIP_GOALBALL - 1 || cn == CHIP_GOALROD - 1))
			{
				continue;
			}

			//マップチップの矩形
			CRectangle cr(x * stage_ChipSize, y * stage_ChipSize, x * stage_ChipSize + stage_ChipSize, y * stage_ChipSize + stage_ChipSize);

			//ゴールフラッグ矩形
			if (cn == 21 || cn == 5)
			{
				CRectangle temp(x * stage_ChipSize + 12, y * stage_ChipSize, x * stage_ChipSize + stage_ChipSize - 12, y * stage_ChipSize + stage_ChipSize);
				//マップチップの矩形
				cr = temp;
			}
			//マグマ矩形
			if (cn == 27)
			{
				CRectangle temp(x * stage_ChipSize, y * stage_ChipSize + 10, x * stage_ChipSize + stage_ChipSize, y * stage_ChipSize + stage_ChipSize);
				//マップチップの矩形
				cr = temp;
			}

			CRectangle grec = r;
			grec.Top = grec.Bottom;
			grec.Bottom = grec.Top + 1;
			grec.Expansion(-6, 0);
			if (cr.CollisionRect(grec)) {
				og = true;
			}
			//当たり判定用のキャラクタ矩形
			//下で範囲を限定した専用の矩形を作成する
			CRectangle bottomRect = r;
			bottomRect.Top = bottomRect.Bottom - 1;
			bottomRect.Expansion(-6, 0);
			//下と当たり判定
			if (cr.CollisionRect(bottomRect)) {
				re = true;
				//下の埋まりなのでチップ上端から矩形の下端の値を引いた値が埋まりの値
				oy += cr.Top - bottomRect.Bottom;
				r.Top += cr.Top - bottomRect.Bottom;
				r.Bottom += cr.Top - bottomRect.Bottom;

				//接触しているブロックが動いているとき、敵とアイテムのフラグをTrue
				if (stage_gap[y * stage_XCount + x] != 0)
				{
					dead = true;
					jump = true;
				}
				if (cn == CHIP_GOALROD -1 || cn == CHIP_GOALBALL -1)
				{
					pl.Setplayer_ClearFlg(true);
				}
				if (cn == 35)
				{
					pl.SetWarpFlg(true);
				}
				if (cn == 27)
				{
					magma = true;
				}
			}
			//当たり判定用のキャラクタ矩形
			//上で範囲を限定した専用の矩形を作成する
			CRectangle topRect = r;
			topRect.Bottom = topRect.Top + 1;		//上の矩形は下側を上と同じ値にする
			topRect.Expansion(-6, 0);				//横の範囲を少し狭める
			//上と当たり判定
			if (cr.CollisionRect(topRect)) {

				re = true;
				//上の埋まりなのでチップ下端から矩形の上の値を引いた値が埋まりの値
				oy += cr.Bottom - topRect.Top;
				r.Top += cr.Bottom - topRect.Top;
				r.Bottom += cr.Bottom - topRect.Top;

				//接触したブロックの動きフラグをTrueにする
				if (cn == CHIP_QUESTION - 1 || cn == CHIP_HARDBLOCK - 1 
					|| cn == CHIP_EMOJI - 1 || cn == CHIP_BLOCK - 1 || cn == CHIP_COINBLOCK - 1)
				{

					//XとYの値を退避
					stage_tmpChipX = x;
					stage_tmpChipY = y;
					//ブロック動きフラグをTrue
					stage_chipUp = true;
				}
				//破壊
				if (cn == CHIP_BLOCK - 1 && pl.Getplayer_BigFlg())
				{
					stage_tmpChipX = x;
					stage_tmpChipY = y;
					stage_BlockDestroy = true;
					stage_BlockDestroyWait = 5;
				}
				//ブロック変化
				if (cn == CHIP_QUESTION - 1 && stage_chipUp)
				{
					stage_tmpChipX = x;
					stage_tmpChipY = y;
					stage_BlockChange = true;
				}

			}
			//当たり判定用のキャラクタ矩形
			//左、右それぞれで範囲を限定した専用の矩形を作成する
			CRectangle leftRect = r;
			leftRect.Right = leftRect.Left + 1;		//左の矩形は右側を左と同じ値にする
			leftRect.Expansion(0, -6);			//縦の範囲を少し狭める
			CRectangle rightRect = r;
			rightRect.Left = rightRect.Right - 1;		//右の矩形は左側を右と同じ値にする
			rightRect.Expansion(0, -6);			//縦の範囲を少し狭める
			//左と当たり判定
			if (cr.CollisionRect(leftRect)) {
				re = true;

				ox += cr.Right - leftRect.Left;
				r.Left += cr.Right - leftRect.Left;
				r.Right += cr.Right - leftRect.Left;
				if (cn == CHIP_GOALROD - 1)
				{
					pl.Setplayer_ClearFlg(true);
				}
				if (cn == CHIP_CLEARTRANSITION - 1)
				{
					pl.Setplayer_ClearTransitionFlg(true);
				}
				if (cn == 35)
				{
					pl.SetWarpFlg(true);
				}
				if (cn == 34)
				{
					pl.SetBossClearTrantionFlg(true);
				}

			}
			//右と当たり判定
			else if (cr.CollisionRect(rightRect)) {
				re = true;

				ox += cr.Left - rightRect.Right;
				r.Left += cr.Left - rightRect.Right;
				r.Right += cr.Left - rightRect.Right;

				if (cn == CHIP_GOALROD - 1)
				{
					pl.Setplayer_ClearFlg(true);
				}
				if (cn == CHIP_CLEARTRANSITION - 1)
				{
					pl.Setplayer_ClearTransitionFlg(true);
				}
				if (cn == 35)
				{
					pl.SetWarpFlg(true);
				}
				if (cn == 34)
				{
					pl.SetBossClearTrantionFlg(true);
				}
			}

		}
	}

	return re;

}


