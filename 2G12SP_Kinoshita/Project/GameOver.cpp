#include "GameOver.h"
#include "GameOver.h"

extern  int  gChangeScene;
CGameOver::CGameOver()
{
}

CGameOver::~CGameOver()
{
}

bool CGameOver::Load(void)
{
    if (!m_BackTexture.Load("GameOver.png"))
    {
        return false;
    }
    return false;
}

void CGameOver::Initialize(void)
{
}

void CGameOver::Update(void)
{
    if (g_pInput->IsKeyPush(MOFKEY_RETURN))
    {
        gChangeScene= SCENENO_TITLE;
    }

    if (g_pInput->IsKeyPush(MOFKEY_RETURN) && g_pInput->IsKeyHold(MOFKEY_LEFT))
    {
        gChangeScene = SCENENO_GAME;
    }
}

void CGameOver::Render(void)
{
    m_BackTexture.Render(0, 0);
    CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_CWHITE, "Press Enter Key");
}

void CGameOver::RenderDebug(void)
{
   
}

void CGameOver::Release(void)
{
    m_BackTexture.Release();
}
