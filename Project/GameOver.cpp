#include "GameDefine.h"
#include "GameOver.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;


CGameOver::CGameOver() :
	GameOvertexture() {
}


CGameOver::~CGameOver() {
}

bool CGameOver::Load(void) {
	//テクスチャの読み込み
	if (!GameOvertexture.Load("GameOver.png"))
	{
		return false;
	}
	return true;
}


void CGameOver::Initialize(void) {
}


void CGameOver::Update(void) {
	//Enterキーでタイトル画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_TITLE;
	}
}

void CGameOver::Render(void) {
	GameOvertexture.RenderScale(0, 0,1.3f);
	CGraphicsUtilities::RenderString(400, 600, MOF_COLOR_WHITE,"EnterKeyでタイトル");
}


void CGameOver::RenderDebug(void) {
}


void CGameOver::Release(void) {
	GameOvertexture.Release();
}