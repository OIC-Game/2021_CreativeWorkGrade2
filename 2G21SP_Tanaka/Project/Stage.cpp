#include "Stage.h"



CStage::CStage():
m_ChipTexture(),
m_BackTexture(),
m_ChipSize(0),
m_XCount(0),
m_YCount(0),
m_pChipData(NULL),
m_ScrollX(0),
m_ScrollY(0),
m_EnemyTextureCount(0),
m_pEnemyTexture(NULL),
m_EnemyCount(0),
m_ItemTextureCount(0),
m_pItemTexture(NULL),
m_ItemCount(0){
}

CStage::~CStage(){
}

bool CStage::Load(char* pName){
	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルを全てバッファに読み込み
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '/0';
	char* pstr;

	//テクスチャの読み込み
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr))
	{
		return false;
	}

	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr))
	{
		return false;
	}

	//チップサイズ
	m_ChipSize = atof(strtok(NULL, ","));

	//マップのチップ数
	m_XCount = atoi(strtok(NULL, ","));
	m_YCount = atoi(strtok(NULL, ","));

	//マップチップ用のメモリ確保
	m_pChipData = (char*)malloc(m_XCount * m_YCount);

	//マップデータの読み込み
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pChipData[y * m_XCount + x] = atoi(strtok(NULL, ","));
		}
	}

	//敵のテクスチャ読み込み
	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);
	m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
	for (int i = 0; i < m_EnemyTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pEnemyTexture[i].Load(pstr))
		{
			return false;
		}
	}
	//配置データの読み込み
	m_pEnemyData = (char*)malloc(m_XCount * m_YCount);
	m_EnemyCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pEnemyData[y * m_XCount + x] = atoi(strtok(NULL, ","));
			if (m_pEnemyData[y * m_XCount + x] > 0)
			{
				m_EnemyCount++;
			}
		}
	}
	//アイテムのテクスチャの読み込み
	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for (int i = 0; i < m_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pItemTexture[i].Load(pstr))
		{
			return false;
		}
	}
	//配置データの読み込み
	m_pItemData = (char*)malloc(m_XCount * m_YCount);
	m_ItemCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pItemData[y * m_XCount + x] = atoi(strtok(NULL, ","));
			if (m_pItemData[y * m_XCount + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}
	//音の読み込み
	if (m_bleakblockSound.Load("se_gareki01.mp3"))
	{
		return false;
	}
	//ファイルを閉じる
	fclose(fp);
	free(pBuffer);
	return true;
}

void CStage::Initialize(char* pName, CEnemy* pEnemy, CItem* pItem) {
	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルを全てバッファに読み込み
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '/0';
	char* pstr;

	//テクスチャの読み込み
	pstr = strtok(pBuffer, ",");
	m_BackTexture.Load(pstr);

	pstr = strtok(NULL, ",");
	m_ChipTexture.Load(pstr);

	//チップサイズ
	m_ChipSize = atof(strtok(NULL, ","));

	//マップのチップ数
	m_XCount = atoi(strtok(NULL, ","));
	m_YCount = atoi(strtok(NULL, ","));

	//マップチップ用のメモリ確保
	m_pChipData = (char*)malloc(m_XCount * m_YCount);

	//マップデータの読み込み
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pChipData[y * m_XCount + x] = atoi(strtok(NULL, ","));
		}
	}

	//敵のテクスチャ読み込み
	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);
	for (int i = 0; i < m_EnemyTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		m_pEnemyTexture[i].Load(pstr);
	}
	
	//配置データの読み込み
	m_pEnemyData = (char*)malloc(m_XCount * m_YCount);
	m_EnemyCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pEnemyData[y * m_XCount + x] = atoi(strtok(NULL, ","));
			if (m_pEnemyData[y * m_XCount + x] > 0)
			{
				m_EnemyCount++;
			}
		}
	}

	//アイテムのテクスチャの読み込み
	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	for (int i = 0; i < m_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		m_pItemTexture[i].Load(pstr);
	}
	//配置データの読み込み
	m_pItemData = (char*)malloc(m_XCount * m_YCount);
	m_ItemCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pItemData[y * m_XCount + x] = atoi(strtok(NULL, ","));
			if (m_pItemData[y * m_XCount + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}
	//ファイルを閉じる
	fclose(fp);
	free(pBuffer);

	m_ScrollX = 0;
	m_ScrollY = 0;
	int n = 0;
	//敵
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号0は配置しない
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on]);
			pEnemy[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
	//アイテム
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号0は配置しない
			char on = m_pItemData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pItem[n].SetTexture(&m_pItemTexture[on]);
			pItem[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
}

void CStage::Update(CPlayer& pl){
	//プレイヤーの矩形取得
	CRectangle prec = pl.GetRect();
	//スクリーンの幅
	float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	//ステージ全体の幅
	float stgw = m_ChipSize * m_XCount;
	//座標が画面端によっている（右端から500pixel,左端から400pixel)場合スクロールを行って補正する
	if (prec.Right - m_ScrollX > sw - 500)
	{
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - 500);
		if (m_ScrollX >= stgw - sw)
		{
			m_ScrollX = stgw - sw;
		}
	}
	else if (prec.Left - m_ScrollX < 400)
	{
		m_ScrollX -= 400 - (prec.Left - m_ScrollX);
		if (m_ScrollX <= 0)
		{
			m_ScrollX = 0;
		}
	}
	
}

