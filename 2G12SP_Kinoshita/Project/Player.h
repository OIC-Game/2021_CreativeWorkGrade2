#pragma once

#include "Mof.h"
#include "GameDefine.h"
#include "Enemy.h"
#include "Block.h"
#include "Coin.h"
#include "breakBlock.h"
#include"Goal.h"
#include"QuestionBlock.h"
#include"Item.h"


#define PLAYER_SPEED   0.3f

#define PLAYER_SPEED2   1.0f

#define PLAYER_MAXSPEED   5.0f

#define PLAYER_MAXSPEED2   9.0f

#define PLAYER_JUMP       -10.0f

#define PLAYER_RECTDECREASE  10

#define PLAYER_LEG            -5

#define Item_count           500

#define Item_Wait            20
class CPlayer
{
private:
	float m_PosX;
	float m_PosY;
	float m_MoveX ;
	float m_MoveY;

	float sc = 64;

	bool  m_bMove;
	bool  m_bJump;
	bool  m_bReverse;
	bool  m_bDash;

	CRectangle  m_SrcRect;
	CTexture      player;
	CSpriteMotionController  m_Motion;

	bool m_bDead;
	bool m_bSky;

	int       m_HP;
	int       m_Power;
	int      m_DamageWait;

	bool m_bGoal;

	CItem         m_Item;
	int           m_ItemTextureCount;
	CTexture      m_ItemTexture;
	CItem         m_ItemArray[Item_count];
	
	int           m_ItemCount;
	int           m_Itemwait;
	bool           m_ItemShow;
	//CItem       m_ItemArray[m_ItemCount];
	CQuestionBlock    m_Question;

	enum tag_MOTION
	{
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMPSTART,
		MOTION_JUMPEND,
		MOTION_Dash,
		MOTION_SupeerWAIT,
		MOTION_SupeerMove,
		MOTION_SupeerJUMPSTART,
		MOTION_SupeerJUMPEND,
		MOTION_SupeerDash,

		MOTION_COUNT,

	};
public:
	CPlayer();
	~CPlayer();
	
	bool Lood(void);
	void Initalize();
	
	void Update(void);
	void UpdateMove(void);
	void UpdateKey(void);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	

	CRectangle GetRect(void);
	CRectangle GetLEG(void);
	CRectangle Getbody(void);
	CRectangle Gethed(void);
	

	void CollisionStage(float ox, float oy);
	bool CollisionEnemy(CEnemy& ene);
	
	bool IsDead(void) { return m_bDead; }


	bool CollisionBlock(CBlock& Block,float ox,float oy);
	bool CollisionQBlock(CQuestionBlock& QBlock,float ox,float oy);
	
	
	bool CollisionGoal(CGoal& goal);
	bool IsGoal(void) { return m_bGoal; }
	/*bool CollisionbreakBlock(float ox,float oy);*/
	bool CollisionbreakBlock(CbreakBlock& blo, float ox, float oy);

	bool CollusionItem(CItem& itm);
	int GetItemCount() { return Item_count; }

	bool IsSky(void) { return m_bSky; }

	CItem *GetItem() { return m_ItemArray; }
	bool  GetItemshow() { return m_ItemShow; }
	
	
};

