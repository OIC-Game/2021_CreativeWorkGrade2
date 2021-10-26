#include "Game.h"

extern int						gChangeScene;
CGame::CGame()
{
}

CGame::~CGame()
{
}

bool CGame::Load(void)
{
    m_Player.Load();
	m_Stage.Load("Stage1.txt", "Stage1Information.txt");
    m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
    return true;
}

void CGame::Initialize(void)
{
    m_Player.Initialize();
    m_Stage.Initialize(m_EnemyArray,m_ItemArray);
}

void CGame::Update(void)
{
	m_Player.Update(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	m_Stage.Update(m_Player);
	m_Player.CollisionPipe(m_Stage.GettPipe(),m_Stage.GetbPipe(), m_Stage.GetlPipe(), m_Stage.GetrPipe(),m_Stage.GetuPipe());
	float ox = 0, oy = 0;
	if (m_Player.GetDead())
	{
		if (m_Player.DeadEnd())
		{
			m_Information.DecLife();
			if (m_Information.GetLife() > 0 && m_Stage.GetTime() > 0)
			{
				gChangeScene = SCENENO_INFORMATION;
			}
			else
			{
				m_Information.InLife();
				if (m_Stage.GetTime() <= 0)
				{
					gChangeScene = SCENENO_TIMEUP;
				}
				else
				{
					gChangeScene = SCENENO_GAMEOVER;
				}
				
			}
		}
		return;
	}
	if (m_Player.GetGiant()) 
	{
		return;
	}
	if (m_Player.GetUnder() && !m_Stage.GetUnder())
	{
		m_Stage.UnderGround();
	}
	if (!m_Player.GetUnder() && m_Stage.GetUnder())
	{
		m_Stage.OnGround();
	}
	if (m_Player.GetdPipe())
	{
		return;
	}
	if (m_Player.GetmPipe())
	{
		return;
	}
	if (m_Player.GetuPipe())
	{
		return;
	}
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}
    if (m_Stage.GetGoal(m_Player,ox))
	{
		if (m_Player.GoalEnd(ox, m_Stage.GetGoalBottom(), m_Stage.GetCastle()))
		{
			gChangeScene = SCENENO_TITLE;
		}
		return;
	}
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update(m_Stage.GetScrollX(),m_Stage.GetScrollY());
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy))
		{
			m_ItemArray[i].CollisionStage(ox, oy);
		}
	}
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_Player.CollisionItem(m_ItemArray[i]);
	}
}

void CGame::Render(void)
{
	m_Stage.Render();
    m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	m_Stage.PipeRender();
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
}

void CGame::RenderDebug(void)
{
    m_Stage.RenderDebug();
    m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
}

void CGame::Release(void)
{
    m_Stage.Release();
    m_Player.Release();
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
}
