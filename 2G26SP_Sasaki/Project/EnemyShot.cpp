#include	"EnemyShot.h"

/**
 * コンストラクタ
 *
 */
CEnemyShot::CEnemyShot() :
m_pTexture(NULL) ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_SpeedX(0.0f),
m_SpeedY(0.0f),
m_bShow(false) {
}

/**
 * デストラクタ
 *
 */
CEnemyShot::~CEnemyShot(){
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 *
 */
void CEnemyShot::Initialize(void){
	m_PosX = 0;
	m_PosY = 0;
	m_SpeedX = 0;
	m_SpeedY = 0;
	m_bShow = false;
}
/**
 * 発射
 * 引数の座標に位置を設定して、表示フラグをtrueに変更する。
 *
 * 引数
 * [in]			px				発射Ｘ座標
 * [in]			py				発射Ｙ座標
 * [in]			sx				移動Ｘ速度
 * [in]			sy				移動Ｙ速度
 * [in]			type			弾の種類
 */
void CEnemyShot::Fire(float px,float py,float sx,float sy,int type){
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py;
	m_SpeedX = sx;
	m_SpeedY = sy;
	m_EnemyShotType = type;
	m_bShow = true;
	m_ScaleX = 1;
	m_ScaleY = 1;
	m_CenterPosX = px;
}

/**
 * 更新
 *
 */
void CEnemyShot::Update(){
	//非表示
	if(!m_bShow)
	{
		return;
	}

	if (m_EnemyShotType == 0)
	{
		//速度を利用した移動
		m_PosX += m_SpeedX;
		m_PosY += m_SpeedY;
	}
	if (m_EnemyShotType == 1)
	{
		m_PosX = m_CenterPosX - ((m_pTexture->GetWidth() * m_ScaleX)*0.5f);
		if (m_PosX < 0)
			m_PosX = 0;
		m_PosY += m_SpeedY;
	}

	//画面外で消去
	if(m_PosX + m_pTexture->GetWidth() < 0 || m_PosX > g_pGraphics->GetTargetWidth() ||
		m_PosY + m_pTexture->GetHeight() < 0 || m_PosY > g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
}

/**
 * 描画
 *
 */
void CEnemyShot::Render(float xscal,float yscal,BYTE alp) {
	//非表示
	if (!m_bShow)
	{
		return;
	}

	m_ScaleX = xscal;
	m_ScaleY = yscal;
	//テクスチャの描画
	m_pTexture->RenderScale(m_PosX, m_PosY, xscal,yscal,MOF_ARGB(alp,255,255,255));
}

/**
 * デバッグ描画
 *
 */
void CEnemyShot::RenderDebug(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CGraphicsUtilities::RenderRect(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight(),MOF_XRGB(255,0,0));
}