#include	"GameApp.h"
#include	"Title.h"
//#include	"GlobalDefine.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;


/**
 * �R���X�g���N�^
 *
 */
CTitle::CTitle() :
	title_Texture()
{
}

/**
 * �f�X�g���N�^
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
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CTitle::Initialize(void) {


	

}

/**
 * �X�V
 *
 */
void CTitle::Update(void)
{
	//Enter�L�[�ŃQ�[����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_GAME;
	}

}



/**
 * �`��
 *
 */
void CTitle::Render(void) {
	title_Texture.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, "PRESS ENTER TO START");

}

void CTitle::RenderDebug(void)
{
	CGraphicsUtilities::RenderString(10, 10, "�^�C�g�����");
}

void CTitle::Release(void)
{
	title_Texture.Release();
}
