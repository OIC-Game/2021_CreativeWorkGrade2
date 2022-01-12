/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
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
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
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
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	//�V�[���ԍ��ɂ���čX�V
	g_pSceneBase->Update();

	//�V�[���ύX���������ꍇ�ύX��V�[���̏�����
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
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,0.0f,0.0f,0.0f,0);

	g_pSceneBase->Render();

	if (g_Debug)
	{
		g_pSceneBase->RenderDebug();
	}
	
	
	CGraphicsUtilities::RenderString(100, 25, "MARIWO");
	CGraphicsUtilities::RenderString(600, 25, "WORLD");
	CGraphicsUtilities::RenderString(800, 25, "TIME");
	
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
	if (g_pSceneBase)
	{
		g_pSceneBase->Release();
		delete g_pSceneBase;
		g_pSceneBase = NULL;
	}
	return TRUE;
}