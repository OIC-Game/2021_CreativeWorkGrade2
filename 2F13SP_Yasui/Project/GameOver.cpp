#include "GameOver.h"
#include "GameApp.h"
#include "GlobalDefine.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
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

	//ゲームオーバーSEロード
	if (!gameover_GameOverSE.Load("GameOver2.wav"))
	{
		return false;
	}
	return true;
}

void CGameOver::Initialize(void)
{
	gameover_Font.Create(100, "MS 明朝");
	gameover_GameOverSE.Play();
}

void CGameOver::Update(void)
{
	//Enterキーでタイトル画面へ
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
	CGraphicsUtilities::RenderString(370, 450, "Enterでタイトル画面へ");
}

void CGameOver::RenderDebug(void)
{
}

void CGameOver::Release(void)
{
	gameover_GameOverSE.Release();
	gameover_Font.Release();
}
