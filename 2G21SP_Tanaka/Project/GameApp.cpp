/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"Player.h"
#include	"Title.h"
#include	"Game.h"
#include	"GameClear.h"
#include	"GameOver.h"
#include	"GameRetry.h"
#include	"GameDefine.h"

//���݂̃V�[��
int						gScene = SCENENO_TITLE;
//�ύX����V�[��
int						gChangeScene = SCENENO_TITLE;

//�e�V�[���N���X
CTitle					gTitleScene;
CGame					gGameScene;
CGameClear				gGameClear;
CGameOver				gGameOver;
CGameRetry				gGameRetry;
//�f�o�b�O�\���t���O
bool					g_bDebug = false;
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");
	//�V�[���̕K�v���\�[�X��S�ēǂݍ���
	gTitleScene.Load();
	gGameScene.Load();
	gGameClear.Load();
	gGameOver.Load();
	gGameRetry.Load();
	gGameRetry.Load();
	//�ŏ��Ɏ��s�����V�[���̏�����
	gTitleScene.Initialize();
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
			gGameClear.Update();
			break;
		case SCENENO_GAMEOVER:
			gGameOver.Update();
			break;
		case SCENENO_GAMERETRY:
			gGameRetry.Update();
	}

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
				gGameClear.Initialize();
				break;
			case SCENENO_GAMEOVER:
				gGameOver.Initialize();
				break;
			case SCENENO_GAMERETRY:
				gGameRetry.Initialize();
				break;
		}
		gScene = gChangeScene;
	}
	//�f�o�b�O�\���̐؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = ((g_bDebug) ? false : true);
	}
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
			gGameClear.Render();
			break;
		case SCENENO_GAMEOVER:
			gGameOver.Render();
			break;
		case SCENENO_GAMERETRY:
			gGameRetry.Render();
			break;
	}

	//�f�o�b�O�\��������ꍇ
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
		case SCENENO_GAMECLEAR:
			gGameClear.RenderDebug();
			break;
		case SCENENO_GAMEOVER:
			gGameOver.RenderDebug();
			break;
		case SCENENO_GAMERETRY:
			gGameRetry.RenderDebug();
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
	gGameClear.Release();
	gGameOver.Release();
	gGameRetry.Release();
	return TRUE;
}