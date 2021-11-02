#include "GoalFlg.h"

CGoalFlg::CGoalFlg():
	m_pTexture(NULL),
	m_Pos(),
	m_SrcRect()
{

}

CGoalFlg::~CGoalFlg()
{
}

void CGoalFlg::Initialize(float px, float py, int type)
{
	m_Pos.x = px;
	m_Pos.y = py;

}

void CGoalFlg::Update(void)
{
}

void CGoalFlg::CollisionStage(float ox, float oy)
{
}

void CGoalFlg::Render(float wx, float wy)
{
	//非表示
	if (!m_bShow)
	{
		return;
	}

	//描画矩形
	CRectangle dr = CRectangle(129,0 ,190 ,64 );
	
	//テクスチャの描画
	m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
	//m_pTexture->Render(0, 0);
}

void CGoalFlg::RenderDebug(float wx, float wy)
{
}

void CGoalFlg::Release(void)
{
}
