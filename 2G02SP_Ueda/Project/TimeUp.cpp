#include "GameDefine.h"
#include "TimeUp.h"
extern int						gChangeScene;
CTimeUp::CTimeUp()
{
}

CTimeUp::~CTimeUp()
{
}

bool CTimeUp::Load(void)
{
	if (!m_TimeUpTexture.Load("timeup.png"))
	{
		return false;
	}
	return true;
}

void CTimeUp::Initialize(void)
{
	m_bTimeUpCount = 150;
}

void CTimeUp::Update(void)
{
	if (m_bTimeUpCount > 0)
	{
		m_bTimeUpCount--;
	}
	else
	{
		gChangeScene = SCENENO_GAMEOVER;
	}
}

void CTimeUp::Render(void)
{
	m_TimeUpTexture.Render(0, 0);
}

void CTimeUp::RenderDebug(void)
{
}

void CTimeUp::Release(void)
{
	m_TimeUpTexture.Release();
}
