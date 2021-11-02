#include "Stage.h"


CStage::CStage() :
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

	m_GoalTextureCount(0),
	m_pGoalTexture(NULL),
	m_GoalCount(0),

	m_BlockTextureCount(0),
	m_pBlockTexture(NULL),
	m_BlockCount(0),

	m_breakBlockTextureCount(0),
	m_pbreakBlockTexture(NULL),
	m_breakBlockCount(0),

	/*m_DokanTextureCount(0),
	m_pDokanTexture(NULL),
	m_DokanCount(0),*/

	m_QuestionBlockTextureCount(0),
	m_pQuestionBlockTexture(NULL),
	m_QuestionBlockCount(0),

	

	m_GoalFlgTextureCount(0),
	m_pGoalFlgTexture(NULL),
	m_GoalFlgCount(0)
{
}


CStage::~CStage() {
}


bool CStage::Load(char* pName) {
	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//ファイルの全容量を調べる
	//一度ファイルの終端に移動して、その位置を調べることでサイズがわかる
	//調べ終わった後はファイルの先頭に移動して戻しておく
	//ただしこの方法でも正常なサイズを読み込むことはできない
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	//終端を含めるため＋１しておく
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルを全てバッファに読み込む
	//ここで実際に読み込めたサイズを調べてその終端に\0を入る
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
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
	pstr = strtok(NULL, ",");
	m_ChipSize = atof(pstr);

	//マップのチップ数
	pstr = strtok(NULL, ",");
	m_XCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YCount = atoi(pstr);

	//マップチップ用のメモリ確保
	m_pChipData = (char*)malloc(m_XCount * m_YCount);

	//チップデータの読み込み
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			m_pChipData[y * m_XCount + x] = atoi(pstr);
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
			pstr = strtok(NULL, ",");
			m_pEnemyData[y * m_XCount + x] = atoi(pstr);
			if (m_pEnemyData[y * m_XCount + x] > 0)
			{
				m_EnemyCount++;
			}
		}
	}
	pstr = strtok(NULL, ",");
	m_GoalTextureCount = atoi(pstr);
	m_pGoalTexture = new CTexture[m_GoalTextureCount];
	for (int i = 0; i < m_GoalTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pGoalTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pGoalData = (char*)malloc(m_XCount * m_YCount);
	m_GoalCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			m_pGoalData[y * m_XCount + x] = atoi(pstr);
			if (m_pGoalData[y * m_XCount + x] > 0)
			{
				m_GoalCount++;
			}
		}
	}

	//ゴールフラグ
		pstr = strtok(NULL, ",");
		m_GoalFlgTextureCount = atoi(pstr);
		m_pGoalFlgTexture = new CTexture[m_GoalFlgTextureCount];
		for (int i = 0; i < m_GoalFlgTextureCount; i++)
		{
			pstr = strtok(NULL, ",");
			if (!m_pGoalFlgTexture[i].Load(pstr))
			{
				return false;
			}
		}

		//配置データの読み込み
		m_pGoalFlgData = (char*)malloc(m_XCount * m_YCount);
		m_GoalFlgCount = 0;
		for (int y = 0; y < m_YCount; y++)
		{
			for (int x = 0; x < m_XCount; x++)
			{
				pstr = strtok(NULL, ",");
				m_pGoalFlgData[y * m_XCount + x] = atoi(pstr);
				if (m_pGoalFlgData[y * m_XCount + x] > 0)
				{
					m_GoalFlgCount++;
				}
			}
		}

	

	//ハテナブロック
	pstr = strtok(NULL, ",");
    m_QuestionBlockTextureCount = atoi(pstr);
	m_pQuestionBlockTexture = new CTexture[m_QuestionBlockTextureCount];
	for (int i = 0; i < m_QuestionBlockTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pQuestionBlockTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pQuestionBlockData = (char*)malloc(m_XCount * m_YCount);
	m_QuestionBlockCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			m_pQuestionBlockData[y * m_XCount + x] = atoi(pstr);
			if (m_pQuestionBlockData[y * m_XCount + x] > 0)
			{
				m_QuestionBlockCount++;
			}
		}
	}

	//レンガブロック
	pstr = strtok(NULL, ",");
	m_breakBlockTextureCount = atoi(pstr);
	m_pbreakBlockTexture = new CTexture[m_breakBlockTextureCount];
	for (int i = 0; i < m_breakBlockTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pbreakBlockTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pbreakBlockData = (char*)malloc(m_XCount * m_YCount);
	m_breakBlockCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			m_pbreakBlockData[y * m_XCount + x] = atoi(pstr);
			if (m_pbreakBlockData[y * m_XCount + x] > 0)
			{
				m_breakBlockCount++;
			}
		}
	}

	//ゴールポール
	//pstr = strtok(NULL, ",");
	//m_GoalTextureCount = atoi(pstr);
	//m_pGoalTexture = new CTexture[m_GoalTextureCount];
	//for (int i = 0; i < m_GoalTextureCount; i++)
	//{
	//	pstr = strtok(NULL, ",");
	//	if (!m_pGoalTexture[i].Load(pstr))
	//	{
	//		return false;
	//	}
	//}

	////配置データの読み込み
	//m_pGoalData = (char*)malloc(m_XCount * m_YCount);
	//m_GoalCount = 0;
	//for (int y = 0; y < m_YCount; y++)
	//{
	//	for (int x = 0; x < m_XCount; x++)
	//	{
	//		pstr = strtok(NULL, ",");
	//		m_pGoalData[y * m_XCount + x] = atoi(pstr);
	//		if (m_pGoalData[y * m_XCount + x] > 0)
	//		{
	//			m_GoalCount++;
	//		}
	//	}
	//}




	//四角ブロック
	pstr = strtok(NULL, ",");
	m_BlockTextureCount = atoi(pstr);
	m_pBlockTexture = new CTexture[m_BlockTextureCount];
	for (int i = 0; i < m_BlockTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pBlockTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pBlockData = (char*)malloc(m_XCount * m_YCount);
	m_BlockCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			m_pBlockData[y * m_XCount + x] = atoi(pstr);
			if (m_pBlockData[y * m_XCount + x] > 0)
			{
				m_BlockCount++;
			}
		}
	}

	

	//土管
	/*pstr = strtok(NULL, ",");
	m_DokanTextureCount = atoi(pstr);
	m_pDokanTexture = new CTexture[m_DokanTextureCount];
	for (int i = 0; i < m_DokanTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pDokanTexture[i].Load(pstr))
		{
			return false;
		}
	}*/

	//配置データの読み込み
	//m_pDokanData = (char*)malloc(m_XCount * m_YCount);
	//m_DokanCount = 0;
	//for (int y = 0; y < m_YCount; y++)
	//{
	//	for (int x = 0; x < m_XCount; x++)
	//	{
	//		pstr = strtok(NULL, ",");
	//		m_pDokanData[y * m_XCount + x] = atoi(pstr);
	//		if (m_pDokanData[y * m_XCount + x] > 0)
	//		{
	//			m_DokanCount++;
	//		}
	//	}
	//}
		


		
		//ファイルを閉じる
		fclose(fp);
		free(pBuffer);
		return true;
	
}


