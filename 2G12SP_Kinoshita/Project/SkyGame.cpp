#include "SkyGame.h"
#include "GameDefine.h"
#include "Mof.h"

extern   int  gChangeScene;
CSkyGame::CSkyGame()
{
}

CSkyGame::~CSkyGame()
{
}

bool CSkyGame::load(void)
{
    m_Player.Lood();
    m_Sky.Load("sukai.txt");
    return false;
}

void CSkyGame::Initialize(void)
{
    m_Player.Initalize();
    m_Sky.Initialize();
}

void CSkyGame::Update()
{
    m_Player.Update();
    m_Sky.Update(m_Player);
	float ox = 0, oy = 0;
	if (m_Sky.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}

    if (g_pInput->IsKeyPush(MOFKEY_F3))
    {
        gChangeScene = SCENENO_GAME;
    }
}

void CSkyGame::Render(void)
{
    m_Sky.Render();
    m_Player.Render(m_Sky.GetScrollX(), m_Sky.GetScrollY());
}

void CSkyGame::RenderDebug(void)
{
}

void CSkyGame::Release(void)
{
    m_Sky.Release();
    m_Player.Release();
}
