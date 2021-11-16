#include	"GameDefine.h"
#include	"GameRetry.h"

//変更するシーン
extern int						gChangeScene;

float							Time = 0;
CGameRetry::CGameRetry()
{
}

CGameRetry::~CGameRetry()
{
}

bool CGameRetry::Load(void)
{
	return false;
}

void CGameRetry::Initialize(void)
{
	Time = 0;
}

void CGameRetry::Update(void)
{
	//時間経過
	Time += CUtilities::GetFrameSecond();
	//時間経過でゲーム画面へ
	if (Time >= 3)
	{
		gChangeScene = SCENENO_GAME;
	}
}

void CGameRetry::Render(void)
{
	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_XRGB(0, 0, 0));
}

void CGameRetry::RenderDebug(void)
{
}

void CGameRetry::Release(void)
{
}
