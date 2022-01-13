#include "Item.h"


CItem::CItem():
m_pTexture(NULL),
m_Motion(),
m_PosX(0.0f),
m_PosY(0.0f),
m_MoveX(0.0f),
m_MoveY(0.0f),
m_bShow(false),
m_SrcRect(){
}

CItem::~CItem()
{
}


void CItem::Initialize(float px, float py, int type)
{
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bShow = true;
	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim = {
		"�A�C�e��",
		0,0,
		32,32,
		FALSE,{{5,0,0}}
	};
	m_Motion.Create(anim);
}

void CItem::Update()
{
}

void CItem::CollisionStage(float ox, float oy) {
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

void CItem::Render(float wx, float wy)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}

	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, m_SrcRect);
}

void CItem::RenderDebug(float wx, float wy)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));

}

void CItem::Release(void){
	m_Motion.Release();
}
