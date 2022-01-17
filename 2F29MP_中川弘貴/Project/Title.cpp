#include	"Title.h"

//�ύX����V�[��(�O���Q��)
extern int		gChangeScene;

/*
  �R���X�g���N�^
*/
CTitle::CTitle():
m_backTexture(),
m_startFlg(false),
m_titleBGM()
{
}

/*
  �f�X�g���N�^
*/
CTitle::~CTitle() {
}

/*  
  �ǂݍ���
*/
bool CTitle::Load(void)
{
	//�e�N�X�`���̓ǂݍ���
	if (!m_backTexture.Load("�w�i.png"))
	{
		return false;
	}
	if (!m_TitleLogoTexture.Load("���S����.png"))
	{
		return false;
	}
	if (!m_MenuBarTexture.Load("MenuBar.png"))
	{
		return false;
	}
	if (!m_ButtonVsMode1.Load("ButtonVSMode1.png"))
	{
		return false;
	}
	if (!m_ButtonFreeMode1.Load("ButtonFreeMode1.png"))
	{
		return false;
	}
	if (!m_ButtonHowToPlay1.Load("ButtonHowToPlay1.png"))
	{
		return false;
	}
	if (!m_ButtonVsMode2.Load("ButtonVSMode2.png"))
	{
		return false;
	}
	if (!m_ButtonFreeMode2.Load("ButtonFreeMode2.png"))
	{
		return false;
	}
	if (!m_ButtonHowToPlay2.Load("ButtonHowToPlay2.png"))
	{
		return false;
	}
	if (!m_RuleTexture.Load("Rule.png"))
	{
		return false;
	}
	if (!m_CloseTexture1.Load("Close1.png"))
	{
		return false;
	}
	if (!m_CloseTexture2.Load("Close2.png"))
	{
		return false;
	}
	//���̓ǂݍ���
	if (!m_titleBGM.Load("TitleBGM.mp3"))
	{
		return false;
	}
	if (!m_clickSound.Load("ButtonClickSound.mp3"))
	{
		return false;
	}
	if (!m_cursorSound.Load("CursorOnButtonSound.mp3"))
	{
		return false;
	}
	//���[�v�ݒ�
	m_titleBGM.SetLoop(TRUE);


	return true;
}

/*
  ������
*/
void CTitle::Initialize(void)
{
	//BGM�̍Đ�
	m_titleBGM.Play();

	//���ʂ̒���
	m_titleBGM.SetVolume(0.06f);
	m_clickSound.SetVolume(0.35f);
	m_cursorSound.SetVolume(0.45f);

	//�J�n�t���O��������
	m_startFlg = false;

	m_vsAiFlg = false;

	m_CursorOnVsModeFlg = false;
	m_CursorOnFreeModeFlg = false;
	m_CursorOnHowToPlayFlg = false;
	m_CursorOnCloseFlg = false;
	m_RulePopUpShowFlg = false;


	m_VsModeRect = CRectangle(700, 230, 950, 330);
	m_FreeModeRect = CRectangle(700, 360, 950, 460);
	m_HowToPlayRect = CRectangle(700, 490, 950, 590);
	m_CloseRect = CRectangle(745, 105, 825, 185);

	//�t�F�[�h�C��
	m_fade.FadeIn();
}

