#pragma once

#include	"Mof.h"
#include    "EnemyShot.h"

#define      ENEMYSHOT_COUNT   50
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
	CEnemyShot              m_ShotArray[ENEMYSHOT_COUNT];
	int                     m_ShotWait;
	int                     m_ShotWaitSet;
	int						m_EnemyColor;

public:
	CEnemy();
	~CEnemy();
	void Initialize(void);				//����������
	void Start(float px,float py);		//�o�������ipx,py�̈ʒu����o��������j
	void Update(void);					//�ړ����̍X�V����
	void Render(void);					//�`�揈��
	void RenderDebug(int i);			//�f�o�b�O�`�揈��
	void SetTexture(CTexture* pt){ m_pTexture = pt; }	//�摜�̐ݒ�B�K���Ăяo�����ƁI
	bool GetShow(void){ return m_bShow; }				//�\����Ԃ̎擾

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
		for (int i = 0; i < ENEMYSHOT_COUNT; i++) { m_ShotArray[i].SetTexture(st); }
	}
	//n�Ԗڂ̒e���擾�i�e�̎Q�Ƃ�Ԃ��j
	CEnemyShot& GetShot(int n) { return m_ShotArray[n]; }
};