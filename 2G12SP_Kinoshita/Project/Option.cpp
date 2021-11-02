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
	CGraphicsUtilities::RenderString(300, 50, MOF_COLOR_BLACK, "���{�^���F�E�Ɉړ�");
	CGraphicsUtilities::RenderString(300, 100, MOF_COLOR_BLACK, "���{�^���F���Ɉړ�");
	CGraphicsUtilities::RenderString(300, 150, MOF_COLOR_BLACK, "���{�^���F��ɃW�����v");
	CGraphicsUtilities::RenderString(300, 200, MOF_COLOR_BLACK, "�����́��{�^��+B�{�^���F�_�b�V��");
	CGraphicsUtilities::RenderString(800, 700, MOF_COLOR_BLACK, "Enter�Ń^�C�g��");

}

void COption::COption::Relase(void)
{
	optionTexture.Release();
}
