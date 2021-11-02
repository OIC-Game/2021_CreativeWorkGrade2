#pragma once

#include"Mof.h"

#include "GameDefine.h"


#define Block_RECTDECREASE		10

//enum  tag_breakBlockTYPE
//{
//	breakBlock_renga,   //レンガブロック
//	breakBlock_hatena,  //？ブロック
//
//	breakBlock_TYEPCOUNT,
//};
class CbreakBlock
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
	CbreakBlock();
	~CbreakBlock();
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
	
	CRectangle GetRect() { return CRectangle(m_Pos.x , m_Pos.y , m_Pos.x + m_SrcRect.GetWidth() + 35, m_Pos.y + m_SrcRect.GetHeight() + 35); }
	//bool CollisionPlayer(CPlayer& ply);
	bool Collision(CRectangle r, float& ox, float& oy);
};
