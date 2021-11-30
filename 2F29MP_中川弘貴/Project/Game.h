#pragma once
#include "Fade.h"

//ぷよのサイズ
#define		PUYO_SIZE	50
//フィールドのマス数
#define		FH 13
#define		FW 8
//ブロックサイズ
#define		BL 50
//自由落下の速度
#define		DROP_SPEED				80
//ぷよが操作によって移動する速度
#define		PUYO_SPEED				5
//初期位置
#define		INIT_POSITION_X			200.0f
#define		INIT_POSITION_Y			100.0f
//フィールド座標
#define		INIT_FIELD_POSITION_X	3
#define		INIT_FIELD_POSITION_Y	0
//スピン初期値
#define		INIT_SPIN_X				0
#define		INIT_SPIN_Y				-50.0f
//レディカウントが表示される時間
#define		READY_TIME				200
//ぷよが長押しによってすばやく移動するようになるまでにかかる時間
#define		INIT_HOLD_TIME			10
//操作不能待ち時間
#define		WAIT_TIME				20

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

//操作中のサブぷよの位置
enum Rotation
{
	Top,
	Right,
	Bottom,
	Left,
};

//全体の流れ
enum Flow
{
	Ready,
	Pause,
	Drop,
	Tear,
	Chain,
	ReStart,
	GameOver,
};

struct FieldPos
{
	int x;
	int y;
};

class CGame {
private:

	//ぷよ格納用配列
	int			m_field[FH][FW];
	//操作している、次に降ってくるぷよの色
	int			m_type[2][2];


	//タイマー

	//自動落下まで待つ変数
	int			m_dropTimeCnt;
	int			m_leftRotateTimeCnt;
	//また後で名前変える　　間を生み出すためタイム変数
	int			m_waitTimeCnt;
	//readyカウント
	int			m_readyTimeCnt;
	//ぷよを長押しによって移動させる際に動くを抑制するためのタイム
	int			m_downHoldTimeCnt;
	int			m_leftHoldTimeCnt;
	int			m_rightHoldTimeCnt;

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
	
	//操作するぷよ座標
	Vector2		m_pos;
	//回転による座標の変化
	Vector2		m_spin;
	//フィールド配列に格納するための座標
	FieldPos	m_sFldPos;
	//ぷよの向き
	Rotation	m_eRotation;
	//流れを制御
	Flow		m_eFlow;
	//乱数
	CRandom		m_random;

	//ぷよ素材
	CTexture    m_RedPuyoTexture;
	CTexture    m_BluePuyoTexture;
	CTexture    m_YellowPuyoTexture;
	CTexture    m_GreenPuyoTexture;
	//背景
	CTexture	m_BackTexture;
	//ゲームオーバーのバツ部分
	CTexture	m_CrossMarkTexture;
	//ゲームオーバー時の背景
	CTexture	m_GameOverTexture;
	//ポーズ画面
	CTexture    m_PauseTexture;

	//音素材
	CSoundBuffer	m_chainSound;
	CSoundBuffer	m_moveSound;
	CSoundBuffer	m_setSound;
	CSoundBuffer	m_rotateSound;
	CSoundBuffer	m_gameBGM;
	CSoundBuffer	m_pauseSound;
	CSoundBuffer	m_gameOverSound;

	//フェード用
	CFade			fade;

public:
	CGame();
	~CGame();
	bool Load(void);
	void Initialize(void);
	void ChainCheck(int y, int x);
	void Update(void);
	void ReadyUpdate();
	void PauseUpdate();
	void DropUpdate();
	void TearUpdate();
	void ChainUpdate();
	void ReStartUpdate();
	void GameOverUpdate();
	void Render(void);
	void Release(void);
};