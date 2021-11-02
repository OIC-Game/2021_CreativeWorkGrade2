#include	"GameApp.h"
#include	"Title.h"

//�ύX����V�[��(�O���Q��)
extern int		gChangeScene;

/*
  �R���X�g���N�^
*/
CTitle::CTitle():
m_BackTexture(),
m_fade(0),
m_bStart(false),
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
	if (!m_BackTexture.Load("TitleBack.png"))
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

	m_fade = 0;
	m_bStart = false;
}

/*
  �X�V
*/
void CTitle::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bStart = true;
	}

	//�Q�[���̊J�n�t���O��True�ɂȂ莟��A��ʂ�^���Âɂ���
	if (m_bStart)
	{
		m_fade += 3;
		//��ʂ��^�����ɂȂ�����(m_fade��255�ɂȂ�Ɛ^����)
		if (m_fade >= 255)
		{
			m_titleBGM.Stop();
			gChangeScene = SCENENO_GAME;

		}
	}
	
	
}

/*
  �`��
*/
void CTitle::Render(void)
{
	m_BackTexture.Render(0, 0);
	CGraphicsUtilities::RenderString(340, 400, MOF_COLOR_BLACK, "�Q�[�����J�n����[Enter]");
	//�t�F�[�h�p�̍����l�p
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_ARGB(m_fade, 0, 0, 0));
}

/*
  ���
*/
void CTitle::Release(void)
{
	m_BackTexture.Release();

	//���̉��
	m_titleBGM.Release();
}

