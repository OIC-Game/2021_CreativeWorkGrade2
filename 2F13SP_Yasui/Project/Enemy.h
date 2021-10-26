#pragma once
#include	"Mof.h"
#include	"GlobalDefine.h"
#include	"EnemyShot.h"

//玉の発射限界
#define		ENEMYSHOT_COUNT		10

	//敵種類列挙
	enum tag_ENEMYTYPE{
		ENEMY_MUSH,				//キノコ
		ENEMY_SKELETON,			//スケルトン
		ENEMY_MARIO,			//マリオ
		ENEMY_FISH,				//マグロ

		ENEMY_TYPECOUNT,
	};

class CEnemy
{
private:
	int							enemy_Type;
	CVector2					enemy_Position;
	CVector2					enemy_Move;
	bool						enemy_Reverse;
	bool						enemy_Show;
	CTexture*					enemy_pTexture;
	CSpriteMotionController		enemy_Motion;
	CRectangle					enemy_RectTexture;
	bool						enemy_Dead;
	int							enemy_DisappearTime;
	bool						enemy_DeadJump;
	bool						enemy_BlockJump;
	bool						enemy_srcDeadJump;
	int							enemy_MarioHP;
	int							enemy_MarioNowAttackPettern;
	bool						enemy_MarioDamageFlg;
	int							enemy_MarioDamageWait;
	bool						enemy_MarioChangeFlg;
	bool						enemy_MarioDead;

	float							tmp_playerPositionX;
	float							tmp_playerMoveX;
	float							tmp_DistanceBetweenPlayer;
	bool							tmp_playerJumpFlg;
	bool							tmp_playerWarpFlg;

	//マリオの行動パターンで使用
	bool							one;
	int								loop;
	bool							jumpFlg;
	bool							changeFireMode;
	bool							fire;
	int								fireWait;
	int								dashCount;
	int								otherAttack;
	int								debug_MarioAttackPettern;
	bool							debugModeFlg;


	
	//マリオ行動パターン
	enum tag_MARIO_MOVEMENTPETTERN
	{
		MARIOATTACK_DASH = 1,
		MARIOATTACK_HIPDROP,
		MARIOATTACK_JUMP,
		MARIOATTACK_HOPJUMP,
		MARIOATTACK_TURN,
		MARIOATTACK_CHANGE,
		MARIOATTACK_FIRE,
		MARIOATTACK_DAMAGE,
		MARIOATTACK_DEAD,
	};

	//モーション種類
	//キノコ
	enum tag_MushMOTION
	{
		MUSHMOTION_MOVE,
		MUSHMOTION_DEAD,

		MUSHMOTION_COUNT,
	};
	//スケルトン
	enum tag_SkeletonMOTION
	{
		SKELETONMOTION_WAIT,
		SKELETONMOTION_MOVE,
		SKELETONMOTION_DEAD,
		SKELETONMOTION_REVIVAL,
		SKELETONMOTION_ATTACK,

		SKELETONMOTION_COUNT,
	};
	//マリオ
	enum tag_MarioMOTION
	{
		MARIOMOTION_MOVE,
		MARIOMOTION_WAIT,
		MARIOMOTION_JUMPSTART,
		MARIOMOTION_JUMPEND,
		MARIOMOTION_HIPDROP,
		MARIOMOTION_BRAKE,
		MARIOMOTION_DAMAGE,

		MARIOMOTION_FIRE_MOVE,
		MARIOMOTION_FIRE_WAIT,
		MARIOMOTION_FIRE_JUMPSTART,
		MARIOMOTION_FIRE_JUMPEND,
		MARIOMOTION_FIRE_HIPDROP,
		MARIOMOTION_FIRE_BRAKE,
		MARIOMOTION_FIRE_ATTACK,
		MARIOMOTION_FIRE_DAMAGE,
		MARIOMOTION_FIRE_DEAD,

		MARIOMOTION_COUNT,
	};
	enum tag_FISHMOTION
	{
		FISHMOTION_MOVE,

		FISHMOTION_COUNT,
	};


	CEnemyShot		m_ShotArray[ENEMYSHOT_COUNT];
	int				enemy_ShotWait;
	bool			enemy_AttackFlg;
	float			enemy_DistanceBetweenToPlayer;

public:
	CEnemy();
	~CEnemy();
	bool Load(void);
	void Initialize(float px, float py, int type);
	void Update(void);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void SetTexture(CTexture* pt, CTexture* st) { enemy_pTexture = pt; for (int i = 0; i < ENEMYSHOT_COUNT; i++) { m_ShotArray[i].SetTexture(st); } }
	bool GetShow(void) { return enemy_Show; };
	bool GetEnemyDead(void) { return enemy_Dead; };
	void CollisionStage(float ox, float oy);
	void ShotCollisionStage(float ox, float oy,int n);
	CRectangle GetRect() {
		return CRectangle(enemy_Position.x + 5, enemy_Position.y + 5,
			enemy_Position.x + enemy_RectTexture.GetWidth() - 5, enemy_Position.y + enemy_RectTexture.GetHeight());
	}
	void Dead(bool bDead);
	float Getenemy_PositionY() { return enemy_Position.y; }
	void DeadJump(bool jumpFlg);
	void BlockJump(bool jumpFlg) { enemy_BlockJump = jumpFlg; };
	int GetType() { return enemy_Type; }
	CRectangle GetAttackRangeRect() {
		return CRectangle(enemy_Position.x - 120, enemy_Position.y - 100,
			enemy_Position.x + enemy_RectTexture.GetWidth() + 120, enemy_Position.y + enemy_RectTexture.GetHeight());
	}
	CEnemyShot& GetShot(int n) { return m_ShotArray[n]; }
	bool GetShotShow(int n) { return m_ShotArray[n].GetShow(); }
	CRectangle GetShotRect(int n) {
		return CRectangle(m_ShotArray[n].GetPositionX(), m_ShotArray[n].GetPositionY(),
			m_ShotArray[n].GetPositionX() + 16, m_ShotArray[n].GetPositionY() + 16);
	}


	void SkeletonShot(void);
	void Setenemy_AttackFlg(bool attackFlg) { enemy_AttackFlg = attackFlg; }
	void DistanceBetweenPlayer(float px);
	void MarioAttack(void);
	void GetPlayerInfo(float positionX,float moveX,bool jumpFlg,bool warpFlg);
	void MarioDamage(float damage);
	int GetMarioDamageWait() { return enemy_MarioDamageWait; }
	bool GetMarioJumpFlg() { return jumpFlg; }
	bool GetMarioChangeFlg() { return changeFireMode; }
	bool GetMarioDeadFlg() { return enemy_MarioDead; }

	void MarioActionConditions();

	void MarioActionModeDash();
	void MarioActionModeHipDrop();
	void MarioActionModeTurn();
	void MarioActionModeJump();
	void MarioActionModeHopJump();
	void MarioActionModeFire();
	void MarioActionModeDamage();
	void MarioActionModeDead();
	void MarioActionModeMove();




	


};

