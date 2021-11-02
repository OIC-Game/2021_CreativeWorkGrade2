#include "Coin.h"

CCoin::CCoin():
m_pTexture(NULL),
m_Pos()
{

}

CCoin::~CCoin()
{
}

void CCoin::Initialize(float px, float py, int type)
{
	m_Pos.x = px;
	m_Pos.y = py;
	m_bShow = true;
}

void CCoin::Update(void)
{
}

void CCoin::CollisionStage(float ox, float oy)
{
}

void CCoin::Render(float wx, float wy)
{
	if (!m_bShow)
	{
		return;
	}

	//描画矩形
	


	CRectangle dr = CRectangle(192, 0, 256, 96);
	
	//テクスチャの描画
	m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr);



	/*m_pTexture2->Render(m_Pos.x - wx, m_Pos.y - wy, dr2);
	m_pTexture3->Render(m_Pos.x - wx, m_Pos.y - wy, dr3);*/
	/*m_pTexture4->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
	m_pTexture5->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
	m_pTexture6->Render(m_Pos.x - wx, m_Pos.y - wy, dr);*/
}

void CCoin::RenderDebug(float wx, float wy)
{
}

void CCoin::Release(void)
{
}
