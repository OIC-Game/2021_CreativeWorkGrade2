#pragma once

#include	"Enemy.h"
#include	"Item.h"
#include	"EnemyShot.h"

#include	<array>
#include	"SceneBase.h"
#include	"GlobalDefine.h"
class CGame : public CSceneBase{
private:
	CSoundBuffer	game_BGM;
	CSoundBuffer	game_LAST_BGM;
	CSoundBuffer	game_BOSS_BGM;
	CSoundBuffer	game_GameOverSE;
	CSoundBuffer	game_GameClearSE;
	bool			game_playSoundFlg;
	bool			game_playBGMFlg;
	CEnemy*			m_EnemyArray;
	CItem*			m_ItemArray;
	CEnemyShot*		m_EnemyShotArray;
	float				game_Time;
	float				game_TimeWait;
	bool			game_ScoreFlg;
	bool			game_ScoreDesplayFlg;
	float			game_tempPlayerPositionX;
	float			game_tempPlayerPositionY;
	int				game_NowStage;
	CSoundBuffer	game_MarioJumpSE;
	CSoundBuffer	game_MarioFireSE;
	bool			game_playMarioSEFlg;
	CSoundBuffer	game_MarioDeadSE;
	CSoundBuffer	game_BossClearSE;
	bool			game_ab;
	bool			game_MarioFireSEFlg;

	std::array<const char*, 2 >stagePathArray;


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

