#pragma once

#include "Mof.h"

#include "GameDefine.h"
//#include"Item.h"
//#include"Player.h"

#define Block_RECTDECREASE		10
class CQuestionBlock
{
private:
	CTexture* m_pTexture;
	Mof::CVector2 m_Pos;
	bool					m_bShow;
	CRectangle				m_SrcRect;
	bool                    m_ItemShow;
	//CItem*                  m_Item;
	

public:
	CQuestionBlock();
	~CQuestionBlock();
	void Initialize(float px, float py, int type);
	void Update(void);
	void CollisionStage(float ox, float oy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void SetTexture(CTexture* pt)
	{
		m_pTexture = pt;
	}

	bool GetShow(void) { return m_bShow; }
	bool GetItemShow(void) { return m_ItemShow; }
	
	/*CRectangle GetRect() {
		return CRectangle(m_Pos.x + Block_RECTDECREASE, m_Pos.y + Block_RECTDECREASE, m_Pos.x + m_SrcRect.GetWidth() + 20, m_Pos.y + m_SrcRect.GetHeight()+20);
	}*/
	CRectangle GetRect() {
		return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRect.GetWidth() + 30, m_Pos.y + m_SrcRect.GetHeight() + 30);
	}
	//bool CollstionPlayer(CPlayer& ply);

	float GetPosx() { return m_Pos.x; }
	float GetPosy() { return m_Pos.y; }
	bool  GetItem() { return m_ItemShow; }
};

