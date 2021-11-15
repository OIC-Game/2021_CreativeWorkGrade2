#include "Player.h"
#include "GlobalDefine.h"
#include <thread>

extern  int		player_Life = PLAYER_INITIALLIFE;

//�X�R�A
extern	int		score;
extern	bool	scoreDisplayFlg;
extern	bool	player1UpDisplayFlg;
extern	int		getScore;
extern	int		scoreDesplayTime;
extern	int		enemyDeadCount = 0;
extern  int     getCoinCount;




//�R���X�g���N�^
CPlayer::CPlayer() :
	player_Position(0, 0),
	player_Move(0.0f),
	player_Jump(0.0f),
	player_JumpFlg(false),
	player_CheckGround(false),
	player_Texture(),
	player_RectTexture(),
	player_Reverse(false),
	player_Motion(),
	player_MoveFlg(false),
	player_JumpSE(),
	player_StepEnemySE(),
	player_ChangeBigSE(),
	player_ChangeSmallSE(),
	player_1upSE(),
	player_GoalFlagSE(),
	player_DeadFlg(false),
	player_DeadTransitionFlg(false),
	player_a(false),
	player_TimeWait(0),
	player_ClearFlg(false),
	player_ClearTransitionFlg(false),
	player_HP(0),
	player_DamageWait(0),
	player_ChangeBig(false),
	player_ChangeWait(0),
	player_ChangeWaitFlg(false),
	player_ChangeSizeFlg(false),
	player_DamageFlg(false),
	player_TempPositionX(0),
	player_TempPositionY(0),
	player_GoalMoveFlg(false),
	player_WarpFlg(false),
	player_tmpWarpFlg(false),
	player_playSEFlg(false),
	player_MarioDead(false),
	player_BossClearFlg(false),
	player_Scroll(false),
	player_BossClearTransitionFlg(false)
{
}


//�f�X�g���N�^
CPlayer::~CPlayer()
{

}

bool CPlayer::Load(void)
{
	if (!player_Texture.Load("Player.png"))
	{
		return false;
	}
	if (!player_JumpSE.Load("Jump.wav"))
	{
		return false;
	}
	if (!player_StepEnemySE.Load("StepEnemy.mp3"))
	{
		return false;
	}
	if (!player_ChangeBigSE.Load("ChangeBigSE.wav"))
	{
		return false;
	}
	if (!player_ChangeSmallSE.Load("ChangeSmallSE.mp3"))
	{
		return false;
	}
	if (!player_1upSE.Load("1UP.wav"))
	{
		return false;
	}
	if (!player_GoalFlagSE.Load("GoalFlag.mp3"))
	{
		return false;
	}
	if (!player_GetCoinSE.Load("GetCoin.wav"))
	{
		return false;
	}
	
	//�A�j���[�V�����쐬
	CreateAnimation();

	return true;
}

void CPlayer::Initialize(void)
{
	player_Position = Vector2(100, 500);
	player_Move = 0.0f;
	player_Jump = 0.0f;
	player_JumpFlg = false;
	player_CheckGround = false;
	player_Reverse = false;
	player_MoveFlg = false;
	player_DeadFlg = false;
	player_DeadTransitionFlg = false;
	player_a = false;
	player_ClearFlg = false;
	player_ClearTransitionFlg = false;
	player_HP = PLAYER_HP;
	player_DamageWait = 0;
	player_ChangeWait = 0;
	player_ChangeWaitFlg = false;
	player_ChangeBig = false;
	player_ChangeSizeFlg = false;
	player_DamageFlg = false;
	player_GoalMoveFlg = false;
	if (player_Motion.GetMotionNo() != MOTION_SMALL_WAIT)
	{
		player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
	}

	player_TempPositionX = 0.0f;
	player_TempPositionY = 0.0f;
	player_WarpFlg = false;
	player_tmpWarpFlg = false;
	player_playSEFlg = false;
	player_MarioDead = false;
	player_BossClearFlg = false;
	player_BossClearTransitionFlg = false;
}

