#include "GameOver.h"
#include "GameApp.h"

extern int						gChangeScene;

CGameOver::CGameOver()
{
}

CGameOver::~CGameOver()
{
}

bool CGameOver::Load(void)
{
	return true;
}

void CGameOver::Initialize(void)
{
}

void CGameOver::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		
		gChangeScene = SCENENO_TITLE;
	}
}

void CGameOver::Render(void)
{
	CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "�Q�[���I�[�o�[�@�F�@Enter�L�[�ł�����x�ŏ�����");
}

void CGameOver::RenderDebug(void)
{
}

void CGameOver::Release(void)
{
}

