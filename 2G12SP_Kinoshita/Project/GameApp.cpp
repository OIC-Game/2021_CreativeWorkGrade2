/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
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

//���݂̃V�[��
int           gScene = SCENENO_TITLE;

int           gChangeScene = SCENENO_TITLE;
//�e�V�[���N���X
CTitle       gTitleScene;
CGame        gGameScene;
CGameOver    gGameOverScene;
CGameClear   gGameClearScene;
COption      gOptionScene;
CSkyGame     gSkyGameScene;

//�v���C���[
CTexture   player;

//CTexture   tesuto;
bool   g_bDebug = false;

//�X�e�[�W
//CCStage   g_Stage;
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	CUtilities::SetCurrentDirectory("Resource");

	//�v���C���[�̑f�ޓǂݍ���
	//player.Load("Run (1).png");

	//�X�e�[�W�̑f�ޓǂݍ���
	//g_Stage.Lord();
   
	//�v���C���[�̏�ԏ�����
	

	//�X�e�[�W�̏�ԏ�����
	//g_Stage.Initialize();

	//�V�[���̕K�v���\�[�X
	gTitleScene.Load();
	gGameScene.load();
	gSkyGameScene.load();
	gGameOverScene.Load();
	gGameClearScene.Load();
	gOptionScene.Load();

	//�ŏ��̎��s�����V�[���̏�����
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
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
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
	

	//�X�e�[�W�̍X�V
	//g_Stage.Update();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	//�X�e�[�W�̕`��
	//g_Stage.Render();

	//�V�[���ԍ��ɂ���ĕ`��
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
		//�V�[���ԍ��ɂ���ĕ`��
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

	//�v���C���[�̕`��
	//player.Render(100, 200);
	/*float sc=94;
	sc /= tesuto.GetHeight();
	tesuto.RenderScale(0, 0,sc);*/

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