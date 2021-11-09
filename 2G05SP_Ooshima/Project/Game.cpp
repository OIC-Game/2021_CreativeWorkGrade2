#include	"GameDefine.h"
#include	"Game.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int						gChangeScene;

/**
 * �R���X�g���N�^
 *
 */
CGame::CGame(){
}

/**
 * �f�X�g���N�^
 *
 */
CGame::~CGame(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGame::Load(void){
	//�v���C���[�̑f�ޓǂݍ���
	m_Player.Load();
	//�X�e�[�W�̑f�ޓǂݍ���
	m_Stage.Load("Stage1.txt");
	//�G�������m��
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//�A�C�e���������m��
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//�G�t�F�N�g�̑f��
	m_EffectManager.Load();
	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGame::Initialize(void){
	//�v���[���[�̏�ԏ�����
	m_Player.Initialize();
	//�X�e�[�W�̏�ԏ�����
	m_Stage.Initialize(m_EnemyArray,m_ItemArray);
	//�G�t�F�N�g��Ԃ̏�����
	m_EffectManager.Initialize();
	//�v���C���[�ƓG�ɃG�t�F�N�g�N���X�̐ݒ�
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}

}

/**
 * �X�V
 *
 */
void CGame::Update(void){
	//�f�o�b�O�p
	//�v���[���[�̍X�V
	m_Player.Update();
	//�X�e�[�W�ƃv���[���[�̓����蔻��
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
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
	}
	//�A�C�e���̍X�V
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy))
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
	//�X�e�[�W�̍X�V
	m_Stage.Update(m_Player);
	//F2Key�ŃQ�[���N���A��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		gChangeScene = SCENENO_GAMECLEAR;
	}
	//F3�L�[�ŃQ�[���I�[�o�[��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		gChangeScene = SCENENO_GAMEOVER;
	}
}

/**
 * �`��
 *
 */
void CGame::Render(void){
	//�X�e�[�W�̕`��
	m_Stage.Render();
	//�G�t�F�N�g�̍X�V
	m_EffectManager.Update();
	//�v���[���[�̕`��
	m_Player.Render(m_Stage.GetScrollX(),m_Stage.GetScrollY());
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
	//�v���[���[�̏�ԕ`��
	m_Player.RenderStatus();
	//�G�t�F�N�g�̕`��
	m_EffectManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	CGraphicsUtilities::RenderString(10,10,"�Q�[�����");
	CGraphicsUtilities::RenderString(10,40,"F2�L�[�ŃQ�[���N���A�AF3�L�[�ŃQ�[���I�[�o�[");
}

/**
 * �f�o�b�O�`��
 *
 */
void CGame::RenderDebug(void){
	//�X�e�[�W�̃f�o�b�O�`��
	m_Stage.RenderDebug();
	//�v���[���[�̃f�o�b�O�`��
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//�G�̃f�o�b�O���
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�A�C�e���̃f�o�b�O���
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�G�t�F�N�g�̃f�o�b�O�`��
	m_EffectManager.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

/**
 * ���
 *
 */
void CGame::Release(void){
	//�X�e�[�W�̉��
	m_Stage.Release();
	//�v���[���[�̉��
	m_Player.Release();
	//�G�̉��
	if (m_EnemyArray)
	{
		delete[]m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//�A�C�e���̉��
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//�G�t�F�N�g�̉��
	m_EffectManager.Release();
}