void CPlayer::Update(void)
{
	//�v���C���[���S����
	DeadJudge();

	//��ʊO�ɏo�Ȃ��悤�ɂ���
	if (player_Position.x < 0)
	{
		player_Move = 0;
		player_Position.x = 0;
	}
	if (player_Position.x > 7500 && !player_BossClearFlg)
	{
		
		player_BossClearFlg = true;
	}
	//���S,�N���A�t���O��false�̎��v���C���[�𓮂���
	if (!player_DeadFlg && !player_ClearFlg && !player_BossClearFlg)
	{
		if (player_WarpFlg && player_Position.x < 6000)
		{
			player_tmpWarpFlg = player_WarpFlg;
			player_Position.x = 6400;
			player_Position.y = 400;
		}

		if (player_ChangeWait > 0 && !player_ChangeWaitFlg)
		{
			player_ChangeWaitFlg = true;
		}
		else if (player_ChangeWait <= 0 && player_ChangeWaitFlg)
		{
			player_ChangeWaitFlg = false;
		}
		//�v���C���[�T�C�Y�ω�(bool�Ő؂�ւ�)
		ChangeSize();
		//�v���C���[���T�C�Y�ω����Ă��Ȃ��Ƃ��ɏ���
		if (player_ChangeWait <= 0)
		{
			//�v���C���[�ړ�
			PlayerMove();

			//�v���C���[�W�����v(�v���C���[���n�ʂɐڐG���Ă���Ȃ�W�����v)
			if (player_CheckGround)
			{
				PlayerJump();

			}
			//�v���C���[�̑��x�ɏd�͂�^��������
			player_Jump += PLAYER_GRAVITY;
			player_Position.y += player_Jump;

		}
		////�������������S�t���O��TRUE
		//if (player_Position.y > 800)
		//{
		//	player_DeadFlg = true;
		//}

	}
	else if (player_DeadFlg)
	{
		//�v���C���[�����񂾂Ƃ��̏���(1�񂾂����s)
		if (!player_a)
		{
			if (!player_ChangeBig)
			{
				if (player_Motion.GetMotionNo() != MOTION_SMALL_DAMAGE)
				{
					player_Motion.ChangeMotion(MOTION_SMALL_DAMAGE);
				}
			}
			else
			{
				if (player_Motion.GetMotionNo() != MOTION_BIG_DAMAGE)
				{
					player_Motion.ChangeMotion(MOTION_BIG_DAMAGE);
				}
			}
			player_Life--;
			Sleep(300);
			player_Jump = -PLAYER_JUMPSPEED;
			player_a = true;
		}
		//�����鏈��
		player_Jump += PLAYER_GRAVITY;
		if (player_Jump > 20.0f)
		{
			player_Jump = 20.0f;
		}
		player_Position.y += player_Jump;
	}
	else if (player_ClearFlg)
	{
		if (player_Reverse)
		{
			player_Reverse = false;
		}
		
		//�v���C���[���S�[���t���b�O�𗎂��؂�����
		if (!player_JumpFlg && player_CheckGround)
		{
			if (player_GoalFlagSE.IsPlay())
			{
				player_GoalFlagSE.Stop();
			}

			if (!player_ChangeBig)
			{
				if (player_Motion.GetMotionNo() == MOTION_SMALL_WAIT)
				{
					player_Motion.ChangeMotion(MOTION_SMALL_MOVE);
				}
			}
			else
			{
				if (player_Motion.GetMotionNo() == MOTION_BIG_WAIT)
				{
					player_Motion.ChangeMotion(MOTION_BIG_MOVE);
				}
			}
			
			if (!player_ClearTransitionFlg)
			{
				player_Position.x += 5;
			}

		}
		else
		{
			if (!player_GoalMoveFlg)
			{
				player_GoalFlagSE.Play();
				player_GoalMoveFlg = true;
			}

			if (!player_ChangeBig)
			{
				if (player_Motion.GetMotionNo() != MOTION_SMALL_WAIT)
				{
					player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
				}
			}
			else
			{
				if (player_Motion.GetMotionNo() != MOTION_BIG_WAIT)
				{
					player_Motion.ChangeMotion(MOTION_BIG_WAIT);
				}
			}
			player_Position.y += 5;
		}
	}
	else if (player_BossClearFlg && !player_BossClearTransitionFlg)
	{
		player_Jump = 5;
		player_Move = 1;
		player_Position.x += player_Move;
		player_Position.y += player_Jump;
		if (!player_ChangeBig)
		{
			if (player_Motion.GetMotionNo() != MOTION_SMALL_MOVE)
			{
				player_Motion.ChangeMotion(MOTION_SMALL_MOVE);
			}
		}
		else
		{
			if (player_Motion.GetMotionNo() != MOTION_BIG_MOVE)
			{
				player_Motion.ChangeMotion(MOTION_BIG_MOVE);
			}
		}

	}

	//�_���[�W�̃C���^�[�o�������炷
	if (player_DamageWait > 0)
	{
		player_DamageWait--;
	}
	//�A�j���[�V�����̍X�V
	player_Motion.AddTimer(CUtilities::GetFrameSecond());
	//�v���C���[��`
	player_RectTexture = player_Motion.GetSrcRect();

}

