#pragma once

#include    "Player.h"
#include    "Enemy.h"

//“G‚ÌÅ‘å”
#define ENEMY_COUNT 40

class CGame
{
private:

	//ƒvƒŒƒCƒ„[
	CPlayer     g_Player;
	
	CEnemy   g_EnemyArray[ENEMY_COUNT];
	
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

