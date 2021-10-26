#include	"GameDefine.h"
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
CTitle::~CTitle(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CTitle::Load(void){
	if (!m_BackImage.Load("title.png")) 
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
void CTitle::Initialize(void){
}

/**
 * 更新
 *
 */
void CTitle::Update(void){
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_INFORMATION;
	}
}

/**
 * 描画
 *
 */
void CTitle::Render(void){
	m_BackImage.Render(0, 0);
}

/**
 * デバッグ描画
 *
 */
void CTitle::RenderDebug(void){
}

/**
 * 解放
 *
 */
void CTitle::Release(void){
	m_BackImage.Release();
}