void CPlayer::Render(float wx, float wy)
{
	//�v���C���[��`
	CRectangle player_drow = player_RectTexture;

	//�`��ʒu
	float px = player_Position.x - wx;
	float py = player_Position.y - wy;
	//�X�R�A�p�ޔ�ϐ�
	player_TempPositionX = px;
	player_TempPositionY = py;


	if (player_ChangeBig)
	{
		if (player_Motion.GetMotionNo() == MOTION_SMALL_WAIT)
		{
			py += 32;
		}
	}
	else if (!player_ChangeBig && player_DamageFlg)
	{
		if (player_Motion.GetMotionNo() == MOTION_SMALL_WAIT)
		{
			py += 32;
		}
	}
	if (player_Reverse)
	{
		float temp = player_drow.Right;
		player_drow.Right = player_drow.Left;
		player_drow.Left = temp;
	}
	player_Texture.Render(px, py, player_drow);

}

void CPlayer::RenderDebug(float wx, float wy)
{
	//�����蔻��`��
	CGraphicsUtilities::RenderRect(player_Position.x + 5 - wx, player_Position.y - wy, (player_Position.x + player_RectTexture.GetWidth() - 5) - wx, (player_Position.y + player_RectTexture.GetHeight()) - wy, MOF_XRGB(0, 255, 0));

	CGraphicsUtilities::RenderString(100, 100, "�W�����v�t���O�F%d", player_JumpFlg);
	CGraphicsUtilities::RenderString(100, 150, "�n�ʐڐG�t���O%d", player_CheckGround);
	CGraphicsUtilities::RenderString(100, 200, "�W�����v:%f", player_Jump);
	CGraphicsUtilities::RenderString(100, 250, "�c�@�F%d", player_Life);
	CGraphicsUtilities::RenderString(100, 300, "PX�F%f", player_Position.x);
	CGraphicsUtilities::RenderString(100, 350, "PY�F%f", player_Position.y);
	CGraphicsUtilities::RenderString(100, 400, "�ω��E�F�C�g�F%d", player_ChangeWait);
	CGraphicsUtilities::RenderString(100, 600, "�N���A�[�t���O%d", player_ClearFlg);
}

void CPlayer::Release(void)
{
	player_Texture.Release();
	player_Motion.Release();
	player_JumpSE.Release();
	player_StepEnemySE.Release();
	player_ChangeBigSE.Release();
	player_ChangeSmallSE.Release();
	player_1upSE.Release();
	player_GoalFlagSE.Release();
	player_GetCoinSE.Release();
}








