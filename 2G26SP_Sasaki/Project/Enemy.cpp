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
 * [in]			encol			�G�F
 * [in]			type			�G�̎��
 * [in]			hp				�̗�
 */
void CEnemy::Start(float px,float py ,int encol,int type,int hp){
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py - m_pTexture->GetHeight();
	m_EnemyColor = encol;
	m_SpeedX = 0;
	m_SpeedY = ENEMY_MOVESPEED;
	ShotScaleX = 1;
	ShotScaleY = 1;
	m_bShow = true;
	m_HP = hp;
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

	//����ł���ʊO�ɍs���܂Œe�͏����Ȃ�
	for (int i = 0; i < ENEMYSHOT_LINE; i++)
	{
		for (int j = 0; j < ENEMYSHOT_COUNT; j++)
		{
			m_ShotArray[i][j].Update();
		}
	}

	//��\��
	if(!m_bShow)
	{
		return;	//�������^�[��
	}


	m_PosX += m_SpeedX;
	m_PosY += m_SpeedY;

	/*
		�O�@�ʏ�G
		�P�@��~���ړ�
		�Q�@�E���ړ�
		�R�@�����ړ�
		�S�@�E�����ړ�
		�T�@�������ړ�
		
		�W�@BOSS����
		�X�@BOSS�E��
		�P�O�@BOSS��
	*/

	if (m_EnemyType == 0)
	{
		NomalEnemyMove();
	}
	if (m_EnemyType == 1)
	{
		StopAndStartMove();
	}
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
	if (m_EnemyType == 8)
	{
		if (!m_bStart)
			ShowMove();
		else
			BossMoveBlackLeft();
	}
	if (m_EnemyType == 9)
	{
		if(!m_bStart)
			ShowMove();
		else
			BossMoveBlackRight();
	}
	if (m_EnemyType == 10)
	{
		if(!m_bStart)
			ShowMove();
		else
			BossMoveWhite();
	}
	

	if (second <= 0)
	{
		Secondcount++;
		freeSecond++;
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
}

/**
 * �`��
 *
 */
void CEnemy::Render(void){

	//����ł��e�͏����Ȃ�
	for (int i = 0; i < ENEMYSHOT_LINE; i++)
	{
		for (int j = 0; j < ENEMYSHOT_COUNT; j++)
		{
			m_ShotArray[i][j].Render(ShotScaleX, ShotScaleY);
		}
	}

	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->RenderScale(m_PosX,m_PosY,1);

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

void CEnemy::EnemyDead()
{
	m_bShow = false;
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
	m_SpeedY = ENEMY_MOVESPEED;
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

//True�ō��ړ��Afalse�ŉE�ړ�
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

//True�ō��ړ��Afalse�ŉE�ړ�
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

void CEnemy::BossMoveBlackLeft()
{
	int count = (Secondcount % 8);
	if (count < 1)
	{
		m_SpeedX = 0;
		m_SpeedY = ENEMY_MOVESPEED * 0.5;
	}
	else if (count < 3)
	{
		m_SpeedX = -ENEMY_MOVESPEED * 0.5;
		m_SpeedY = 0;
	}
	else if (count < 5)
	{
		m_SpeedX = 0;
		m_SpeedY = -ENEMY_MOVESPEED * 0.5;
	}
	else if (count < 7)
	{
		m_SpeedX = ENEMY_MOVESPEED * 0.5;
		m_SpeedY = 0;
	}
	else if (count < 8)
	{
		m_SpeedX = 0;
		m_SpeedY = ENEMY_MOVESPEED * 0.5;
	}
}

void CEnemy::BossMoveBlackRight()
{
	int count = (Secondcount % 12);
	if (count < 2)
	{
		m_SpeedX = 0;
		m_SpeedY = -ENEMY_MOVESPEED * 0.5;
	}
	else if (count < 8)
	{
		m_SpeedX = 0;
		m_SpeedY = ENEMY_MOVESPEED * 0.5;
	}
	else if (count < 12)
	{
		m_SpeedX = 0;
		m_SpeedY = -ENEMY_MOVESPEED * 0.5;
	}

	//�ǒe�̑傫��
	ShotScaleX += freeSecond;
	if (ShotScaleY < 0.7)
		ShotScaleY -= Secondcount * 0.2;
}

void CEnemy::BossMoveWhite()
{
	int count = (Secondcount % 4);
	if (count < 1)
	{
		m_SpeedX = ENEMY_MOVESPEED * 0.5;
		m_SpeedY = 0;
	}
	else if (count < 3)
	{
		m_SpeedX = -ENEMY_MOVESPEED * 0.5;
		m_SpeedY = 0;
	}
	else if(count < 4)
	{
		m_SpeedX = ENEMY_MOVESPEED * 0.5;
		m_SpeedY = 0;
	}
}

void CEnemy::ShowMove()
{
	if (m_PosY <= 50)
		m_SpeedY = ENEMY_MOVESPEED;
	else
	{
		m_bStart = true;
		Secondcount = 0;
		second = 60;
	}
}


/*
	�O�@�ʏ�G
	�P�@��~���ړ�
	�Q�@�E���ړ�
	�R�@�����ړ�
	�S�@�E�����ړ�
	�T�@�������ړ�

	�W�@BOSS����
	�X�@BOSS�E��
	�P�O�@BOSS��
*/

void CEnemy::ShotSelect(int j)
{
	if (m_EnemyType == 0)
	{
		DownBullet(j);
	}

	if (m_EnemyType == 1)
	{
		DownBullet(j);
	}

	if (m_EnemyType == 2)
	{
		DownBullet(j);
		SlowBullet(j);
		SlantRightBullet4(j);
	}

	if (m_EnemyType == 3)
	{
		DownBullet(j);
		SlowBullet(j);
		SlantLeftBullet4(j);
	}

	if (m_EnemyType == 4)
	{
		SlowBullet(j);
		SlantRightBullet3(j);
		SlantLeftBullet3(j);
	}

	if (m_EnemyType == 5)
	{
		SlowBullet(j);
		SlantRightBullet3(j);
		SlantLeftBullet3(j);
	}
	
	if (m_EnemyType == 8)
	{
		if (m_bStart)
		{
			DownBullet(j);
			SlantRightBullet2(j);
			SlantRightBullet4(j);
			SlantRightBullet6(j);
			SlantLeftBullet2(j);
			SlantLeftBullet4(j);
			SlantLeftBullet6(j);
		}
	}
	if (m_EnemyType == 9)
	{
		if (m_bStart)
		{
			if (!m_ShotArray[16][0].GetShow())
			{
				WallBullet(j);
				ShotScaleX = 1;
				freeSecond = 0; 
			}
		}
	}
	if (m_EnemyType == 10)
	{
		if (m_bStart)
		{
			DownBullet(j);
			SlantRightBullet1(j);
			SlantRightBullet2(j);
			SlantRightBullet3(j);
			SlantRightBullet4(j);
			SlantRightBullet5(j);
			SlantRightBullet6(j);
			SlantLeftBullet1(j);
			SlantLeftBullet2(j);
			SlantLeftBullet3(j);
			SlantLeftBullet4(j);
			SlantLeftBullet5(j);
			SlantLeftBullet6(j);
			RightBullet(j);
			LeftBullet(j);
		}
	}
}

void CEnemy::DownBullet(int j)
{
	m_ShotArray[0][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 0, 2.8,0);
}

void CEnemy::SlantRightBullet1(int j)
{
	m_ShotArray[1][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 0.5, 2.6,0);
}

void CEnemy::SlantRightBullet2(int j)
{
	m_ShotArray[2][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 1, 2.4,0);
}

void CEnemy::SlantRightBullet3(int j)
{
	m_ShotArray[3][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 1.5, 2.2,0);
}

void CEnemy::SlantRightBullet4(int j)
{
	m_ShotArray[4][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 2, 2,0);
}

void CEnemy::SlantRightBullet5(int j)
{
	m_ShotArray[5][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 2.5, 1.8, 0);
}

void CEnemy::SlantRightBullet6(int j)
{
	m_ShotArray[6][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 3, 1.6, 0);
}

void CEnemy::SlowBullet(int j)
{
	m_ShotArray[15][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 0, 1.4, 0);
}

void CEnemy::SlantLeftBullet1(int j)
{
	m_ShotArray[7][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), -0.5, 2.6, 0);
}

void CEnemy::SlantLeftBullet2(int j)
{
	m_ShotArray[8][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), -1, 2.4, 0);
}

void CEnemy::SlantLeftBullet3(int j)
{
	m_ShotArray[9][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), -1.5, 2.2, 0);
}

void CEnemy::SlantLeftBullet4(int j)
{
	m_ShotArray[10][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), -2, 2, 0);
}

void CEnemy::SlantLeftBullet5(int j)
{
	m_ShotArray[11][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), -2.5, 1.8, 0);
}

void CEnemy::SlantLeftBullet6(int j)
{
	m_ShotArray[12][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), -3, 1.6, 0);
}

void CEnemy::RightBullet(int j)
{
	m_ShotArray[13][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 3.5, 1.4,0);
}

void CEnemy::LeftBullet(int j)
{
	m_ShotArray[14][j].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), -3.5, 1.4,0);
}

void CEnemy::WallBullet(int j)
{
	m_ShotArray[16][0].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f, m_PosY + m_pTexture->GetHeight(), 0, 1.5, 1);
}
