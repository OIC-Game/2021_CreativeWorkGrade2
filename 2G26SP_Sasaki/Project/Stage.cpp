/***********************************

Stageクラス関連のソース
ステージクラスの定義を記述
作成日：2016/12/8
作成者：和田

************************************/
#include "Stage.h"
#include "Enemy.h"
//コンストラクタ
CStage::CStage():
m_Texture(),
m_Scroll(0.0f),
m_pEnemyStart(NULL),
m_EnemyCount(0),
m_EnemyTexture(),
m_EnemyShotTexture(),
m_EnemyNo(0)
{
}

//デストラクタ
CStage::~CStage()
{
}

//リソースの読み込み
bool CStage::Load()
{
	//背景テクスチャの読み込み
	if (!m_Texture.Load("Stage1.png"))
	{
		return false;
	}
	if (!m_EnemyTexture.Load("EnemyBlack.png"))
	{
		return false;
	}
	if (!m_EnemyTextureWhite.Load("EnemyWhite.png"))
	{
		return false;
	}
	if (!m_EnemyTextureBlack.Load("EnemyBlack.png"))
	{
		return false;
	}
	if (!m_EnemyShotTexture.Load("E_missileBlack.png"))
	{
		return false;
	}
	if (!m_EnemyShotTextureBlack.Load("E_missileBlack.png"))
	{
		return false;
	}
	if (!m_EnemyShotTextureWhite.Load("E_missileWhite.png"))
	{
		return false;
	}
	if (!m_BossBlack.Load("BossBlack.png"))
	{
		return false;
	}
	if (!m_BossWhite.Load("BossWhite.png"))
	{
		return false;
	}
	return true;
}

//パラメタ等の初期化
void CStage::Initialize(ENEMYSTART* pst,int cnt)
{
	//スクロール値を初期化
	m_Scroll = 0.0f;

	m_EnemyNo = 0;
	m_pEnemyStart = pst;
	m_EnemyCount = cnt;
}

//更新処理
void CStage::Update(CEnemy* ene,int ecnt)
{
	//スクロール処理
	m_Scroll += SCROLL_SPEED;
	//敵の出現条件
	if (m_EnemyNo < m_EnemyCount && m_Scroll >= m_pEnemyStart[m_EnemyNo].Scroll)
	{//出現していない敵を探す
		for (int i = 0; i < ecnt; i++)
		{//敵が表示されている場合は、使用中
			if (ene[i].GetShow()) { continue; }
			//色がどちらか
			//if(EnemyColor)
			if (m_pEnemyStart[m_EnemyNo].Color == 0)
			{
				//敵出現
				ene[i].SetTexture(&m_EnemyTextureWhite,&m_EnemyShotTextureWhite);
				ene[i].Start(m_pEnemyStart[m_EnemyNo].PosX, 0, m_pEnemyStart[m_EnemyNo].Color, m_pEnemyStart[m_EnemyNo].Type, m_pEnemyStart[m_EnemyNo].hp);
			}
			if (m_pEnemyStart[m_EnemyNo].Color == 1)
			{
				//敵出現
				ene[i].SetTexture(&m_EnemyTextureBlack, &m_EnemyShotTextureBlack);
				ene[i].Start(m_pEnemyStart[m_EnemyNo].PosX, 0, m_pEnemyStart[m_EnemyNo].Color, m_pEnemyStart[m_EnemyNo].Type, m_pEnemyStart[m_EnemyNo].hp);
			}
			break;
		}
		//敵出現数を加算
		m_EnemyNo++;
	}
}

//描画処理
void CStage::Render()
{
	//描画
	int h = m_Texture.GetHeight();
	int sch = g_pGraphics->GetTargetHeight();
	for (float y = ((int)m_Scroll % h) - h; y < sch; y += h)
	{
		m_Texture.Render(0.0f,y);
	}
	
}


//リソース等の解放処理
void CStage::Release()
{
	//背景テクスチャを解放
	m_Texture.Release();
	m_EnemyTexture.Release();
	m_EnemyTextureBlack.Release();
	m_EnemyTextureWhite.Release();
	m_EnemyShotTexture.Release();
	m_EnemyShotTextureBlack.Release();
	m_EnemyShotTextureWhite.Release();
	m_BossBlack.Release();
	m_BossWhite.Release();
}

//void CStage::RenderDebug(void)
//{
//	CGraphicsUtilities::RenderString(10, 10, MOF_XRGB(0, 0, 0), "スクロール:%.0f", m_Scroll);
//}

void CStage::RenderDebug(void)
{
	CGraphicsUtilities::RenderString(10, 10, MOF_XRGB(0, 0, 0), "スクロール:%.0f,敵の出現番号:%d", m_Scroll, m_EnemyNo);
}