#include "Block.h"

CBlock::CBlock():
	m_pTexture(NULL),
	m_Pos(),
	m_SrcRect()
{
}


CBlock::~CBlock() {
	
}


void CBlock::Initialize(float px, float py, int type) {
	m_Pos.x = px;
	m_Pos.y = py;
	m_bShow = true;
	
	

}


void CBlock::Update(void) {
	
	if (!m_bShow)
	{
		return;
	}
	
}



 
void CBlock::CollisionStage(float ox, float oy) {
	
}


void CBlock::Render(float wx, float wy) {
	
	//非表示
	if (!m_bShow)
	{
		return;
	}
	
	//描画矩形
	CRectangle dr = CRectangle(96, 0, 128, 32);
	CRectangle(96, 0, 128, 32) = m_SrcRect;
	
	
	
	//テクスチャの描画
	m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy,dr);
	//m_pTexture->Render(0, 0);
}

void CBlock::RenderDebug(float wx, float wy)
{
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
}


//void CBlock::RenderDebug(float wx, float wy) {
//	//非表示
//	if (!m_bShow)
//	{
//		return;
//	}
//	//当たり判定の表示
//	CRectangle hr = GetRect();
//	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
//}


void CBlock::Release(void) {

}










	