void CStage::Render(void){
	//遠景の描画
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-m_ScrollY % hn) - hn; y < sch; y += hn)
	{
		for (float x = ((int)-m_ScrollX % wn) - wn; x < scw; x += wn)
		{
			m_BackTexture.Render(x, y);
		}
	}

	//テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	// マップチップの描画
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//描画するチップ番号
			//チップ番号0は描画しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize * (cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//マップチップの描画
			m_ChipTexture.Render(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize, cr);
		}
	}
}
void CStage::RenderDebug(void){
	//位置の描画
	CGraphicsUtilities::RenderString(10, 100, "スクロール X : %.0f , Y : %.0f", m_ScrollX, m_ScrollY);
}

void CStage::Release(void){
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
	//敵
	if (m_pEnemyData)
	{
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pEnemyTexture)
	{
		delete[] m_pEnemyTexture;
		m_pEnemyTexture = NULL;
	}
	//アイテム
	if (m_pItemData)
	{
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pItemTexture)
	{
		delete[] m_pItemTexture;
		m_pItemTexture = NULL;
	}
	m_bleakblockSound.Release();
}

bool CStage::Collision(CRectangle r, CPlayer& pl, float& ox, float& oy,int& popItemNo){
	bool re = false;
	
	//当たり判定をする矩形の左上と右下のチップ位置を求める
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;
	//ステージの範囲外にはならないようにする
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	//当たり判定をする矩形の左上から右下の範囲のみ当たり判定を行う
	//それ以外の番号は当たることがないので判定が必要ない
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			//チップ番号0は当たり判定しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			if (cn == FLAG1)
			{
				continue;
			}
			if (cn == WALL1 || cn == WALL2 || cn == WALL3 || cn == WALL4)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//当たり判定用のキャラクタの矩形
			//上で範囲を限定した専用の矩形を作成
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;		//上の矩形は下側を上と同じ値に
			trec.Expansion(-6, 0);			//横の範囲を少し狭める
			//上との当たり判定
			if (cr.CollisionRect(trec))
			{
				if (cn == GOALPOOL)
				{
					continue;
				}
				if (cn == KINOKOBLOCK)
				{
					m_pChipData[y * m_XCount + x] = 23 + 1;
					popItemNo = 1;
				}
				if (cn == HIDENBLOCK)
				{
					m_pChipData[y * m_XCount + x] = 23 + 1;
					popItemNo = 2;
				}
				if (cn == COINBLOCK)
				{
					pl.BlockCoinGet();
					m_pPoPItemManager->Start(cr.Left, cr.Top - m_ChipSize, POP_COIN);
					m_pChipData[y * m_XCount + x] = 23 + 1;
				}
				if (cn == BLOCK && pl.GetStat() >= 1)
				{
					pl.BreakBlock();
					m_pChipData[y * m_XCount + x] = 0;
					m_bleakblockSound.Play();
				}
				if (cn == CCOINBLOCK)
				{
					if (m_CoinCount < 9)
					{
						m_CoinCount = m_CoinCount + 1;
						pl.BlockCoinGet();
						m_pPoPItemManager->Start(cr.Left, cr.Top - m_ChipSize, POP_COIN);
					}
					else if (m_CoinCount >= 9)
					{
						pl.BlockCoinGet();
						m_pPoPItemManager->Start(cr.Left, cr.Top - m_ChipSize, POP_COIN);
						m_pChipData[y * m_XCount + x] = 23 + 1;
						m_CoinCount = 0;
					}
				}
				re = true;
				//上との埋まりなのでチップ下端から矩形の上端の値を引いた値が埋まりの値
				oy += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}
			//当たり判定用のキャラクタ矩形
			//下で範囲を限定した専用の矩形を作成
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;		//下の矩形は上側を下と同じ値
			brec.Expansion(-6, 0);			//横の範囲を少し狭める
			//下との当たり判定
			if (cr.CollisionRect(brec))
			{
				if (cn == GOALPOOL)
				{
					continue;
				}
				if (cn == HIDENBLOCK)
				{
					continue;
				}
				re = true;
				//下の埋まりなのでチップ上端から矩形の下端の値を引いた値が埋まりの値
				oy += cr.Top - brec.Bottom;
				r.Top += cr.Top - brec.Bottom;
				r.Bottom += cr.Top - brec.Bottom;
			}
			//当たり判定用のキャラクタ矩形
			//左、右それぞれで範囲を限定した専用の矩形を作成
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;		//左の矩形は右側を左と同じ値に
			lrec.Expansion(0, -6);			//縦の範囲を少し狭める
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;		//右の矩形は左側を右と同じ値に
			rrec.Expansion(0, -6);			//****
			//左と当たり判定
			if (cr.CollisionRect(lrec))
			{
				if (cn == HIDENBLOCK)
				{
					continue;
				}
				re = true;
				//左の埋まりなのでチップ右側から矩形の左端の値を引いた値が埋まりの値
				ox += cr.Right - lrec.Left;
				r.Left += cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//右と当たり判定
			else if (cr.CollisionRect(rrec))
			{
				if (cn == HIDENBLOCK)
				{
					continue;
				}
				if (cn == GOALPOOL || cn == FLAG2 || cn == FLAG3)
				{
					pl.IsGoal();
				}
				else if (cn == CASLE)
				{
					pl.Clear();
				}
				else
				{
					re = true;
					//右の埋まりなのでチップ左側から矩形の右端の値を引いた値が埋まりの値
					ox += cr.Left - rrec.Right;
					r.Left += cr.Left - rrec.Right;
					r.Right += cr.Left - rrec.Right;
				}
			}
		}
	}
	return re;
}

