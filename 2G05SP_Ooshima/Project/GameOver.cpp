#include	"GameDefine.h"
#include	"GameOver.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;

/**
 * �R���X�g���N�^
 *
 */
CGameOver::CGameOver() :
m_BackImage() {
}

/**
 * �f�X�g���N�^
 *
 */
CGameOver::~CGameOver(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGameOver::Load(void){
	//�e�N�X�`���̓ǂݍ���
	if (!m_BackImage.Load("GameOver.png"))
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
void CGameOver::Initialize(void){
}

/**
 * �X�V
 *
 */
void CGameOver::Update(void){
	//Enter�L�[�Ń^�C�g����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_TITLE;
	}
}

/**
 * �`��
 *
 */
void CGameOver::Render(void){
	m_BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Press Enter Key");
}

/**
 * �f�o�b�O�`��
 *
 */
void CGameOver::RenderDebug(void){
}

/**
 * ���
 *
 */
void CGameOver::Release(void){
	m_BackImage.Release();
}