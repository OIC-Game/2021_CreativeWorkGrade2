/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
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
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//gpScene = new CTitle;
	gpScene = new CGame;
	gpScene->Initialize();
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
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {

	gpScene->Render();

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	if (gpScene)
	{
		delete gpScene;
		gpScene = NULL;
	}
	return TRUE;
}