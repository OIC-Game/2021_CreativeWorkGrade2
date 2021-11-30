#include "Player.h"   




CPlayer::CPlayer() :
	px(200),
	py(640),
	vx(5),
	JumpSpd	(0.0f),
	MoveFlg(false),
	JumpFlg(false),
    m_bReverse(false),
	LifeCount(3),
	m_DamageWait(0){
}


CPlayer::~CPlayer()
{

}

bool CPlayer::Load(void)
{
	//�L�����N�^�̃e�N�X�`���̓ǂݍ���
	if (!gTexture.Load("Fox.png")) {
		return	false;
	}

	//���C�t�Q�[�W�̃e�N�X�`���̓ǂݍ���
if (!HP1.Load("Heart_1.png"))
{
	return false;
}
if (!HP2.Load("Heart_2.png"))
{
	return false;
}
if(!HP3.Load("Heart_3.png"))
{
	return false;
}



	//�A�j���[�V�����̍쐬
	SpriteAnimationCreate anim[] = {
		{
			"�ҋ@",  
			0,8,
			30,35,
			TRUE,{{10,0,0},{10,1,0},{10,2,0}}
		},
		{
			"�ړ�",
			0,260,
			30,35,
			TRUE,{{10,0,0},{10,1,0},{10,2,0}}
},
		
		{
			"�W�����v",
			0,50,
			30,35,
			FALSE,{{10,0,0},{10,1,0},{10,2,0}}
},
	
		{
			"�_���[�W",
			0,353,
			30,35,
			FALSE,{{5,0,0},{5,1,0},{5,2,0}}
},
	};


	m_Motion.Create(anim, MOTION_COUNT);

	return true;
}

void CPlayer::Initialize(void)
{
	px = 200;
	py=640;
	vx = 5;
	JumpSpd = 0.0f;
	MoveFlg = false;
	JumpFlg = false;
	m_bReverse = false;
	LifeCount = 3;
	m_DamageWait=0;
//	m_Motion.ChangeMotion(MOTION_WAIT);
	
}

void CPlayer::Update(void)
{

	MoveFlg = false;
	//�_���[�W���̓���
	if (m_Motion.GetMotionNo()==MOTION_DAMAGE)
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
	

	UpdateMove();

	px += vx;
	py += JumpSpd;


	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}


//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	
}

void CPlayer::UpdateKey(void)
{
	

	//���L�[�ňړ�
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		vx -= PLAYER_SPEED;
		m_bReverse=true;
		MoveFlg = true;
		if (vx<-PLAYER_MAXSPEED)
		{
			vx = -PLAYER_MAXSPEED;
		}

		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}

	}
	//�E�L�[�ňړ�
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		vx += PLAYER_SPEED;
		m_bReverse = false;
		MoveFlg =true;
		if (vx>PLAYER_MAXSPEED)
		{
			vx = PLAYER_MAXSPEED;
		}

		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}

	}
	else if(m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(MOTION_WAIT);
	}
	
	//�X�y�[�X�L�[�ŃW�����v
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !JumpFlg)
	{
		//�W�����v�J�n
		JumpFlg = true;
		JumpSpd = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMP);
		
	}
	

	if (JumpFlg == false)
	{
		m_Motion.ChangeMotion(MOTION_WAIT);
	}
	
}

void CPlayer::UpdateMove(void)
{

	if (!MoveFlg)
	{
		if (vx > 0)
		{
			vx -= PLAYER_SPEED;
			if (vx <= 0)
			{
				vx = 0;
			}
		}
		else if (vx < 0)
		{
			vx += PLAYER_SPEED;
			if (vx >= 0)
			{
				vx = 0;
			}
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}

     }
	

		//�v���C���[�̑��x�ɏd�͂�������
	JumpSpd += GRAVITY;
	if (JumpSpd >= 20.0f)
	{
		JumpSpd = 20.0f;
	}

}


