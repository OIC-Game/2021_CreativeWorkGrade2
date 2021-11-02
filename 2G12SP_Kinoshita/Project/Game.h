#pragma once

#include "Player.h"
#include "Mof.h"
#include "Stage.h"
#include "breakBlock.h"
#include "Enemy.h"
#include "Block.h"
#include "Coin.h"
#include "QuestionBlock.h"
#include"Goal.h"
#include "GoalFlg.h"
#include"Item.h"

//#include <vector>
class CGame
{
private:
	CPlayer   m_Player;
	CStage    m_Stage;
	CTexture   coinTexture;
	
	CEnemy*   m_EnemyArray;
	CQuestionBlock  m_QuestionBlock;

	//std::vector<CBlock>    m_BlockArray;

	CBlock                   m_Block;
	CBlock*                  m_BlockArray;
	CbreakBlock*             m_breakBlockArray;
	CCoin*                  m_DokanArray;
	CQuestionBlock*          m_QuestionBlockArray;
	CGoal*                   m_GoalArray;
	CGoalFlg*                m_GoalFlgArray;
	CItem*                   m_ItemArray;

	float                     Time;
	//bool       m_bEnd;
	//int        m_NextScene;
	//CBlock     m_Block;
public:
	CGame();
	~CGame();
	bool load(void);
	void Initialize(void);
	void Update();
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	//int GetNextScene(void) { return m_NextScene; }
	//bool IsEnd(void) { return m_bEnd; }
};

