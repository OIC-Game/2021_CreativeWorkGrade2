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

#include    "Title.h"
#include"Game.h"
#include"GameOver.h"
#include"GameClear.h"
//���݂̃V�[��
int						gScene = SCENENO_TITLE;
//�ύX����V�[��
int                     gChangeScene = SCENENO_TITLE;

CTitle		g_Title;
CGame		g_Game;
CGameOver g_GameOver;
CGameClear g_GameClear;

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");
	g_Title.Load();
	g_Game.Load();
	g_Title.Initialize();
	g_GameOver.Load();
	g_GameClear.Load();
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
	g_Title.Release();
	g_Game.Release();
	g_GameOver.Release();
	g_GameClear.Release();
	return TRUE;
}