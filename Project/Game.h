#pragma once
#include "SceneBase.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <array>

class CGame : public CSceneBase
{
private:
	float dropDTime[2] = { 0, 0 };							//dropTimeまで数値が増えれば落下処理
	float obstacleDTime[2] = { 0,0 };
	//float obstacleCreateTime = 10.0f;
	CSoundBuffer gSound[2];

	float aiControllTime = 0.0f;
	bool isStop = false;
	bool isMenu = false;
	int selectMenu = 0;
	char* menu[3] = { "　　ポーズ","　　閉じる","タイトルに戻る" };

public:
	CGame();
	~CGame();
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);

	void ObstacleThrow(int p, int c);
};

