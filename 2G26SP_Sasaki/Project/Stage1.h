#pragma once
#include "Stage.h"
//ステージ１の情報を定義する

//敵の開始情報の構造体
ENEMYSTART g_Stg1EnemyStart[] = {
	{100.0f,	100.0f,1,0},
	{409.0f,	150.0f,1,0},
	{203.0f,	200.0f,1,0},
	{306.0f,	250.0f,1,0},
	{100.0f,	300.0f,1,0},

	{924.0f,	600.0f,0,0},
	{612.0f,	650.0f,0,0},
	{821.0f,	700.0f,0,0},
	{718.0f,	750.0f,0,0},
	{924.0f,	800.0f,0,0},

	{100.0f,	1000.0f,0,0},
	{924.0f,	1000.0f,1,0},
	{260.5f,	1050.0f,0,0},
	{764.0f,	1050.0f,1,0},
	{420.0f,	1100.0f,0,0},
	{604.0f,	1100.0f,1,0},
	{580.0f,	1150.0f,0,0},
	{444.0f,	1150.0f,1,0},
	{740.0f,	1200.0f,0,0},
	{284.0f,	1200.0f,1,0},
};

//敵の開始情報の数
int g_Stg1EnemyCount = _countof( g_Stg1EnemyStart );
