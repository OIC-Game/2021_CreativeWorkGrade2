#pragma once

#include	"Mof.h"
#include	"GameDefine.h"

//ƒAƒCƒeƒ€Ží—Þ—ñ‹“
enum tag_POPITEMTYPE {
	POP_COIN,
	POP_KINOKO,

	POP_TYPECOUNT,
};

class CPoPItem{
private:
	CTexture*					m_pTexture;
	CSpriteMotionController		m_Motion;
	int							m_Type;
	float						m_PosX;
	float						m_PosY;
	float						m_MoveX;
	float						m_MoveY;
	bool						m_bShow;
	float						m_bShowTime;
	CRectangle					m_SrcRect;

public:
	CPoPItem();
	~CPoPItem();
	void Initialize(int type);
	void Start(float px, float py);
	void Update(void);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void CollisionStage(float ox, float oy);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	int GetType(void) { return m_Type; }
	CRectangle GetRect() {
		return CRectangle(m_PosX, m_PosY, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight());
	}
};

