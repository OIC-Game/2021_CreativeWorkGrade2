/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"GameDefine.h"
#include	"Title.h"
#include	"Game.h"
#include	"Information.h"
#include    "GameOver.h"
#include    "TimeUp.h"
int						gScene = SCENENO_TITLE;
//変更するシーン
int						gChangeScene = SCENENO_TITLE;

//各シーンクラス
CTitle					gTitleScene;
CGame					gGameScene;
CInformation			gInfoScene;
CGameOver				gGameOverScene;
CTimeUp					gTimeUpScene;
bool					g_bDebug = false;
int						g_LifeCount;
/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	CUtilities::SetCurrentDirectory("Resource");
    g_pGraphics->SetScreenSize(512, 448);
	gTitleScene.Load();
	gGameScene.Load();
	gTitleScene.Initialize();
	gInfoScene.Load();
	gInfoScene.Initialize(g_LifeCount);
	gGameOverScene.Load();
	gTimeUpScene.Load();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();
	switch (gScene)
	{
	case SCENENO_TITLE:
		gTitleScene.Update();
		break;
	case SCENENO_GAME:
		gGameScene.Update();
		break;
	case SCENENO_INFORMATION:
		gInfoScene.Update();
		break;
	case SCENENO_GAMEOVER:
		gGameOverScene.Update();
		break;
	case SCENENO_TIMEUP:
		gTimeUpScene.Update();
		break;
	}

	if (gChangeScene != gScene)
	{
		switch (gChangeScene)
		{
		case SCENENO_TITLE:
			g_LifeCount = 0;
			gTitleScene.Initialize();
			break;
		case SCENENO_GAME:
			gGameScene.Initialize();
			break;
		case SCENENO_INFORMATION:
			gInfoScene.Initialize(g_LifeCount);
			g_LifeCount++;
			break;
		case SCENENO_GAMEOVER:
			gGameOverScene.Initialize();
			break;
		case SCENENO_TIMEUP:
			gTimeUpScene.Initialize();
			break;
		}
		gScene = gChangeScene;
	}

	/*if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = ((g_bDebug) ? false : true);
	}*/
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
	switch (gScene)
	{
	case SCENENO_TITLE:
		gTitleScene.Render();
		break;
	case SCENENO_GAME:
		gGameScene.Render();
		break;
	case SCENENO_INFORMATION:
		gInfoScene.Render();
		break;
	case SCENENO_GAMEOVER:
		gGameOverScene.Render();
		break;
	case SCENENO_TIMEUP:
		gTimeUpScene.Render();
		break;
	}

	if (g_bDebug)
	{
		//シーン番号によって描画
		switch (gScene)
		{
		case SCENENO_TITLE:
			gTitleScene.RenderDebug();
			break;
		case SCENENO_GAME:
			gGameScene.RenderDebug();
			break;
		case SCENENO_INFORMATION:
			gInfoScene.RenderDebug();
			break;
		case SCENENO_GAMEOVER:
			gGameOverScene.RenderDebug();
			break;
		case SCENENO_TIMEUP:
			gTimeUpScene.RenderDebug();
			break;
		}
	}
	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	gTitleScene.Release();
	gGameScene.Release();
	gInfoScene.Release();
	gGameOverScene.Release();
	gTimeUpScene.Release();
	return TRUE;
}