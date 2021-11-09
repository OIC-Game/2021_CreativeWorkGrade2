#include	"Player.h"

/**
 * �R���X�g���N�^
 *
 */
CPlayer::CPlayer() :
m_Texture() ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bMove(false) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bJump(false) ,
m_bReverse(false) ,
m_SrcRect() {
}

/**
 * �f�X�g���N�^
 *
 */
CPlayer::~CPlayer(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CPlayer::Load(void){
	//�e�N�X�`���̓ǂݍ���
	//�e�N�X�`���̓ǂݍ���
	if (!m_Texture.Load("player.png"))
	{
		return false;
	}
	if (!m_FrameTexture.Load("Frame.png"))
	{
		return false;
	}
	if (!m_HPTexture.Load("HP.png"))
	{
		return false;
	}
	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		{
			"�ҋ@",
			0,0,
		33,115,
		TRUE,{{5,0,0,},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"�ړ�",
			0,0,
			33,115,
			TRUE,{{5,0,0,},{5,1,0},{5,2,0}, {5,3,0},{5,4,0},{5,5,0}}
			},
		{
			"�W�����v�J�n",
			0,0,
		33,115,
		FALSE,{{5,0,0,},{5,1,0}, {5,2,0},{5,3,0}}
		},
		{
			"�W�����v�I��",
			0,0,
		33,115,
		FALSE,{{2,0,0},{2,1,0}}
		},
		{
			/*"�U��",
			0,350,
			33,115,
			FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}}*/
		},
		{
		/*	"�_���[�W",
			480,0,
		60,64,
		FALSE,{{20,0,0}}*/
        },
	};
	m_Motion.Create(anim, MOTION_COUNT);
	
	//�A�j���[�V�������쐬
	
	
	return true;
}
/**
* �����蔻��
* �����̓G�ɑ΂��ċ�`���m�̓����蔻������s����
* �������Ă����ꍇ�̓v���[���[�̏�Ԃ�ύX����
* 
* ����
* [in]         ene        ������s���G
* 
* �߂�l
* �������Ă���ꍇ��true,�������Ă��Ȃ����false��Ԃ�
*/

bool CPlayer::CollisionEnemy(CEnemy& ene) {
	if (!ene.GetShow())
	{
		return false;
	}
	//�_���[�W���̓����蔻����s��Ȃ�
	if (m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}
	//�G�̋�`�Ǝ����̋�`�_���[�W
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();

	if (prec.CollisionRect(erec))
	{
		m_HP -= 5;
		m_DamageWait = 60;
		if (prec.Left < erec.Left)
		{
			m_MoveX = -5.0f;
			m_bReverse = false;
		}
		else
		{
			m_MoveX = 5.0f;
			m_bReverse = true;
		}
		m_Motion.ChangeMotion(MOTION_DAMAGE);
		//�_���[�W�G�t�F�N�g�𔭐�������
		m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f,
			m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_DAMAGE);
		return true;
	}
	//�U�����̏ꍇ�̂ݍU���Ƃ̓����蔻������s
	if (m_Motion.GetMotionNo() != MOTION_ATTACK)
	{
		return false;
	}
	//�G�̋�`�Ǝ����̍U����`�œG���_���[�W
	prec = GetAttackRect();
	if (prec.CollisionRect(erec))
	{
		ene.Damage(5, m_bReverse);
		return true;
	}
	return false;

}

/**
* �����蔻��
* �����̃A�C�e���ɑ΂��ċ�`���m�̓����蔻������s����
* �������Ă����ꍇ�̓v���[���[�̏�Ԃ�ύX����
* 
* ����
* [in] itm ������s���A�C�e��
* 
*�߂�l
* �������Ă���ꍇ��true,�������Ă��Ȃ����false��Ԃ�
*/
bool CPlayer::CollisionItem(CItem& itm) {
	if (!itm.GetShow())
	{
		return false;
	}
	//�A�C�e���̋�`�Ǝ����̋�`�œ����蔻��
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	if (prec.CollisionRect(irec))
	{
		itm.SetShow(false);
		switch (itm.GetType())
		{
		case ITEM_RECOVER:
			m_HP += 30;
			if (m_HP >= 100)
			{
				m_HP = 100;
			}
			break;
		}
		return true;
	}
	return false;
}
/**
 * ������
 * �p�����[�^�[����W������������B
 * �v���C���[�̈ʒu�ȂǏ�Ԃ��������������Ƃ��Ɏ��s����B
 */
	void CPlayer::Initialize(void){
	m_PosX = 50;
	m_PosY = 500;
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_bJump = false;
	m_HP = 100;
	m_DamageWait = 0;
	m_bEnd = false;
	m_pEndEffect = NULL;
	m_Motion.ChangeMotion(MOTION_WAIT);
}

/**
 * �X�V
 *
 */
