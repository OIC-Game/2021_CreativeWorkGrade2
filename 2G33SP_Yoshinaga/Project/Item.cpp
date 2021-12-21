#include "Item.h"



CItem::CItem():

	m_Motion()
{}

CItem::~CItem()
{
}

void CItem::Initialize()
{
	//m_Type=type;
	//m_PosX=px;
	//m_PosY=py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bShow = true;

	

	//アニメーション
	SpriteAnimationCreate anim = {
		"アイテム",
		0,0,
		32,32,
		TRUE,{{5,0,0}}

	};
	
	m_Motion.Create(anim, ITEM_TYPECOUNT);
}
