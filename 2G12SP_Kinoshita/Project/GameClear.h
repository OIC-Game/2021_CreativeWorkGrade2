#pragma once

#include "Mof.h"
#include "Title.h"
#include "GameDefine.h"
class CGameClear
{
	private:
		CTexture m_GameClear;
public:
	CGameClear();
	~CGameClear();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

};

