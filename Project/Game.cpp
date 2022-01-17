#include "GameApp.h"
#include "Game.h"
#include "time.h"
#include "Field.h"
#include "Puyo.h"

CField gField[2];
int aiSwitch = 0;
bool aiThink = true;

CGame::CGame() :
	CSceneBase() {}

CGame::~CGame() {
	for(int i = 0; i < 2; i++)
	gField[i].Release();

	Release();
}

void CGame::Initialize(void) 
{
	for (int i = 0; i < 2; i++)
	gField[i].Initialize();
	gField[1].SetAI();


	CUtilities::SetCurrentDirectory("Resource");
	gSound[0].Load("Candy Crush.mp3");
	gSound[0].SetLoop(true);
	gSound[0].Play();
	gSound[1].Load("Accent07-1.mp3");

	isStop = false;
	isMenu = false;
	selectMenu = 0;
	aiControllTime = 0.0f;
}

void CGame::Update(void) 
{
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
	{
		isStop = isStop ^ true;
		isMenu = isMenu ^ true;
	}
	
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		if (isStop && !isMenu)
		{
			m_NextScene = SCENENO_TITLE;
			m_bEnd = true;
		}
		else if (isMenu && selectMenu == 0)
		{
			isStop = false;
			isMenu = false;
		}
		else if (isMenu && selectMenu == 1)
		{
			m_NextScene = SCENENO_TITLE;
			m_bEnd = true;
		}
	}

	if (isMenu)
	{
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			selectMenu++;
			if (selectMenu > 1) selectMenu = 0;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			selectMenu--;
			if (selectMenu < 0) selectMenu = 1;
		}
	}

	if (isStop) return;

	for (int i = 0; i < 2; i++)
	{
		if (gField[i].CheckStop())
		{
			gField[i].Wait();
		}
		else 
		{
			switch (gField[i].GetNowState())
			{
				case gField[i].eDrop:

					if (i == 0) 
					{
						if (g_pInput->IsKeyPush(MOFKEY_RIGHTARROW)) {
							gField[0].Right();
						}
						else if (g_pInput->IsKeyPush(MOFKEY_LEFTARROW)) {
							gField[0].Left();
						}

						if (g_pInput->IsKeyPush(MOFKEY_X)) {
							gField[0].RRotate();
						}
						else if (g_pInput->IsKeyPush(MOFKEY_Z)) {
							gField[0].LRotate();
						}

						if (g_pInput->IsKeyPush(MOFKEY_DOWNARROW))
						{
							gField[0].Down();
							dropDTime[0] = 0.0f;
						}

						if (g_pInput->IsKeyHold(MOFKEY_DOWNARROW)) {
							if (!gField[0].GetDropOnce()) {
								dropDTime[0] += gField[0].GetDropTime() * 0.15f;
							}
						}
					}
					else 
					{
						if (aiControllTime <= 0) 
						{
							int dif;

							if (aiThink)
							{
								aiThink = false;
								aiSwitch = 0;
								std::array<int, 3> main = gField[i].GetPuyoConM();
								std::array<int, 3> sub = gField[i].GetPuyoConS();

								for (int x = 5; x >= 0; x--) 
								{
									int y = gField[i].CheckBottom(x);

									if (gField[i].GetField()[x][y] == main[2] - 1)
									{
										dif = x - main[0];

										if (dif > 0 && main[1] > sub[1] && main[2] != sub[2])
										{
											aiSwitch = 4;
											break;
										}
										else if (dif < 0 && main[1] > sub[1] && main[2] != sub[2])
										{
											aiSwitch = 3;
											break;
										}
										else if (dif == 0 && main[1] > sub[1] && main[2] != sub[2])
										{
											aiSwitch = 7;
											break;
										}
										else if (dif == 0)
										{
											aiSwitch = 5;
											break;
										}
										else if (dif > 0)
										{
											aiSwitch = 1;
											break;
										}
										else if (dif < 0) 
										{
											aiSwitch = 2;
											break;
										}
									}
									else if (gField[i].GetField()[x][y] == sub[2] - 1)
									{
										dif = x - sub[0];

										if (dif == 0 && main[1] > sub[1])
										{
											aiSwitch = 7;
											break;
										}
										else if (dif > 0 && main[1] > sub[1])
										{
											aiSwitch = 3;
										}
										else if (dif < 0 && main[1] > sub[1])
										{
											aiSwitch = 4;
										}
										else if (dif == 0)
										{
											aiSwitch = 5;
											break;
										}
										else if (dif > 0) 
										{
											aiSwitch = 1;
											break;
										}
										else if (dif < 0) 
										{
											aiSwitch = 2;
											break;
										}
									}
								}

								if (aiSwitch == 0)
								{
									dif = gField[i].CheckBottomest() - main[0];

									if (dif == 0)
									{
										if (main[1] > sub[1] && main[2] != sub[2]) aiSwitch = 7;
										else aiSwitch = 5;
									}
									else if (dif > 0) aiSwitch = 1;
									else if(dif < 0) aiSwitch = 2;
								}

							}

							switch (aiSwitch)
							{

								case 1:
									if (gField[i].Right()) aiControllTime = 0.1f;
									else
									{
										if(gField[i].Down()) aiControllTime = 0.3f;
									}
									aiThink = true;
									break;
								
								case 2:
									if (gField[i].Left()) aiControllTime = 0.1f;
									else
									{
										if (gField[i].Down()) aiControllTime = 0.3f;
									}
									aiThink = true;
									break;

								case 3:
									gField[i].RRotate();
									aiControllTime = 0.05f;
									aiThink = true;
									break;

								case 4:
									gField[i].LRotate();
									aiControllTime = 0.05f;
									aiThink = true;
									break;

								case 5:
									if(gField[i].Down()) aiControllTime = 0.3f;
									break;

								case 7:
									std::array<int, 3> main = gField[i].GetPuyoConM();
									if (main[0] != 0 && main[0] != 5)
									{
										if (gField[i].CheckBottom(main[0] - 1) > gField[i].CheckBottom(main[0] + 1)) gField[i].LRotate();
										else gField[i].RRotate();
									}
									else if (main[0] == 0) gField[i].RRotate();
									else gField[i].LRotate();

									aiThink = true;
									aiControllTime = 0.1f;
									break;

								default:
									break;
							}

							/*
							case 1:
							if (gField.GetField()[3][1] == -1)
							{
								if (gField.Right())
								{
									//aiControllTime = 0.5f;
									aiControllTime = 0.1f;
								}
								else 
								{
									dropDTime += gField.GetDropTime() * 0.15f;
									aiControllTime = 0.01f;
									//aiControllTime = 0.1f;
								}
							}
							else 
							{
								if (gField.Left())
								{
									//aiControllTime = 0.5f;
									aiControllTime = 0.1f;
								}
								else
								{
									dropDTime += gField.GetDropTime() * 0.15f;
									aiControllTime = 0.01f;
									//aiControllTime = 0.1f;
								}
							}
							break;

							case 2:
							if (gField.GetField()[1][1] == -1)
							{
								if (gField.Left())
								{
									aiControllTime = 0.1f;
								}
								else
								{
									dropDTime += gField.GetDropTime() * 0.15f;
									aiControllTime = 0.01f;
								}
							}
							else
							{
								if (gField.Right())
								{
									aiControllTime = 0.1f;
								}
								else
								{
									dropDTime += gField.GetDropTime() * 0.15f;
									aiControllTime = 0.01f;
								}
							}
							break;
							*/
						}

						aiControllTime -= CUtilities::GetFrameSecond();
					}

					dropDTime[i] += CUtilities::GetFrameSecond();

					if (dropDTime[i] >= gField[i].GetDropTime()) 
					{
						gField[i].Down();
						dropDTime[i] = 0.0f;
					}

					//obstacleDTime += CUtilities::GetFrameSecond();
					/*
					if (obstacleDTime >= gField[i].GetObstacleTime()) 
					{
						obstacleDTime = 0;
						gField[i].AddObstacle(gField[i].GetObstacleAmount());
						gSound[1].Play();
					}
					*/
					break;

				case gField[i].eFall:
					aiControllTime = 0.3f;
					aiThink = true;
					gField[i].CheckHollow();
					break;
					
				case gField[i].eDelete:
					gField[i].CheckDelete(false);
					break;

				case gField[i].eBanish:
					gField[i].Banish();
					if (gField[i].GetCombo() >= 2) ObstacleThrow(i, gField[i].GetCombo());
					break;

				case gField[i].eSet:
					if (gField[i].CheckObstacle()) gField[i].SetObstacle();
					else gField[i].AddPuyo();
					break;

				case gField[i].eGameover:
					isStop = true;
					break;
			}
		}
	}

	if (gField[0].GetDropOnce() && !g_pInput->IsKeyHold(MOFKEY_DOWNARROW)) gField[0].SetDropOnce(false);

	if (g_pInput->IsKeyPush(MOFKEY_C)) gField[0].Stock();

	//if (g_pInput->IsKeyPush(MOFKEY_O)) gField.addobs(6);
}


