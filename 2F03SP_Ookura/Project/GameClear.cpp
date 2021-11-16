#include "GameClear.h"
#include "GameApp.h"

extern int						gChangeScene;

CGameClear::CGameClear()
{
}

CGameClear::~CGameClear()
{
}

bool CGameClear::Load(void)
{
	return true;
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
	CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームクリア　：　Enterキーでもう一度最初から");
}

void CGameClear::RenderDebug(void)
{
}

void CGameClear::Release(void)
{
}
