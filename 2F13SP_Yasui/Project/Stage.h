#pragma once
#include	"Mof.h"
#include	"GlobalDefine.h"
#include	"Player.h"
#include	"Enemy.h"
#include	"Item.h"

class CStage
{
private:
	CTexture		stage_ChipTexture;
	CTexture		stage_BackTexture;

	float			stage_ChipSize;
	int				stage_XCount;
	int				stage_YCount;
	char*			stage_pChipData;
	float*			stage_gap;
	float*			stage_gapMove;
	float			stage_ChipMove;
	bool			stage_CollisionBlockFlg;
	bool			stage_SrcPlayerDeadFlg;

	CVector2		stage_Scroll;

	int				stage_EnemyTextureCount;
	CTexture*		stage_pEnemyTexture;
	char*			stage_pEnemyData;
	int				stage_EnemyCount;

	int				stage_ItemTextureCount;
	CTexture*		stage_pItemTexture;
	char*			stage_pItemData;
	int				stage_ItemCount;

	bool			stage_chipUp;
	bool			stage_break;
	int				stage_tmpChipX;
	int				stage_tmpChipY;
	bool			stage_BlockDestroy;
	int				stage_BlockDestroyWait;
	bool			stage_BlockChange;
	bool			stage_FixScroll;
	int				stage_State;

	CSoundBuffer	stage_BlockAttackSE;
	CSoundBuffer	stage_BlockDestroySE;

	CSoundBuffer	stage_MarioFireSE;
	CSoundBuffer    stage_MarioSE[MARIOSOUND_COUNT];
	CSoundBuffer	stage_ExplosionSE;



	int				stage_NowStage;

	CTexture		stage_EnemyShotTexture;
	CTexture		stage_EnemyFireTexture;
	CTexture		stage_EnemyKuriboTexture;
	CTexture		stage_EnemyMushTexture;
	CTexture		stage_FishesTexture;
	CVector2		stage_FishesMove;
	CVector2		stage_FishesPos;



public:
	CStage();
	~CStage();
	bool Load(char* pName);
	void Initialize(CEnemy* pEnemy, CItem* pItem,int stageState);
	void Update(CPlayer& pl);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	bool Collision(CRectangle r, float& ox, float& oy, bool& og , bool& dead,bool& jump,CPlayer& pl, bool& magma);
	float GetScrollX() { return stage_Scroll.x; };
	float GetScrollY() { return stage_Scroll.y; };
	int GetEnemyCount() { return stage_EnemyCount; }
	int GetItemCount() { return stage_ItemCount; }

	void ExplotionCastle();
	
};

