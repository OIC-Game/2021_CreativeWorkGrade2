#include "breakBlock.h"

CbreakBlock::CbreakBlock():
	m_pTexture(NULL),
	m_Pos()
	//m_Move(),
	//m_SrcRect()
	//m_bShow(false)
{
}

CbreakBlock::~CbreakBlock()
{
}

void CbreakBlock::Initialize(float px, float py, int type)
{
	m_Pos.x = px;
	m_Pos.y = py;
	m_bShow = true;
	m_PosWait = 0;
	m_Type = type;
}

void CbreakBlock::Update(void)
{
	if (!m_bShow)
	{
		return;
	}
	if (m_PosWait > 0)
	{
		m_PosWait--;
	}
}

void CbreakBlock::CollisionStage(float ox, float oy)
{
}

void CbreakBlock::Render(float wx, float wy)
{
	//ρ\¦
	if (!m_bShow)
	{
		return;
	}

	//`ζι`
	
	CRectangle dr = CRectangle(0, 224,32 ,256 );
	CRectangle(0,224,32,256) = m_SrcRect;

	//½]tOͺONΜκ`ζι`π½]³Ήι

	/*{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}*/
	//eNX`Μ`ζ
	m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
}

void CbreakBlock::RenderDebug(float wx, float wy)
{
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
}

void CbreakBlock::Release(void)
{
}

bool CbreakBlock::Collision(CRectangle r, float& ox, float& oy)
{
	return false;
}

void CbreakBlock::GetPos(void)
{
	m_PosY = m_Pos.y;
	m_PosWait = 2;
	if (m_PosWait > 0 && m_PosY<m_Pos.y )
	{
		m_PosWait--;
		m_Pos.y -= 3;
		if (m_Pos.y < m_PosY)
		{
			m_Pos.y = m_PosY;
		}
	}
 
	
	
}

void CbreakBlock::GetShow(void)
{
	m_bShow = false;
}
