#include	"Stage.h"

CStage::CStage() :
m_Texture() ,
m_Scroll(0.0f) ,
m_pEnemyStart(NULL) ,
m_EnemyTexture() ,
m_EnemyCount(0),
m_EnemyShotTexture() ,
m_EnemyNo(0) {
}


CStage::~CStage(){
}


bool CStage::Load(void) {
	//テクスチャの読み込み
	if (!m_Texture.Load("Stage1.png"))
	{
		return false;
	}
	

	
	if(!m_EnemyTexture.Load("Enemy1.png"))
	{
		return false;
	}
	if(!m_EnemyShotTexture.Load("E_missile.png"))
	{
		return false;
	}
	return true;
}

/**
 * 初期化
 */
void CStage::Initialize(ENEMYSTART* pSt, int cnt){
	m_Scroll = 0;
	m_EnemyNo = 0;
	m_pEnemyStart = pSt;
	m_EnemyCount = cnt;
	
}

/**
 * 更新

 */
void CStage::Update(CEnemy* ene,int ecnt){
	m_Scroll += SCROLL_SPEED;
	//スクロール位置が敵の出現位置より大きくなったら敵を出現させる
	if(m_EnemyNo < m_pEnemyStart->Count && m_Scroll >= m_pEnemyStart->Scroll[m_EnemyNo])
	{
		for(int i = 0;i < ecnt;i++)
		{
			if(ene[i].GetShow())
			{
				continue;
			}
			ene[i].SetTexture(&m_EnemyTexture,&m_EnemyShotTexture);
			ene[i].Start(m_pEnemyStart->PosX[m_EnemyNo],0,m_pEnemyStart->Type[m_EnemyNo]);
			break;
		}
		m_EnemyNo++;
	}
}

/**
 * 描画
 *
 */
void CStage::Render(void){
	//テクスチャの描画
	//同じテクスチャを繰り返しで画面端を超えるまで描画を行う
	int h = m_Texture.GetHeight();
	int sch = g_pGraphics->GetTargetHeight();
	for(float y = ((int)m_Scroll % h) - h;y < sch;y += h) 
	{
		m_Texture.Render(0.0f , y);
	}
}

/**
 * デバッグ描画
 *
 */
void CStage::RenderDebug(void){
	//スクロール値の描画
	CGraphicsUtilities::RenderString(10,10,MOF_XRGB(0,0,0),"スクロール : %.0f , 敵の出現番号 : %d",m_Scroll,m_EnemyNo);
}

/**
 * 解放
 *
 */
void CStage::Release(void){
	m_Texture.Release();
	m_EnemyTexture.Release();
	m_EnemyShotTexture.Release();
}