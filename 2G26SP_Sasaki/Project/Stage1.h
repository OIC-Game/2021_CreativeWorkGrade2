#pragma once
#include "Stage.h"
//ステージ１の情報を定義する

//敵の開始情報の構造体
ENEMYSTART g_Stg1EnemyStart[] = {
	{100.0f,	100.0f,1},
	{100.0f,	150.0f,1},
	{100.0f,	200.0f,1},
	{100.0f,	250.0f,1},
	{100.0f,	300.0f,1},
					  
	{924.0f,	600.0f,0},
	{924.0f,	650.0f,0},
	{924.0f,	700.0f,0},
	{924.0f,	750.0f,0},
	{924.0f,	800.0f,0},

	{100.0f,	1000.0f,0},
	{924.0f,	1000.0f,0},
	{100.0f,	1050.0f,0},
	{924.0f,	1050.0f,0},
	{100.0f,	1100.0f,0},
	{924.0f,	1100.0f,0},
	{100.0f,	1150.0f,0},
	{924.0f,	1150.0f,0},
	{100.0f,	1200.0f,0},
	{924.0f,	1200.0f,0},
};

//敵の開始情報の数
int g_Stg1EnemyCount = _countof( g_Stg1EnemyStart );
