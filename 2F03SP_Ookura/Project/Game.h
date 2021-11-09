#pragma once
#include	"GameApp.h"
#include	"Game.h"
#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"

class CGame{
private:
	int a;
public:
CGame();
	~CGame();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

