#include	"GameApp.h"
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
	if (!m_backTexture.Load("TitleBack.png"))
	{
		return false;
	}
	//���̓ǂݍ���
	if (!m_titleBGM.Load("TitleBGM.mp3"))
	{
		return false;
	}
	//���[�v�ݒ�
	m_titleBGM.SetLoop(TRUE);
	//BGM�̍Đ�
	m_titleBGM.Play();

	return true;
}

/*
  ������
*/
void CTitle::Initialize(void)
{
	Load();

	//���ʂ̒���
	m_titleBGM.SetVolume(0.06f);
	//�J�n�t���O��������
	m_startFlg = false;
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

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_startFlg = true;
		//�t�F�[�h�A�E�g
		m_fade.FadeOut();
	}

	
}

/*
  �`��
*/
void CTitle::Render(void)
{
	//�w�i�̕`��
	m_backTexture.Render(0, 0);
	//������
	CGraphicsUtilities::RenderString(340, 400, MOF_COLOR_BLACK, "�Q�[�����J�n����[Enter]");

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
}

