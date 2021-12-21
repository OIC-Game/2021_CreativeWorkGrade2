#pragma once

#include "GameDefine.h"

class CItem
{
private:



	float m_PosX;
	float m_PosY;
	float m_MoveX;
	float m_MoveY;
	bool  m_bShow;
	CSpriteMotionController	m_Motion;
	CRectangle				m_SrcRect;


	//�A�C�e�����
	enum tagITEMTYPE {
		ITEM_RECOVER,		//�񕜃A�C�e��

		ITEM_TYPECOUNT,
	};

public:
	CItem();
	~CItem();

	void Initialize();

	bool GetShow(void) { return m_bShow;}
	CRectangle GetRect(void){ return m_SrcRect;}

};

