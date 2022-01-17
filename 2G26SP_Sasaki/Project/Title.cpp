#include    "GameApp.h"
#include	"Title.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;


/**
 * コンストラクタ
 *
 */
CTitle::CTitle() :
	m_BackImage() {
}

/**
 * デストラクタ
 *
 */
CTitle::~CTitle() {
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CTitle::Load(void) {
	//テクスチャの読み込み
	if (!m_BackImage.Load(""))
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
void CTitle::Initialize(void) {
}

/**
 * 更新
 *
 */
void CTitle::Update(void) {
	//Enterキーでゲーム画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_GAME;
	}
}

/**
 * 描画
 *
 */
void CTitle::Render(void) {
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_COLOR_WHITE);
	m_BackImage.Render(0, 200);
	CGraphicsUtilities::RenderString(400, 250, MOF_COLOR_BLACK, "強くなったクリボー");
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_BLACK, "Press Enter Key");
}

/**
 * デバッグ描画
 *
 */
void CTitle::RenderDebug(void) {
}

/**
 * 解放
 *
 */
void CTitle::Release(void) {
	m_BackImage.Release();
}
