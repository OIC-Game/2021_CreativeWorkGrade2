#include    "GameApp.h"
#include	"GameClear.h"
#include    "Mof.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;

/**
 * �R���X�g���N�^
 *
 */
CGameClear::CGameClear() :
	m_BackImage() {
}

/**
 * �f�X�g���N�^
 *
 */
CGameClear::~CGameClear() {
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGameClear::Load(void) {
	//�e�N�X�`���̓ǂݍ���
	if (!m_BackImage.Load("Clear.png"))
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
void CGameClear::Initialize(void) {
}

/**
 * �X�V
 *
 */
void CGameClear::Update(void) {
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
void CGameClear::Render(void) {
	m_BackImage.Render(0, 0);
}

/**
 * �f�o�b�O�`��
 *
 */
void CGameClear::RenderDebug(void) {
}

/**
 * ���
 *
 */
void CGameClear::Release(void) {
	m_BackImage.Release();
}