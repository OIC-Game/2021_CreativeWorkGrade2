/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include "Title.h"
#include "Game.h"
//#include "Scene.h"

//int gChangeScene = SCENENO_TITLE;
//int gScene = SCENENO_TITLE;

CSceneBase* gpScene = NULL;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//gpScene = new CTitle;
	gpScene = new CGame;
	gpScene->Initialize();
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

	gpScene->Update();

	if (gpScene->IsEnd()) {
		int change = gpScene->GetNextScene();
		delete gpScene;

		switch (change)
		{
			case SCENENO_TITLE:
				gpScene = new CTitle();
				break;

			case SCENENO_GAME:
				gpScene = new CGame();
				break;
		}

		gpScene->Initialize();
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {

	gpScene->Render();

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	if (gpScene)
	{
		delete gpScene;
		gpScene = NULL;
	}
	return TRUE;
}