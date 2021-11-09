#include "Enemy.h"



CEnemy::CEnemy() :
	m_pTexture(NULL),
	m_Motion(),
	m_Pos(),
	m_Move(),
	
	//m_bShow(false),
	m_bReverse(false),
	m_SrcRect(),
	m_HP(0),
	m_DamageWait(0) {
}

/**
 * �f�X�g���N�^
 *
 */
CEnemy::~CEnemy() {
	//delete[] �ŉ�������悤��Release���f�X�g���N�^�Ŏ��s����
	//Release();
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 * [in]			type				�G�^�C�v
 */
void CEnemy::Initialize(float px, float py, int type) {
	//m_Type = type;
	m_Pos.x = px;
	m_Pos.y = py;
	m_Move.x = -2.0f;
	m_Move.y = 0.0f;
	m_bReverse = false;
	m_bShow = true;
	m_HP = 1;
	m_DamageWait = 0;
	//�A�j���[�V�������쐬
	std::vector<SpriteAnimationCreate> anim = {
		//�ړ�
		SpriteAnimationCreate{
			"�ړ�",
			0,0,
			30,32,
			TRUE,{{7,0,0},{7,1,0}}
		},

		SpriteAnimationCreate{

			"���S",
			0,32,
			30,32,
			FALSE,{{5,0,0}}
        }
		
	};
	m_Motion.Create(anim.data(),anim.size());

	
}

/**
 * �X�V
 *
 */
void CEnemy::Update() {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�_���[�W���̓���
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
			if (m_HP <= 0)
			{
				m_bShow = false;
				

			}
			/*if (m_Stage.GetScrollX < 1000)
			{
				m_Move.x = true;
			}*/
			if (m_bReverse)
			{
				m_Move.x = -3.0f;
			}
			else
			{
				m_Move.x = 3.0f;
			}
		}
		else
		{
			if (m_Move.x > 0)
			{
				m_Move.x -= 0.2f;
				if (m_Move.x <= 0)
				{
					m_Move.x = 0;
				}
			}
			else if (m_Move.x < 0)
			{
				m_Move.x += 0.2f;
				if (m_Move.x >= 0)
				{
					m_Move.x = 0;
				}
			}
		}
	}
	//�d�͂ɂ�艺�ɏ�����������
	m_Move.y += GRAVITY;
	if (m_Move.y >= 20.0f)
	{
		m_Move.y = 20.0f;
	}
	//���ۂɍ��W���ړ�������
	m_Pos += m_Move;
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

/**
 * �_���[�W����
 * �������̂g�o�����炵�g�o���O�ȉ��ɂȂ�ΓG����������
 *
 * ����
 * [in]			dmg				�_���[�W
 * [in]			bRev			���]�t���O
 */
 void CEnemy::Damage(int dmg, bool bRev) {
 	m_HP -= dmg;
 	m_DamageWait = 60;
	
 	/*if (bRev)
 	{
 		m_Move.x = -5.0f;
 		m_bReverse = false;
 	}
 	else
 	{
 		m_Move.x = 5.0f;
 		m_bReverse = true;
 	}*/
 	m_Motion.ChangeMotion(MOTION_DAMAGE);
	
 	
 }

 /**
  * �X�e�[�W�Ƃ̓�����
  *
  * ����
  * [in]			ox					X���܂��
  * [in]			oy					Y���܂��
  */
void CEnemy::CollisionStage(float ox, float oy) {
	m_Pos.x += ox;
	m_Pos.y += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if (oy > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (ox < 0 && m_Move.x > 0)
	{
		if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
		{
			m_Move.x = 0;
		}
		else
		{
			m_Move.x *= -1;
			m_bReverse = true;
		}
	}
	else if (ox > 0 && m_Move.x < 0)
	{
		if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
		{
			m_Move.x = 0;
		}
		else
		{
			m_Move.x *= -1;
			m_bReverse = false;
		}
	}
}

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEnemy::Render(float wx, float wy) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�C���^�[�o��2�t���[�����Ƃɕ`������Ȃ�
	/*if (m_DamageWait % 4 >= 2)
	{
		return;
	}*/
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
	m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
}

/*
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEnemy::RenderDebug(float wx, float wy) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
	CRectangle bo = Gethed();
	CGraphicsUtilities::RenderRect(bo.Left - wx, bo.Top - wy, bo.Right - wx, bo.Bottom - wy, MOF_XRGB(255, 0, 0));
}

/**
 * ���
 *
 */
void CEnemy::Release(void) {
	m_Motion.Release();
}

bool CEnemy::CollisionQBlock(CQuestionBlock& QBlock, float ox, float oy)
{
	CRectangle prlg = GetRect();
	CRectangle bl = QBlock.GetRect();
	if (prlg.CollisionRect(bl))
	{
		m_Pos.x += ox;
		m_Pos.y += oy - 0.3;

		if (oy < 40 && m_Move.y>0)
		{
			m_Move.y = 0;
		}
		else if (oy > 0 && m_Move.y < 30)
		{
			m_Move.y = 0;

		}

		if (ox < 0 && m_Move.x >40)
		{
			m_Move.x = 0;
		}
		else if (ox > 0 && m_Move.x < 40)
		{
			m_Move.x = 0;
		}
	}
	return false;
}

bool CEnemy::CollisionbreakBlock(CbreakBlock& blo, float ox, float oy)
{
	CRectangle prlg = GetRect();
	CRectangle bl = blo.GetRect();
	if (prlg.CollisionRect(bl))
	{
		m_Pos.x += ox;
		m_Pos.y += oy - 0.3;

		if (oy < 40 && m_Move.y>0)
		{
			m_Move.y = 0;
		}
		else if (oy > 0 && m_Move.y < 0)
		{
			m_Move.y = 0;

		}

		if (ox < 0 && m_Move.x >0)
		{
			m_Move.x = 0;
		}
		else if (ox > 0 && m_Move.x < 0)
		{
			m_Move.x = 0;
		}
	}
	return false;
}



