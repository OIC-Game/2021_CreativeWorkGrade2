#include	"PlayerShot.h"

/**
 * コンストラクタ
 *
 */
CPlayerShot::CPlayerShot() :
m_pTexture(NULL) ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bShow(false) {
}

/**
 * デストラクタ
 *
 */
CPlayerShot::~CPlayerShot(){
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 *
 */
void CPlayerShot::Initialize(void){
	m_PosX = 0;
	m_PosY = 0;
	m_bShow = false;
}
/**
 * 発射
 * 引数の座標に位置を設定して、表示フラグをtrueに変更する。
 *
 * 引数
 * [in]			px				発射Ｘ座標
 * [in]			py				発射Ｙ座標
 */
void CPlayerShot::Fire(float px,float py){
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py;
	m_bShow = true;
}

/**
 * 更新
 *
 */
void CPlayerShot::Update(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//上に移動
	m_PosY -= PLAYERSHOT_SPEED;
	//画面上（Y:0）より上で消去
	if(m_PosY + m_pTexture->GetHeight() < 0)
	{
		m_bShow = false;
	}
}

/**
 * 描画
 *
 */
void CPlayerShot::Render(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX,m_PosY);
}

/**
 * デバッグ描画
 *
 */
void CPlayerShot::RenderDebug(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CGraphicsUtilities::RenderRect(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight(),MOF_XRGB(0,255,0));
}