//�v���C���[�ړ�
void CPlayer::PlayerMove(void)
{
	//�v���C���[�ړ�
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		player_Move += PLAYER_SPEED;
		player_MoveFlg = true;
		//�W�����v���ĂȂ��Ƃ�������ς�����
		if (!player_JumpFlg)
		{
			player_Reverse = false;
		}
		//�ō����x
		if (player_Move > PLAYER_TOPSPEED)
		{
			player_Move = PLAYER_TOPSPEED;
		}
		//�ړ����[�V�����ɐ؂�ւ�
		if (!player_ChangeBig)
		{
			if (player_Motion.GetMotionNo() == MOTION_SMALL_WAIT)
			{
				player_Motion.ChangeMotion(MOTION_SMALL_MOVE);
			}
		}
		else
		{
			if (player_Motion.GetMotionNo() == MOTION_BIG_WAIT)
			{
				player_Motion.ChangeMotion(MOTION_BIG_MOVE);
			}
		}

	}
	else if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		player_Move -= PLAYER_SPEED;
		player_MoveFlg = true;
		//�W�����v���ĂȂ��Ƃ�������ς�����
		if (!player_JumpFlg)
		{
			player_Reverse = true;
		}
		//�ō����x
		if (player_Move < -PLAYER_TOPSPEED)
		{
			player_Move = -PLAYER_TOPSPEED;
		}
		//�ړ����[�V�����ɐ؂�ւ�
		if (!player_ChangeBig)
		{
			if (player_Motion.GetMotionNo() == MOTION_SMALL_WAIT)
			{
				player_Motion.ChangeMotion(MOTION_SMALL_MOVE);
			}
		}
		else
		{
			if (player_Motion.GetMotionNo() == MOTION_BIG_WAIT)
			{
				player_Motion.ChangeMotion(MOTION_BIG_MOVE);
			}
		}
	}
	else
	{

		//�L�[���͂��Ȃ��ꍇ�͑��x������������
		if (player_Move < 0)
		{
			player_Move += PLAYER_SPEED;
			if (player_Move >= 0)
			{
				player_Move = 0;
			}
		}
		else if (player_Move > 0)
		{
			player_Move -= PLAYER_SPEED;
			if (player_Move <= 0)
			{
				player_Move = 0;
			}
		}
		player_MoveFlg = false;
		if (!player_ChangeBig)
		{
			if (player_Motion.GetMotionNo() == MOTION_SMALL_MOVE)
			{
				player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
			}
		}
		else
		{
			if (player_Motion.GetMotionNo() == MOTION_BIG_MOVE)
			{
				player_Motion.ChangeMotion(MOTION_BIG_WAIT);
			}
		}
	}
	//X���W�̕ω�
	player_Position.x += player_Move;
}

//�v���C���[�W�����v
void CPlayer::PlayerJump(void)
{

	//�v���C���[�W�����v
	if (g_pInput->IsKeyPush(MOFKEY_UP) && !player_JumpFlg)
	{
		//�W�����v�̊J�n�A������ݒ肵�ăW�����v�t���O��L���ɂ���
		player_JumpFlg = true;
		player_Jump = -PLAYER_JUMPSPEED;
		//�W�����v���[�V�����ɐ؂�ւ�
		if (player_JumpFlg)
		{
			if (!player_ChangeBig)
			{
				player_Motion.ChangeMotion(MOTION_SMALL_JUMP);
			}
			else
			{
				player_Motion.ChangeMotion(MOTION_BIG_JUMP);
			}

		}
		player_JumpSE.Play();
	}

	if (player_JumpFlg)
	{
		//�r���ŃW�����v�{�^���𗣂������W�����v���x�𔼌�(���W�����v)
		if (player_Jump < 0 && g_pInput->IsKeyPull(MOFKEY_UP))
		{
			player_Jump *= 0.2f;
		}
	}
}