bool CStage::CollisionPlayerFire(CRectangle r){
	bool re = false;

	//当たり判定する矩形の左上と右下のチップ位置を求める
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;
	//ステージの範囲外にはならないようにする
	if (lc < 0)
	{
		lc = 0;
	}
	if (tc < 0)
	{
		tc = 0;
	}
	if (rc >= m_XCount)
	{
		rc = m_XCount - 1;
	}
	if (bc >= m_YCount)
	{
		bc = m_YCount - 1;
	}
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			//チップ番号０は当たり判定しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//下で範囲を限定した専用の矩形を作成する。
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;	//下の矩形は上側を下と同じ値にする
			brec.Expansion(-1, 0);		//横の範囲を少し狭める
			//下と当たり判定
			if (cr.CollisionRect(brec))
			{
				re = true;
			}
			//当たり判定用のキャラクタ矩形
			//左、右それぞれで範囲を限定した専用の矩形を作成する。
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;	//左の矩形は右側を左と同じ値にする
			lrec.Expansion(0, -1);		//縦の範囲を少し狭める
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;	//右の矩形は左側を右と同じ値にする
			rrec.Expansion(0, -1);		//縦の範囲を少し狭める
			//左と当たり判定
			if (cr.CollisionRect(lrec))
			{
				re = true;
			}
			//右と当たり判定
			else if (cr.CollisionRect(rrec))
			{
				re = true;
			}
			//当たり判定用のキャラクタ矩形
			//上で範囲を限定した専用の矩形を作成する。
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;	//上の矩形は下側を上と同じ値にする
			trec.Expansion(-1, 0);		//横の範囲を少し狭める
			//上と当たり判定
			if (cr.CollisionRect(trec))
			{
				re = true;
			}
		}
	}
	return re;
}
