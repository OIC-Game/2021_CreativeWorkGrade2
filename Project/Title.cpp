#include "GameApp.h"
#include "Title.h"

CTitle::CTitle() :
	CSceneBase() {

	}

CTitle::~CTitle() {
	Release();
}

void CTitle::Initialize() {
}

void CTitle::Update() {
	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
		m_NextScene = SCENENO_GAME;
		m_bEnd = true;
	}
}

void CTitle::Render() {
	g_pGraphics->RenderStart();

	g_pGraphics->ClearTarget(0.0f, 0.3f, 0.5f, 0.0f, 1.0f, 0);
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2, g_pGraphics->GetTargetHeight() / 2, "‚Õ‚æ‚Õ‚æ");
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2 - 25, g_pGraphics->GetTargetHeight() / 2 + 25, "Press Enter");

	g_pGraphics->RenderEnd();
}

void CTitle::Release() {

}