//�`�悷��͈͂̃e�N�X�`����`���擾
CRectangle CPlayer::GetRectTexture(void)
{
	return CRectangle(0, 0, player_Texture.GetWidth(), player_Texture.GetHeight());
}

//�X�e�[�W�Ƃ̓�����
/*

		ox		X���܂��
		oy		Y���܂��
*/
void CPlayer::CollisionStage(float ox, float oy)
{

	//���S�t���Ofalse�̎������蔻����s��
	if (!player_DeadFlg && !player_ClearTransitionFlg)
	{

		player_Position.x += ox;
		player_Position.y += oy;
		player_CheckGround = true;
		//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������
		if (oy < 0)
		{

			player_Jump = 0;

			if (player_JumpFlg)
			{
				player_JumpFlg = false;
				if (!player_ChangeBig)
				{
					if (player_Motion.GetMotionNo() != MOTION_SMALL_WAIT)
					{
						player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
					}
				}
				else
				{
					if (player_Motion.GetMotionNo() != MOTION_BIG_WAIT)
					{
						player_Motion.ChangeMotion(MOTION_BIG_WAIT);
					}
				}

			}
		}
		else if (oy > 0)
		{
			player_Jump = 0;

		}
		//���ړ��̍����܂�A�E�ړ��̉E���܂�̏ꍇ�͈ړ�������������
		if (ox < 0 && player_Move > 0)
		{

			player_Move = 0;

			if (!player_ChangeBig)
			{
				if (player_Motion.GetMotionNo() == MOTION_SMALL_MOVE)
				{
					player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
				}
			}
			else
			{
				if (player_Motion.GetMotionNo() == MOTION_BIG_MOVE)
				{
					player_Motion.ChangeMotion(MOTION_BIG_WAIT);
				}
			}
		}
		else if (ox > 0 && player_Move < 0)
		{
			player_Move = 0;
			if (!player_ChangeBig)
			{
				if (player_Motion.GetMotionNo() == MOTION_SMALL_MOVE)
				{
					player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
				}
			}
			else
			{
				if (player_Motion.GetMotionNo() == MOTION_BIG_MOVE)
				{
					player_Motion.ChangeMotion(MOTION_BIG_WAIT);
				}
			}
		}
	}
}

void CPlayer::FallCheck(bool og)
{
	if (!og && !player_JumpFlg)
	{
		player_CheckGround = false;
	}
}

bool CPlayer::CollisionEnemy(CEnemy & ene)
{
	if (!ene.GetShow() || ene.GetEnemyDead() || player_DeadFlg || player_ClearFlg)
	{
		return false;
	}
	if (player_DamageWait > 0 || ene.GetMarioDamageWait() > 0)
	{
		return false;
	}
	CRectangle playerRect = GetRectPlayer();
	CRectangle enemyRect = ene.GetRect();
	CRectangle enemyAttackRect = ene.GetAttackRangeRect();
	if (ene.GetType() == ENEMY_MARIO && !player_playSEFlg)
	{
		if (ene.GetMarioChangeFlg())
		{
			player_ChangeBigSE.Play();
			player_playSEFlg = true;
		}
	}
	if (ene.GetMarioDeadFlg())
	{
		player_MarioDead = true;
	}
	//�X�P���g���̍U���͈͔���
	if (playerRect.CollisionRect(enemyAttackRect))
	{
		ene.DistanceBetweenPlayer(player_Position.x);
		ene.Setenemy_AttackFlg(true);
	}
	else
	{
		ene.Setenemy_AttackFlg(false);
	}
	//�G�Ƃ̓����蔻��
	if (playerRect.CollisionRect(enemyRect))
	{
		//�v���C���[��bottom���G�̏㔼����荂�����A���݂�
		if (playerRect.Bottom <= ene.Getenemy_PositionY() + 20)
		{
			//���݂����Ƃ��̏��W�����v
			player_Jump = -PLAYER_ENEMYSTEP_JUMPSPEED;
			player_StepEnemySE.Play();
			if (ene.GetType() == ENEMY_MARIO)
			{
				ene.MarioDamage(1);
				return true;
			}
			else
			{
				ene.Dead(true);
				score += SCORE_ENEMYSTEP;
				//�A���œ��񂾎��̃X�R�A���Z����
				AddScoreEnemyStep();
				return true;
			}

		}
		//����ȊO�̓_���[�W
		else
		{
			Damage();
			return true;
		}
	}
	//�G�̒e�Ǝ����̔���
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		if (!ene.GetShot(i).GetShow())
		{
			return false;
		}
		CRectangle srec = ene.GetShot(i).GetRect();
		if (srec.CollisionRect(playerRect))
		{
			Damage();
			ene.GetShot(i).SetShow(false);
			break;
		}
	}


	return false;
}

