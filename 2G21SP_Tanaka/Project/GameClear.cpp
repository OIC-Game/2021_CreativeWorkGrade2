#include "GameDefine.h"
#include "GameClear.h"

//�ύX����V�[��
extern int						gChangeScene;

CGameClear::CGameClear(){
}

CGameClear::~CGameClear(){
}

bool CGameClear::Load(void){
	if (!BackImage.Load("GameClear.png"))
	{
		return false;;
	}
	return true;
}

void CGameClear::Initialize(void){
}

void CGameClear::Update(void){
	//Enter�Ń^�C�g����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_TITLE;
	}
}

void CGameClear::Render(void){
	BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Prese Enter Key");
}

void CGameClear::RenderDebug(void){
	CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_WHITE, "GameClear");
}

void CGameClear::Release(void){
	BackImage.Release();
}
