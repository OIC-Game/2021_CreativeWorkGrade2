#include    "GameApp.h"
#include	"GameClear.h"
#include    "Mof.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;

/**
 * コンストラクタ
 *
 */
CGameClear::CGameClear() :
	m_BackImage() {
}

/**
 * デストラクタ
 *
 */
CGameClear::~CGameClear() {
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGameClear::Load(void) {
	//テクスチャの読み込み
	if (!m_BackImage.Load("Clear.png"))
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
void CGameClear::Initialize(void) {
}

/**
 * 更新
 *
 */
void CGameClear::Update(void) {
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
void CGameClear::Render(void) {
	m_BackImage.Render(0, 0);
}

/**
 * デバッグ描画
 *
 */
void CGameClear::RenderDebug(void) {
}

/**
 * 解放
 *
 */
void CGameClear::Release(void) {
	m_BackImage.Release();
}