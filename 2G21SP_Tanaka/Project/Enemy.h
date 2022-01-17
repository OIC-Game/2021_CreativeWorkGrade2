#pragma once
#include		"Mof.h"
#include		"GameDefine.h"

enum tag_ENEMYTYPE {
	ENEMY_01,
	ENEMY_02,
	ENEMY_BOSS,
	ENEMY_FIRE,

	ENEMY_TYPECOUNT,
};

//ìñÇΩÇËîªíËå∏êäïù
#define		ENEMY_RECTDECREASE		7

class CEnemy{
private:
	CTexture*					m_pTexture;
	CSpriteMotionController		m_Motion;
	int							m_Type;
	float						m_PosX;
	float						m_PosY;
	float						m_MoveX;
	float						m_MoveY;
	float						m_BossMoveX;
	float						m_JumpTime;
	float						m_MoveKameX;
	bool						m_bShow;
	bool						m_bMove;
	bool						m_bReverse;
	int							m_Kame;
	bool						m_bKame;
	bool						m_bDead;
	int							m_ShowWait;
	int							m_DamageWait;
	int							m_BOSSDamege;
	int							m_BOSSFireDamege;
	CRectangle					m_SrcRect;

	//ÉÇÅ[ÉVÉáÉìéÌóﬁíËã`
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DEATH,

		MOTION_COUNT,
	};

	enum tag_MOTION2 {
		MOTION2_MOVE,
		MOTION2_DEATH,
		MOTION2_KAME,

		MOTION2_COUNT,
	};

	enum tag_MOTIONBOSS {
		MOTIONBOSS_MOVE,

		MOTIONBOSS_COUNT,
	};

	enum tag_MOTIONFIRE {
		MOTIONFORE_MOVE,

		MOTIONFIRE_COUNT,
	};
public:
	CEnemy();
	~CEnemy();
	void Initialize(float px, float py, int type);
	void Update(float wx, float wy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();
	void CollisionStage(float ox, float oy);
	void CollisionEnemy(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	bool GetMove(void) { return m_bMove; }
	int GetType(void) { return m_Type; }
	bool GetDead(void) { return m_bDead; }
	bool GetKame(void) { return m_bKame; }
	CRectangle GetRect() {
		return CRectangle(m_PosX + ENEMY_RECTDECREASE, m_PosY, m_PosX + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE, m_PosY + m_SrcRect.GetHeight());
	}

	CRectangle Left() {
		return CRectangle(m_PosX, m_PosY + ENEMY_RECTDECREASE, m_PosX + m_SrcRect.GetWidth() - 35, m_PosY + m_SrcRect.GetHeight());
	}

	CRectangle Right() {
		return CRectangle(m_PosX + 35, m_PosY + ENEMY_RECTDECREASE, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight());
	}
	void Damege(void);
	void EnemyDamege(void);
	void BOSSDamege(void);
	void BOSSFireDamege(void);
	int  GetDamageWait(void) { return m_DamageWait; }
	void KameLeftMove(void);
	void KameRightMove(void);
	void KameStop(void);

	int GetMoveX() { return m_MoveX; }

	void SetMoveDir(bool isRight);
};

