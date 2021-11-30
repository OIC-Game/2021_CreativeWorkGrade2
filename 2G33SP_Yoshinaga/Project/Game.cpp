#include "GameDefine.h"
#include "Game.h"


//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;





CGame::CGame() {
}


CGame::~CGame() {
}


bool CGame::Load(void) {

	//�v���C���[�f�ޓǂݍ���
	m_Player.Load();


	//�X�e�[�W�̑f�ޓǂݍ���
	m_Stage.Load("Stage1.txt");

	
	
	//�G�������m��
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	return true;

	}


void CGame::Initialize(void) {

	bool HedColflg = false;

	m_Player.Initialize();

	m_Stage.Initialize(m_EnemyArray);

	//�X�e�[�W�̏�ԏ�����
	m_Stage.Initialize(m_EnemyArray);

	GameBGM.Load("FantasyBGM.mp3");

	GameBGM.SetLoop(TRUE);
	GameBGM.Play();
		

}

void CGame::Update(void) {
	
	//�v���C���[�̈ړ�����
	m_Player.Update();


	//�X�e�[�W�ƃv���C���[�̓����蔻��
	float ox = 0, oy = 0;
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}	

	//�G�̍X�V
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}

		m_EnemyArray[i].Update();

		float ox = 0, oy = 0;


		for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
		{
			//�G�̓��Ƃ̐ڐG��
			if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
			{
				m_EnemyArray[i].CollisionStage(ox, oy);
			}

			/*//�G�̑̂Ƃ̐ڐG��
			if (m_Player.CollisionEnemyBody(m_EnemyArray[i]))
			{
				m_Player.Damage();
			}*/
		}


		//
		if (m_Player.CollisionEnemyHed(m_EnemyArray[i]))
		{

			m_Player.CollisionJump();

			m_EnemyArray[i].Damage();
		}

	}


	//�X�e�[�W�̃X�N���[������
	m_Stage.Update(m_Player);

	//F2�L�[�ŃQ�[���N���A��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		gChangeScene = SCENENO_GAMECLEAR;
		GameBGM.Stop();
	}
	//F3�L�[�ŃQ�[���I�[�o�[��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		gChangeScene = SCENENO_GAMEOVER;
		GameBGM.Stop();
	}

	//���ɗ�������Q�[���I�[�o�[��ʂ�
	if (m_Player.GetPosY()>g_pGraphics->GetTargetHeight())
	{
		gChangeScene = SCENENO_GAMEOVER;
		GameBGM.Stop();
	}

	CRectangle e_Rect = m_EnemyArray->GetRect();
	CRectangle p_Rect = m_Player.GetRect();

	
	int PLayerLife = m_Player.GetLife();

	if (PLayerLife == 0)
	{
		gChangeScene = SCENENO_GAMEOVER;
	}

	

}

void CGame::Render(void) {
	m_Stage.Render();
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());


	//�G�̕`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
}

void CGame::RenderDebug(void)
{

	//�X�e�[�W�̃f�o�b�O�`��
	m_Stage.RenderDebug();

	m_Player.renderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());

	//�G�̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
}

void CGame::Release(void) {
	//�e�N�X�`���̉��
	m_Stage.Release();
	m_Player.Release();
	GameBGM.Release();

	//�G�̊J��
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}


}








