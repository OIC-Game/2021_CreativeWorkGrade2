/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"Game.h"
#include	"Title.h"
#include	"GameClear.h"
#include    "GameOver.h"

//���݂̃V�[��
int						gScene = SCENENO_GAME;
//�ύX����V�[��
int						gChangeScene = SCENENO_GAME;

//�e�V�[���N���X
CTitle					gTitleScene;
CGame					gGameScene;
CGameClear				gGameClearScene;
CGameOver				gGameOverScene;

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");
	
	//�V�[���̕K�v���\�[�X��S�ēǂݍ���
	gTitleScene.Load();
	gGameScene.Load();
	gGameClearScene.Load();
	gGameOverScene.Load();
	//�ŏ��Ɏ��s�����V�[���̏�����
	gGameScene.Initialize();

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
	switch (gScene)
	{
	case SCENENO_TITLE:
		gTitleScene.Update();
		break;
	case SCENENO_GAME:
		gGameScene.Update();
		break;
	case SCENENO_GAMECLEAR:
		gGameClearScene.Update();
		break;
	case SCENENO_GAMEOVER:
		gGameOverScene.Update();
		break;
	}

	//�V�[���ύX���������ꍇ�ύX��V�[���̏�����
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
		case SCENENO_GAMECLEAR:
			gGameClearScene.Initialize();
			break;
		case SCENENO_GAMEOVER:
			gGameOverScene.Initialize();
			break;
		}
		gScene = gChangeScene;
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
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	//�V�[���ԍ��ɂ���ĕ`��
	switch (gScene)
	{
	case SCENENO_TITLE:
		gTitleScene.Render();
		break;
	case SCENENO_GAME:
		gGameScene.Render();
		break;
	case SCENENO_GAMECLEAR:
		gGameClearScene.Render();
		break;
	case SCENENO_GAMEOVER:
		gGameOverScene.Render();
		break;
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
MofBool CGameApp::Release(void){
	gTitleScene.Release();
	gGameScene.Release();
	gGameClearScene.Release();
	gGameOverScene.Release();
	return TRUE;
}