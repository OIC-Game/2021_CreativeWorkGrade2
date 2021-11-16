#include	"GameDefine.h"
#include	"GameRetry.h"

//�ύX����V�[��
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
	//���Ԍo��
	Time += CUtilities::GetFrameSecond();
	//���Ԍo�߂ŃQ�[����ʂ�
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
