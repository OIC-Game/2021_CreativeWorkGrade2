#include "Item.h"

CItem::CItem():
	m_pTexture(NULL),
	m_Motion(),
	m_Type(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_MoveX(0.0f),
	m_MoveY(0.0f),
	m_bShow(false){
}

CItem::~CItem(){
	//delete[] �ŉ�������悤��Release���f�X�g���N�^�Ŏ��s����
	Release();
}

void CItem::Initialize(float px, float py, int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	switch (GetType())
	{
		case ITEM_KINOKO:
			 m_MoveX = 2.0f;
			 m_bShow = false;
			 break;
		case ITEM_COIN:
			 m_bShow = true;
			 break;
		case ITEM_1UPKINOKO:
			m_MoveX = 2.0f;
			m_bShow = false;
	}
	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim = {
		"�A�C�e��",
		0,0,
		32,32,
		TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
	};
	m_Motion.Create(anim);
}

void CItem::Update(void){
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�d�͂ɂ�艺�ɏ�����������
	m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
	switch (GetType())
	{
		case ITEM_KINOKO:
			 //���ۂɍ��W���ړ�������
			 m_PosX += m_MoveX;
			 m_PosY += m_MoveY;
			 break;
		case ITEM_1UPKINOKO:
			//���ۂɍ��W���ړ�������
			m_PosX += m_MoveX;
			m_PosY += m_MoveY;
			break;
	}
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

void CItem::Render(float wx, float wy){
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX - wx, m_PosY - wy,m_SrcRect);
}

void CItem::RenderDebug(float wx, float wy){
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	hr.Expansion(-5, -5);
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
}

void CItem::Release(void){
	m_Motion.Release();
}

void CItem::CollisionStage(float ox, float oy){
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
		m_MoveX *= -1;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX *= -1;
	}
}


void CItem::PoPItem(int popItemNo){
	if (popItemNo == 1)
	{
		switch (GetType())
		{
			case ITEM_KINOKO:
				 m_bShow = true;
				 break;
		}
	}
	else if (popItemNo == 2)
	{
		switch (GetType())
		{
			case ITEM_1UPKINOKO:
				m_bShow = true;
				break;
		}
	}
}
