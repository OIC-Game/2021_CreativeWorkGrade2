#include "GameDefine.h"
#include "GameOver.h"
extern int						gChangeScene;
CGameOver::CGameOver():
	m_bGameOverCount(0)
{
}

CGameOver::~CGameOver()
{
}

bool CGameOver::Load(void)
{
	if (!m_GameOverTexture.Load("gameover.png"))
	{
		return false;
	}
	return true;
}

void CGameOver::Initialize(void)
{
	m_bGameOverCount = 150;
}

void CGameOver::Update(void)
{
	if (m_bGameOverCount > 0)
	{
		m_bGameOverCount--;
	}
	else
	{
		gChangeScene = SCENENO_TITLE;
	}
}

void CGameOver::Render(void)
{
	m_GameOverTexture.Render(0, 0);
}

void CGameOver::RenderDebug(void)
{
}

void CGameOver::Release(void)
{
	m_GameOverTexture.Release();
}
