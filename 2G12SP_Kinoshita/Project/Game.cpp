#include "Game.h"
#include "GameDefine.h"
#include "Mof.h"


extern   int  gChangeScene;
//コンストラクタ
CGame::CGame()
	//m_bEnd(false),
	//m_NextScene(0)
{

}
 //デストラクタ
CGame::~CGame()
{
	//m_bEnd = false;
		
}

bool CGame::load(void)
{
	m_Player.Lood();

	m_Stage.Load("stage1-3.txt");
	//m_Sky.Load("sukai.txt");
	if (!coinTexture.Load("coin2.png"))
	{
		return false;
	}

	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	m_GoalArray = new CGoal[m_Stage.GetGoalCount()];
	m_GoalFlgArray = new CGoalFlg[m_Stage.GetGoalFlgCount()];
	
	m_QuestionBlockArray = new CQuestionBlock[m_Stage.GetQuestionBlockCount()];
	m_breakBlockArray = new CbreakBlock[m_Stage.GetbreakBlockCount()];
	//m_ItemArray = new CItem[m_Stage.GetItem()];
	m_BlockArray = new CBlock[m_Stage.GetBlockCount()];
	
	
	return true;
}

//初期化
void CGame::Initialize(void)
{
	m_Player.Initalize();
	
	m_Stage.Initialize(m_EnemyArray,m_GoalArray, m_GoalFlgArray, m_QuestionBlockArray, m_breakBlockArray, m_BlockArray);
	
	Time = 100;
	//m_Sky.Initialize();
}

//更新
void CGame::Update(void)
{
	m_Player.Update();
	m_Stage.Update(m_Player);
	
	float ox = 0, oy = 0;
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}
	/*for (int i = 0; i < m_Player.GetItem(); i++)
	{
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy))
		{
			m_ItemArray[i].CollisionStage(ox, oy);
		}
	}*/
	//敵更新
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow() || !m_EnemyArray[i].IsScreen(m_Stage.GetScrollX(), m_Stage.GetScrollY()))
		
		{
			continue;
		}
		
		m_EnemyArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
	}

	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)

	{
		m_Player.CollisionEnemy(m_EnemyArray[i]);
	}

	//ブロックの更新
	for (int i = 0; i < m_Stage.GetBlockCount(); i++)
	{
		float ox = 0, oy = 0;
		
		// TODO: 明らかにおかしい
		if(m_Stage.Collision(m_BlockArray[i].GetRect() , ox, oy));
		{
			m_BlockArray[i].CollisionStage(ox, oy);
			m_Player.CollisionBlock(m_BlockArray[i], ox, oy);
		}
	}

	//ゴールの更新
	for (int i = 0; i < m_Stage.GetGoalCount(); i++)
	{
		m_Player.CollisionGoal(m_GoalArray[i]);
	}
	if (m_Player.IsGoal())
	{
		gChangeScene = SCENENO_GAMEClear;
	}

	if (Time <= 0)
	{
		gChangeScene = SCENENO_GAMEOVER;
	}

	//レンガブロックの更新
	for (int i = 0; i < m_Stage.GetbreakBlockCount();i++)
	{
		m_Player.CollisionbreakBlock(m_breakBlockArray[i],ox,oy);
		m_EnemyArray->CollisionbreakBlock(m_breakBlockArray[i], ox, oy);
	   
	}

	//ハテナブロックの更新
	for (int i = 0; i < m_Stage.GetQuestionBlockCount(); i++)
	{
		
			m_Player.CollisionQBlock(m_QuestionBlockArray[i], ox, oy);
	
			m_EnemyArray[i].CollisionQBlock(m_QuestionBlockArray[i], ox, oy);
	}

	//アイテムの更新
	/*for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy))
		{
			m_ItemArray[i].CollisionStage(ox, oy);
			
		}
		m_Player.CollusionItem(m_ItemArray[i]);
		
	}*/


	for (int i = 0; i < Item_count; i++)
	{
		
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_Player.GetItem()[i].GetRect(), ox, oy))
		{

			m_Player.GetItem()[i].CollisionStage(ox, oy);

		}
		m_Player.CollusionItem(m_Player.GetItem()[i]);
		
	}

	

	//for (int i = 0; i < m_Stage.GetBlockCount(); i++)
	//{
	//	m_Player.CollisionBlock(m_BlockArray[i], ox, oy);
	//}

	if (m_Player.IsDead())
	{
		gChangeScene = SCENENO_GAMEOVER;
	}

	if (m_Player.IsSky())
	{
		gChangeScene = SCENENO_Sky;
	}



	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		gChangeScene = SCENENO_GAMEOVER;
	}

	Time -= CUtilities::GetFrameSecond();
}