void CPlayer::CollisionStage(float ox, float oy)
{

	px+= ox;
	py += oy;
	
	if (oy<0 && JumpSpd>0)
	{
		//�������̉����܂�
		JumpSpd = 0;
		if (JumpFlg)
		{
			JumpFlg = false;
			m_Motion.ChangeMotion(MOTION_JUMP);
		}		
	}
	else if (oy>0 &&JumpSpd<0)
	{
		JumpSpd = 0;
	}


	//���ړ����̍����܂�
	if (ox < 0 && vx> 0)
	{
	   vx = 0;		
	}		
	else if (ox > 0 && vx < 0)
	{
	 vx = 0;
	}
	
}

void CPlayer::Render(float wx, float wy)
{

	/*if (CollisionEneHed)
	{
		CGraphicsUtilities::RenderString(100, 100, "�������Ă���I�I", MOF_COLOR_BLACK);
	}*/



	//�C���^�[�o��2�t���[�����Ƃɕ`������Ȃ�
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	//�`���`
	CRectangle dr = m_SrcRect;


	//���]�t���O��ON�̏ꍇ��`�𔽓]
	if (m_bReverse) {
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//�`��ʒu&�e�N�X�`���̕`�� 
	gTexture.Render(px - wx, py - wy, dr);


	switch (LifeCount) {
	case 1:
	{
		HP1.RenderScale(50, 20,2.0f);
		break;
	}
	case 2:
	{
		HP2.RenderScale(50, 20,2.0f);
		break;
	}
	case 3:
	{
		HP3.RenderScale(50,20,2.0f);
		break;
	}
	default:
		break;
	}

}

void CPlayer::renderDebug(float wx, float wy)
{
	CGraphicsUtilities::RenderString(10, 70, "�v���C���[�ʒu X : %.0f , Y : %.0f", px, py,MOF_XRGB(255,0,0));

		CRectangle hr = GetRect();
		CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy,
			hr.Right - wx, hr.Bottom - wy, MOF_COLOR_RED);	

		CRectangle lR = GetLegRect();
		CGraphicsUtilities::RenderRect(lR.Left - wx, lR.Top - wy, lR.Right - wx, lR.Bottom - wy, MOF_COLOR_HGREEN);
	
}

void CPlayer::Release(void)
{
	//�e�N�X�`���̉��
	gTexture.Release();
	m_Motion.Release();
	HP1.Release();
	HP2.Release();
	HP3.Release();
}






float CPlayer::GetPosY()
{
	return py;
}



//�G�Ƃ̓����蔻��
bool CPlayer::CollisionEnemyBody(CEnemy& ene)
{
	if (!ene.GetShow())
	{
		return false;
	}

	//�_���[�W���̂��ߓ����蔻��������Ȃ�Ȃ�
	if (m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}
	//�G�̋�`�Ǝ����̋�`�Ń_���[�W
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();
	if (prec.CollisionRect(erec))
	{
		m_DamageWait = 60;
		if (LifeCount > 0)
		{
			LifeCount--;
		}

		if (prec.Left < erec.Left)
		{
			vx = -5.0f;
			m_bReverse = false;
		}
		else
		{
			vx = 5.0f;
			m_bReverse = true;
		}
		
	}
}

void CPlayer::Damage(void)
{
	m_DamageWait = 60;
	if (LifeCount > 0)
	{
		LifeCount--;
	}
	m_Motion.ChangeMotion(MOTION_DAMAGE);
}


bool CPlayer::CollisionEnemyHed(CEnemy& ene)
{

	CRectangle plrec=GetLegRect();
	CRectangle ehrec=ene.GetHedRect();

	if (plrec.CollisionRect(ehrec))
	{
		m_HedCollFlg = true;
	}
	return false;
}

void CPlayer::CollisionJump(void)
{
	m_Motion.ChangeMotion(MOTION_JUMP);

	JumpSpd = -10;
}



