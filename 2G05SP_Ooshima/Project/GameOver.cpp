#include	"GameDefine.h"
#include	"GameOver.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;

/**
 * コンストラクタ
 *
 */
CGameOver::CGameOver() :
m_BackImage() {
}

/**
 * デストラクタ
 *
 */
CGameOver::~CGameOver(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGameOver::Load(void){
	//テクスチャの読み込み
	if (!m_BackImage.Load("GameOver.png"))
	{
		return false;
	}

	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGameOver::Initialize(void){
}

/**
 * 更新
 *
 */
void CGameOver::Update(void){
	//Enterキーでタイトル画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_TITLE;
	}
}

/**
 * 描画
 *
 */
void CGameOver::Render(void){
	m_BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Press Enter Key");
}

/**
 * デバッグ描画
 *
 */
void CGameOver::RenderDebug(void){
}

/**
 * 解放
 *
 */
void CGameOver::Release(void){
	m_BackImage.Release();
}