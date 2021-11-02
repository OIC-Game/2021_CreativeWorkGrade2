#include "GameApp.h"
#include "Game.h"
#include "time.h"
#include "Field.h"

CField gField;

CGame::CGame() :
	CSceneBase() {}

CGame::~CGame() {
	gField.Release();
	Release();
}

void CGame::Initialize(void) {
	gField.Initialize();

	CUtilities::SetCurrentDirectory("Resource");
	gSound[0].Load("Candy Crush.mp3");
	gSound[0].SetLoop(true);
	gSound[0].Play();
	gSound[1].Load("Accent07-1.mp3");
}

void CGame::Update(void) {
	if (gField.CheckStop())
	{
		gField.Wait();
	}
	else 
	{
		switch (gField.GetNowState())
		{
			case gField.eDrop:

				if (g_pInput->IsKeyPush(MOFKEY_RIGHTARROW)) {
					gField.Right();
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFTARROW)) {
					gField.Left();
				}

				if (g_pInput->IsKeyPush(MOFKEY_X)) {
					gField.RRotate();
				}
				else if (g_pInput->IsKeyPush(MOFKEY_Z)) {
					gField.LRotate();
				}

				if (g_pInput->IsKeyHold(MOFKEY_DOWNARROW)) {
					if (!gField.GetDropOnce()) {
						dropDTime += gField.GetDropTime() * 0.15f;
					}
				}
				dropDTime += CUtilities::GetFrameSecond();

				if (dropDTime >= gField.GetDropTime() || g_pInput->IsKeyPush(MOFKEY_DOWNARROW)) {
					gField.Down();
					dropDTime = 0.0f;
				}

				obstacleDTime += CUtilities::GetFrameSecond();
				if (obstacleDTime >= gField.GetObstacleTime()) {
					obstacleDTime = 0;
					gField.AddObstacle(gField.GetObstacleAmount());
					gSound[1].Play();
				}

				break;

			case gField.eFall:
				gField.CheckHollow();
				break;
					
			case gField.eDelete:
				gField.CheckDelete(false);
				break;

			case gField.eBanish:
				gField.Banish();
				break;

			case gField.eSet:
				if (gField.CheckObstacle()) gField.SetObstacle();
				else gField.AddPuyo();
				break;

			case gField.eGameover:
				if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
					m_NextScene = SCENENO_TITLE;
					m_bEnd = true;
				}
				break;
		}
	}

	if (gField.GetDropOnce() && !g_pInput->IsKeyHold(MOFKEY_DOWNARROW)) gField.SetDropOnce(false);

	if (g_pInput->IsKeyPush(MOFKEY_C)) gField.Stock();

	//if (g_pInput->IsKeyPush(MOFKEY_O)) gField.addobs(6);
}


void CGame::Render(void) {
	g_pGraphics->RenderStart();

	g_pGraphics->ClearTarget(0.3f, 0.35f, 0.05f, 0.0f, 1.0f, 0);
	CGraphicsUtilities::RenderFillRect(100, 25, 400, 625, MOF_XRGB(0, 0, 0));//field
	CGraphicsUtilities::RenderFillRect(420, 100, 480, 220, MOF_XRGB(0, 0, 0));//Next
	CGraphicsUtilities::RenderFillRect(465, 175, 525, 260, MOF_XRGB(0, 0, 0));//Next
	CGraphicsUtilities::RenderFillRect(25, 100, 85, 195, MOF_XRGB(0, 0, 0));//stock
	CGraphicsUtilities::RenderFillCircle(225, 50, 11, MOF_XRGB(180, 180, 180));//GameOverLine
	CGraphicsUtilities::RenderFillRect(5, 645, 200, 680, MOF_XRGB(0, 0, 0));
	CGraphicsUtilities::RenderString(10, 650, "Score:%d", gField.GetScore());
	CGraphicsUtilities::RenderString(10, 700, "←/→：左右移動　↓：高速落下\nZ/X:左右回転　C:ストック");

	float rate = obstacleDTime / obstacleCreateTime;
	int x = 255 * rate;

	CGraphicsUtilities::RenderFillCircle(225, 50, 7, MOF_XRGB(x, 0, x));

	gField.Render();
	
	g_pGraphics->RenderEnd();
}

void CGame::Release(void) {
	gField.Release();
	gSound->Release();
}