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
	m_ShotWaitSet = 60;
	m_ShotWait = m_ShotWaitSet;
	Secondcount = 0;
	second = 60;
	for (int i = 0; i < ENEMYSHOT_LINE; i++)
	{
		for (int j = 0; j < ENEMYSHOT_COUNT; j++)
		{
			m_ShotArray[i][j].Initialize();
		}
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


	m_PosX += m_SpeedX;
	m_PosY += m_SpeedY;

	if (m_EnemyType == 0)
		NomalEnemyMove();
	if (m_EnemyType == 1)
		StopAndStartMove();
	if (m_EnemyType == 2)
	{
		SlantMove(false);
		NomalEnemyMove();
	}
	if (m_EnemyType == 3)
	{
		SlantMove(true);
		NomalEnemyMove();
	}
	if (m_EnemyType == 4)
	{
		HardEnemyMove(false);
		NomalEnemyMove();
	}
	if (m_EnemyType == 5)
	{
		HardEnemyMove(true);
		NomalEnemyMove();
	}
	

	if (second <= 0)
	{
		Secondcount++;
		second = 60;
	}
	else
	{
		second--;
	}


	//��ʊO�ŏ���
	if(m_PosY >= g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMYSHOT_LINE; i++)
		{
			for (int j = 0; j < ENEMYSHOT_COUNT; j++)
			{
				if (m_ShotArray[i][j].GetShow())
				{
					continue;
				}
				m_ShotWait = m_ShotWaitSet;
				ShotSelect(j);

				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}

	for (int i = 0; i < ENEMYSHOT_LINE; i++)
	{
		for (int j = 0; j < ENEMYSHOT_COUNT; j++)
		{
			m_ShotArray[i][j].Update();
		}
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

	for (int i = 0; i < ENEMYSHOT_LINE; i++)
	{
		for (int j = 0; j < ENEMYSHOT_COUNT; j++)
		{
			m_ShotArray[i][j].Render();
		}
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

	for (int i = 0; i < ENEMYSHOT_LINE; i++)
	{
		for (int j = 0; j < ENEMYSHOT_COUNT; j++)
		{
			m_ShotArray[i][j].RenderDebug();
		}
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

void CEnemy::NomalEnemyMove()
{
	if (m_PosY < 100)
		m_SpeedY = ENEMY_MOVESPEED;
	else
		m_SpeedY = 0;
}

void CEnemy::StopAndStartMove()
{
	int count = (Secondcount % 3);
	if (count < 1)
	{
		m_SpeedX = 0;
		m_SpeedY = ENEMY_MOVESPEED * 1.5;
	}
	else if (count < 3)
	{
		m_SpeedX = 0;
		m_SpeedY = 0;
	}
}

void CEnemy::SlantMove(bool left)
{
	if (left)
	{
		m_SpeedX = -ENEMY_MOVESPEED / 1.1;
	}
	else
	{
		m_SpeedX = ENEMY_MOVESPEED / 1.1;
	}
}

void CEnemy::HardEnemyMove(bool left)
{
	
	if (m_PosX + m_pTexture->GetWidth() > g_pGraphics->GetTargetWidth())
	{
		m_EnemyType = 5;
		m_SpeedX = -1;
	}

	if (m_PosX < 0)
	{
		m_EnemyType = 4;
		m_SpeedX = 1;
	}

	if (left)
	{
		m_SpeedX += -ENEMY_MOVESPEED * 0.02;
	}
	else
	{
		m_SpeedX += ENEMY_MOVESPEED * 0.02;
	}
}

void CEnemy::BossMoveBlack()
{
}

void CEnemy::BossMoveWhite()
{
}




void CEnemy::ShotSelect(int j)
{
	if (m_EnemyType == 0)
	{
		DownBullet(j);
		SlantLeftBullet(j);
		SlantLeftBullet2(j);
		SlantRightBullet(j);
		SlantRightBullet2(j);
		RightBullet(j);
		LeftBullet(j);
	}

	if (m_EnemyType == 1)
	{
		DownBullet(j);
	}

	if (m_EnemyType == 2)
	{
		DownBullet(j);
	}

	if (m_EnemyType == 3)
	{
		DownBullet(j);
	}

	if (m_EnemyType == 4)
	{
		DownBullet(j);
	}

	if (m_EnemyType == 5)
	{
		DownBullet(j);
	}
	
}

void CEnemy::DownBullet(int j)
{
	m_ShotArray[1][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 0, 5);
}

void CEnemy::SlantRightBullet(int j)
{
	m_ShotArray[2][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 2, 5);
}

void CEnemy::SlantRightBullet2(int j)
{
	m_ShotArray[6][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 4, 3);
}

void CEnemy::SlantLeftBullet(int j)
{
	m_ShotArray[3][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), -2, 5);
}

void CEnemy::SlantLeftBullet2(int j)
{
	m_ShotArray[7][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), -4, 3);
}

void CEnemy::RightBullet(int j)
{
	m_ShotArray[4][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 1, 0);
}

void CEnemy::LeftBullet(int j)
{
	m_ShotArray[5][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), -1, 0);
}
