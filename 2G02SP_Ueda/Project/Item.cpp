#include "Item.h"
/**
 * コンストラクタ
 *
 */
CItem::CItem() :
	m_pTexture(NULL),
	m_Motion(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_MoveX(3.0f),
	m_MoveY(0.0f),
	m_bShow(false),
	m_SrcRect(),
	m_bSpawn(false),
	m_bMove(false) {
}

CItem::~CItem() {
}

void CItem::Initialize(float px, float py, int type) {
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 2.5f;
	m_MoveY = 0.0f;
	m_bShow = true;
	if (m_Type == ITEM_GIANT)
	{
		m_bSpawn = false;
	}
	else if (m_Type == ITEM_COIN)
	{
		m_bSpawn = true;
	}
	if (m_Type == ITEM_GIANT)
	{
		m_bMove = false;
	}
	else if (m_Type == ITEM_COIN)
	{
		m_bMove = true;
	}
	SpriteAnimationCreate anim[] = {
	{
		"出現",
		0,0,
		32,32,
		FALSE,{{3,0,0},{3,1,0},{3,2,0},{3,3,0},{3,4,0},{3,5,0},{3,6,0},{3,7,0},{3,8,0},{3,9,0},{3,10,0},{6,11,0}}
	},
	{
		"消滅",
		0, 0,
		32, 32,
		FALSE, { {3,12,0} }
	},
	{
		"コイン",
		0, 0,
		32, 32,
		TRUE, { {32,0,0},{8,1,0},{8,2,0},{8,3,0} }
	}
	};
	m_Motion.Create(anim,MOTION_COUNT);
	if (m_Type == ITEM_GIANT)
	{
		m_Motion.ChangeMotion(MOTION_DESPAWN);
	}
	else if (m_Type == ITEM_COIN)
	{
		m_Motion.ChangeMotion(MOTION_COIN);
	}
}

void CItem::Update(void) {
	
	if (!m_bShow)
	{
		return;
	}
	if (m_Type == ITEM_GIANT)
	{
		if (m_bSpawn)
		{
			if ((m_Motion.GetMotionNo() != MOTION_SPAWN))
			{
				m_Motion.ChangeMotion(MOTION_SPAWN);
			}

			if (m_Motion.GetMotionNo() == MOTION_SPAWN && m_Motion.IsEndMotion())
			{
				if (!m_bMove)
				{
					m_bMove = true;
				}
			}
		}
		if (m_bMove)
		{
			m_MoveY += GRAVITY;
			if (m_MoveY >= 20.0f)
			{
				m_MoveY = 20.0f;
			}
			m_PosX += m_MoveX;
			m_PosY += m_MoveY;
		}
	}
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

void CItem::CollisionStage(float ox, float oy) {
	if (m_Type == ITEM_COIN)
	{
		return;
	}
	m_PosX += ox;
	m_PosY += oy;
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX *= -1;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX *= -1;
	}
}

void CItem::Render(float wx, float wy) {
	if (!m_bShow)
	{
		return;
	}
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, m_SrcRect);
}

void CItem::RenderDebug(float wx, float wy) {
	if (!m_bShow)
	{
		return;
	}
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
}

void CItem::Release(void) {
	m_Motion.Release();
}
