#pragma once

#include    "Player.h"
#include    "Enemy.h"

//敵の最大数
#define ENEMY_COUNT 40

class CGame
{
private:

	//プレイヤー
	CPlayer     g_Player;
	
	CEnemy   g_EnemyArray[ENEMY_COUNT];

	CTexture zButtonBlack;
	CTexture zButtonWhite;
	CTexture zChangeCircleBlack;
	CTexture zChangeCircleWhite;

	int cnt;
	
	bool g_bclear;

public:
	CGame();
	~CGame();
	void Load();
	void Initialize();
	void Update();
	void Render();
	void Release();

};

