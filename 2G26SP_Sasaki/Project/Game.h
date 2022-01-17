#pragma once

#include    "Player.h"
#include    "Enemy.h"

//�G�̍ő吔
#define ENEMY_COUNT 40

class CGame
{
private:

	//�v���C���[
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