bool CPlayer::CollisionItem(CItem& item)
{
	if (!item.GetShow() || player_DeadFlg || player_ClearFlg)
	{
		return false;
	}
	if (!item.GetitemAppear() && item.GetType() == ITEM_MUSH)
	{
		return false;
	}
	//�A�C�e���̋�`�Ǝ����̋�`�œ����蔻��
	CRectangle playerRect = GetRectPlayer();
	CRectangle itemRect = item.GetRect();
	if (playerRect.CollisionRect(itemRect))
	{
		item.SetShow(false);
		switch (item.GetType())
		{
		case ITEM_MUSH:
			ChangeBig();
			player_ChangeBigSE.Play();
			scoreDesplayTime = SCORE_DISPLAYTIME;
			getScore = SCORE_GETITEM;
			score += SCORE_GETITEM;
			scoreDisplayFlg = true;
			break;
		case ITEM_COIN:
			player_GetCoinSE.Play();
			getCoinCount++;
			scoreDesplayTime = SCORE_DISPLAYTIME;
			getScore = SCORE_COIN;
			score += SCORE_COIN;
			scoreDisplayFlg = true;
			break;
		}
		return true;
	}
	return false;
}

void CPlayer::ChangeSize(void)
{
	//���剻
	if (player_ChangeBig)
	{
		player_DamageFlg = false;
		//�T�C�Y�ύX�E�F�C�g
		if (player_ChangeWait > 0)
		{

			player_ChangeWait--;


			if (player_ChangeWait == 59 || player_ChangeWait == 40 || player_ChangeWait == 20 || player_ChangeWait == 0)
			{


				if (player_Motion.GetMotionNo() != MOTION_BIG_WAIT)
				{

					player_Motion.ChangeMotion(MOTION_BIG_WAIT);

					//�A�j���[�V�����̍X�V
					player_Motion.Refresh();
					//�v���C���[��`
					player_RectTexture = player_Motion.GetSrcRect();
				}

			}

			else if (player_ChangeWait == 50 || player_ChangeWait == 30 || player_ChangeWait == 10)
			{

				if (player_Motion.GetMotionNo() != MOTION_SMALL_WAIT)
				{

					player_Motion.ChangeMotion(MOTION_SMALL_WAIT);

					//�A�j���[�V�����̍X�V
					player_Motion.Refresh();
					//�v���C���[��`
					player_RectTexture = player_Motion.GetSrcRect();
				}

			}
		}
	}
	//�_���[�W�i�����j
	else if (!player_ChangeBig && player_DamageFlg)
	{
		//�T�C�Y�ύX�E�F�C�g
		if (player_ChangeWait > 0)
		{

			player_ChangeWait--;

			if (player_ChangeWait == 59 || player_ChangeWait == 40 || player_ChangeWait == 20 || player_ChangeWait == 1)
			{


				if (player_Motion.GetMotionNo() != MOTION_SMALL_WAIT)
				{

					player_Motion.ChangeMotion(MOTION_SMALL_WAIT);

					//�A�j���[�V�����̍X�V
					player_Motion.Refresh();
					//�v���C���[��`
					player_RectTexture = player_Motion.GetSrcRect();

				}

			}
			else if (player_ChangeWait == 50 || player_ChangeWait == 30 || player_ChangeWait == 10)
			{

				if (player_Motion.GetMotionNo() != MOTION_BIG_WAIT)
				{

					player_Motion.ChangeMotion(MOTION_BIG_WAIT);

					//�A�j���[�V�����̍X�V
					player_Motion.Refresh();
					//�v���C���[��`
					player_RectTexture = player_Motion.GetSrcRect();

				}

			}
		}
		else if (player_ChangeWait <= 0 && player_DamageFlg)
		{
			player_DamageFlg = false;
		}
	}
}

