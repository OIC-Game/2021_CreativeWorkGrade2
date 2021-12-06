#include "Enemy.h"

CEnemy::CEnemy():
m_pTexture(NULL),
m_Type(),
m_PosX(0.0f),
m_PosY(0.0f),
m_MoveX(0.0f),
m_MoveY(0.0f),
m_bShow(false),
m_bMove(false),
m_bReverse(false),
m_bDead(false){
}

CEnemy::~CEnemy(){
}

void CEnemy::Initialize(float px, float py, int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = -1.0f;
	m_MoveY = 0.0f;
	m_MoveKameX = -6.0f;
	m_bShow = true;
	m_bMove = false;
	m_bKame = false;
	m_bDamege = true;
	m_bDead = false;
	m_DamageWait = 10;
	switch (GetType())
	{
		case ENEMY_01:
		//�A�j���[�V�������쐬
		SpriteAnimationCreate anim[] = {
			{
				"�ړ�",
				0,0,
				32,32,
				TRUE,{{5,0,0},{5,1,0}}
			},
			{
				"���S",
				96,0,
				32,32,
				FALSE,{{5,0,0}}
			},
		};
		m_Motion.Create(anim, MOTION_COUNT);
		break;
	}

	switch (GetType())
	{
		case ENEMY_02:
		//�A�j���[�V�������쐬
		SpriteAnimationCreate anim2[] = {
			{
				"�ړ�",
				0,0,
				32,44,
				TRUE,{{5,0,0},{5,1,0}}
			},
			{
				"���S",
				64,0,
				32,44,
				FALSE,{{5,0,0}}
			},
			{
				"�J��",
				96,0,
				32,44,
				FALSE,{{5,0,0}}
			},
		};
		m_Motion.Create(anim2, MOTION2_COUNT);
		break;
	}
}

void CEnemy::Update(float wx, float wy){
	//��\��
	if (!m_bShow)
	{
		return;
	}
	if (m_bDead)
	{
		m_DamageWait--;
		if (m_DamageWait == 0)
		{
			m_bShow = false;
		}
	}
	if (m_PosX - wx < 1100)
	{
		if (!m_bKame)
		{
			m_bMove = true;
		}
	}

	//�d�͂ɂ�艺�ɏ�����������
	m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
	//���ۂɍ��W���ړ�������
	if (m_bMove)
	{
		if (m_bKame)
		{
			m_PosX += m_MoveKameX;
		}
		else
		{
			m_PosX += m_MoveX;

		}
		m_PosY += m_MoveY;
	}
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

void CEnemy::Render(float wx, float wy){
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�`���`
	CRectangle dr = m_SrcRect;
	//���]�t���O��ON�̏ꍇ�`���`�𔽓]������
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, dr);
}

void CEnemy::RenderDebug(float wx, float wy){
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));

	CRectangle le = Left();
	CGraphicsUtilities::RenderRect(le.Left - wx, le.Top - wy, le.Right - wx, le.Bottom - wy, MOF_XRGB(0, 0, 0));

	CRectangle re = Right();
	CGraphicsUtilities::RenderRect(re.Left - wx, re.Top - wy, re.Right - wx, re.Bottom - wy, MOF_XRGB(255, 255, 255));
}

void CEnemy::Release(){
	m_Motion.Release();
}

void CEnemy::CollisionStage(float ox, float oy){
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX *= -1;
		m_bReverse = true;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX *= -1;
		m_bReverse = false;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	else if (ox < 0 && m_MoveKameX > 0)
	{
		m_MoveKameX *= -1;
		m_bReverse = true;
	}
	else if (ox > 0 && m_MoveKameX < 0)
	{
		m_MoveKameX *= -1;
		m_bReverse = false;
	}
}

void CEnemy::Damege(void){
	switch (GetType())
	{
		case ENEMY_01:
			m_Motion.ChangeMotion(MOTION_DEATH);
			m_bDead = true;
			return;
			break;
		case ENEMY_02:
			m_Motion.ChangeMotion(MOTION_DEATH);
			m_bKame = true;
			m_bMove = false;
			m_bDamege = false;
			return;
			break;
	}
}

void CEnemy::KameMove(bool reverse){
	m_bMove = true;
	m_bDamege = true;
	m_bReverse = reverse;

}

