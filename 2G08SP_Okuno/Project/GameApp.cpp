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
#include	"SettingWin.h"

CTitle		g_Title;
CGame		g_Game;
CSettingWin g_SettingWin;

bool		bDebug = false;

int			g_bScene;
int			g_nScene;
int			g_nSceneChange;

CTexture	g_PlTexture;
CGameDefine* g_pGameDefine;

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	CUtilities::SetCurrentDirectory("Resource");

	if (!g_PlTexture.Load("mario1.png")) {
		return false;
	}

	//-----Load-------
	if (!g_Title.Load(&g_PlTexture)) {
		return false;
	}
	if (!g_SettingWin.Load("Settings.txt")) {
		return false;
	}
	if (!g_Game.Load(&g_PlTexture)) {
		return false;
	}

	g_pGameDefine = CGameDefine::GetGameDefine();
	if (!g_pGameDefine->Load()) {
		return false;
	}

	//----Initialize----
	g_Title.Initialize();
	//g_Game.Initialize();
	g_SettingWin.Initialize();

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	DWORD prevTime = timeGetTime();
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	switch (g_nScene)
	{
	case SCENE_TITLE:
		g_Title.Update();
		break;
	case SCENE_GAME:
		g_Game.Update();
		break;
	case SCENE_SETTING:
		g_SettingWin.Update();
		if (g_SettingWin.IsChangeVolume()) {
			g_Game.SetSoundVolume(g_SettingWin.GetSoundVolume());
		}
		break;
	}

	if (g_pInput->IsKeyPush(MOFKEY_F1)) {
		g_nSceneChange = SCENE_SETTING;
	}
	if (g_pInput->IsKeyPush(MOFKEY_F2)) {
		bDebug = !bDebug;
	}

	if (g_nScene != g_nSceneChange) {
		if (g_nScene != SCENE_SETTING) {
			switch (g_nSceneChange)
			{
			case SCENE_TITLE:
				g_Title.Initialize();
				break;
			case SCENE_GAME:
				if (!g_Game.Initialize(g_Title.GetCurrentStage(), g_Title.GetCurrentStageIdx())) g_nSceneChange = g_nScene;
				break;
			case SCENE_SETTING:
				g_SettingWin.Initialize();
				break;
			}
		}
		if (g_nScene == SCENE_GAME) {
			int c_Stage = g_Title.GetClearStageIdx();
			if (g_Game.IsStageClear()) {
				if (c_Stage < g_Game.GetStageIdx()) c_Stage = g_Game.GetStageIdx();
				g_Title.SetClearStage(c_Stage);
			}
			g_Title.SetStageCursor(c_Stage);
		}
		g_bScene = g_nScene;
		g_nScene = g_nSceneChange;
	}

	DWORD time = timeGetTime() - prevTime;
	//MOF_PRINTLOG("%d\n", time);

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
	g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0);

	switch (g_nScene)
	{
	case SCENE_TITLE:
		g_Title.Render();
		break;
	case SCENE_GAME:
		g_Game.Render();
		break;
	case SCENE_SETTING:
		g_SettingWin.Render();
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
MofBool CGameApp::Release(void) {

	g_Title.Release();
	g_Game.Release();

	g_pGameDefine->Release();
	g_PlTexture.Release();

	return TRUE;
}