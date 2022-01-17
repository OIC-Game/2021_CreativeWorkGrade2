#include "Game.h"
#include    "Stage1.h"

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

	//�f�o�b�N�p
	//�X�e�[�W�̃X�N���[���l
	//g_Stage.MoveScroll(4800);
}

void CGame::Update(void) {
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
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && (g_Player.IsDead() || g_bclear))
	{
		g_bclear = false;
		//�Q�[�����̃I�u�W�F�N�g��S�ď����l
		g_Player.Initialize();
		g_Stage.Initialize(g_Stg1EnemyStart, g_Stg1EnemyCount);
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			g_EnemyArray[i].Initialize();
		}
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
		CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_BLACK, "Z�L�[�ŐF�ϊ�");
	}
	else
	{
		CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_WHITE, "Z�L�[�ŐF�ϊ�");
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

	if (g_Player.IsDead())
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "�Q�[���I�[�o�[  :  Enter�L�[�ł�����x�ŏ�����");
	}
	else if (g_bclear)
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "�Q�[���N���A: ENTER�L�[�ł�����x�ŏ�����");
	}


	//�`��̏I��
	g_pGraphics->RenderEnd();
}

void CGame::Release(void) {
	//�v���C���[�̉��
	g_Player.Release();

	//�X�e�[�W�̉��
	g_Stage.Release();

	//m_EnemyTexture.Release();
}