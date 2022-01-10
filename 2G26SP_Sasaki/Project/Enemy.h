#pragma once

#include	"Mof.h"
#include    "EnemyShot.h"

#define		ENEMY_MOVESPEED		1

//�G�̎ˌ��{��
#define		ENEMYSHOT_LINE		20
#define     ENEMYSHOT_COUNT		60

//�G�P�̕��̏����Ǘ�����N���X
class CEnemy {
private:
	CTexture*				m_pTexture;	//�G�摜�ւ̃|�C���^�B���̂�CStage�ŗp�ӁB
	float					m_PosX;		//�����W
	float					m_PosY;		//�����W
	float					m_SpeedX;	//�������̈ړ���
	float					m_SpeedY;	//�������̈ړ���
	bool					m_bShow;	//�\���i�o���j���Ă���ꍇ��true
	int                     m_HP;       //�G��HP
	CEnemyShot              m_ShotArray[ENEMYSHOT_LINE][ENEMYSHOT_COUNT];
	int                     m_ShotWait;
	int                     m_ShotWaitSet;
	int						m_EnemyColor;
	int						m_EnemyType;

	int						Secondcount;
	int						freeSecond;
	int						second;
	bool					m_bStart;

	float					ShotScaleX;
	float					ShotScaleY;

public:
	CEnemy();
	~CEnemy();
	void Initialize(void);				//����������
	void Start(float px,float py,int encol,int type,int hp);		//�o�������ipx,py�̈ʒu����o��������j
	void Update(void);					//�ړ����̍X�V����
	void Render(void);					//�`�揈��
	void RenderDebug(int i);			//�f�o�b�O�`�揈��
	void SetTexture(CTexture* pt){ m_pTexture = pt; }	//�摜�̐ݒ�B�K���Ăяo�����ƁI
	bool GetShow(void){ return m_bShow; }				//�\����Ԃ̎擾
	int	 GetEnemyType(void) { return m_EnemyType; }
	void EnemyDead();

	CRectangle GetRect()
	{
		return CRectangle(m_PosX, m_PosY, m_PosX + m_pTexture->GetWidth(), m_PosY + m_pTexture->GetHeight());
	}

	//�G�̐F��Ԃ�
	int GetEnemyColor(void) { return m_EnemyColor; }

	void Damage(int dmg);

	void SetTexture(CTexture* pt, CTexture* st)
	{
		m_pTexture = pt;
		for (int i = 0; i < ENEMYSHOT_LINE; i++)
		{
			for (int j = 0; j < ENEMYSHOT_COUNT; j++)
			{
				m_ShotArray[i][j].SetTexture(st);
			}
		}
	}

	//n�Ԗڂ̒e���擾�i�e�̎Q�Ƃ�Ԃ��j
	CEnemyShot& GetShot(int n,int m) { return m_ShotArray[n][m]; }

	//�^��
	void NomalEnemyMove();
	//�~�܂��ē���
	void StopAndStartMove();
	//�΂߉E�ړ�
	void SlantMove(bool left);
	//��]
	void HardEnemyMove(bool left);
	//�{�X����
	void BossMoveBlackLeft();
	//�{�X���E
	void BossMoveBlackRight();
	//�{�X��
	void BossMoveWhite();
	//���ȂȂ��o��
	void ShowMove();

	
	void ShotSelect(int j);


	//�^��
	void DownBullet(int j);

	void SlantRightBullet1(int j);
	void SlantRightBullet2(int j);
	void SlantRightBullet3(int j);
	void SlantRightBullet4(int j);
	void SlantRightBullet5(int j);
	void SlantRightBullet6(int j);

	void SlowBullet(int j);
	
	void SlantLeftBullet1(int j);
	void SlantLeftBullet2(int j);
	void SlantLeftBullet3(int j);
	void SlantLeftBullet4(int j);
	void SlantLeftBullet5(int j);
	void SlantLeftBullet6(int j);
	
	//�E
	void RightBullet(int j);
	//��
	void LeftBullet(int j);

	void WallBullet(int j);
};