#pragma once
#include "Fade.h"

//�Ղ�̃T�C�Y
#define		PUYO_SIZE	50
//�t�B�[���h�̃}�X��
#define		FH 13
#define		FW 8
#define		BL 50
//���R�����̑��x
#define		DROP_SPEED 80

enum Type
{
	Empty,
	Wall,
	Red,
	Blue,
	Yellow,
	Green,

	TypeCount,
};

typedef enum
{
	Top,
	Right,
	Bottom,
	Left,
} E_Rotation;

typedef enum
{
	ready,
	pause,
	drop,
	tear,
	chain,
	reStart,
	gameOver,
} E_Process;

struct S_FieldPos
{
	int x;
	int y;
};

class CGame {
private:

	int			m_field[FH][FW];
	int			m_type[2][2];

	//�^�C�}�[

	//���������܂ő҂ϐ�
	int			m_dropTimeCnt;
	int			m_leftRotateTimeCnt;
	//�܂���Ŗ��O�ς���@�@�Ԃ𐶂ݏo�����߃^�C���ϐ�
	int			m_sleepTime;
	//ready�J�E���g
	int			m_readyTime;
	int			m_downHoldTime;
	int			m_leftHoldTime;
	int			m_rightHoldTime;

	//�X�R�A
	int			m_maxChainCnt;
	int			m_score;

	//�A��

	//�Ղ悪���ł���
	bool		m_chainFlg;
	//��ł��ǂł��Ȃ��Ղ�ł���
	bool		m_puyoCheckFlg[FH][FW];
	//���ł�����Ղ�
	bool		m_destroyFlg[FH][FW];
	//�����F�����q�����Ă��邩
	int			m_bondCnt;
	//�A����
	int			m_chainCnt;

	bool		m_endFlg;



	//�Ղ�f��
	CTexture    m_RedPuyoTexture;
	CTexture    m_BluePuyoTexture;
	CTexture    m_YellowPuyoTexture;
	CTexture    m_GreenPuyoTexture;
	//�w�i
	CTexture	m_BackTexture;
	//�Q�[���I�[�o�[�̃o�c����
	CTexture	m_CrossMarkTexture;
	CTexture	m_GameOverTexture;
	CTexture    m_PauseTexture;
	
	Vector2		pos;
	Vector2		spin;
	S_FieldPos	sFPos;
	E_Rotation	eStep;
	E_Process	eFlow;
	CRandom		random;

	CSoundBuffer	m_chainSound;
	CSoundBuffer	m_moveSound;
	CSoundBuffer	m_setSound;
	CSoundBuffer	m_rotateSound;
	CSoundBuffer	m_gameBGM;
	CSoundBuffer	m_pauseSound;
	CSoundBuffer	m_gameOverSound;

	CFade			fade;

public:
	CGame();
	~CGame();
	bool Load(void);
	void Initialize(void);
	void ChainCheck(int y, int x);
	void Update(void);
	void Render(void);
	void Release(void);
};