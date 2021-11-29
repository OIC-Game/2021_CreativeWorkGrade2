#pragma once

#include	"Mof.h"
#include	"GlobalDefine.h"
#include	"Enemy.h"
#include	"Item.h"



class CPlayer
{
private:
	CVector2		player_Position;
	float			player_Move;
	float			player_Jump;
	bool			player_JumpFlg;
	bool			player_CheckGround;
	CTexture		player_Texture;
	CRectangle		player_RectTexture;
	bool			player_Reverse;
	CSpriteMotionController  player_Motion;
	bool			player_MoveFlg;
	CSoundBuffer	player_JumpSE;
	CSoundBuffer	player_StepEnemySE;
	CSoundBuffer	player_ChangeBigSE;
	CSoundBuffer	player_ChangeSmallSE;
	CSoundBuffer	player_1upSE;
	CSoundBuffer	player_GoalFlagSE;
	CSoundBuffer	player_GetCoinSE;
	bool			player_DeadFlg;
	bool			player_DeadOnceRunFlg;
	int				player_TimeWait;
	int				player_ChangeWait;
	bool			player_ChangeWaitFlg;
	bool			player_ChangeSizeFlg;
	bool			player_DeadTransitionFlg;
	bool			player_ClearFlg;
	bool			player_ClearTransitionFlg;
	int				player_HP;
	int				player_DamageWait;
	bool			player_ChangeBig;
	bool			player_DamageFlg;
	float			player_TempPositionX;
	float			player_TempPositionY;
	bool			player_GoalMoveFlg;
	bool			player_WarpFlg;
	bool			player_tmpWarpFlg;
	bool			player_playSEFlg;
	bool			player_MarioDead;
	bool			player_Scroll;
	bool			player_BossClearFlg;
	bool			player_BossClearTransitionFlg;
	bool			player_DokanWarpFlg;

	//ÉÇÅ[ÉVÉáÉìéÌóﬁ
	enum tag_MOTION
	{
		MOTION_SMALL_WAIT,
		MOTION_SMALL_DAMAGE,
		MOTION_SMALL_MOVE,
		MOTION_SMALL_JUMP,
		MOTION_BIG_WAIT,
		MOTION_BIG_DAMAGE,
		MOTION_BIG_MOVE,
		MOTION_BIG_JUMP,
		MOTION_COUNT,
	};

	void CreateAnimation();

public:
	CPlayer();
	~CPlayer();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void PlayerMove(void);
	void PlayerJump(void);
	CRectangle GetRectTexture(void);
	CRectangle GetRectPlayer() { 
		return CRectangle(player_Position.x + 5, player_Position.y, player_Position.x + player_RectTexture.GetWidth() -5, player_Position.y + player_RectTexture.GetHeight());
	};
	void CollisionStage(float ox, float oy);
	void FallCheck(bool og);
	bool Getplayer_DeadFlg() { return player_DeadFlg; };
	void Setplayer_DeadFlg(bool deadFlg) { player_DeadFlg = deadFlg; };
	bool Getplayer_DeadTransitionFlg() { return player_DeadTransitionFlg; }
	void Setplayer_DeadTransitionFlg(bool deadFlg) { player_DeadTransitionFlg = deadFlg; }
	bool Getplayer_ClearFlg() { return player_ClearFlg; };
	void Setplayer_ClearFlg(bool clearFlg) { player_ClearFlg = clearFlg; };
	bool Getplayer_ClearTransitionFlg() { return player_ClearTransitionFlg; };
	void Setplayer_ClearTransitionFlg(bool clearTransFlg) { player_ClearTransitionFlg = clearTransFlg; };
	bool CollisionEnemy(CEnemy& ene);
	bool CollisionItem(CItem& item);
	void ChangeSize(void);
	void DeadJudge(void);
	bool Getplayer_JumpFlg() { return player_JumpFlg; };
	bool Getplayer_FallFlg() { return player_CheckGround; };
	float Getplayer_DispPositionX() { return player_TempPositionX; };
	float Getplayer_DispPositionY() { return player_TempPositionY; };
	void AddScoreEnemyStep(void);
	bool Getplayer_BigFlg() { return player_ChangeBig; };
	bool Getplayer_ChangeWaitFlg() { return player_ChangeWaitFlg; };
	void Damage(void);
	void ChangeBig(void);
	float Getplayer_PositionX() { return player_Position.x; };
	float Getplayer_PositionY() { return player_Position.y; };
	bool GetWarpFlg() { return player_WarpFlg; }
	void SetWarpFlg(bool Warp) { player_WarpFlg = Warp; }
	float GetPlayer_MoveX() { return player_Move; }
	bool GetTmpWorpFlg() { return player_tmpWarpFlg; }
	bool GetMarioDead() { return player_MarioDead; }
	void SetMarioDead(bool dead) { player_MarioDead = dead; }
	void SetBossClearTrantionFlg(bool clear) { player_BossClearTransitionFlg = clear; }
	bool GetBossClearTrantionFlg() { return player_BossClearTransitionFlg; }
	bool GetBossClearFlg() { return player_BossClearFlg; }
	bool GetDokanWorpFlg() { return player_DokanWarpFlg; }
	void SetPlayerPos(CVector2 position) { player_Position = position; }
};

