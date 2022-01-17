#pragma once
#include "mof.h"
#include "GameDefine.h"
enum tag_ITEMTYPE {
	ITEM_GIANT,
	ITEM_COIN,
	ITEM_BOXCOIN,

	ITEM_TYPECOUNT,
};
class CItem
{
private:
	CTexture* m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	float					m_PosX;
	float					m_PosY;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bShow;
	CRectangle				m_SrcRect;
	bool					m_bSpawn;
	bool					m_bMove;
	enum tag_MOTION {
		MOTION_SPAWN,
		MOTION_GIANTDESPAWN,
		MOTION_COIN,
		MOTION_COINDESPAWN,

		MOTION_COUNT,
	};
public:
	CItem();
	~CItem();
	void Initialize(float px, float py, int type);
	void Update(void);
	void CollisionStage(float ox, float oy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	void SetShow(bool bs) { m_bShow = bs; }
	int GetType(void) { return m_Type; }
	CRectangle GetRect() { return CRectangle(m_PosX, m_PosY, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight()); }
	bool GetSpawn() { return m_bSpawn; }
	void SetSpawn(bool bs) { m_bSpawn = bs; }
	bool GetMove(void) { return m_bMove; }
};

