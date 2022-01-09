#include"GameDefine.h"
#include "GameClear.h"


//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;


CGameClear::CGameClear() :
	ClearTexture() {
}


CGameClear::~CGameClear() {
}

bool CGameClear::Load(void) {
	//テクスチャの読み込み
	if (!ClearTexture.Load("GameClear.png"))
	{
		return false;
	}
	return true;
}

void CGameClear::Initialize(void) {
}


void CGameClear::Update(void) {
	//Enterキーでタイトル画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_TITLE;
	}
}


void CGameClear::Render(void) {
		ClearTexture.RenderScale(0, 0,1.3f);
		CGraphicsUtilities::RenderString(400, 600, MOF_COLOR_WHITE, "EnterKeyでタイトル");

}


void CGameClear::RenderDebug(void) {
}


void CGameClear::Release(void) {
	ClearTexture.Release();
}