void CStage::Initialize(CEnemy* pEnemy, CGoal* pGoal, CGoalFlg* pGoalFlg, CQuestionBlock* pQuestionBlock, CbreakBlock* pbreakBlock,CBlock* pBlock)
{//CBlock* pBlock, ,, CDokan* pDokan, ) {
	m_ScrollX = 0;
	m_ScrollY = 0;
	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{

			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on]);
			pEnemy[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	//ゴールポール
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			char on = m_pGoalData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pGoal[n].SetTexture(&m_pGoalTexture[on]);
			pGoal[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	//ゴールフラグ
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			char on = m_pGoalFlgData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pGoalFlg[n].SetTexture(&m_pGoalFlgTexture[on]);
			pGoalFlg[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	//ハテナブロック
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			char on = m_pQuestionBlockData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pQuestionBlock[n].SetTexture(&m_pQuestionBlockTexture[on]);
			pQuestionBlock[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	//レンガブロック
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			char on = m_pbreakBlockData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pbreakBlock[n].SetTexture(&m_pbreakBlockTexture[on]);
			pbreakBlock[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	//四角ブロック
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			char on = m_pBlockData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pBlock[n].SetTexture(&m_pBlockTexture[on]);
			pBlock[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	

	//土管
	/*n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			char on = m_pDokanData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pDokan[n].SetTexture(&m_pDokanTexture[on]);
			pDokan[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}*/

	CUtilities::SetCurrentDirectory("Resource");
	//m_gBGM.Load("Stage01Loop.wav");

	/*m_gBGM.SetLoop(TRUE);
	m_gBGM.Play();*/

	
}


void CStage::Update(CPlayer& pl) {
	//プレイヤーの矩形取得
	CRectangle prec = pl.GetRect();
	//スクリーンの幅
	float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	//ステージ全体の幅
	float stgw = m_ChipSize * m_XCount;
	//座標が画面端によっている（各端から200pixel）場合スクロールを行って補正する
	if (prec.Left - m_ScrollX-50 < 200)
	{
		m_ScrollX -= 200 - (prec.Left - m_ScrollX);
		if (m_ScrollX <= 0)
		{
			m_ScrollX = 0;
		}
	}
	else if (prec.Right - m_ScrollX > sw -200)
	{
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - 100);
		if (m_ScrollX >= stgw - sw)
		{
			m_ScrollX = stgw - sw;
		}
	}
}


bool CStage::Collision(CRectangle r, float& ox, float& oy) {
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

	//当たり判定をする矩形の左上から右下の範囲のみ当たり判定をおこなう
	//それ以外の番号は当たることはないので判定が必要ない
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
			//当たり判定用のキャラクタ矩形
			//下で範囲を限定した専用の矩形を作成する。
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;	//下の矩形は上側を下と同じ値にする
			brec.Expansion(-6, 0);		//横の範囲を少し狭める
			//下と当たり判定
			if (cr.CollisionRect(brec))
			{
				re = true;
				//チップが斜面の場合自分の立ち位置から高さの割合を求める
				if (cn == LEFTSLOPE)
				{
					float sp = (brec.Right - cr.Left) / cr.GetWidth();
					if (sp < 0.0f)
					{
						sp = 0.0f;
					}
					else if (sp > 1.0f)
					{
						sp = 1.0f;
					}
					//斜面の上の位置を求める
					float cTop = cr.Bottom - cr.GetHeight() * sp;
					if (brec.Bottom < cTop)
					{
						continue;
					}
					oy += cTop - brec.Bottom;
					r.Top += cTop - brec.Bottom;
					r.Bottom += cTop - brec.Bottom;
				}
				else
				{
					//下の埋まりなのでチップの上端から矩形の下端の値を引いた値が埋まりの値になる
					oy += cr.Top - brec.Bottom;
					r.Top += cr.Top - brec.Bottom;
					r.Bottom += cr.Top - brec.Bottom;
				}
			}
			//チップが斜面の場合壁・天井としての当たり判定をおこなわない
			if (cn != LEFTSLOPE)
			{
				//当たり判定用のキャラクタ矩形
				//左、右それぞれで範囲を限定した専用の矩形を作成する。
				CRectangle lrec = r;
				lrec.Right = lrec.Left + 1;	//左の矩形は右側を左と同じ値にする
				lrec.Expansion(0, -6);		//縦の範囲を少し狭める
				CRectangle rrec = r;
				rrec.Left = rrec.Right - 1;	//右の矩形は左側を右と同じ値にする
				rrec.Expansion(0, -6);		//縦の範囲を少し狭める
				//左と当たり判定
				if (cr.CollisionRect(lrec))
				{
					re = true;
					//左の埋まりなのでチップの右端から矩形の左端の値を引いた値が埋まりの値になる
					ox += cr.Right - lrec.Left;
					r.Left += cr.Right - lrec.Left;
					r.Right += cr.Right - lrec.Left;
				}
				//右と当たり判定
				else if (cr.CollisionRect(rrec))
				{
					re = true;
					//右の埋まりなのでチップの左端から矩形の右端の値を引いた値が埋まりの値になる
					ox += cr.Left - rrec.Right;
					r.Left += cr.Left - rrec.Right;
					r.Right += cr.Left - rrec.Right;
				}
				//当たり判定用のキャラクタ矩形
				//上で範囲を限定した専用の矩形を作成する。
				CRectangle trec = r;
				trec.Bottom = trec.Top + 1;	//上の矩形は下側を上と同じ値にする
				trec.Expansion(-6, 0);		//横の範囲を少し狭める
				//上と当たり判定
				if (cr.CollisionRect(trec))
				{
					re = true;
					//上の埋まりなのでチップの下端から矩形の上端の値を引いた値が埋まりの値になる
					oy += cr.Bottom - trec.Top;
					r.Top += cr.Bottom - trec.Top;
					r.Bottom += cr.Bottom - trec.Top;
				}
			}
		}
	}

	return re;
}


void CStage::Render(void) {
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
	//マップチップの描画
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//描画するチップ番号
			//チップ番号０は描画しない
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


void CStage::RenderDebug(void) {
	//位置の描画
	CGraphicsUtilities::RenderString(10, 100, "スクロール X : %.0f , Y : %.0f", m_ScrollX, m_ScrollY);
}

/**
 * 解放
 *
 */
void CStage::Release(void) {
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
	

	////ハテナブロック
	if (m_pQuestionBlockData)
	{
		free(m_pQuestionBlockData);
		m_pQuestionBlockData = NULL;
	}
	if (m_pQuestionBlockTexture)
	{
		delete[] m_pQuestionBlockTexture;
		m_pQuestionBlockTexture = NULL;
	}

	//ゴールポール
	if (m_pGoalData)
	{
		free(m_pGoalData);
		m_pGoalData = NULL;
	}
	if (m_pGoalTexture)
	{
		delete[] m_pGoalTexture;
		m_pGoalTexture = NULL;
	}

	//ゴールフラグ
	if (m_pGoalFlgData)
	{
		free(m_pGoalFlgData);
		m_pGoalFlgData = NULL;
	}
	if (m_pGoalFlgTexture)
	{
		delete[] m_pGoalFlgTexture;
		m_pGoalFlgTexture = NULL;
	}

	//レンガブロック
	if (m_pbreakBlockData)
	{
		free(m_pbreakBlockData);
		m_pbreakBlockData = NULL;
	}
	if (m_pbreakBlockTexture)
	{
		delete[] m_pbreakBlockTexture;
		m_pbreakBlockTexture = NULL;
	}

	//四角ブロック
	if (m_pBlockData)
	{
		free(m_pBlockData);
		m_pBlockData = NULL;
	}
	if (m_pBlockTexture)
	{
		delete[] m_pBlockTexture;
		m_pBlockTexture = NULL;
	}
	
	////土管
	//if (m_pDokanData)
	//{
	//	free(m_pDokanData);
	//	m_pDokanData = NULL;
	//}
	//if (m_pDokanTexture)
	//{
	//	delete[] m_pDokanTexture;
	//	m_pDokanTexture = NULL;
	//}
}