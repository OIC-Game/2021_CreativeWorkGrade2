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
	
	if (!m_LifeTexture.Load("Life.png"))
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
	CGraphicsUtilities::RenderString(470, 30, "STATUS:");
	CGraphicsUtilities::RenderString(700, 30, "Å~");
	CGraphicsUtilities::RenderString(770, 30, "COMBO:");
	CGraphicsUtilities::RenderString(910, 30, "TIME:");
	//ÉRÉCÉìâÊëúÇï\é¶
	m_Texture.Render(350, 30);
	m_LifeTexture.Render(680, 30);
}

void CUI::Release(void){
	m_Texture.Release();
	m_LifeTexture.Release();
}
