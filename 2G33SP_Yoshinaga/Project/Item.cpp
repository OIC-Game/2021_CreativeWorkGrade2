#include "Item.h"

void CItem::Initialize()
{
	//m_Type=type;
	//m_PosX=px;
	//m_PosY=py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bshow = true;

	//�A�j���[�V����
	SpriteAnimationCreate anim = {
		"�A�C�e��",
		0,0,
		32,32,
		TRUE,{{,,}{,,}{,,}}

	}


}
