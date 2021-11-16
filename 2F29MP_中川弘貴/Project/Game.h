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

	//タイマー

	//自動落下まで待つ変数
	int			m_dropTimeCnt;
	int			m_leftRotateTimeCnt;
	//また後で名前変える　　間を生み出すためタイム変数
	int			m_sleepTime;
	//readyカウント
	int			m_readyTime;
	int			m_downHoldTime;
	int			m_leftHoldTime;
	int			m_rightHoldTime;

	//スコア
	int			m_maxChainCnt;
	int			m_score;

	//連鎖

	//ぷよが消滅した
	bool		m_chainFlg;
	//空でも壁でもなくぷよである
	bool		m_puyoCheckFlg[FH][FW];
	//消滅させるぷよ
	bool		m_destroyFlg[FH][FW];
	//同じ色が何個繋がっているか
	int			m_bondCnt;
	//連鎖数
	int			m_chainCnt;

	bool		m_endFlg;



	//ぷよ素材
	CTexture    m_RedPuyoTexture;
	CTexture    m_BluePuyoTexture;
	CTexture    m_YellowPuyoTexture;
	CTexture    m_GreenPuyoTexture;
	//背景
	CTexture	m_BackTexture;
	//ゲームオーバーのバツ部分
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