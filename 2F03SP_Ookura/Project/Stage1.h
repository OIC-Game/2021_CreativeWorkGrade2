#pragma once
#include"Game.h"
//�X�e�[�W�P�̏����`����

//�G�̏o���ʒu��`
float			g_Stg1EnemyStartPosX[] = {
	
	100.0f,
	150.0f,
	200.0f,
	250.0f,
	300.0f,
	350.0f,
	400.0f,
	924.0f,
	874.0f,
	824.0f,
	774.0f,
	724.0f,
	674.0f,
	624.0f,
	574.0f,
};
float			g_Stg1EnemyStartScroll[] = {
	
	150.0f,
	200.0f,
	250.0f,
	300.0f,
	350.0f,
	400.0f,
	600.0f,
	650.0f,
	700.0f,
	750.0f,
	800.0f,
	850.0f,
	900.0f,
	950.0f,
	2000.0f,
};
int        g_Stg1EnemyStartType[] = {
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
1,
};

//�G�̊J�n���̍\���̂��쐬����
int g_Stg1EnemyCount = _countof(g_Stg1EnemyStartPosX);
ENEMYSTART g_Stg1EnemyStart = {
	g_Stg1EnemyCount,
	g_Stg1EnemyStartPosX,
	g_Stg1EnemyStartScroll,
	g_Stg1EnemyStartType,
};