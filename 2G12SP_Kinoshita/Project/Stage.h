#pragma once

#include "Mof.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"
#include "breakBlock.h"
#include "Coin.h"
#include  "QuestionBlock.h"
#include "Goal.h"
#include "GoalFlg.h"
#include "Item.h"

#define		LEFTSLOPE							2
class CStage


{
	private:
		CTexture				m_ChipTexture;
		CTexture				m_BackTexture;
		//CSoundBuffer            m_gBGM;

		float					m_ChipSize;
		int						m_XCount;
		int						m_YCount;
		char* m_pChipData;

		float					m_ScrollX;
		float					m_ScrollY;

		int						m_EnemyTextureCount;
		CTexture*               m_pEnemyTexture;
		char*                   m_pEnemyData;
		int						m_EnemyCount;

		int                    m_GoalTextureCount;
		CTexture*              m_pGoalTexture;
		char*                  m_pGoalData;
		int                    m_GoalCount;

		int                    m_GoalFlgTextureCount;
		CTexture*              m_pGoalFlgTexture;
		char*                  m_pGoalFlgData;
		int                    m_GoalFlgCount;

		int                    m_QuestionBlockTextureCount;
		CTexture*              m_pQuestionBlockTexture;
		char*                  m_pQuestionBlockData;
		int                    m_QuestionBlockCount;

		int                    m_breakBlockTextureCount;
		CTexture*              m_pbreakBlockTexture;
		char*                  m_pbreakBlockData;
		int                    m_breakBlockCount;

		int                    m_ItemCount;

		int                    m_BlockTextureCount;
		CTexture*              m_pBlockTexture;
		char*                  m_pBlockData;
		int                    m_BlockCount;

		
		
		/*int                    m_DokanTextureCount;
		CTexture*              m_pDokanTexture;
		char*                  m_pDokanData;
		int                    m_DokanCount;*/

		


		

	public:
		CStage();
		~CStage();
		bool Load(char* pName);
		void Initialize(CEnemy* pEnemy, CGoal* pGoal, CGoalFlg* pGoalFlg, CQuestionBlock* pQuestionBlock, CbreakBlock* pbreakBlock, CBlock* pBlock);
		void Update(CPlayer& pl);
		bool Collision(CRectangle r, float& ox, float& oy);
		void Render(void);
		void RenderDebug(void);
		void Release(void);
		float GetScrollX() { return m_ScrollX; }
		float GetScrollY() { return m_ScrollY; }
		int GetEnemyCount() { return m_EnemyCount; }
		int GetGoalCount() { return m_GoalCount; }
		int GetGoalFlgCount() { return m_GoalFlgCount; }
		int GetQuestionBlockCount() { return m_QuestionBlockCount; }
		int GetbreakBlockCount() { return m_breakBlockCount; }
		int GetItemCount() { return m_ItemCount; }
		bool GetIem() { return &m_ItemCount; }

		int GetBlockCount() { return m_BlockCount; }
		bool CollusionItem(CItem& itm);
		
		
		
	};