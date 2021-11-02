#include "Goal.h"

CGoal::CGoal():
	m_pTexture(NULL),
	m_Pos(),
	m_SrcRect()
{
	
}

CGoal::~CGoal()
{
}

void CGoal::Initialize(float px, float py, int type)
{
	m_Pos.x = px;
	m_Pos.y = py;
	m_bShow = true;
}

void CGoal::Update(void)
{
}

void CGoal::CollisionStage(float ox, float oy)
{
}

void CGoal::Render(float wx, float wy)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}

	//�`���`
	CRectangle dr = CRectangle(161, 64, 192, 96);
	CRectangle(161, 64, 192, 96) = m_SrcRect;

	
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
}

void CGoal::RenderDebug(float wx, float wy)
{
}

void CGoal::Release(void)
{
}
