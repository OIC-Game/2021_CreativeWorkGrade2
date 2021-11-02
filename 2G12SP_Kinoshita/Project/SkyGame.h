#pragma once

#include "Mof.h"
#include "Player.h"
#include"SkyStage.h"
class CSkyGame
{
private:
	CPlayer   m_Player;
	CSkyStage m_Sky;
public:
	CSkyGame();
	~CSkyGame();
	bool load(void);
	void Initialize(void);
	void Update();
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

