#include "GameApp.h"
#include "Title.h"
#include "Game.h"

//現在のシーン
int			gScene = SCENENO_TITLE;
//変更するシーン
int			gChangeScene = SCENENO_TITLE;

//各シーンクラス
CTitle		gTitleScene;
CGame		gGameScene;

MofBool CGameApp::Initialize(void) {
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	//最初に実行されるシーンの初期化
	gTitleScene.Initialize();
	//gGameScene.Initialize();
	return TRUE;
}

MofBool CGameApp::Update(void) {
	g_pInput->RefreshKey();

	//シーン番号によって更新
	switch (gScene)
	{
		case SCENENO_TITLE:
			gTitleScene.Update();
			break;
		case SCENENO_GAME:
			gGameScene.Update();
			break;
	}

	//シーン変更があった場合変更先シーンの初期化
	if (gChangeScene != gScene)
	{
		switch (gChangeScene)
		{
			case SCENENO_TITLE:
				gTitleScene.Initialize();
				break;
			case SCENENO_GAME:
				gGameScene.Initialize();
				break;
		}
		gScene = gChangeScene;
	}

	return TRUE;
}

MofBool CGameApp::Render(void) {
	g_pGraphics->RenderStart();

	g_pGraphics->ClearTarget(0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0);

	//シーン番号によって描画
	switch (gScene)
	{
	case SCENENO_TITLE:
		gTitleScene.Render();
		break;
	case SCENENO_GAME:
		gGameScene.Render();
		break;
	}

	g_pGraphics->RenderEnd();

	return TRUE;
}

MofBool CGameApp::Release(void) {

	gTitleScene.Release();
	gGameScene.Release();

	return TRUE;
}
