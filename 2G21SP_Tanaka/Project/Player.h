#pragma once
#include		"Mof.h"
#include		"GameDefine.h"
#include		"Enemy.h"
#include		"Item.h"
#include		"PlayerFire.h"

//移動速度
#define			PLAYER_SPEED			0.3f

//ダッシュ速度
#define			PLAYER_RUNSPEED			0.5f

//移動最大速度
#define			PLAYER_MAXSPEED			4.0f

//ダッシュ最大速度
#define			PLAYER_MAXRUNSPEED		7.0f

//ジャンプ初速
#define			PLAYER_JUMP				-11.0f

//弾の発射限界数
#define			PLAYERFIRE_COUNT		3

//弾の発射間隔
#define			PLAYERFIRE_WAIT			50

//当たり判定減衰幅
#define			PLAYER_RECTDECREASE		12

class CPlayer{
private:
	CTexture				m_Texture;
	CSpriteMotionController	m_Motion;
	float					m_PosX;
	float					m_PosY;
	bool					m_bMove;
	float					m_MoveX;
	float					m_MoveY;
	int						m_Life;
	int						m_Stat;
	int						m_Comb;
	bool					m_bCombStart;
	int						m_Coin;
	bool					m_bJump;
	bool					m_bShow;
	bool					m_bReverse;
	bool					m_bGoal;
	bool					m_bClear;
	bool					m_bRetry;
	float					m_ShowTime;
	bool					m_bEnd;
	bool					m_bDead;
	int						m_bEndTime;
	int						m_DamageWait;
	CRectangle				m_SrcRect;

	int						m_Time;
	int						m_Score;

	CTexture				m_FireTexture;
	CPlayerFire				m_FireArray[PLAYERFIRE_COUNT];
	int						m_FireWait;

	CSoundBuffer			m_JumpSound;
	CSoundBuffer			m_coinSound;
	CSoundBuffer			m_upSound;
	CSoundBuffer			m_downSound;
	CSoundBuffer			m_enemySound;
	CSoundBuffer			m_blockcoinSound;
	CSoundBuffer			m_clearSound;
	CSoundBuffer			m_endSound;
	CSoundBuffer			m_BGM;

	//モーション種類定義
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMP,
		MOTION_JUMPEND,

		MOTION_COUNT,
};
public:
	CPlayer();
	~CPlayer();
	bool Load(void);
	void Initialize(void);
	void Update(float wx, float wy);
	void UpdateKey(void);
	void UpdateMove(void);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	CRectangle GetRect() {
		return CRectangle(
			m_PosX + PLAYER_RECTDECREASE, m_PosY + PLAYER_RECTDECREASE, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE, m_PosY + m_SrcRect.GetHeight()
		);
	}
	void CollisionStage(float ox, float oy);
	void CollisionStageFire(int i);
	void IsGoal(void);
	bool CollisionEnemy(CEnemy& ene);
	bool CollisionItem(CItem& itm);
	bool GetStat(void) { return m_Stat; }
	bool GetLife(void) { return m_Life; }
	bool IsEnd(void) { return m_bEnd; }
	bool Retry()
	{
		if (m_Life >= 0)
		{
			m_bRetry = true;
		}
		else if (m_Life < 0)
		{
			m_bRetry = false;
		}
		return m_bRetry;
	}
	bool IsDead(void) { return m_bDead; }
	bool IsClear(void){ return m_bClear; }
	void PlusScore(void);
	void CoinGet(void);
	void BlockCoinGet(void);
	void BreakBlock(void);
	void EnemyScore(void);
	void Clear(void);

	CPlayerFire GetFireArray(int i) {
		return m_FireArray[i];
	};
};