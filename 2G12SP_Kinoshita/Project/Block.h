#pragma once

#include "Mof.h"

#include "GameDefine.h"

#define		Block_RECTDECREASE		10
//#define		LEFTSLOPE							2
class CBlock
{
private:
	CTexture* m_pTexture;
	Mof::CVector2 m_Pos;
	bool					m_bShow;
	CRectangle				m_SrcRect;

	float   m_PosX;
	float   m_PosY;

	float					m_ChipSize;
	int						m_XCount;
	int						m_YCount;
	//char* m_pChipData;
public:
	CBlock();
	~CBlock();
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
	
	CRectangle GetRect() {
		//return CRectangle(m_Pos.x + Block_RECTDECREASE, m_Pos.y + Block_RECTDECREASE, m_Pos.x + m_SrcRect.GetWidth() - Block_RECTDECREASE, m_Pos.y + m_SrcRect.GetHeight());
		return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRect.GetWidth() + 30, m_Pos.y + m_SrcRect.GetHeight() + 30);
	}

	//bool Collisionplayer(CPlayer& player);
	bool Collision(CRectangle r, float& ox, float& oy);

};

