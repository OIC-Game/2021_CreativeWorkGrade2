/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"


#include    "Player.h"
#include "GameOver.h"
#include    "Title.h"
#include     "Game.h"
#include "GameDefine.h"
#include "GameClear.h"
#include "Option.h"
#include"SkyGame.h"

//#include    "CStage.h"

//現在のシーン
int           gScene = SCENENO_TITLE;

int           gChangeScene = SCENENO_TITLE;
//各シーンクラス
CTitle       gTitleScene;
CGame        gGameScene;
CGameOver    gGameOverScene;
CGameClear   gGameClearScene;
COption      gOptionScene;
CSkyGame     gSkyGameScene;

//プレイヤー
CTexture   player;

//CTexture   tesuto;
bool   g_bDebug = false;

//ステージ
//CCStage   g_Stage;
/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	CUtilities::SetCurrentDirectory("Resource");

	//プレイヤーの素材読み込み
	//player.Load("Run (1).png");

	//ステージの素材読み込み
	//g_Stage.Lord();
   
	//プレイヤーの状態初期化
	

	//ステージの状態初期化
	//g_Stage.Initialize();

	//シーンの必要リソース
	gTitleScene.Load();
	gGameScene.load();
	gSkyGameScene.load();
	gGameOverScene.Load();
	gGameClearScene.Load();
	gOptionScene.Load();

	//最初の実行されるシーンの初期化
	gTitleScene.Initalize();
	gGameScene.Initialize();
	gSkyGameScene.Initialize();
	gGameOverScene.Initialize();
	gGameClearScene.Initialize();
	gOptionScene.Initialize();

	/*switch (gScene)
	{
	case SCENENO_TITLE:
		gTitleScene.Load();
		gTitleScene.Initalize();
		break;
	case SCENENO_GAME:
		gGameScene.load();
		gGameScene.Initialize();
		break;
	case SCENENO_GAMEClear:
		gGameClearScene.Load();
		gGameClearScene.Initialize();
		break;
	case SCENENO_GAMEOVER:
		gGameOverScene.Load();
		gGameClearScene.Initialize();
		break;
	}*/



	//tesuto.Load("Run (1).png");

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();

	switch (gScene)
	{
	case SCENENO_TITLE:
		gTitleScene.Update();
		/*if (gTitleScene.IsEnd())
		{
			gChangeScene = gTitleScene.GetNextScene();
		}*/
		break;

	case SCENENO_GAME:
		gGameScene.Update();
		
		break;

	case SCENENO_Sky:
		gSkyGameScene.Update();

		break;

	case SCENENO_GAMEOVER:
		gGameOverScene.Update();
		break;

	case SCENENO_GAMEClear:
		gGameClearScene.Update();
		break;
	case SCENENO_Option:
		gOptionScene.Update();
		break;
	}

	if (gChangeScene != gScene)
	{
		switch (gScene)
		{
		case SCENENO_TITLE:
			//gTitleScene.Load();
			gTitleScene.Initalize();
			
			break;
		case SCENENO_GAME:
			//gGameScene.load();
			gGameScene.Initialize();
			break;

		case SCENENO_Sky:
			gSkyGameScene.Initialize();

			break;

			
		case SCENENO_GAMEOVER:
			//gGameOverScene.Load();
			gGameOverScene.Initialize();
			break;

		case SCENENO_GAMEClear:
			//gGameClearScene.Load();
			gGameClearScene.Initialize();
			break;
		case SCENENO_Option:
			//gOptionScene.Load();
			gOptionScene.Initialize();
			break;
		}
		gScene = gChangeScene;
	}


	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = ((g_bDebug) ? false : true);
	}
	

	//ステージの更新
	//g_Stage.Update();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	//ステージの描画
	//g_Stage.Render();

	//シーン番号によって描画
	switch (gScene)
	{
	case SCENENO_TITLE:
		gTitleScene.Render();
		break;
	case SCENENO_GAME:
		gGameScene.Render();
		break;
	case SCENENO_Sky:
		gSkyGameScene.Render();
		break;
	case SCENENO_GAMEOVER:
		gGameOverScene.Render();
		break;
	case SCENENO_GAMEClear:
		gGameClearScene.Render();
		break;
	case SCENENO_Option:
		gOptionScene.Render();
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
		/*case SCENENO_Sky:
			gSkyGameScene.Render();
			break;*/
		case SCENENO_GAMEClear:
			gGameClearScene.RenderDebug();
			break;
		case SCENENO_GAMEOVER:
			gGameOverScene.RenderDebug();
			break;
		}
	}

	//プレイヤーの描画
	//player.Render(100, 200);
	/*float sc=94;
	sc /= tesuto.GetHeight();
	tesuto.RenderScale(0, 0,sc);*/

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
MofBool CGameApp::Release(void){

	gTitleScene.Release();
	gGameScene.Release();
	gSkyGameScene.Release();
	gGameOverScene.Release();
	gGameClearScene.Release();
	gOptionScene.Relase();
	//player.Release();
	//tesuto.Release();

	/*switch (gScene)
	{
	case SCENENO_TITLE:		gTitleScene.Release();		break;
	case SCENENO_GAME:		gGameScene.Release();		break;
	case SCENENO_GAMEClear:  gGameClearScene.Release(); break;
	case SCENENO_GAMEOVER: gGameOverScene.Release(); break;
	case SCENENO_Option: gOptionScene.Relase(); break;
	}*/

	//g_Stage.Release();
	return TRUE;
}