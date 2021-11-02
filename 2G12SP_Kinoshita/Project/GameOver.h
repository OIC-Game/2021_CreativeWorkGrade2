#pragma once

#include "Mof.h"
#include "Title.h"
#include "GameDefine.h"
class CGameOver
{
private:
	CTexture   m_BackTexture;
	//int        m_NextScene;
public:
	CGameOver();
	~CGameOver();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	
};

