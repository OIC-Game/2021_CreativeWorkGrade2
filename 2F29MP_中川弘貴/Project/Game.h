#pragma once
#include	"GameApp.h"
#include	"Player.h"

//���f�B�J�E���g���\������鎞��
#define		READY_TIME				180
#define		TO_TITLE_TIME			240

class CGame {
private:
	CPlayer pl;
	CPlayer ai;

	//�w�i
	CTexture	m_BackTexture;
	//Ready
	CTexture	m_ReadyTexture;
	//Fight
	CTexture	m_FightTexture;
	//�|�[�Y���
	CTexture    m_PauseTexture;
	//�Q�[���I�[�o�[���̔w�i
	CTexture	m_GameOverTexture;
	//����
	CTexture	m_WinTexture;
	//����
	CTexture	m_LoseTexture;
	//�ȒP�ȑ������
	CTexture	m_HowMoveTexture;

	//bgm
	CSoundBuffer	m_gameBGM;
	//���ʉ�
	CSoundBuffer	m_pauseSound;
	CSoundBuffer	m_gameOverSound;
	CSoundBuffer	m_victorySound;
	CSoundBuffer	m_readySound;
	CSoundBuffer	m_fightSound;

	//�|�[�Y�t���O
	bool		m_pauseFlg;
	bool		m_readyFlg;
	bool		m_endFlg;
	bool		m_deadFlg;

	//ready�J�E���g
	int			m_readyTimeCnt;
	//�Q�[���I�[�o�[����^�C�g����ʂɍs���܂ł����鎞�Ԃ��J�E���g
	int			m_toTitleTimeCnt;
	//ready�J�E���g��i�߂��Ŕ�����������ʉ��𕡐���炳�Ȃ����߂̕ϐ�
	int			m_readyStep;
	//�󂯎�邨����܂Ղ�
	int			m_plReceiveObstacleCnt;
	int			m_aiReceiveObstacleCnt;

	//�t�F�[�h�p
	CFade			fade;

	CFont			font;
public:
	CGame();
	~CGame();
	void Load();
	void Initialize(bool vsAiFlg);
	void Update(bool vsAiFlg);
	void Render(bool vsAiFlg);
	void Release();
};