//描画
void CGame::Render(void)
{
	m_Stage.Render();
	//m_Sky.Render();
	m_Player.Render(m_Stage.GetScrollX(),m_Stage.GetScrollY());

	
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	

	for (int i = 0; i < m_Stage.GetQuestionBlockCount(); i++)
	{
		m_QuestionBlockArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	for (int i = 0; i < m_Stage.GetGoalCount(); i++)
	{
		m_GoalArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	for (int i = 0; i < m_Stage.GetGoalFlgCount(); i++)
	{
		m_GoalFlgArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	for (int i = 0; i < m_Stage.GetbreakBlockCount(); i++)
	{
		m_breakBlockArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	for (int i = 0; i < m_Stage.GetQuestionBlockCount(); i++)
	{
		m_QuestionBlockArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	for (int i = 0; i < m_Stage.GetBlockCount(); i++)
	{
		m_BlockArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	//UIの表示
	CGraphicsUtilities::RenderString(10, 0, MOF_COLOR_RED, "MARIO");
	CGraphicsUtilities::RenderString(10, 20, MOF_COLOR_RED, "000000");
	coinTexture.Render(475,17);
	CGraphicsUtilities::RenderString(500, 20, MOF_COLOR_RED, "×00");
	CGraphicsUtilities::RenderString(700, 0, MOF_COLOR_RED, "WORLD");
	CGraphicsUtilities::RenderString(710, 20, MOF_COLOR_RED, "1-1");
	CGraphicsUtilities::RenderString(800,20,MOF_COLOR_RED, "TIME:%5.2f",Time);

	
	//CGraphicsUtilities::RenderString(10, 10, "ゲーム画面");
	
}

void CGame::RenderDebug(void)
{
	m_Stage.RenderDebug();
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	/*for (int i = 0; i < m_Stage.GetBlockCount(); i++)
	{
		m_BlockArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}*/
	for (int i = 0; i < m_Stage.GetbreakBlockCount(); i++)
	{
		m_breakBlockArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	for (int i = 0; i < m_Stage.GetQuestionBlockCount(); i++)
	{
		m_QuestionBlockArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	for (int i = 0; i < m_Player.GetItemCount(); i++)
	{
		m_Player.GetItem()[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	



}

void CGame::Release(void)
{
	m_Stage.Release();
	//m_Sky.Release();
	m_Player.Release();
	//敵
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	

	//ハテナブロック
	if (m_DokanArray)
	{
		delete[]m_QuestionBlockArray;
		m_QuestionBlockArray = NULL;

	}

	//ゴールポール
	if (m_GoalArray)
	{
		delete[]m_GoalArray;
		m_GoalArray = NULL;

	}

	//ゴールフラグ
	if (m_GoalFlgArray)
	{
		delete[]m_GoalFlgArray;
		m_GoalFlgArray = NULL;

	}
	//レンガブロック
	if (m_breakBlockArray)
	{
		delete[]m_breakBlockArray;
		m_breakBlockArray = NULL;

	}

	//四角ブロック
	if (m_BlockArray)
	{
		delete[]m_BlockArray;
		m_BlockArray = NULL;

	}

	if (m_ItemArray)
	{
		delete[]m_ItemArray;
		m_ItemArray = NULL;
	}
	
	coinTexture.Release();
	////土管
	//if (m_DokanArray)
	//{
	//	delete[]m_DokanArray;
	//	m_DokanArray = NULL;

	//}
}