void CPlayer::DeadJudge(void)
{
	//�v���C���[���S����
	if (player_HP <= 0)
	{
		player_DeadFlg = true;
	}
}


//�A���œG�𓥂񂾎��̃X�R�A���Z����
void CPlayer::AddScoreEnemyStep(void)
{
	//�A���œG�𓥂񂾐��̃J�E���g
	enemyDeadCount++;
	if (enemyDeadCount <= 1)
	{
		player1UpDisplayFlg = false;
		scoreDesplayTime = SCORE_DISPLAYTIME;
		//�l���X�R�A�\���p
		getScore = SCORE_ENEMYSTEP;
		//�l���X�R�A�\���t���O
		scoreDisplayFlg = true;
	}
	//���񂾐���2�ȏ�̎��A�ǉ��ŃX�R�A���Z
	if (enemyDeadCount > 1)
	{
		if (getScore < 1200)
		{
			scoreDesplayTime = SCORE_DISPLAYTIME;
			getScore *= 2;
			score += getScore;
			
			scoreDisplayFlg = true;
		}
		if (getScore >= 1400)
		{
			scoreDesplayTime = SCORE_DISPLAYTIME;
			//1UP
			player1UpDisplayFlg = true;
			player_Life++;
			player_1upSE.Play();

		}

	}
}

void CPlayer::Damage(void)
{
	if (player_HP == 1)
	{
		player_HP--;
		return;
	}
	else if (player_HP == 2)
	{
		if (player_ChangeBig)
		{
			player_DamageFlg = true;
			player_ChangeWait = 60;
			if (player_DamageWait <= 0)
			{
				player_DamageWait = PLAYER_INVINCIBLE;
			}
			player_ChangeSmallSE.Play();
			player_ChangeBig = false;
		}
		player_HP--;
		return;
	}
}

void CPlayer::ChangeBig(void)
{
	if (player_HP == 1)
	{
		if (!player_ChangeBig)
		{
			player_ChangeWait = 60;
			if (player_DamageWait <= 0)
			{
				player_DamageWait = PLAYER_INVINCIBLE;
			}
			player_HP++;
			player_ChangeBig = true;
		}
		return;
	}
}

void CPlayer::CreateAnimation()
{
	//�A�j���[�V�������쐬
	SpriteAnimationCreate animation[] = {

		{
			"���ҋ@",
			0,0,
			32,32,
			FALSE,{{5,0,0}}
		},
		{
			"���_���[�W",
			32,0,
			32,32,
			FALSE,{{5,0,0}}
		},
		{
			"���ړ�",
			0,32,
			32,32,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"���W�����v",
			0,64,
			32,32,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0}}
		},
		{
			"��ҋ@",
			0,96,
			32,64,
			FALSE,{{5,0,0}}
		},
		{
			"��_���[�W",
			32,96,
			32,64,
			FALSE,{{5,0,0}}
		},
		{
			"���ړ�",
			0,160,
			32,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"���W�����v",
			0,224,
			32,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0}}
		},

	};
	player_Motion.Create(animation, MOTION_COUNT);
}


