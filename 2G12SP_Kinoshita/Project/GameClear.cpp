#include "GameClear.h"

extern  int  gChangeScene;

CGameClear::CGameClear()
{
}

CGameClear::~CGameClear()
{
}

bool CGameClear::Load(void)
{
    if (!m_GameClear.Load("Clear.png"))
    {
        return false;
    }
	return false;
}

void CGameClear::Initialize(void)
{
}

void CGameClear::Update(void)
{
    if (g_pInput->IsKeyPush(MOFKEY_RETURN))
    {
        gChangeScene = SCENENO_TITLE;
    }
}

void CGameClear::Render(void)
{
    m_GameClear.Render(0,0);
    CGraphicsUtilities::RenderString(350, 400, MOF_COLOR_RED, "ÉNÉäÉAÇ®ÇﬂÇ≈Ç∆Ç§Ç≤Ç¥Ç¢Ç‹Ç∑ÅI");
    CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_CWHITE, "Press Enter Key");
}

void CGameClear::RenderDebug(void)
{
}

void CGameClear::Release(void)
{
    m_GameClear.Release();
}
