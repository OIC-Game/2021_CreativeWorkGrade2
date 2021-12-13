#include "Player.h"

extern int			gStage;

CPlayer::CPlayer():
m_Texture(),
m_PosX(0.0f),
m_PosY(0.0f),
m_bMove(false),
m_MoveX(0.0f),
m_MoveY(0.0f),
m_Life(3),
m_Stat(0),
m_Comb(0),
m_bJump(false),
m_bReverse(false), 
m_bClear(false),
m_bDead(false),
m_DamageWait(0),
m_SrcRect(),
m_Time(0),
m_Score(0){
}

CPlayer::~CPlayer(){
}

bool CPlayer::Load(void){
	//�e�N�X�`���̓ǂݍ���
	if (!m_Texture.Load("player1.png"))
	{
		return false;
	}
	//���̓ǂݍ���
	if (!m_JumpSound.Load("�W�����v��.mp3"))
	{
		return false;
	}
	if (!m_coinSound.Load("coin01.mp3"))
	{
		return false;
	}
	if (!m_upSound.Load("powerup05.mp3"))
	{
		return false;
	}
	if (!m_downSound.Load("powerdown01.mp3"))
	{
		return false;
	}
	if (!m_clearSound.Load("nc106378.wav"))
	{
		return false;
	}
	if (!m_enemySound.Load("nc27241.mp3"))
	{
		return false;
	}
	if (!m_blockcoinSound.Load("coin05.mp3"))
	{
		return false;
	}
	if (!m_endSound.Load("nc67702.wav"))
	{
		return false;
	}
	if (!m_BGM.Load("MusMus-BGM-034.mp3"))
	{
		return false;
	}
	//�A�j���[�V�����̍쐬
	SpriteAnimationCreate anim[] = {
		{
			"�ҋ@",
			0,0,
			60,75,
			TRUE,{{5,0,0}}
		},
		{
			"�ړ�",
			64,0,
			60,70,
			TRUE,{{5,0,0},{5,1,0}}
		},
		{
			"�W�����v�J�n",
			0,165,
			60,70,
			FALSE,{{5,0,0}}
		},
		{
			"�W�����v�I��",
			64,165,
			60,70,
			FALSE,{{5,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
	return true;
}

void CPlayer::Initialize(void){
	m_PosX = 200;
	m_PosY = 645;
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	if (m_Life < 0)
	{
		m_Life = 3;
	}
	if (gStage == STAGENO_01)
	{
		m_Stat = 0;
		m_Coin = 0;
		m_Score = 0;
	}
	m_Time = 300;
	m_Comb = 0;
	m_bJump = false;
	m_bShow = true;
	m_bReverse = false;
	m_bGoal = false;
	m_bClear = false;
	m_ShowTime = 20;
	m_bEnd = false;
	m_bDead = false;
	m_bEndTime = 0;
	m_DamageWait = 0;
	m_Motion.ChangeMotion(MOTION_WAIT);
	m_BGM.SetLoop(TRUE);
	m_BGM.Play();
}

void CPlayer::Update(float wx, float wy){
	if (m_bEnd)
	{
		m_bEndTime--;
		if (m_bEndTime > 0)
		{
			m_Motion.ChangeMotion(MOTION_JUMP);
			m_MoveY = PLAYER_JUMP;
			m_PosY += m_MoveY;
			return;
		}
		m_MoveY += GRAVITY;
		m_PosY += m_MoveY;
		if (m_PosY >= g_pGraphics->GetTargetHeight() - m_SrcRect.GetHeight())
		{
			m_bDead = true;
			m_Life = m_Life - 1;
		}
		return;
	}
	if (m_bGoal)
	{
		m_BGM.Stop();
		if (!m_clearSound.IsPlay())
		{
			m_clearSound.Play();
		}
		
		m_Motion.ChangeMotion(MOTION_WAIT);
		if (m_PosY < 630)
		{
			m_MoveY = 2.0f;
			m_PosY += m_MoveY;
		}
		else if (m_PosY > 630)
		{
			m_MoveX = 3.0f;
			m_PosX += m_MoveX;
			m_MoveY = 3.0f;
			m_PosY += m_MoveY;
		}
		if (!m_bShow)
		{
			m_ShowTime--;
			if (m_ShowTime <= 0)
			{
				m_bClear = true;
			}
		}
		return;
	}
	m_bMove = false;
	if (m_Motion.GetMotionNo() == MOTION_JUMPEND)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else 
	{
		UpdateKey();
	}
	
	if (!m_bJump)
	{
		m_Comb = 0;
	}

	UpdateMove();
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;

	//�n�ʂɐڐG����ƃW�����v�I��
	if (m_PosY + m_SrcRect.GetHeight() >= g_pGraphics->GetTargetHeight())
	{
		if (m_bJump)
		{
			m_bJump = false;
			m_bCombStart = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	
	//��ʊO�ɂłȂ��悤��
	if (m_PosX  < 0)
	{
		m_PosX = 0.0f;
	}
	
	//��ʉ��Ŏ��S
	if (m_PosY >= g_pGraphics->GetTargetHeight() - m_SrcRect.GetHeight())
	{
		m_bDead = true;
		m_Life = m_Life - 1;
		m_BGM.Stop();
		m_endSound.Play();
		return;
	}
	
	// �A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

void CPlayer::UpdateKey(){
	//�L�[�{�[�h�ňړ�
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		//A�L�[�Ń_�b�V��
		if (g_pInput->IsKeyHold(MOFKEY_A))
		{
			m_MoveX -= PLAYER_RUNSPEED;
			m_bReverse = true;
			m_bMove = true;
			if (m_MoveX < -PLAYER_MAXRUNSPEED)
			{
				m_MoveX = -PLAYER_MAXRUNSPEED;
			}
			if (m_Motion.GetMotionNo() == MOTION_WAIT)
			{
				m_Motion.ChangeMotion(MOTION_MOVE);
			}
		}
		else
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
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		//A�L�[�Ń_�b�V��
		if (g_pInput->IsKeyHold(MOFKEY_A))
		{
			m_MoveX += PLAYER_RUNSPEED;
			m_bReverse = false;
			m_bMove = true;
			if (m_MoveX > PLAYER_MAXRUNSPEED)
			{
				m_MoveX = PLAYER_MAXRUNSPEED;
			}
			if (m_Motion.GetMotionNo() == MOTION_WAIT)
			{
				m_Motion.ChangeMotion(MOTION_MOVE);
			}
		}
		else
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
	}
	
	//S�L�[�ŃW�����v
	if (g_pInput->IsKeyPush(MOFKEY_S) && !m_bJump)
	{
		m_bJump = true;
		m_MoveY = PLAYER_JUMP;
		m_MoveY += GRAVITY;
		m_Motion.ChangeMotion(MOTION_JUMP);
		m_JumpSound.Play();
	}
	else
	{
		m_MoveY += GRAVITY * 1.5f;
	}

	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		m_bClear = true;
	}
}

void CPlayer::UpdateMove(void){
	//���̃t���[���ł̈ړ��������Ȃ���Ό�������
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
		else if (m_MoveX < 0)
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
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
}

void CPlayer::Render(float wx, float wy){
	//���݂̃X�e�[�^�X��\��
	CGraphicsUtilities::RenderString(560, 30, "0%0i",m_Stat);
	//���݂̃X�R�A��\��
	CGraphicsUtilities::RenderString(220, 30, "%0i", m_Score);
	//���݂̃R�C����������\��
	CGraphicsUtilities::RenderString(380, 30, "�~%i",m_Coin);
	//���݂̃��C�t�̐���\��
	CGraphicsUtilities::RenderString(720, 30, "%0i", m_Life);
	//���݂̃R���{�̐���\��
	CGraphicsUtilities::RenderString(740, 30, "%0i", m_Comb);
	if (!m_bShow)
	{
		return;
	}
	//�C���^�[�o���Q�t���[�����Ƃɕ`������Ȃ�
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
	}
	//�e�N�X�`���̕`��
	m_Texture.Render(px, py, dr);
}

void CPlayer::RenderDebug(float wx, float wy){
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10, 10, "�v���C���[�ʒu X : %.0f , Y : %.0f", m_PosX, m_PosY);
	//���x�̕`��
	CGraphicsUtilities::RenderString(10, 40, "�v���C���[���x X : %.0f ",m_MoveX);
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	CRectangle er = GetRect();
	er.Top = er.Bottom - 0.5;
	er.Expansion(-6, 0);
	CGraphicsUtilities::RenderRect(er.Left - wx, er.Top - wy, er.Right - wx, er.Bottom - wy, MOF_XRGB(255, 0, 0));
}

void CPlayer::Release(void){
	m_Texture.Release();
	m_Motion.Release();
	m_JumpSound.Release();
	m_coinSound.Release();
	m_upSound.Release();
	m_downSound.Release();
	m_enemySound.Release();
	m_blockcoinSound.Release();
	m_clearSound.Release();
	m_endSound.Release();
	m_BGM.Release();
}

void CPlayer::CollisionStage(float ox, float oy){
	if (m_bEnd)
	{
		return;
	}
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������
	if (oy < 0 && m_MoveY>0)
	{
		m_MoveY = 0;
		if (m_bJump)
		{
			m_bJump = false;
			m_bCombStart = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ���������
	if (ox < 0 && m_MoveX>0)
	{
		m_MoveX = 0;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

void CPlayer::IsGoal(void){
	m_bGoal = true;
}

bool CPlayer::CollisionEnemy(CEnemy& ene){
	if (m_bEnd)
	{
		return false;
	}
	if (ene.GetDead())
	{
		return false;
	}
	if (m_bDead)
	{
		return false;
	}
	//�_���[�W���̂��ߓ����蔻����s��Ȃ�
	if (m_DamageWait > 0)
	{
		return false;
	}
	//�G�̋�`�Ǝ����̋�`�Ń_���[�W
	CRectangle prec = GetRect();
	CRectangle er = GetRect();
	er.Top = er.Bottom - 1;
	er.Expansion(-6, 0);
	CRectangle erec = ene.GetRect();

	CRectangle Lefterec = ene.Left();

	CRectangle Righterec = ene.Right();

	if (!ene.GetMove())
	{
		if (er.CollisionRect(Lefterec))
		{
			ene.KameLeftMove();
		}
		else if (er.CollisionRect(Righterec))
		{
			ene.KameRightMove();
		}
	}
	else
	{
		if (er.CollisionRect(erec))
		{
			m_MoveY = -6.0f;
			m_enemySound.Play();
			ene.Damege();
			EnemyScore();
			return true;
		}

		if (prec.CollisionRect(erec))
		{
			if (m_Stat >= 1)
			{
				m_DamageWait = 60;
				m_downSound.Play();
				m_Stat = m_Stat - 1;
				return true;
			}
			else if (m_Stat <= 0)
			{
				m_bEnd = true;
				m_bEndTime = 5;
				m_BGM.Stop();
				m_endSound.Play();
				return true;
			}
		}
	}
	
	
	return false;
}

bool CPlayer::CollisionItem(CItem& itm){
	if (!itm.GetShow())
	{
		return false;
	}
	//�A�C�e���̋�`�Ǝ����̋�`�œ����蔻��
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	irec.Expansion(-5, -5);

	if (prec.CollisionRect(irec))
	{
		itm.SetShow(false);
		switch(itm.GetType())
		{
			case ITEM_KINOKO:
				if (m_Stat < 1)
				{
					m_upSound.Play();
					m_Stat = 1;
					m_Score = m_Score + 1000;
				}
				break;
			case ITEM_COIN:
				CoinGet();
				break;
			case ITEM_1UPKINOKO:
				m_Life = m_Life + 1;
				break;
		}
		return true;
	}
	return false;
}

void CPlayer::CoinGet(void){
	m_coinSound.Play();
	m_Coin = m_Coin + 1;
	m_Score = m_Score + 200;
}

void CPlayer::BlockCoinGet(void){
	m_blockcoinSound.Play();
	m_Coin = m_Coin + 1;
	m_Score = m_Score + 200;
}

void CPlayer::BreakBlock(void){
	m_Score = m_Score + 50;
}

void CPlayer::EnemyScore(void){
	if (m_bJump)
	{
		m_Comb++;
	}
	m_Score = m_Score + 100 * m_Comb;
}

void CPlayer::Clear(void){
	m_bShow = false;
}
