#include    "GameApp.h"
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
CTitle::~CTitle() {
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CTitle::Load(void) {
	//�e�N�X�`���̓ǂݍ���
	if (!m_BackImage.Load(""))
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
void CTitle::Update(void) {
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
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_COLOR_WHITE);
	m_BackImage.Render(0, 200);
	CGraphicsUtilities::RenderString(400, 250, MOF_COLOR_BLACK, "�����Ȃ����N���{�[");
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_BLACK, "Press Enter Key");
}

/**
 * �f�o�b�O�`��
 *
 */
void CTitle::RenderDebug(void) {
}

/**
 * ���
 *
 */
void CTitle::Release(void) {
	m_BackImage.Release();
}
