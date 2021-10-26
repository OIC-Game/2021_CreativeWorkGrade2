#include "GameDefine.h"
#include "GameOver.h"

//変更するシーン
extern int						gChangeScene;

CGameOver::CGameOver(){
}

CGameOver::~CGameOver(){
}

bool CGameOver::Load(void){
	if (!BackImage.Load("GameOver.png"))
	{
		return false;
	}
	return true;
}

void CGameOver::Initialize(void){
}

void CGameOver::Update(void){
	//Enterでタイトル画面に
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_TITLE;
	}
}

void CGameOver::Render(void){
	BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Prese Enter Key");
}

void CGameOver::RenderDebug(void){
	CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_WHITE, "GameOver");
}

void CGameOver::Release(void){
	BackImage.Release();
}
