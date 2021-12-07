#include "Enemy.h"
#include"Game.h"



CEnemy::CEnemy():
m_Type(0),
m_pTexture(NULL),
m_Motion(),
m_PosX(0.0f),
m_PosY(0.0f),
m_MoveX(0.0f),
m_MoveY(0.0f),
m_bShow(true),
m_bReverse(false),
m_SrcRect(){
}

CGame		gGame;
CPlayer		gPlayer;

CEnemy::~CEnemy(){
}


void CEnemy::Initialize(float px, float py, int type) {

	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = -3.0f;
	m_MoveY = 0.0f;
	m_bReverse = true;
	m_bShow = true;
	m_DamageWait = 0;
	


	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		//�ړ�
		{
			"�ړ�",
			0,0,
			32,32,
			TRUE,{{13,0,0},{13,1,0}}
		},
		//�_���[�W
		{
			"���S",
			0,96,
			32,32,
			FALSE,{{20,3,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);

}


void CEnemy::Update(void) {


	//��\��
	if (!m_bShow)
	{
		return;
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	

	//�_���[�W���̓���
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_MOVE);		
		}
		else
		{
			if (m_MoveX > 0)
			{
				m_MoveX -= 0.2f;
				if (m_MoveX <= 0)
				{
					m_MoveX = 0;
				}
			}
			else if (m_MoveX < 0)
			{
				m_MoveX += 0.2f;
				if (m_MoveX >= 0)
				{
					m_MoveX = 0;
				}
			}
		}
	}
	//�d�͂ɂ�艺�ɏ�����������
	m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
	//���ۂɍ��W���ړ�������
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();

	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

}


void CEnemy::CollisionStage(float ox, float oy) {
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
}


void CEnemy::Render(float wx, float wy) {



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


void CEnemy::RenderDebug(float wx, float wy) {

	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CRectangle HeadRect=GetHedRect();

	//�G�̋�`�̃f�o�b�O�\��
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_COLOR_RED);

	//�G�̓��̋�`�̃f�o�b�O�\��
	CGraphicsUtilities::RenderRect(hr.Left - wx,HeadRect.Top - wy, HeadRect.Right - wx, HeadRect.Bottom - wy, MOF_COLOR_HGREEN);

}
/**
 * ���
 *
 */
void CEnemy::Release(void) {
	m_Motion.Release();
}


bool CEnemy::CollisionPlayer()
{
	
	if (gPlayer.GetCollisionFlg())
	{		
		return true;
	}
	return false;
}


void CEnemy::Damage()
{
	m_Motion.ChangeMotion(MOTION_DAMAGE);

		m_bShow = false;
			
}