void CPlayer::Update( void ) {
	//HP���Ȃ��Ȃ�Ɣ����̏I����ҋ@���ďI��
	if (m_HP <= 0)
	{
		if (!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bEnd = true;
		}
		return;
  }
	//�ړ��t���O�A���̃t���[���ł̈ړ������������ǂ����ۑ�
	m_bMove = false;
	//�U�����A���n�̓���
	if (m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_JUMPEND)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//�_���[�W���̓���
	else if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else
	{
		//�L�[���͂ɂ�铮��
		UpdateKey();
	}
	//�ړ��X�V
	UpdateMove();
	//���ۂɍ��W���ړ�������
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;
	//�n�ʂɐڐG����ƃW�����v�I���i���������ʉ��[�Œ�~����悤�ɐݒ肷��j
	if (m_PosY + m_SrcRect.GetHeight() >= g_pGraphics->GetTargetHeight())
	{
		m_PosY = g_pGraphics->GetTargetHeight() - m_SrcRect.GetHeight();
		m_MoveY = 0;
		if (m_bJump)
		{
			m_bJump = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	//��ʊO�ŗ����Ƃ���HP��0�ɂ���
	if (m_PosY >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f,
			m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION02);
	}
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
 * �L�[���͂ɂ�铮��X�V
 *
 */
void CPlayer::UpdateKey( void ) {
	//�L�[�{�[�h�ł̈ړ�
	//���͂Œ��ڍ��W�𓮂����̂ł͂Ȃ��A���x��ω�������
	//�U�����͈ړ��ł��Ȃ��悤�ɂ���
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_MoveX -= PLAYER_SPEED;
		m_bReverse = true;
		m_bMove = true;
		if (m_MoveX < -PLAYER_MAXSPEED)
		{
			m_MoveX = -PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_MoveX += PLAYER_SPEED;
		m_bReverse = false;
		m_bMove = true;
		if (m_MoveX > PLAYER_MAXSPEED)
		{
			m_MoveX = PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	//��L�[�ŃW�����v
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !m_bJump)
	{
		m_bJump = true;
		m_MoveY = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
	}
	//SPACE�L�[�ōU��
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		m_Motion.ChangeMotion(MOTION_ATTACK);
	}
}

/**
 * �ړ��X�V
 *
 */
void CPlayer::UpdateMove(void){
	//���̃t���[���ł̈ړ����͂��Ȃ���Ό������������s����
	if (!m_bMove)
	{
		if (m_MoveX > 0)
		{
			m_MoveX -= PLAYER_SPEED;
			if (m_MoveX <= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_MoveX <0)
		{
			m_MoveX += PLAYER_SPEED;
			if (m_MoveX >= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//�d�͂ɂ�艺�ɏ�����������
	m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
}

/**
 * �`��
 *
 */
void CPlayer::Render(float wx, float wy){
	//�C���^�[�o��2�t���[�����Ƃɕ`�悵�Ȃ�
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}
	//�`���`
	CRectangle dr = m_SrcRect;
	//�`��ʒu
	float px = m_PosX - wx;
	float py = m_PosY - wy;
	//���]�t���O��ON�̏ꍇ�`���`�𔽓]������
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
		if (m_Motion.GetMotionNo() == MOTION_ATTACK)
		{
			px -= PLAYER_ATTACKWIDTH;
		}
	}
	//�e�N�X�`���̕`��
	m_Texture.Render(px, py, dr);
}

/**
 * �f�o�b�O�`��
 *
 */
void CPlayer::RenderDebug(float wx, float wy){
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10,70,"�v���C���[�ʒu X : %.0f , Y : %.0f",m_PosX,m_PosY);
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy,
		hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	//�U���̓����蔻��\��
	if(IsAttack())
	{
		CRectangle hr = GetAttackRect();
		CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy,
			hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	}
}

/**
 * ���
 *
 */
void CPlayer::Release(void){
	m_Texture.Release();
	m_Motion.Release();
	m_FrameTexture.Release();
	m_HPTexture.Release();
}
/**
* �X�e�[�W�Ƃ̓�����
* 
* ����
* [in] ox X���܂��
* [in] oy Y���܂�� 
*/

void CPlayer::CollisionStage(float ox, float oy) {
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_MoveY>0)
	{
		m_MoveY = 0;
		if (m_bJump)
		{
			m_bJump = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������
	if (ox < 0 && m_MoveX>0)
	{
		m_MoveX = 0;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}
/**
* �X�e�[�^�X�`��
*/
void CPlayer::RenderStatus(void) {
	//HP�ɉ����ċ�`�̕���ω�������
	CRectangle rec(0, 0, 532 * (m_HP * 0.01f), 64);
	m_HPTexture.Render(248, 20, rec);
	//�t���[�����㕔�ɕ`��
	m_FrameTexture.Render(0, 0);
}