void CGame::Render(void) {
	g_pGraphics->RenderStart();

	g_pGraphics->ClearTarget(0.3f, 0.35f, 0.05f, 0.0f, 1.0f, 0);
	//for (int i = 0; i < 2; i++)

	CGraphicsUtilities::RenderFillRect(25, 100, 85, 195, MOF_XRGB(0, 0, 0));//stock
	CGraphicsUtilities::RenderFillRect(100, 25, 400, 625, MOF_XRGB(0, 0, 0));//field
	CGraphicsUtilities::RenderFillCircle(225, 50, 11, MOF_XRGB(180, 180, 180));//GameOverLine
	CGraphicsUtilities::RenderFillRect(420, 100, 480, 220, MOF_XRGB(0, 0, 0));//Next
	CGraphicsUtilities::RenderFillRect(465, 175, 525, 260, MOF_XRGB(0, 0, 0));//Next
	CGraphicsUtilities::RenderFillRect(5, 645, 200, 680, MOF_XRGB(0, 0, 0));
	CGraphicsUtilities::RenderString(10, 650, "Score:%d", gField[0].GetScore());
	CGraphicsUtilities::RenderString(10, 700, "←/→：左右移動　↓：高速落下\nZ/X:左右回転　C:ストック");

	CGraphicsUtilities::RenderFillRect(595, 100, 655, 220, MOF_XRGB(0, 0, 0));//Next
	CGraphicsUtilities::RenderFillRect(550, 175, 610, 260, MOF_XRGB(0, 0, 0));//Next
	CGraphicsUtilities::RenderFillRect(675, 25, 975, 625, MOF_XRGB(0, 0, 0));//field
	CGraphicsUtilities::RenderFillCircle(800, 50, 11, MOF_XRGB(180, 180, 180));//GameOverLine
	CGraphicsUtilities::RenderFillRect(990, 100, 1050, 195, MOF_XRGB(0, 0, 0));//stock
	/*
	float rate = obstacleDTime / obstacleCreateTime;
	int x = 255 * rate;
	CGraphicsUtilities::RenderFillCircle(225, 50, 7, MOF_XRGB(x, 0, x));
	*/

	gField[0].Render(125,450,495,55,250);
	gField[1].Render(700,625,580,1020,725);
	
	/*
	float cir = 0.0f * M_PI / 180;
	CGraphicsUtilities::RenderCircle(200, 200, 1,MOF_XRGB(100,100,100));
	CGraphicsUtilities::RenderCircle((cos(cir) * 50) + 200, (sin(cir) * 50) + 200, 1, MOF_XRGB(0, 100, 100));
	*/

	if (gField[0].GetNowState() == gField->eGameover)
	{
		CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2, g_pGraphics->GetTargetHeight() / 2, "GameOver");
		CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2, g_pGraphics->GetTargetHeight() / 2 + 25, "Press Enter");
	}
	else if (gField[1].GetNowState() == gField->eGameover)
	{

		CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2, g_pGraphics->GetTargetHeight() / 2, "Player Win!");
		CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2, g_pGraphics->GetTargetHeight() / 2 + 25, "Press Enter");
	}

	if (isMenu)
	{
		CGraphicsUtilities::RenderFillRect(420, 380, 620, 480, MOF_XRGB(50, 50, 50));
		CGraphicsUtilities::RenderString(430, 390, menu[0]);
		for (int i = 1; i < 3; i++)
		{
			MofU32 col = MOF_COLOR_WHITE;

			if (selectMenu + 1 == i)
			{
				col = MOF_COLOR_RED;
			}
			CGraphicsUtilities::RenderString(430, 400 + (i * 25), col,menu[i]);

		}
	}

	g_pGraphics->RenderEnd();
}

void CGame::Release(void) {
	for(int i = 0; i < 2; i++)
	gField[i].Release();
	gSound->Release();
}

void CGame::ObstacleThrow(int p, int c)
{
	for(int i = 0; i < 2; i++)
	{
		if (i == p) continue;
		gField[i].AddObstacle(c * c);
	}
}
