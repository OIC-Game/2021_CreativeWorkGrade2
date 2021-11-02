#include "QuestionBlock.h"


CQuestionBlock::CQuestionBlock():
	m_pTexture(NULL),
	m_Pos()
{
	
}

CQuestionBlock::~CQuestionBlock()
{
}

void CQuestionBlock::Initialize(float px, float py, int type)
{
	m_Pos.x = px;
	m_Pos.y = py;
	m_bShow = true;
	m_ItemShow = false;
}

void CQuestionBlock::Update(void)
{
	if (m_ItemShow == false)
	{
		m_ItemShow = true;
		
	}
	else if(m_ItemShow == true)
	{
		m_ItemShow = false;
	}
	
}

void CQuestionBlock::CollisionStage(float ox, float oy)
{
}

void CQuestionBlock::Render(float wx, float wy)
{
	//非表示
	if (!m_bShow)
	{
		return;
	}

	//描画矩形

	CRectangle dr = CRectangle(96, 32, 128, 64);
	//CRectangle dr = m_SrcRect;
	CRectangle(96, 32, 128, 64) = m_SrcRect;
	
	//テクスチャの描画
	m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
}

void CQuestionBlock::RenderDebug(float wx, float wy)
{
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
}

void CQuestionBlock::Release(void)
{
}

//bool CQuestionBlock::CollstionPlayer(CPlayer& ply)
//{
//	CRectangle bl = GetRect();
//	CRectangle pl = ply.GetRect();
//	if (bl.CollisionRect(pl))
//	{
//		m_bShow = false;
//		/*m_MoveX = -1;
//		m_MoveY = 1;*/
//		//ply.getm_MoveY = -0.1;
//		//m_MoveY -= GRAVITY;
//		//if (m_MoveY <= 20.0f)
//		//{
//		//	m_MoveY = 20.0f;
//		//	m_MoveX = 0;
//		//	//m_MoveY = 0;
//		//}
//	}
//	return false;
//}
