#include	"GameDefine.h"
#include	"GameRetry.h"
#include	"Player.h"

CFont		gFont;

//�ύX����V�[��
extern int						gChangeScene;

extern int						gStage;

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
	gFont.Create(36, "MS ����");
}

void CGameRetry::Update(void)
{
	//���Ԍo��
	Time += CUtilities::GetFrameSecond();
	//���Ԍo�߂ŃQ�[����ʂ�
	if (Time >= 5)
	{
		gChangeScene = SCENENO_GAME;
	}
}

void CGameRetry::Render(void)
{
	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_XRGB(0, 0, 0));
	if (gStage == STAGENO_01)
	{
		gFont.RenderString(500, 200, "1-1");
	}
	else if (gStage == STAGENO_02)
	{
		gFont.RenderString(500, 200, "1-2");
	}
	else if (gStage == STAGENO_03)
	{
		gFont.RenderString(500, 200, "1-3");
	}
}

void CGameRetry::RenderDebug(void)
{
}

void CGameRetry::Release(void)
{
}
