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


	//アイテム種類
	enum tagITEMTYPE {
		ITEM_RECOVER,		//回復アイテム

		ITEM_TYPECOUNT,
	};


public:

	void Initialize();
	
};

