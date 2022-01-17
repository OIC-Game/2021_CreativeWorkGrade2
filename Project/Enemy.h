#pragma once
#include	"Mof.h"
#include	"GameDefine.h"


//ìñÇΩÇËîªíËå∏êäïù
#define		ENEMY_RECTDECREASE		4
enum tag_ENEMYTYPE {
	ENEMY_K,
	ENEMY_N,

	ENEMY_TYPECOUNT,
};
class CEnemy {
private:
	
	CTexture* m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	float					m_PosX;
	float					m_PosY;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bShow;
	bool					m_bReverse;
	CRectangle				m_SrcRect;
	int						m_HP;
	int						m_DamageWait;
	bool					m_bMove;
	bool					m_bkMove;
	bool					m_way;
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};
public:
	CEnemy();
	~CEnemy();
	void Initialize(float px, float py, int type);
	void Update(float wx,float wy);
	void Damage(int dmg,bool way);
	void CollisionStage(float ox, float oy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	CRectangle GetRect() {
		return CRectangle(m_PosX + ENEMY_RECTDECREASE, m_PosY + ENEMY_RECTDECREASE, m_PosX + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE, m_PosY + m_SrcRect.GetHeight());
	}
	int GetDamageWait(void) { return m_DamageWait; }
};
