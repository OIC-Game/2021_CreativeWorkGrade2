#include "Game.h"
#include "GameDefine.h"

//�ύX����V�[��
extern int						gChangeScene;

int								gStage = STAGENO_01;
CGame::CGame(){
}

CGame::~CGame(){
}

bool CGame::Load(void){
	//�v���C���[�f�ނ̓ǂݍ���
	m_Player.Load();
	//�X�e�[�W�̑f�ޓǂݍ���
	switch (gStage)
	{
		case STAGENO_01:
		m_Stage.Load("Stage01.txt");
		break;
		case STAGENO_02:
		m_Stage.Load("Stage02.txt");
		break;
		case STAGENO_03:
		m_Stage.Load("Stage03.txt");
		break;
	}
	//�G�������m��
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//�A�C�e���������m��
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//�|�b�v�A�C�e���̑f�ޓǂݍ���
	m_PoPItemManager.Load();
	//UI�̑f�ޓǂݍ���
	m_UI.Load();
	return true;
}

void CGame::Initialize(void){
	//�v���C���[�̏�ԏ�����
	m_Player.Initialize();
	//�X�e�[�W�̏�ԏ�����
	switch (gStage)
	{
		case STAGENO_01:
			m_Stage.Initialize("Stage01.txt", m_EnemyArray, m_ItemArray);
			break;
		case STAGENO_02:
			m_Stage.Initialize("Stage02.txt", m_EnemyArray, m_ItemArray);
			break;
		case STAGENO_03:
			m_Stage.Initialize("Stage03.txt", m_EnemyArray, m_ItemArray);
			break;
	}
	m_PoPItemManager.Initialize();
	m_Stage.SetPoPItemManager(&m_PoPItemManager);
}

void CGame::Update(void){
	//�v���C���[�̍X�V
	m_Player.Update(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	
	//�X�e�[�W�ƃv���C���[�̓����蔻��
	float ox = 0, oy = 0;
	int popItemNo = 0;
	if (m_Stage.Collision(m_Player.GetRect(),m_Player, ox, oy,popItemNo))
	{
		m_Player.CollisionStage(ox, oy);
		for (int i = 0; i < m_Stage.GetItemCount(); i++)
		{
			m_ItemArray[i].PoPItem(popItemNo);
		}
	}
	//�G�̍X�V
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update(m_Stage.GetScrollX(), m_Stage.GetScrollY());
		for (int s = 0; s < m_Stage.GetEnemyCount(); s++)
		{
			CRectangle ene = m_EnemyArray[i].GetRect();
			CRectangle left = m_EnemyArray[s].Left();
			CRectangle right = m_EnemyArray[s].Right();
			if (m_EnemyArray[s].GetKame()&&m_EnemyArray[s].GetMove())
			{
				if (ene.CollisionRect(left))
				{
					m_EnemyArray[i].EnemyDamege();
				}
				else if (ene.CollisionRect(right))
				{
					m_EnemyArray[i].EnemyDamege();
				}
			}
			else
			{
				if (ene.CollisionRect(left))
				{
					m_EnemyArray[i].CollisionEnemy();
				}
				else if (ene.CollisionRect(right))
				{
					m_EnemyArray[i].CollisionEnemy();
				}
			}
		}

		if (gStage == STAGENO_03)
		{
			CRectangle r = m_EnemyArray[i].GetRect();
			r.Bottom += 10;
			if (m_EnemyArray[i].GetMoveX() < 0 && !m_Stage.IsGround(r.Left - 5, r.Bottom))
			{
				m_EnemyArray[i].SetMoveDir(false);
			}
			if (m_EnemyArray[i].GetMoveX() > 0 && !m_Stage.IsGround(r.Right + 5, r.Bottom))
			{
				m_EnemyArray[i].SetMoveDir(true);
			}
		}
		
		float ox = 0, oy = 0;
		int popItemNo = 0;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), m_Player, ox, oy,popItemNo))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
	}
	//�A�C�e���̍X�V
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Pop(m_Stage.GetScrollX(), m_Stage.GetScrollY());
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		int PopItemNo = 0;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), m_Player, ox, oy,popItemNo))
		{
			m_ItemArray[i].CollisionStage(ox, oy);
		}
	}
	//�����蔻��̎��s
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_Player.CollisionItem(m_ItemArray[i]);
	}

	//�e�ƃX�e�[�W�̓����蔻��
	for (int i = 0; i < PLAYERFIRE_COUNT; i++)
	{
		m_WorkFire = m_Player.GetFireArray(i);
		if (!m_WorkFire.GetShow())
		{
			continue;
		}
		float ox = 0, oy = 0;
		if (m_Stage.CollisionPlayerFire(m_WorkFire.GetRect()))
		{
			m_Player.CollisionStageFire(i);
		}
	}

	//�X�e�[�W�̍X�V
	m_Stage.Update(m_Player);

	//�|�b�v�A�C�e���̍X�V
	//for(int i=0;i<)
	m_PoPItemManager.Update();

	//�v���C���[�̃t���O�Ń��g���C��ʁA�Q�[���I�[�o�[��ʂ�
	if (m_Player.IsDead())
	{
		if (m_Player.Retry())
		{
			gChangeScene = SCENENO_GAMERETRY;
		}
		else if(!m_Player.Retry())
		{
			gChangeScene = SCENENO_GAMEOVER;
		}
	}
	//�S�[���t���O�ŃN���A��ʂ�
	if (m_Player.IsClear())
	{
		if (gStage == STAGENO_03)
		{
			gStage = STAGENO_01;
			gChangeScene = SCENENO_GAMECLEAR;
		}
		else
		{
			gStage++;
			gChangeScene = SCENENO_GAMERETRY;
		}
	}
}

void CGame::Render(void){
	//�X�e�[�W�̕`��
	m_Stage.Render();
	//�v���C���[�̕`��
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//�G�̕`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�A�C�e���̕`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�|�b�v�A�C�e���̕`��
	m_PoPItemManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//UI�̕`��
	m_UI.Render();
}

void CGame::RenderDebug(void){
	//�X�e�[�W�̃f�o�b�O�`��
	m_Stage.RenderDebug();
	//�v���C���[�̃f�o�b�O�`��
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//�G�̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�A�C�e���̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�|�b�v�A�C�e���̃f�o�b�O�`��
	m_PoPItemManager.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

void CGame::Release(void){
	//�X�e�[�W�̉��
	m_Stage.Release();
	//�v���C���[�̉��
	m_Player.Release();
	//�G�̉��
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//�A�C�e���̉��
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//�|�b�v�A�C�e���̉��
	m_PoPItemManager.Release();
	//UI�̉��
	m_UI.Release();
}

