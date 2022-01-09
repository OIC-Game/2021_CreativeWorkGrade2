#include "GameDefine.h"
#include "GameOver.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;


CGameOver::CGameOver() :
	GameOvertexture() {
}


CGameOver::~CGameOver() {
}

bool CGameOver::Load(void) {
	//�e�N�X�`���̓ǂݍ���
	if (!GameOvertexture.Load("GameOver.png"))
	{
		return false;
	}
	return true;
}


void CGameOver::Initialize(void) {
}


void CGameOver::Update(void) {
	//Enter�L�[�Ń^�C�g����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_TITLE;
	}
}

void CGameOver::Render(void) {
	GameOvertexture.RenderScale(0, 0,1.3f);
	CGraphicsUtilities::RenderString(400, 600, MOF_COLOR_WHITE,"EnterKey�Ń^�C�g��");
}


void CGameOver::RenderDebug(void) {
}


void CGameOver::Release(void) {
	GameOvertexture.Release();
}