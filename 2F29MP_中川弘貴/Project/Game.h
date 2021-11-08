#pragma once
#include "Fade.h"

//ぷよのサイズ
#define		PUYO_SIZE	50
//フィールドのマス数
#define		FH 13
#define		FW 8
#define		BL 50
//自由落下の速度
#define		DROP_SPEED 80

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


	bool bChain = false;
	bool bCheck[FH][FW];
	bool bDestroy[FH][FW];
	int bondCnt;

	int			field[FH][FW];
	int			wait;            //自動落下まで待つ変数
	int			type[2][2];
	int			m_sleepTime;         //sleepの代わり
	int			m_downHoldTime;
	int			m_leftHoldTime;
	int			m_rightHoldTime;
	int			m_chainCnt;
	int			m_maxChainCnt;
	int			m_score;
	int			m_readyTime;

	CTexture    m_RedPuyoTexture;
	CTexture    m_BluePuyoTexture;
	CTexture    m_YellowPuyoTexture;
	CTexture    m_GreenPuyoTexture;
	CTexture	m_BackTexture;
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