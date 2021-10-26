#include "GameOver.h"
#include "GameApp.h"
#include "GlobalDefine.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;


CGameOver::CGameOver():
	gameover_GameOverSE(),
	gameover_Font()
{
}

CGameOver::~CGameOver()
{
}

bool CGameOver::Load(void)
{

	//�Q�[���I�[�o�[SE���[�h
	if (!gameover_GameOverSE.Load("GameOver2.wav"))
	{
		return false;
	}
	return true;
}

void CGameOver::Initialize(void)
{
	gameover_Font.Create(100, "MS ����");
	gameover_GameOverSE.Play();
}

void CGameOver::Update(void)
{
	//Enter�L�[�Ń^�C�g����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gameover_GameOverSE.Stop();
		m_NextScene = SCENENO_TITLE;
		m_bEnd = true;
	}
}

void CGameOver::Render(void)
{
	gameover_Font.RenderString(250, 300,"GAME OVER");
	CGraphicsUtilities::RenderString(370, 450, "Enter�Ń^�C�g����ʂ�");
}

void CGameOver::RenderDebug(void)
{
}

void CGameOver::Release(void)
{
	gameover_GameOverSE.Release();
	gameover_Font.Release();
}
