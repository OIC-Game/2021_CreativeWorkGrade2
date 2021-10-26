#pragma once
#include "Mof.h"
#include "SceneBase.h"

class CGameOver : public CSceneBase
{
private:
	CSoundBuffer	gameover_GameOverSE;
	CFont			gameover_Font;
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