#pragma once
#include "mof.h"
#include "GameDefine.h"
#include "Enemy.h"
#include "Item.h"
//移動速度
#define	PLAYER_SPEED 0.2f
//停止速度
#define PLAYER_STOPSPEED 0.2f
//ダッシュ速度
#define PLAYER_DASHSPEED 0.2f
//移動最大速度
#define PLAYER_MAXSPEED 4.0f
//ダッシュ最大速度
#define PLAYER_DASHMAXSPEED 5.0f
//ジャンプ初速
#define PLAYER_JUMP -10.0f
//当たり判定減衰幅
#define PLAYER_RECTDECREASE 4
//ゴール降下速度
#define PLAYER_DOWNSPEED 4.0f
//ゴール後速度
#define PLAYER_GOALEDSPEED 4.0f
//パイプ用当たり判定減衰幅
#define PLAYER_PRECTDECREASE 15
class CPlayer
{
private:
	CSpriteMotionController	m_Motion;
	CRectangle m_SrcRect;
	CTexture m_Texture;
	float m_PosX;
	float m_PosY;
	bool m_bMove;
	bool m_bJump;
	bool m_bReverse;
	float m_MoveX;
	float m_MoveY;
	int m_HP;
	int m_DamageWait;
	bool m_bDead;
	bool m_bGoal;
	bool m_bGoalDown;
	int m_bGoalCount;
	bool m_bCastle;
	int m_bCastleCount;
	int m_bPlayerSize;
	bool m_bGiant;
	bool m_bMotionGiant;
	int m_bPlayerF;
	int m_bPlayerS;
	int m_bPlayerT;
	bool m_bPipeDown;
	bool m_bPipeMove;
	bool m_bUnder;
	bool m_bPipeUp;
	int m_bCoinCount;
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_WALK,
		MOTION_MOVE,
		MOTION_DASH,
		MOTION_JUMPSTART,
		MOTION_JUMPEND,
		MOTION_TURN,
		MOTION_DEAD,
		MOTION_GOAL,
		MOTION_GOALEND,
		MOTION_GIANT,
		MOTION_SQUAT,
		
		MOTION_COUNT,
	};
public:
	CPlayer();
	~CPlayer();
	bool Load(void);
	void Initialize(void);
	void Update(float wx,float wy);
	void UpdateKey(void);
	void UpdateMove(void);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	CRectangle GetRect() {
		return CRectangle(m_PosX + PLAYER_RECTDECREASE, m_PosY, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE, m_PosY + m_SrcRect.GetHeight());
	}
	CRectangle PGetRect() {
		return CRectangle(m_PosX + PLAYER_PRECTDECREASE, m_PosY, m_PosX + m_SrcRect.GetWidth() - PLAYER_PRECTDECREASE, m_PosY + m_SrcRect.GetHeight());
	}
	void CollisionStage(float ox, float oy);
	void MotionRefresh(void);
	bool CollisionEnemy(CEnemy& ene);
	bool GetDead(void) { return m_bDead; };
	bool GetGoal(void) { return m_bGoal; };
	bool GoalEnd(float ox, float glb, float csw);
	bool DeadEnd(void);
	bool CollisionItem(CItem& itm);
	bool GetGiant(void) { return m_bMotionGiant; };
	void CollisionPipe(CRectangle tp,CRectangle bp, CRectangle lp, CRectangle rp, CRectangle up);
	bool GetdPipe(void) { return m_bPipeDown; };
	bool GetmPipe(void) { return m_bPipeMove; };
	bool GetuPipe(void) { return m_bPipeUp; };
	bool GetUnder(void) { return m_bUnder; };
	float GetCoinCount(void) { return m_bCoinCount; };
};

