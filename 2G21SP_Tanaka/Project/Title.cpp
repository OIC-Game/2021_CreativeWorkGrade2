#include "GameDefine.h"
#include "Title.h"

//�ύX����V�[��
extern int						gChangeScene;


CTitle::CTitle():
	BackImage(){
}

CTitle::~CTitle(){
}

bool CTitle::Load(void){
	//�e�N�X�`���̓ǂݍ���
	if (!BackImage.Load("Title.png"))
	{
		return false;
	}
	return true;
}

void CTitle::Initialize(void){
}

void CTitle::Update(void){
	//Enter�ŃQ�[����ʂ�
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
