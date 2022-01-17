#pragma once
#include "mof.h"
class CGameOver
{
private:
	CTexture m_GameOverTexture;
	int m_bGameOverCount;
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

