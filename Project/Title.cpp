#include "GameDefine.h"
#include "Title.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;


CTitle::CTitle() :
	TitleTexture() {
	
}


CTitle::~CTitle() {
}

bool CTitle::Load(void) {

	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	//�e�N�X�`���̓ǂݍ���
	if (!TitleTexture.Load("GameTitle.png"))
	{
		return false;
	}
	return true;
}

void CTitle::Initialize(void) {
	Load();
}

void CTitle::Update(void) {
	

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		switch (m_Select) {
		case 0:
			gChangeScene = SCENENO_GAME;
			break;
		case 1:
			gChangeScene = SCENENO_GAMEOVER;
			break;
		case 2:
			gChangeScene = SCENENO_GAMECLEAR;
			break;

		}

	}

	//�E�F�C�g�O�̂Ƃ���������
	if (m_KeyWait <= 0)
	{
		//�㉺�L�[Hold�őI��
		if (g_pInput->IsKeyHold(MOFKEY_UP))
		{
			m_KeyWait = 15;		//�E�F�C�g��ݒ肱�̃t���[���Ԃ͍ē��͕s��
			m_Select--;
			if (m_Select < 0)
			{
				m_Select = SELECTITEMCOUNT + m_Select;
			}
		}
		else if (g_pInput->IsKeyHold(MOFKEY_DOWN))
		{
			m_KeyWait = 15;		//�E�F�C�g��ݒ肱�̃t���[���Ԃ͍ē��͕s��
			m_Select++;
			if (m_Select >= SELECTITEMCOUNT)
			{
				m_Select = m_Select - SELECTITEMCOUNT;
			}
		}
	}
	else
	{
		m_KeyWait--;
	}
}

void CTitle::Render(void) {
	TitleTexture.RenderScale(0, 0,1.3f);

	//�I������
	const char* selectItem[] = {

		"�Q�[���J�n",
		"�������",
		"�I�v�V����"
	};
	//for���ŌJ��Ԃ��ŕ\��
	for (int i = 0; i < SELECTITEMCOUNT; i++)
	{
		CGraphicsUtilities::RenderString(560, 340 + i * 40, i == m_Select ?
			MOF_COLOR_RED : MOF_COLOR_HWHITE, selectItem[i]);
	}
}


void CTitle::RenderDebug(void) {
}


void CTitle::Release(void) {
	TitleTexture.Release();
}