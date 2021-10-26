/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
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
//�ύX����V�[��
int						gChangeScene = SCENENO_TITLE;

//�e�V�[���N���X
CTitle					gTitleScene;
CGame					gGameScene;
CInformation			gInfoScene;
CGameOver				gGameOverScene;
CTimeUp					gTimeUpScene;
bool					g_bDebug = false;
int						g_LifeCount;
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
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
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
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
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
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
		//�V�[���ԍ��ɂ���ĕ`��
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
	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	gTitleScene.Release();
	gGameScene.Release();
	gInfoScene.Release();
	gGameOverScene.Release();
	gTimeUpScene.Release();
	return TRUE;
}