#include "Game.h"
#include    "Stage1.h"
#include    "GameApp.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;

//�X�e�[�W
CStage     g_Stage;

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Load()
{
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	zButtonBlack.Load("ZButtonBlack.png");
	zButtonWhite.Load("ZButtonWhite.png");
	zChangeCircleBlack.Load("ChangeCircleBlack.png");
	zChangeCircleWhite.Load("ChangeCircleWhite.png");
		
	//�v���C���[�f�ނ̓ǂݍ���
	g_Player.Load();

	//�X�e�[�W�f�ނ̓ǂݍ���
	g_Stage.Load();
}

void CGame::Initialize(void) {

	//�G�f�ނ̓ǂݍ���
	/*if (!m_EnemyTexture.Load("Enemy1.png"))
	{
		return FALSE;
	}*/

	//�v���C���[�̏�ԏ�����
	g_Player.Initialize();

	//�X�e�[�W�̏�ԏ�����
	g_Stage.Initialize(g_Stg1EnemyStart, g_Stg1EnemyCount);

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].Initialize();
	}
	g_bclear = false;

	cnt = 0;
	//�f�o�b�N�p
	//�X�e�[�W�̃X�N���[���l
	//g_Stage.MoveScroll(4800);
}

void CGame::Update(void) {
	if (g_pInput->IsKeyHold(MOFKEY_0))
	{
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			g_EnemyArray[i].EnemyDead();
		}

	}
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	//�X�e�[�W�̍X�V
	g_Stage.Update(g_EnemyArray, ENEMY_COUNT);

	//�v���C���[�̍X�V
	g_Player.Update();

	//�G�̍X�V
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].Update();
	}

	if (!g_bclear && g_Stage.IsAllEnemy())
	{
		//�G����̂ł���ʏ�ɏo�Ă����false��
		bool btmp = true;
		//�o�����̂��ׂĂ̓G�ɑ΂��ČJ��Ԃ�
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			//�G���o�Ă��邩�ǂ����̊m�F
			if (g_EnemyArray[i].GetShow() && g_EnemyArray[i].GetEnemyType() != 8 && g_EnemyArray[i].GetEnemyType() != 9)
			{
				btmp = false;
				//�G����̂ł��Ȃ̂ŁA2�̖ڈȍ~�̏o�Ă���G�����邩�͖��ɂȂ�Ȃ��B
				break;
			}
		}
		//�G����̂��o�Ă��Ȃ����true,��̂ł��o�Ă����false
		g_bclear = btmp;

		//�X�e�[�W�N���A����ƓG�����ׂĎ���
		if (g_bclear)
		{
			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				g_EnemyArray[i].EnemyDead();
			}
		}
	}

	//�Q�[���I�[�o�[�\���܂��̓Q�[���N���A�̎���Enter�ŏ����l
	if(g_Player.IsDead())
	{
		cnt++;
		if (cnt > 70)
		{
			gChangeScene = SCENENO_GAMEOVER;
			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				g_EnemyArray[i].EnemyDead();
				g_EnemyArray[i].EnemyDeadAlpha();
			}
		}
	}

	if (g_bclear)
	{
		cnt++;
		if (cnt > 70)
			gChangeScene = SCENENO_GAMECLEAR;
	}

}

void CGame::Render(void) {
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	//�X�e�[�W�̕`��
	g_Stage.Render();

	//�v���C���[�̕`��
	g_Player.Render();

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].Render();
	}

	if (g_Player.IsPlayerColor() == 1)
	{
		zButtonBlack.Render(g_pGraphics->GetTargetWidth() - zButtonBlack.GetWidth(), g_pGraphics->GetTargetHeight() - zButtonBlack.GetHeight());
		zChangeCircleBlack.RenderRotate(g_pGraphics->GetTargetWidth() - zChangeCircleBlack.GetWidth(), g_pGraphics->GetTargetHeight() - zChangeCircleBlack.GetHeight(),0);
	}
	else
	{
		zButtonWhite.Render(g_pGraphics->GetTargetWidth() - zButtonWhite.GetWidth(), g_pGraphics->GetTargetHeight() - zButtonWhite.GetHeight());
		zChangeCircleWhite.RenderRotate(g_pGraphics->GetTargetWidth() - zChangeCircleWhite.GetWidth(), g_pGraphics->GetTargetHeight() - zChangeCircleWhite.GetHeight(), 0);
	}

	/*if (g_pInput->IsKeyPush(MOFKEY_E))
	{
		if (!g_EnemyArray[0].GetShow())
		{
			g_EnemyArray[0].SetTexture(&m_EnemyTexture);
			g_EnemyArray[0].Start(100, 100);
		}
	}*/

	//�����蔻��̎��s
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_Player.Collision(g_EnemyArray[i]);
	}

	//if (g_Player.IsDead())
	//{
	//	CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "�Q�[���I�[�o�[  :  Enter�L�[�ł�����x�ŏ�����");
	//}
	//else if (g_bclear)
	//{
	//	CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "�Q�[���N���A: ENTER�L�[�ł�����x�ŏ�����");
	//}


	//�`��̏I��
	g_pGraphics->RenderEnd();
}

void CGame::Release(void) {

	zButtonBlack.Release();
	zButtonWhite.Release();
	zChangeCircleBlack.Release();
	zChangeCircleWhite.Release();
	//�v���C���[�̉��
	g_Player.Release();

	//�X�e�[�W�̉��
	g_Stage.Release();

	//m_EnemyTexture.Release();
}