#include "Item.h"



CItem::CItem() :
	m_pTexture(NULL),
	m_Pos(),
	m_bShow(false),
	m_bReverse(false)
{
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_Move.x= 3.0f;
	m_Move.y = 0.0f;
	m_bShow = false;
	m_bReverse = false;

}

void CItem::Fire(float px, float py)
{
	m_Pos.x = px ;
	m_Pos.y = py;
	m_bShow = true;
	
}

void CItem::Update()
{
	
	
	if (!m_bShow)
	{
		return;
	}
	
	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	m_Move.y += GRAVITY;
	if (m_Move.y >= 20.0f)
	{
		m_Move.y = 20.0f;
	}
	
	//m_Pos.x = Item_Speed;

	if (m_Pos.y - m_pTexture->GetHeight() < 0)
	{
		m_bShow = false;
	}
	 //m_Pos.y -= Item_Speed;
	
	
}

void CItem::CollisionStage(float ox, float oy)
{
	if (!m_bShow)
	{
		return;
	}
	m_Pos.x += ox;
	m_Pos.y += oy;

	if (oy < 0 && m_Move.y>0)
	{
		m_Move.y = 0;

	}
	else if (oy > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}

	if (ox < 0 && m_Move.x>0)
	{
		m_Move.x *= -1;
		m_bReverse = true;
	}
	else if (ox > 0 && m_Move.x < 0)
	{
		m_Move.x *= -1;
		m_bReverse = false;
	}
}

void CItem::Render(float wx, float wy)
{
	
	CRectangle dr = m_SrcRect;
	if (!m_bShow)
	{
		return;
	}
	
	m_SrcRect = CRectangle(0, 0, 32, 32);
	float px = m_Pos.x-wx ;
	float py = m_Pos.y-wy;

	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	m_pTexture->Render(px, py);
}

void CItem::RenderDebug(float wx, float wy)
{
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
}

void CItem::Release(void)
{
}

void CItem::showItem()
{
	if (m_bShow == true)
	{
		m_bShow = false;
	}
}

bool CItem::CollisionQBlock(CQuestionBlock& QBlock, float ox, float oy)
{
	return false;
}

bool CItem::CollisionbreakBlock(CbreakBlock& blo, float ox, float oy)
{
	return false;
}
