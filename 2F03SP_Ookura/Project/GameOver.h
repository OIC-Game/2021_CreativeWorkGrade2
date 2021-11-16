#pragma once
#include "Mof.h"

class CGameOver
{
private:
	
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
