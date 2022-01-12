#pragma once

#include	"Enemy.h"
#include	"Item.h"
#include	"EnemyShot.h"

#include	<array>
#include	"SceneBase.h"
#include	"GlobalDefine.h"
#include	"EffectManager.h"

class CGame : public CSceneBase{
private:
	CSoundBuffer	game_BGM;
	CSoundBuffer	game_LAST_BGM;
	CSoundBuffer	game_BOSS_BGM;
	CSoundBuffer	game_GameOverSE;
	CSoundBuffer	game_GameClearSE;
	CSoundBuffer	game_EndSE;
	CFont			game_Font;
	bool			game_playSoundFlg;
	bool			game_playBGMFlg;
	CEnemy*			m_EnemyArray;
	CItem*			m_ItemArray;
	float			game_Time;
	float			game_TimeWait;
	bool			game_ScoreFlg;
	bool			game_ScoreDesplayFlg;
	float			game_tempPlayerPositionX;
	float			game_tempPlayerPositionY;
	CVector2		game_PlayerInitializePosition;
	int				game_NowStage;
	bool			game_playMarioSEFlg;
	CSoundBuffer	game_MarioDeadSE;
	CSoundBuffer	game_BossClearSE;
	bool			game_ab;
	bool			game_MarioFireSEFlg;
	int				game_StageState;
	bool			game_GameEndFlg;
	bool			game_GameEndStrDispFlg;

	CEffectManager	game_EffectManager;


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

