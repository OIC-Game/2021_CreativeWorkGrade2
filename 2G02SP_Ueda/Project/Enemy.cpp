#include "Enemy.h"

CEnemy::CEnemy():
m_pTexture(NULL),
m_Motion(),
m_PosX(0.0f),
m_PosY(0.0f),
m_MoveX(0.0f),
m_MoveY(0.0f),
m_bShow(false),
m_bReverse(false),
m_SrcRect(),
m_HP(0),
m_DamageWait(0),
m_Type(),
m_bMove(false),
m_bkMove(false)
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Initialize(float px, float py, int type)
{
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = -1.2f;
	m_MoveY = 0.0f;
	m_bReverse = true;
	m_bShow = true;
	if (type == ENEMY_K)
		m_HP = 1;
	if (type == ENEMY_N)
		m_HP = 2;
	m_DamageWait = 0;
	m_bMove = false;
	if (type == ENEMY_K)
	{
		SpriteAnimationCreate anim[] = {
			{
				"移動",
				0,0,
				32,32,
				TRUE,{{8,0,0},{8,1,0}}
			},
			{
				"ダメージ",
				0,32,
				32,32,
				FALSE,{{20,0,0}}
			},
		};
		m_Motion.Create(anim, MOTION_COUNT);
	}
	if (type == ENEMY_N)
	{
		SpriteAnimationCreate anim[] = {
			{
				"移動",
				0,0,
				32,64,
				TRUE,{{8,0,0},{8,1,0}}
			},
			{
				"ダメージ",
				0,64,
				32,32,
				FALSE,{{1,0,0}}
			},
		};
		m_Motion.Create(anim, MOTION_COUNT);
	}
}

void CEnemy::Update(float wx,float wy)
{
	if (!m_bShow)
	{
		return;
	}
	if (m_PosX + m_pTexture->GetWidth() < wx || m_PosY > g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
	
	if (m_PosX - wx - 96 < g_pGraphics->GetTargetWidth())
	{
		m_bMove = true;
	}
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		if (m_Motion.IsEndMotion())
		{
			if (m_HP <= 0)
			{
				m_bShow = false;
			}
		}
		else
		{
			m_MoveX = 0;
		}
	}
	m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
	if (m_bMove)
	{
		m_PosX += m_MoveX;
		m_PosY += m_MoveY;
	}
	if (m_bkMove)
	{
		m_MoveX = 4.0f;
	}
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

void CEnemy::Damage(int dmg)
{
	if (m_Type == ENEMY_N && m_HP == 1)
	{
		if (!m_bkMove)
			m_bkMove = true;
		else
			m_bkMove = false;
	}
	else
	{
		m_HP -= dmg;
		m_DamageWait = 10;
		m_Motion.ChangeMotion(MOTION_DAMAGE);
	}
}

void CEnemy::CollisionStage(float ox, float oy)
{
	m_PosX += ox;
	m_PosY += oy;
	if (oy < 0 && m_MoveY>0)
	{
		m_MoveY = 0;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	if (ox < 0 && m_MoveX>0)
	{
		m_MoveX *= -1;
		m_bReverse = true;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX *= -1;
		m_bReverse = false;
	}
}

void CEnemy::Render(float wx, float wy)
{
	if (!m_bShow)
	{
		return;
	}
	CRectangle dr = m_SrcRect;
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, dr);

}

void CEnemy::RenderDebug(float wx, float wy)
{
	if (!m_bShow)
	{
		return;
	}
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
}

void CEnemy::Release(void)
{
	m_Motion.Release();
}
