#pragma once

#include "GameDefine.h"

class CItem
{
private:



	float m_PosX;
	float m_PosY;
	float m_MoveX;
	float m_MoveY;
	bool  m_bshow;


	//�A�C�e�����
	enum tagITEMTYPE {
		ITEM_RECOVER,		//�񕜃A�C�e��

		ITEM_TYPECOUNT,
	};


public:

	void Initialize();
	
};

