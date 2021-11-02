#pragma once

#include"Mof.h"
#include "Player.h"
#include "GameDefine.h"
class CGoalFlg
{
private:
	CTexture* m_pTexture;
	Mof::CVector2           m_Pos;
	bool					m_bShow;
	CRectangle				m_SrcRect;

	float   m_PosX;
	float   m_PosY;
	int     m_Type;
	Mof::Vector2            m_Move;

public:
	CGoalFlg();
	~CGoalFlg();
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
	int  GetType(void) { return m_Type; }
	/*CRectangle GetRect() {
		return CRectangle(m_PosX + Block_RECTDECREASE, m_PosY + Block_RECTDECREASE, m_PosX + m_SrcRect.GetWidth() - Block_RECTDECREASE, m_PosY + m_SrcRect.GetHeight());
	}*/
	CRectangle GetRect() { return CRectangle(m_PosX, m_PosY, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight()); }


};

