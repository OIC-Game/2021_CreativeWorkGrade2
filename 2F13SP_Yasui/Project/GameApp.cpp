/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"Player.h"
#include	"Stage.h"
#include	"Game.h"
#include	"Title.h"
#include	"GameOver.h"
#include	"Infomation.h"
#include	"SceneBase.h"

extern int						stage_number;
bool							bossWarpFlg;

CSceneBase* g_pSceneBase = NULL;

bool	g_Debug = false;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	
	CUtilities::SetCurrentDirectory("Resource");
	bossWarpFlg = false;
	stage_number = 3;
	g_pSceneBase = new CTitle;
	g_pSceneBase->SetStageNumber(3);
	g_pSceneBase->Load();
	g_pSceneBase->Initialize();
	
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

	//シーン番号によって更新
	g_pSceneBase->Update();

	//シーン変更があった場合変更先シーンの初期化
	if (g_pSceneBase->IsEnd())
	{
		int NextScene = g_pSceneBase->GetNextScene();
		g_pSceneBase->Release();
		if (g_pSceneBase)
		{
			delete g_pSceneBase;
			//g_pSceneBase = NULL;
		}
		switch (NextScene)
		{
		case SCENENO_TITLE:
			g_pSceneBase = new CTitle;
			break;
		case SCENENO_GAME:
			g_pSceneBase = new CGame;
			g_pSceneBase->SetStageNumber(stage_number);
			//g_pSceneBase->SetStageNumber(STAGE_LAST);
			break;
		case SCENENO_GAMEOVER:
			g_pSceneBase = new CGameOver;
			break;
		case SCENENO_INFOMATION:
			g_pSceneBase = new CInfomation;
			break;
		}

		g_pSceneBase->Load();
		g_pSceneBase->Initialize();
	}



	if (g_pInput->IsKeyPush(MOFKEY_LSHIFT))
	{
		g_Debug = ((g_Debug) ? false : true);
	}

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
	g_pGraphics->ClearTarget(0.0f,0.0f,0.0f,0.0f,0.0f,0);

	g_pSceneBase->Render();

	if (g_Debug)
	{
		g_pSceneBase->RenderDebug();
	}
	
	
	CGraphicsUtilities::RenderString(100, 25, "MARIWO");
	CGraphicsUtilities::RenderString(600, 25, "WORLD");
	CGraphicsUtilities::RenderString(800, 25, "TIME");
	
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
	if (g_pSceneBase)
	{
		g_pSceneBase->Release();
		delete g_pSceneBase;
		g_pSceneBase = NULL;
	}
	return TRUE;
}