#include "UI.h"

CUI::CUI(){
}

CUI::~CUI(){
}

bool CUI::Load(void){
	if (!m_Texture.Load("UI.png"))
	{
		return false;
	}
	return true;
}

void CUI::Initialize(void){
}

void CUI::Render(void){
	CGraphicsUtilities::RenderString(30, 30, "MARIO");
	CGraphicsUtilities::RenderString(130, 30, "SCORE");
	CGraphicsUtilities::RenderString(460, 30, "STATUS");
	CGraphicsUtilities::RenderString(650, 30, "LIFE");
	//ƒRƒCƒ“‰æ‘œ‚ð•\Ž¦
	m_Texture.Render(350, 30);
	
}

void CUI::Release(void){
	m_Texture.Release();
}
