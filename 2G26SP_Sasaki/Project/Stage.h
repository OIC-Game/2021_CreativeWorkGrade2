#pragma once

#include "Mof.h"
#include "Enemy.h"

//�X�N���[�����x
#define		SCROLL_SPEED	1

//�G�̏o�����̍\����
typedef struct tag_ENEMYSTART
{
	float PosX;
	float Scroll;
	int	  Color;
}ENEMYSTART;

class CStage
{
private:
	CTexture	m_Texture;		//�w�i�摜�̕ϐ�
	float		m_Scroll;		//�X�N���[����
	ENEMYSTART*  m_pEnemyStart;
	int         m_EnemyCount;
	CTexture    m_EnemyTexture;
	CTexture    m_EnemyTextureWhite;
	int         m_EnemyNo;
	int			m_EnemyShotColor;
	CTexture    m_EnemyShotTexture;

public:
	CStage();
	~CStage();
	bool Load();						//���\�[�X�̓ǂݍ���
	void Initialize(ENEMYSTART* pSt,int cnt);					//�p�����^���̏�����
	void Update(CEnemy* ene,int ecnt);						//�X�V����
	void Render();						//�`�揈��
	void Release();						//���\�[�X���̉������
	void RenderDebug(void);
	bool IsAllEnemy(void) { return m_EnemyNo >= m_EnemyCount; }
	int  EnemyShotColorBack(){ return m_EnemyShotColor; }
};

