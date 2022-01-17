#pragma once
#include "GameApp.h"
#include "AI.h"

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
#define		INIT_POSITION_Y			150.0f
//フィールド座標
#define		INIT_FIELD_POSITION_X	3
#define		INIT_FIELD_POSITION_Y	1
//スピン初期値
#define		INIT_SPIN_X				0
#define		INIT_SPIN_Y				-50.0f

//ぷよが長押しによってすばやく移動するようになるまでにかかる時間
#define		INIT_HOLD_TIME			10
//操作不能待ち時間
#define		WAIT_TIME				20
//クイックターン入力受付時間
#define		QUICKTURN_RECEIPTION_TIME	20

enum Type
{
	Empty,
	Wall,
	Red,
	Blue,
	Yellow,
	Green,
	Obstacle,

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
	Drop,
	Tear,
	Chain,
	ReStart,
};

struct FieldPos
{
	int x;
	int y;
};
class CPlayer
{
private:
	//Computer
	CComputer	m_AI;

	//ぷよ格納用配列
	int			m_field[FH][FW];
	//操作している、次に降ってくるぷよの色
	int			m_type[2][2];

	//タイマー

	//自動落下まで待つ変数
	int			m_dropTimeCnt;
	int			m_rotateTimeCnt;
	//また後で名前変える　　間を生み出すためタイム変数
	int			m_waitTimeCnt;

	//ぷよを長押しによって移動させる際に動くを抑制するためのタイム
	int			m_downHoldTimeCnt;
	int			m_leftHoldTimeCnt;
	int			m_rightHoldTimeCnt;

	//スコア
	int			m_maxChainCnt;
	int			m_score;

	//回転回数
	int			m_rotateCnt;

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

	//おじゃまぷよ
	int			m_sendObstacleCnt;
	int			m_sendObstacleCntTemp;
	bool		m_receiveFlg;

	bool		m_deadFlg;

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
	CRandom		m_obstaSetPosRandom;

	//ぷよ素材
	CTexture    m_RedPuyoTexture;
	CTexture    m_BluePuyoTexture;
	CTexture    m_YellowPuyoTexture;
	CTexture    m_GreenPuyoTexture;
	CTexture	m_ObstaclePuyoTexture;
	//ゲームオーバーのバツ部分
	CTexture	m_CrossMarkTexture;

	//音素材
	CSoundBuffer	m_chainSound;
	CSoundBuffer	m_moveSound;
	CSoundBuffer	m_setSound;
	CSoundBuffer	m_rotateSound;


public:
	CPlayer();
	~CPlayer();
	void Load(void);
	void Initialize(bool vsAiFlg);
	void ChainCheck(int y, int x);
	void Update(bool vsAiFlg, int receiveObstacleCnt);
	void DropUpdate(bool vsAiFlg);
	void TearUpdate();
	void ChainUpdate(int receiveObstacleCnt);
	void ReStartUpdate(bool vsAiFlg);
	void Movement(bool vsAiFlg);
	void Rotate(bool vsAiFlg);
	void Render(bool vsAiFlg, bool readyFlg, int receiveObstacleCnt);
	void Release(void);
	void FieldRender(int initPosX);
	void NextPuyoRender(int x, int y);
	void MovingPuyoRender(bool readyFlg);
	bool IsWall(int way)
	{
		//todo:enum作ってわかりやすくする leftwall,rightwall,てきな
		//左壁
		if (way == 0)
		{
			if (((m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty &&
				m_field[m_sFldPos.y - 1][m_sFldPos.x - 1] == Empty && m_eRotation == Top) ||
				(m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty &&
					m_field[m_sFldPos.y + 1][m_sFldPos.x - 1] == Empty && m_eRotation == Bottom) ||
				(m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty && m_eRotation == Right) ||
				(m_field[m_sFldPos.y][m_sFldPos.x - 2] == Empty && m_eRotation == Left)))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		//右壁
		if (way == 1)
		{
			if (((m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty &&
				m_field[m_sFldPos.y - 1][m_sFldPos.x + 1] == Empty && m_eRotation == Top) ||
				(m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty &&
					m_field[m_sFldPos.y + 1][m_sFldPos.x + 1] == Empty && m_eRotation == Bottom) ||
				(m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty && m_eRotation == Left) ||
				(m_field[m_sFldPos.y][m_sFldPos.x + 2] == Empty && m_eRotation == Right)))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		//下壁
		if (way == 2)
		{
			if ((m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty && m_eRotation == Top) ||
				(m_field[m_sFldPos.y + 2][m_sFldPos.x] != Empty && m_eRotation == Bottom) ||
				((m_field[m_sFldPos.y + 1][m_sFldPos.x - 1] != Empty ||
					m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty) && m_eRotation == Left) ||
				((m_field[m_sFldPos.y + 1][m_sFldPos.x + 1] != Empty ||
					m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty) && m_eRotation == Right))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		return false;
	}
	int GetScore()
	{
		return m_score;
	}
	int GetMaxChain()
	{
		return m_maxChainCnt;
	}
	bool GetDead() {
		return m_deadFlg;
	}
	int GetSendObstacleCnt()
	{
		return m_sendObstacleCnt;
	}
	void SetSendObstacleCnt(int num)
	{
		m_sendObstacleCnt = num;
	}
	bool GetReceive()
	{
		return m_receiveFlg;
	}
};

