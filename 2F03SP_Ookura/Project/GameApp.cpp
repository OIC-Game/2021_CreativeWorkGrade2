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

#include    "Title.h"
#include"Game.h"
#include"GameOver.h"
#include"GameClear.h"
//現在のシーン
int						gScene = SCENENO_TITLE;
//変更するシーン
int                     gChangeScene = SCENENO_TITLE;

CTitle		g_Title;
CGame		g_Game;
CGameOver g_GameOver;
CGameClear g_GameClear;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");
	g_Title.Load();
	g_Game.Load();
	g_Title.Initialize();
	g_GameOver.Load();
	g_GameClear.Load();
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
		g_Title.Update();
		break;
	case SCENENO_GAME:
		g_Game.Update();
		break;
	case SCENENO_GAMEOVER:
		g_GameOver.Update();
		break;
	case SCENENO_GAMECLEAR:
		g_GameClear.Update();
		break;
	}
	if (gChangeScene != gScene)
	{
		switch (gChangeScene)
		{
		case SCENENO_TITLE:
			g_Title.Initialize();
			break;
		case SCENENO_GAME:
			g_Game.Initialize();
			break;
		case SCENENO_GAMEOVER:
			g_GameOver.Initialize();
			break;
		case SCENENO_GAMECLEAR:
			g_GameClear.Initialize();
			break;
		}
		gScene = gChangeScene;
	}
		/*if (g_pInput->GetGamePadCount())
		{
			LPGamePad pPad = g_pInput->GetGamePad(0);
			pPad->GetPadState();

			if (pPad != nullptr)
			{
				if (m_ShotWait <= 0) {
					if (pPad->IsKeyHold(2))
					{
						for (int i = 0; i < PLAYERSHOT_COUNT; i++)
						{
							if (m_ShotArray[i].GetShow())
							{
								continue;
							}
							m_ShotWait = PLAYERSHOT_WAIT;
							m_ShotArray[i].Fire(m_PosX + m_Texture.GetWidth() * 0.5f, m_PosY);
							break;
						}
					}
				}
			}*/
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
	switch (gScene)
	{
	case SCENENO_TITLE:
		g_Title.Render();
		break;
	case SCENENO_GAME:
		g_Game.Render();
		break;
	case SCENENO_GAMEOVER:
		g_GameOver.Render();
		break; 
	case SCENENO_GAMECLEAR:
		g_GameClear.Render();
		break;
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
MofBool CGameApp::Release(void){
	g_Title.Release();
	g_Game.Release();
	g_GameOver.Release();
	g_GameClear.Release();
	return TRUE;
}