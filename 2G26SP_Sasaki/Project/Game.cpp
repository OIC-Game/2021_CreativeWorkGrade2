//#include "Game.h"
//
//CGame::CGame()
//{
//}
//
//CGame::~CGame()
//{
//}
//
//void CGame::Initialize()
//{
//	//���\�[�X�z�u�f�B���N�g���̐ݒ�
//	CUtilities::SetCurrentDirectory("Resource");
//
//	//�v���C���[�f�ނ̓ǂݍ���
//	g_Player.Load();
//
//	//�X�e�[�W�f�ނ̓ǂݍ���
//	g_Stage.Load();
//
//	//�v���C���[�̏�ԏ�����
//	g_Player.Initialize();
//
//	//�X�e�[�W�̏�ԏ�����
//	g_Stage.Initialize(g_Stg1EnemyStart, g_Stg1EnemyCount);
//
//	for (int i = 0; i < ENEMY_COUNT; i++)
//	{
//		g_EnemyArray[i].Initialize();
//	}
//
//	return TRUE;
//}
//
//void CGame::Update()
//{
//�L�[�̍X�V
//g_pInput->RefreshKey();
//
//�X�e�[�W�̍X�V
//g_Stage.Update(g_EnemyArray, ENEMY_COUNT);
//
//�v���C���[�̍X�V
//g_Player.Update();
//
//�G�̍X�V
//for (int i = 0; i < ENEMY_COUNT; i++)
//{
//	g_EnemyArray[i].Update();
//}
//
//if (!g_bclear && g_Stage.IsAllEnemy())
//{
//	�G����̂ł���ʏ�ɏo�Ă����false��
//	bool btmp = true;
//	�o�����̂��ׂĂ̓G�ɑ΂��ČJ��Ԃ�
//	for (int i = 0; i < ENEMY_COUNT; i++)
//	{
//		�G���o�Ă��邩�ǂ����̊m�F
//		if (g_EnemyArray[i].GetShow())
//		{
//			btmp = false;
//			�G����̂ł��Ȃ̂ŁA2�̖ڈȍ~�̏o�Ă���G�����邩�͖��ɂȂ�Ȃ��B
//			break;
//		}
//	}
//	�G����̂��o�Ă��Ȃ����true,��̂ł��o�Ă����false
//	g_bclear = btmp;
//}
//
//�f�o�b�O�\���̐؂�ւ�
//if (g_pInput->IsKeyPush(MOFKEY_F1))
//{
//	g_bDebug = ((g_bDebug) ? false : true);
//}
//if (g_bDebug)
//{
//	if (g_pInput->IsKeyPush(MOFKEY_1))
//	{
//		for (int i = 0; i < ENEMY_COUNT; i++)
//		{
//			g_EnemyArray[i].Damage(5);
//		}
//	}
//}
//
//�Q�[���I�[�o�[�\���܂��̓Q�[���N���A�̎���Enter�ŏ����l
//if (g_pInput->IsKeyPush(MOFKEY_RETURN) && (g_Player.IsDead() || g_bclear))
//{
//	g_bclear = false;
//	�Q�[�����̃I�u�W�F�N�g��S�ď����l
//	g_Player.Initialize();
//	g_Stage.Initialize(g_Stg1EnemyStart, g_Stg1EnemyCount);
//	for (int i = 0; i < ENEMY_COUNT; i++)
//	{
//		g_EnemyArray[i].Initialize();
//	}
//}
//}
//
//void CGame::Render()
//{
//}
//
//void CGame::Release()
//{
//}
