#include "Option.h"
//#include"GameApp.h"
#include"GameDefine.h"

extern int    gChangeScene;

COption::COption():
	optionTexture()
{
}

COption::~COption()
{
}

bool COption::COption::Load(void)
{
	if (!optionTexture.Load("BG.png"))
	{
		return false;
	}
	return true;
	
}

void COption::COption::Initialize(void)
{
}

void COption::COption::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		//m_bEnd = true;
		gChangeScene = SCENENO_TITLE;
	}
}

void COption::COption::Render(void)
{
	optionTexture.Render(10, 10);
	CGraphicsUtilities::RenderString(300, 50, MOF_COLOR_BLACK, "→ボタン：右に移動");
	CGraphicsUtilities::RenderString(300, 100, MOF_COLOR_BLACK, "←ボタン：左に移動");
	CGraphicsUtilities::RenderString(300, 150, MOF_COLOR_BLACK, "↑ボタン：上にジャンプ");
	CGraphicsUtilities::RenderString(300, 200, MOF_COLOR_BLACK, "→又は←ボタン+Bボタン：ダッシュ");
	CGraphicsUtilities::RenderString(800, 700, MOF_COLOR_BLACK, "Enterでタイトル");

}

void COption::COption::Relase(void)
{
	optionTexture.Release();
}
