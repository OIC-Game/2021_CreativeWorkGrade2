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
	
	//��\��
	if (!m_bShow)
	{
		return;
	}
	
	//�`���`
	CRectangle dr = CRectangle(96, 0, 128, 32);
	CRectangle(96, 0, 128, 32) = m_SrcRect;
	
	
	
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy,dr);
	//m_pTexture->Render(0, 0);
}

void CBlock::RenderDebug(float wx, float wy)
{
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
}


//void CBlock::RenderDebug(float wx, float wy) {
//	//��\��
//	if (!m_bShow)
//	{
//		return;
//	}
//	//�����蔻��̕\��
//	CRectangle hr = GetRect();
//	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
//}


void CBlock::Release(void) {

}










	
