#include	"GameDefine.h"
#include	"Title.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;

/**
 * �R���X�g���N�^
 *
 */
CTitle::CTitle() :
m_BackImage() {
}

/**
 * �f�X�g���N�^
 *
 */
CTitle::~CTitle(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CTitle::Load(void){
	if (!m_BackImage.Load("title.png")) 
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
void CTitle::Initialize(void){
}

/**
 * �X�V
 *
 */
void CTitle::Update(void){
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_INFORMATION;
	}
}

/**
 * �`��
 *
 */
void CTitle::Render(void){
	m_BackImage.Render(0, 0);
}

/**
 * �f�o�b�O�`��
 *
 */
void CTitle::RenderDebug(void){
}

/**
 * ���
 *
 */
void CTitle::Release(void){
	m_BackImage.Release();
}