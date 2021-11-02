#include "GameApp.h"
#include "Title.h"
#include "Game.h"

//���݂̃V�[��
int			gScene = SCENENO_TITLE;
//�ύX����V�[��
int			gChangeScene = SCENENO_TITLE;

//�e�V�[���N���X
CTitle		gTitleScene;
CGame		gGameScene;

MofBool CGameApp::Initialize(void) {
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	//�ŏ��Ɏ��s�����V�[���̏�����
	gTitleScene.Initialize();
	//gGameScene.Initialize();
	return TRUE;
}

MofBool CGameApp::Update(void) {
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
		}
		gScene = gChangeScene;
	}

	return TRUE;
}

MofBool CGameApp::Render(void) {
	g_pGraphics->RenderStart();

	g_pGraphics->ClearTarget(0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0);

	//�V�[���ԍ��ɂ���ĕ`��
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
