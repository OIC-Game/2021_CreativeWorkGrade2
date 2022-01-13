#pragma once

#include	"GameDefine.h"

//アイテム種類列挙
enum tag_ITEMTYPE {
	ITEM_RECOVER,					//回復
	ITEM_GOAL,						//ゴール

	ITEM_TYPECOUNT,
};

class CItem{

private:

	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	float					m_PosX;
	float					m_PosY;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bShow;
	CRectangle				m_SrcRect;


public:

	CItem();
	~CItem();
		

	
	void Initialize(float px, float py, int type);
	void Update();
	void CollisionStage(float ox, float oy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	void SetShow(bool bs) { m_bShow = bs; }
	int GetType(void) { return m_Type; }
	CRectangle GetRect() { return CRectangle(m_PosX, m_PosY, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight()); }


};

