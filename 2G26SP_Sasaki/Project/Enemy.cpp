#include	"Enemy.h"

/**
 * �R���X�g���N�^
 *
 */
CEnemy::CEnemy() 
/*�@���������X�g�@���@�R���X�g���N�^�Ń����o�ϐ��̏�����������
	�N���X�ł̐錾���ɏ������ƁI
*/
:
m_pTexture(NULL) ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_SpeedX(0.0f) ,
m_SpeedY(0.0f) ,
m_bShow(false),
m_HP(2),
m_ShotArray(),
m_ShotWait(0),
m_ShotWaitSet(0)
{
}

/**
 * �f�X�g���N�^
 *
 */
CEnemy::~CEnemy(){
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * �v���C���[�̈ʒu�ȂǏ�Ԃ��������������Ƃ��Ɏ��s����B
 */
void CEnemy::Initialize(void){
	m_PosX = 0;
	m_PosY = 0;
	m_SpeedX = 0;
	m_SpeedY = 0;
	m_bShow = false;
	m_EnemyColor = 1;
}
/**
 * �J�n
 * �����̍��W�Ɉʒu��ݒ肵�āA�\���t���O��true�ɕύX����B
 *
 * ����
 * [in]			px				���˂w���W
 * [in]			py				���˂x���W
 */
void CEnemy::Start(float px,float py ,int encol,int type){
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py - m_pTexture->GetHeight();
	m_EnemyColor = encol;
	m_SpeedX = 0;
	m_SpeedY = 0.4;
	m_bShow = true;
	m_HP = 2;
	m_ShotWaitSet = 40;
	m_ShotWait = m_ShotWaitSet;
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
	m_EnemyType = type;
}

/**
 * �X�V
 *
 */
void CEnemy::Update(void){
	//��\��
	if(!m_bShow)
	{
		return;	//�������^�[��
	}

	if (m_EnemyType == 0)
		NomalEnemyMove();

	//��ʊO�ŏ���
	if(m_PosY >= g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			if (m_ShotArray[i].GetShow())
			{
				continue;
			}
			m_ShotWait = m_ShotWaitSet;
			m_ShotArray[i].Fire(m_PosX + m_pTexture->GetWidth()*0.5f, m_PosY + m_pTexture->GetHeight(), 0, 5);
			break;
		}
	}
	else
	{
		m_ShotWait--;
	}

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}
}

/**
 * �`��
 *
 */
void CEnemy::Render(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX,m_PosY);

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render();
	}
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			i				�G�̔z����ԍ�
 */
void CEnemy::RenderDebug(int i){
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10,70 + i * 24,MOF_XRGB(0,0,0),"�G[%d] %s , �ʒu X : %.0f , Y : %.0f",i + 1,((m_bShow) ? "�\��" : "��\��"),m_PosX,m_PosY);

	//��\��
	if (!m_bShow)
	{
		return;
	}
	CGraphicsUtilities::RenderRect(GetRect(), MOF_XRGB(255, 0, 0));

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render();
	}
}
void CEnemy::Damage(int dmg)
{
	m_HP -= dmg;
	if (m_HP <= 0)
	{
		m_bShow = false;
	}
}

	//��ʉ��Ɍ������Ĉړ�
void CEnemy::NomalEnemyMove()
{
	m_PosY += m_SpeedY;
}
