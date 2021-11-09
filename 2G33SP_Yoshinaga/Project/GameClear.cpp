#include"GameDefine.h"
#include "GameClear.h"


//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;


CGameClear::CGameClear() :
	ClearTexture() {
}


CGameClear::~CGameClear() {
}

bool CGameClear::Load(void) {
	//�e�N�X�`���̓ǂݍ���
	if (!ClearTexture.Load("GameClear.png"))
	{
		return false;
	}
	return true;
}

void CGameClear::Initialize(void) {
}


void CGameClear::Update(void) {
	//Enter�L�[�Ń^�C�g����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_TITLE;
	}
}


void CGameClear::Render(void) {
		ClearTexture.RenderScale(0, 0,1.3f);
		CGraphicsUtilities::RenderString(400, 600, MOF_COLOR_WHITE, "EnterKey�Ń^�C�g��");

}


void CGameClear::RenderDebug(void) {
}


void CGameClear::Release(void) {
	ClearTexture.Release();
}