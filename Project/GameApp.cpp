#include	"GameApp.h"
#include	"GameDefine.h"
#include	"Title.h"
#include	"Game.h"
#include	"GameClear.h"
#include	"GameOver.h"


//���݂̃V�[��
int				gScene = SCENENO_TITLE;
//�ύX����V�[��
int				gChangeScene = SCENENO_TITLE;

//�e�V�[���N���X
CTitle					gTitleScene;
CGame					gGameScene;
CGameClear				gGameClearScene;
CGameOver				gGameOverScene;

//�f�o�b�N�\���t���O
bool					g_bDebug = false;


MofBool CGameApp::Initialize(void) {
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	//�V�[���̕K�v���\�[�X��S�ēǂݍ���
	gTitleScene.Load();
	gGameScene.Load();
	gGameClearScene.Load();
	gGameOverScene.Load();

	
	gScene = SCENENO_TITLE;

	return TRUE;
}

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
	//�f�o�b�O�\���̐؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = ((g_bDebug) ? false : true);
	}
	return TRUE;
}

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
			gGameClearScene.Render();
			break;
		case SCENENO_GAMEOVER:
			gGameOverScene.Render();
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
				gGameClearScene.RenderDebug();
				break;
			case SCENENO_GAMEOVER:
				gGameOverScene.RenderDebug();
				break;
			}

			
		}
		//�`��̏I��
		g_pGraphics->RenderEnd();
		return TRUE;
	}


		MofBool CGameApp::Release(void) {
			

			gTitleScene.Release();
			gGameScene.Release();
			gGameClearScene.Release();
			gGameOverScene.Release();
			return TRUE;		
}