/*
  �X�V
*/
void CTitle::Update(void)
{
	//�t�F�[�h�̏���
	m_fade.Update();
	if (m_fade.GetFadeIn() || m_fade.GetFadeOut())
	{
		return;
	}
	//�Q�[���̊J�n�t���O��True�ł���A�t�F�[�h�A�E�g�����������
	else if (m_startFlg)
	{
		m_titleBGM.Stop();
		gChangeScene = SCENENO_GAME;
	}

	//if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	//{
	//	m_vsAiFlg = false;
	//	m_startFlg = true;
	//	//�t�F�[�h�A�E�g
	//	m_fade.FadeOut();
	//}

	//if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	//{
	//	m_vsAiFlg = true;
	//	m_startFlg = true;
	//	//�t�F�[�h�A�E�g
	//	m_fade.FadeOut();
	//}

	g_pInput->GetMousePos(m_mousePos);

	//����
	if (m_RulePopUpShowFlg)
	{
		if (m_CloseRect.CollisionPoint(m_mousePos))
		{
			if (!m_CursorOnCloseFlg)
			{
				//���炷
				m_cursorSound.Play();
			}
			m_CursorOnCloseFlg = true;

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				//���炷
				m_clickSound.Play();
				//�|�b�v�A�b�v�����
				m_RulePopUpShowFlg = false;
			}
		}
		else
		{
			m_CursorOnCloseFlg = false;
		}
	}
	else
	{
		//VS���[�h
		if (m_VsModeRect.CollisionPoint(m_mousePos))
		{
			if (!m_CursorOnVsModeFlg)
			{
				//���炷
				m_cursorSound.Play();
			}
			m_CursorOnVsModeFlg = true;

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				//���炷
				m_clickSound.Play();
				//�����őJ��
				m_vsAiFlg = true;
				m_startFlg = true;
				//�t�F�[�h�A�E�g
				m_fade.FadeOut();
			}
		}
		else
		{
			m_CursorOnVsModeFlg = false;
		}

		//�t���[���[�h
		if (m_FreeModeRect.CollisionPoint(m_mousePos))
		{
			if (!m_CursorOnFreeModeFlg)
			{
				//���炷
				m_cursorSound.Play();
			}
			m_CursorOnFreeModeFlg = true;

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				//���炷
				m_clickSound.Play();
				//�����őJ��
				m_vsAiFlg = false;
				m_startFlg = true;
				//�t�F�[�h�A�E�g
				m_fade.FadeOut();
			}
		}
		else
		{
			m_CursorOnFreeModeFlg = false;
		}

		//�����т���
		if (m_HowToPlayRect.CollisionPoint(m_mousePos))
		{
			if (!m_CursorOnHowToPlayFlg)
			{
				//���炷
				m_cursorSound.Play();
			}
			m_CursorOnHowToPlayFlg = true;

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				//���炷
				m_clickSound.Play();
				//�|�b�v�A�b�v
				m_RulePopUpShowFlg = true;
			}
		}
		else
		{
			m_CursorOnHowToPlayFlg = false;
		}
	}

	
}

/*
  �`��
*/
void CTitle::Render(void)
{
	//�w�i�̕`��
	m_backTexture.Render(0, 0);

	m_TitleLogoTexture.Render(0,80);

	m_MenuBarTexture.Render(650, 120);
	CGraphicsUtilities::RenderFillRect(650, 200, 1000, 630, MOF_ARGB(120, 0, 0, 0));

	if(!m_CursorOnVsModeFlg)
		m_ButtonVsMode1.Render(700, 230);
	else
		m_ButtonVsMode2.Render(700, 230);

	if (!m_CursorOnFreeModeFlg)
		m_ButtonFreeMode1.Render(700, 360);
	else
		m_ButtonFreeMode2.Render(700, 360);

	if(!m_CursorOnHowToPlayFlg)
		m_ButtonHowToPlay1.Render(700, 490);
	else
		m_ButtonHowToPlay2.Render(700, 490);


	if (m_RulePopUpShowFlg)
	{
		CGraphicsUtilities::RenderFillRect(0, 0, SW, SH, MOF_ARGB(180, 0, 0, 0));
		m_RuleTexture.Render(150,80);

		if(!m_CursorOnCloseFlg)
			m_CloseTexture1.Render(745, 105);
		else
			m_CloseTexture2.Render(745, 105);
	}

	//������
	//CGraphicsUtilities::RenderString(340, 400, MOF_COLOR_BLACK, "�Q�[�����J�n����[Enter]");

	m_fade.Render();

}

/*
  ���
*/
void CTitle::Release(void)
{
	m_backTexture.Release();
	//���̉��
	m_titleBGM.Release();
	m_clickSound.Release();
	m_cursorSound.Release();

	m_TitleLogoTexture.Release();
	m_MenuBarTexture.Release();

	m_ButtonFreeMode1.Release();
	m_ButtonFreeMode2.Release();
	m_ButtonVsMode1.Release();
	m_ButtonVsMode2.Release();
	m_ButtonHowToPlay1.Release();
	m_ButtonHowToPlay2.Release();

	m_RuleTexture.Release();
	m_CloseTexture1.Release();
	m_CloseTexture2.Release();
}

