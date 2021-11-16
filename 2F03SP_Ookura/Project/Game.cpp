#include	"GameApp.h"
#include	"Game.h"
#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include"GameOver.h"
#include"Stage1.h"
//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;
//�v���C���[
CPlayer		g_Player;
//�G
#define		ENEMY_COUNT					20
CEnemy		g_EnemyArray[ENEMY_COUNT];
//�X�e�[�W
CStage		g_Stage;
//�X�e�[�W�N���A�t���O
bool		g_bClear = false;
//�f�o�b�O�\���t���O
bool		g_bDebug = false;
CGame::CGame():
a(0)
{	
}
CGame::~CGame() {
}
bool CGame::Load(void)
{
	//�v���C���[�̑f�ޓǂݍ���
	g_Player.Load();
	//�X�e�[�W�̑f�ޓǂݍ���
	g_Stage.Load();
	
	return true;
}
void CGame::Initialize(void)
{
	//�v���C���[�̏�ԏ�����
	g_Player.Initialize();
	//�X�e�[�W�̏�ԏ�����
	g_Stage.Initialize(&g_Stg1EnemyStart, g_Stg1EnemyCount);
	//�G�̏�����
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].Initialize();
	}
}

void CGame::Update(void)
{
	//�X�e�[�W�̍X�V
	g_Stage.Update(g_EnemyArray, ENEMY_COUNT);
	//�v���C���[�̍X�V
	g_Player.Update();
	//�G�̍X�V
	CRectangle prec = g_Player.GetRect();
	Vector2 cv = prec.GetCenter();
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].SetTargetPos(cv.x, cv.y);
		g_EnemyArray[i].Update();
	}
	//�����蔻��̎��s
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_Player.Collision(g_EnemyArray[i]);
	}
	//�Q�[���N���A����
	if (!g_bClear && g_Stage.IsAllEnemy())
	{
		bool btmp = true;
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			if (g_EnemyArray[i].IsShow())
			{
				btmp = false;
			}
		}
		g_bClear = btmp;
	}
	//�f�o�b�O�\���̐؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = ((g_bDebug) ? false : true);
	}
	//�Q�[���I�[�o�[�\�����Enter�ŏ��������s��
	//�Q�[���N���A�\�����Enter�ŏ��������s��
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && (g_Player.IsDead() || g_bClear))
	{
		//�N���A�t���O��߂�
		g_bClear = false;
		//�Q�[�����̃I�u�W�F�N�g��S�ď���������
		g_Player.Initialize();
		g_Stage.Initialize(&g_Stg1EnemyStart, g_Stg1EnemyCount);
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			g_EnemyArray[i].Initialize();
		}
	}if (g_pInput->GetGamePadCount())
	{
		LPGamePad pPad = g_pInput->GetGamePad(0);
		pPad->GetPadState();

		if (pPad != nullptr)
		{
			if (pPad->IsKeyPush(2) && (g_Player.IsDead() || g_bClear))
			{
				//�N���A�t���O��߂�
				g_bClear = false;
				//�Q�[�����̃I�u�W�F�N�g��S�ď���������
				g_Player.Initialize();
				g_Stage.Initialize(&g_Stg1EnemyStart, g_Stg1EnemyCount);
				for (int i = 0; i < ENEMY_COUNT; i++)
				{
					g_EnemyArray[i].Initialize();
				}
			}
		}
	}
	//�Q�[���I�[�o�[��ʑJ��
	if (!g_Player.IsDead() == false)
	{
			gChangeScene = SCENENO_GAMEOVER;
	}
	else if (g_bClear)
	{
		gChangeScene = SCENENO_GAMECLEAR;
	}
}

void CGame::Render(void)
{
	//�X�e�[�W�̕`��
	g_Stage.Render();
	//�v���C���[�̕`��
	g_Player.Render();
	//�G�̕`��
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].Render();
	}

	//�f�o�b�O�\��������ꍇ
	if (g_bDebug)
	{
		//�X�e�[�W�̃f�o�b�O�`��
		g_Stage.RenderDebug();
		//�v���C���[�̃f�o�b�O�`��
		g_Player.RenderDebug();
		//�G�̃f�o�b�O�`��
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			g_EnemyArray[i].RenderDebug(i);
		}
	}

	/*/�Q�[���I�[�o�[�\��
	if (g_Player.IsDead())
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "�Q�[���I�[�o�[�@�F�@Enter�L�[�ł�����x�ŏ�����");
	}*/
	//�Q�[���N���A�\��
	/*else if (g_bClear)
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "�Q�[���N���A�@�F�@Enter�L�[�ł�����x�ŏ�����");
	}*/
}

void CGame::RenderDebug(void)
{
}

void CGame::Release(void)
{
	//�v���C���[�̉��
	g_Player.Release();
	//�X�e�[�W�̉��
	g_Stage.Release();
}
