#include "GameDefine.h"
#include "Title.h"

//変更するシーン
extern int						gChangeScene;


CTitle::CTitle():
	BackImage(){
}

CTitle::~CTitle(){
}

bool CTitle::Load(void){
	//テクスチャの読み込み
	if (!BackImage.Load("Title.png"))
	{
		return false;
	}
	return true;
}

void CTitle::Initialize(void){
}

void CTitle::Update(void){
	//Enterでゲーム画面に
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_GAME;
	}
}

void CTitle::Render(void){
	BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_BLACK, "Prese Enter Key");
}

void CTitle::RenderDebug(void){
}

void CTitle::Release(void){
	BackImage.Release();
}
