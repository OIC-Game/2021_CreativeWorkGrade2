#pragma once

#include	"PoPItem.h"

#define		ITEMCOUNT		3

class CPoPItemManager{
private:
	//アイテム
	CPoPItem		m_PoPItem[ITEMCOUNT][POP_TYPECOUNT];
	//アイテム画像
	CTexture		m_Texture[POP_TYPECOUNT];
public:
	CPoPItemManager();
	~CPoPItemManager();
	bool Load(void);
	void Initialize(void);
	CPoPItem* Start(float px, float py, int type);
	void Update(void);
	void Render(float wx, float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
};

