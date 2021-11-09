#include	"GameApp.h"
#include	"Title.h"
//#include	"GlobalDefine.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;


/**
 * コンストラクタ
 *
 */
CTitle::CTitle() :
	title_Texture()
{
}

/**
 * デストラクタ
 *
 */
CTitle::~CTitle() {
}

bool CTitle::Load(void)
{
	if (!title_Texture.Load("Tit0le.png"))
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
void CTitle::Update(void)
{
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
	title_Texture.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, "PRESS ENTER TO START");

}

void CTitle::RenderDebug(void)
{
	CGraphicsUtilities::RenderString(10, 10, "タイトル画面");
}

void CTitle::Release(void)
{
	title_Texture.Release();
}
