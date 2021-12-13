#pragma once
#include		"Mof.h"
#include		"GameDefine.h"

enum tag_ENEMYTYPE {
	ENEMY_01,
	ENEMY_02,

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
	float						m_MoveKameX;
	bool						m_bShow;
	bool						m_bMove;
	bool						m_bReverse;
	int							m_Kame;
	bool						m_bKame;
	bool						m_bDead;
	int							m_DamageWait;
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
	CRectangle GetRect() {
		return CRectangle(m_PosX + ENEMY_RECTDECREASE, m_PosY, m_PosX + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE, m_PosY + m_SrcRect.GetHeight());
	}

	CRectangle Left() {
		return CRectangle(m_PosX, m_PosY + ENEMY_RECTDECREASE, m_PosX + m_SrcRect.GetWidth() - 20, m_PosY + m_SrcRect.GetHeight());
	}

	CRectangle Right() {
		return CRectangle(m_PosX + 20, m_PosY + ENEMY_RECTDECREASE, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight());
	}
	void Damege(void);
	void EnemyDamege(void);
	void KameLeftMove(void);
	void KameRightMove(void);
	void KameStop(void);
};

