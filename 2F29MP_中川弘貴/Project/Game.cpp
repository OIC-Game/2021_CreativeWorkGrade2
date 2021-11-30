#include	"GameApp.h"
#include	"Game.h"

//�ύX����V�[��(�O���Q��)
extern int		gChangeScene;

/*
  �R���X�g���N�^
*/
CGame::CGame() {

}

/*
  �f�X�g���N�^
*/
CGame::~CGame() {

}

/*
  �ǂݍ���
*/
bool CGame::Load(void)
{
	//�e�N�X�`���̓ǂݍ���
	if (!m_RedPuyoTexture.Load("RedPuyo.png"))
	{
		return false;
	}
	//�e�N�X�`���̓ǂݍ���
	if (!m_BluePuyoTexture.Load("BluePuyo.png"))
	{
		return false;
	}
	//�e�N�X�`���̓ǂݍ���
	if (!m_YellowPuyoTexture.Load("YellowPuyo.png"))
	{
		return false;
	}
	//�e�N�X�`���̓ǂݍ���
	if (!m_GreenPuyoTexture.Load("GreenPuyo.png"))
	{
		return false;
	}
	//�e�N�X�`���̓ǂݍ���
	if (!m_BackTexture.Load("GameBack.png"))
	{
		return false;
	}
	//�e�N�X�`���̓ǂݍ���
	if (!m_CrossMarkTexture.Load("Batu.png"))
	{
		return false;
	}
	//�e�N�X�`���̓ǂݍ���
	if (!m_GameOverTexture.Load("GameOverBack.png"))
	{
		return false;
	}
	//�e�N�X�`���̓ǂݍ���
	if (!m_PauseTexture.Load("Pause.png"))
	{
		return false;
	}
	//���̓ǂݍ���
	if (!m_chainSound.Load("ChainSound.mp3"))
	{
		return false;
	}
	//���̓ǂݍ���
	if (!m_moveSound.Load("MoveSound.mp3"))
	{
		return false;
	}
	//���̓ǂݍ���
	if (!m_setSound.Load("SetSound.mp3"))
	{
		return false;
	}
	//���̓ǂݍ���
	if (!m_rotateSound.Load("RotateSound.mp3"))
	{
		return false;
	}
	//���̓ǂݍ���
	if (!m_gameBGM.Load("GameBGM.mp3"))
	{
		return false;
	}
	//���̓ǂݍ���
	if (!m_pauseSound.Load("PauseSound.mp3"))
	{
		return false;
	}
	//���̓ǂݍ���
	if (!m_gameOverSound.Load("GameOverSound.mp3"))
	{
		return false;
	}

	//���[�v�ݒ�
	m_gameBGM.SetLoop(TRUE);
	//�Đ�
	m_gameBGM.Play();

	return true;
}

/*
  ������
*/
void CGame::Initialize(void)
{
	//�e�N�X�`���̓ǂݍ���
	Load();

	//�t�B�[���h�̏����z�u
	for (int y = 0; y < FH; y++)
	{
		for (int x = 0; x < FW; x++)
		{
			if (x == 0 || x == FW - 1)
				m_field[y][x] = Wall;
			else if (y == FH - 1)
				m_field[y][x] = Wall;
			else
				m_field[y][x] = Empty;
		}
	}

	m_random.SetSeed(time(NULL));
	//�Ղ�̐F�������_���Ō��߂�
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_type[i][j] = m_random.Random(Red, TypeCount);
		}
	}

	
	//���ʂ̒���
	m_chainSound.SetVolume(0.60f);
	m_moveSound.SetVolume(0.54f);
	m_setSound.SetVolume(0.5f);
	m_rotateSound.SetVolume(0.3f);
	m_pauseSound.SetVolume(0.5f);
	m_gameOverSound.SetVolume(0.3f);
	m_gameBGM.SetVolume(0.05f);

	//�F�X�����l
	m_dropTimeCnt = DROP_SPEED;
	m_chainCnt = 0;
	m_maxChainCnt = 0;
	m_score = 0;
	m_readyTimeCnt = READY_TIME;
	m_waitTimeCnt = WAIT_TIME;
	m_downHoldTimeCnt = INIT_HOLD_TIME;
	m_leftHoldTimeCnt = INIT_HOLD_TIME;
	m_rightHoldTimeCnt = INIT_HOLD_TIME;
	m_eFlow = Flow::Ready;
	m_pos.x = INIT_POSITION_X;
	m_pos.y = INIT_POSITION_Y;
	m_spin.x = INIT_SPIN_X;
	m_spin.y = INIT_SPIN_Y;
	m_sFldPos.x = INIT_FIELD_POSITION_X;
	m_sFldPos.y = INIT_FIELD_POSITION_Y;
	m_eRotation = Rotation::Top;
	m_endFlg = false;

	fade.FadeIn();
}

void CGame::ChainCheck(int y, int x)
{
	if (m_field[y][x] != Empty && m_field[y][x] != Wall &&
		!m_puyoCheckFlg[y][x])
	{
		m_puyoCheckFlg[y][x] = true;
		m_bondCnt++;
		if (m_field[y][x] == m_field[y - 1][x])
		{
			ChainCheck(y - 1, x);
		}
		if (m_field[y][x] == m_field[y][x + 1])
		{
			ChainCheck(y, x + 1);
		}
		if (m_field[y][x] == m_field[y + 1][x])
		{
			ChainCheck(y + 1, x);
		}
		if (m_field[y][x] == m_field[y][x - 1])
		{
			ChainCheck(y, x - 1);
		}
	}
}

/*
  �X�V
*/
void CGame::Update(void)
{
	//�t�F�[�h�̏���
	fade.Update();
	if (fade.GetFadeIn() || fade.GetFadeOut())
	{
		return;
	}
	else if (m_endFlg)
	{
		m_gameBGM.Stop();
		m_gameOverSound.Stop();
		gChangeScene = SCENENO_TITLE;
	}

	//�����S�̗̂���
	switch (m_eFlow)
	{
		case Flow::Ready:
			ReadyUpdate();
			break;
		case Flow::Pause:
			PauseUpdate();
			break;
		case Flow::Drop:
			DropUpdate();
			break;
		case Flow::Tear:
			TearUpdate();
			break;
		case Flow::Chain:
			ChainUpdate();
			break;
		case Flow::ReStart:
			ReStartUpdate();
			break;
		case Flow::GameOver:
			GameOverUpdate();
			break;
	}
}

//ReadyGo �J�E���g�_�E�� �̏���
void CGame::ReadyUpdate()
{
	if (m_readyTimeCnt <= 0)
	{
		m_eFlow = Drop;
	}
	else
	{
		m_readyTimeCnt--;
	}
}
//�|�[�Y(�ꎞ��~)���̏���
void CGame::PauseUpdate()
{
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
	{
		m_pauseSound.Play();
		m_gameBGM.SetVolume(0.05f);
		m_eFlow = Drop;
	}
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		fade.FadeOut();
		m_endFlg = true;

	}
}
//�v���C���[���Ղ�𑀍삷��H��
void CGame::DropUpdate()
{
	//�|�[�Y
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
	{
		m_pauseSound.Play();
		m_gameBGM.SetVolume(0.01f);
		m_eFlow = Pause;
	}

	//���R����
	if (m_dropTimeCnt < 0)
	{
		//�m�肵�Ă��邩
		if ((m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty && m_eRotation == Top) ||
			(m_field[m_sFldPos.y + 2][m_sFldPos.x] != Empty && m_eRotation == Bottom) ||
			((m_field[m_sFldPos.y + 1][m_sFldPos.x - 1] != Empty ||
				m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty) && m_eRotation == Left) ||
				((m_field[m_sFldPos.y + 1][m_sFldPos.x + 1] != Empty ||
					m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty) && m_eRotation == Right))
		{

			//��ʊO�ɐݒu���Ȃ��悤��
			if (m_sFldPos.y >= 0) {
				//���C���̂Ղ���i�[
				m_field[m_sFldPos.y][m_sFldPos.x] = m_type[0][0];
			}
			//�T�u�̂Ղ���i�[
			if (m_eRotation == Top && m_sFldPos.y - 1 >= 0)
				m_field[m_sFldPos.y - 1][m_sFldPos.x] = m_type[0][1];
			if (m_eRotation == Left && m_sFldPos.y >= 0)
				m_field[m_sFldPos.y][m_sFldPos.x - 1] = m_type[0][1];
			if (m_eRotation == Right && m_sFldPos.y >= 0)
				m_field[m_sFldPos.y][m_sFldPos.x + 1] = m_type[0][1];
			if (m_eRotation == Bottom && m_sFldPos.y + 1 >= 0)
				m_field[m_sFldPos.y + 1][m_sFldPos.x] = m_type[0][1];

			//�X�R�A���Z
			m_score += 10;

			//�ݒu��
			m_setSound.Play();

			//������̍H���Ɉڂ�
			m_eFlow = Tear;

			return;
		}

		//�m�肵�ĂȂ���Έ�}�X������
		m_pos.y += PUYO_SIZE;
		m_sFldPos.y += 1;
		m_dropTimeCnt = DROP_SPEED;
	}
	else
	{
		m_dropTimeCnt--;
	}

	//���Ɉړ�
	if (g_pInput->IsKeyPush(MOFKEY_A) &&
		((m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty &&
			m_field[m_sFldPos.y - 1][m_sFldPos.x - 1] == Empty && m_eRotation == Top || m_sFldPos.y == 0) ||
			(m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty &&
				m_field[m_sFldPos.y + 1][m_sFldPos.x - 1] == Empty && m_eRotation == Bottom) ||
				(m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty && m_eRotation == Right) ||
			(m_field[m_sFldPos.y][m_sFldPos.x - 2] == Empty && m_eRotation == Left)))
	{
		//�ړ���
		m_moveSound.Play();

		m_leftHoldTimeCnt = INIT_HOLD_TIME;
		//���Ɉ�}�X������
		m_pos.x -= PUYO_SIZE;
		m_sFldPos.x -= 1;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_A) &&
		((m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty &&
			m_field[m_sFldPos.y - 1][m_sFldPos.x - 1] == Empty && m_eRotation == Top || m_sFldPos.y == 0) ||
			(m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty &&
				m_field[m_sFldPos.y + 1][m_sFldPos.x - 1] == Empty && m_eRotation == Bottom) ||
				(m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty && m_eRotation == Right) ||
			(m_field[m_sFldPos.y][m_sFldPos.x - 2] == Empty && m_eRotation == Left)))
	{
		if (m_leftHoldTimeCnt <= 0)
		{
			//�ړ���
			m_moveSound.Play();

			m_pos.x -= PUYO_SIZE;
			m_sFldPos.x -= 1;
			m_leftHoldTimeCnt = PUYO_SPEED;
		}
		else
		{
			m_leftHoldTimeCnt--;
		}
	}

	//�E�Ɉړ�
	if (g_pInput->IsKeyPush(MOFKEY_D) &&
		((m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty &&
			m_field[m_sFldPos.y - 1][m_sFldPos.x + 1] == Empty && m_eRotation == Top || m_sFldPos.y == 0) ||
			(m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty &&
				m_field[m_sFldPos.y + 1][m_sFldPos.x + 1] == Empty && m_eRotation == Bottom) ||
				(m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty && m_eRotation == Left) ||
			(m_field[m_sFldPos.y][m_sFldPos.x + 2] == Empty && m_eRotation == Right)))
	{
		//�ړ���
		m_moveSound.Play();

		m_rightHoldTimeCnt = INIT_HOLD_TIME;
		//�E�Ɉ�}�X������
		m_pos.x += PUYO_SIZE;
		m_sFldPos.x += 1;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_D) &&
		((m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty &&
			m_field[m_sFldPos.y - 1][m_sFldPos.x + 1] == Empty && m_eRotation == Top || m_sFldPos.y == 0) ||
			(m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty &&
				m_field[m_sFldPos.y + 1][m_sFldPos.x + 1] == Empty && m_eRotation == Bottom) ||
				(m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty && m_eRotation == Left) ||
			(m_field[m_sFldPos.y][m_sFldPos.x + 2] == Empty && m_eRotation == Right)))
	{
		if (m_rightHoldTimeCnt <= 0)
		{
			//�ړ���
			m_moveSound.Play();

			m_pos.x += PUYO_SIZE;
			m_sFldPos.x += 1;
			m_rightHoldTimeCnt = PUYO_SPEED;
		}
		else
		{
			m_rightHoldTimeCnt--;
		}
	}

	//�L�[�ɂ���ĉ��Ɉړ�(1�}�X)
	if (g_pInput->IsKeyPush(MOFKEY_S))
	{
		m_downHoldTimeCnt = INIT_HOLD_TIME;
		//�������Ƃ���1�}�X���Ƃ�
		m_dropTimeCnt = -1;
	}
	//�L�[�ɂ���ĉ��Ɉړ�(�����~��)
	else if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		if (m_downHoldTimeCnt <= 0) {
			//�������ō����~��
			m_dropTimeCnt -= PUYO_SPEED * 3;
		}
		else
		{
			m_downHoldTimeCnt--;
		}
	}

	//��]�E������
	if (g_pInput->IsKeyPush(MOFKEY_J))
	{
		if (m_eRotation == Top)
		{
			if (m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty ||
				m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty)
			{
				if (m_field[m_sFldPos.y][m_sFldPos.x - 1] != Empty)
				{
					m_pos.x += PUYO_SIZE;
					m_sFldPos.x += 1;
				}
				m_eRotation = Left;
				m_spin.x = -PUYO_SIZE;
				m_spin.y = 0;
			}

		}
		else if (m_eRotation == Left)
		{
			if (m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty)
			{
				m_pos.y -= PUYO_SIZE;
				m_sFldPos.y -= 1;
			}
			m_eRotation = Bottom;
			m_spin.x = 0;
			m_spin.y = PUYO_SIZE;
		}
		else if (m_eRotation == Bottom)
		{
			if (m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty ||
				m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty)
			{
				if (m_field[m_sFldPos.y][m_sFldPos.x + 1] != Empty)
				{
					m_pos.x -= PUYO_SIZE;
					m_sFldPos.x -= 1;
				}
				m_eRotation = Right;
				m_spin.x = PUYO_SIZE;
				m_spin.y = 0;
			}
		}
		else if (m_eRotation == Right)
		{
			m_eRotation = Top;
			m_spin.x = 0;
			m_spin.y = -PUYO_SIZE;
		}
		//���E�ɕǂ�Ղ悪�����]���s���Ȃ������ꍇ
		else
		{
			
		}

		//��]��
		m_rotateSound.Play();
	}

	//��]�E�E����
	if (g_pInput->IsKeyPush(MOFKEY_K))
	{
		if (m_eRotation == Top)
		{
			if (m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty ||
				m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty)
			{
				if (m_field[m_sFldPos.y][m_sFldPos.x + 1] != Empty)
				{
					m_pos.x -= PUYO_SIZE;
					m_sFldPos.x -= 1;
				}
				m_eRotation = Right;
				m_spin.x = PUYO_SIZE;
				m_spin.y = 0;
			}
		}
		else if (m_eRotation == Right)
		{
			if (m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty)
			{
				m_pos.y -= PUYO_SIZE;
				m_sFldPos.y -= 1;
			}
			m_eRotation = Bottom;
			m_spin.x = 0;
			m_spin.y = PUYO_SIZE;
		}
		else if (m_eRotation == Bottom)
		{
			if (m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty ||
				m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty)
			{
				if (m_field[m_sFldPos.y][m_sFldPos.x - 1] != Empty)
				{
					m_pos.x += PUYO_SIZE;
					m_sFldPos.x += 1;
				}
				m_eRotation = Left;
				m_spin.x = -PUYO_SIZE;
				m_spin.y = 0;
			}
		}
		else if (m_eRotation == Left)
		{
			m_eRotation = Top;
			m_spin.x = 0;
			m_spin.y = -PUYO_SIZE;
		}

		//��]��
		m_rotateSound.Play();
	}
}
//������@�����Ă���Ղ�ւ̑Ώ�
void CGame::TearUpdate()
{
	if (m_waitTimeCnt < 0) {
		for (int y = FH - 2; y >= 0; y--)
		{
			for (int x = FW - 1; x >= 1; x--)
			{
				//�Ղ悪���ɕ����Ă���Ƃ�
				if (m_field[y][x] != Empty &&
					m_field[y + 1][x] == Empty)
				{

					for (int i = y; i <= FH - 2; i++)
					{
						m_field[i + 1][x] = m_field[i][x];
						m_field[i][x] = 0;
						if (m_field[i + 2][x] != Empty)
						{
							break;
						}
					}

				}
			}
		}

		//����s�\���� sleep�̑��� 20�͓K��
		m_waitTimeCnt = WAIT_TIME;
		m_eFlow = Chain;
	}
	else
	{
		m_waitTimeCnt--;
	}
}
//�A��
void CGame::ChainUpdate()
{
	if (m_waitTimeCnt < 0) {
		//�A���̃`�F�b�N
		//�A�����s��ꂽ�ꍇ�͂�����ɖ߂��x���n����B
		//�A�����s���Ȃ������ꍇ�A���X�^�[�g��
		m_chainFlg = false;

		for (int y = 0; y < FH; y++)
		{
			for (int x = 0; x < FW; x++)
			{
				ChainCheck(y, x);
				if (m_bondCnt >= 4)
				{
					for (int i = 0; i < FH; i++)
					{
						for (int j = 0; j < FW; j++)
						{
							if (m_puyoCheckFlg[i][j])
							{
								m_destroyFlg[i][j] = true;
							}

						}
					}
				}
				m_bondCnt = 0;
				for (int i = 0; i < FH; i++)
				{
					for (int j = 0; j < FW; j++)
					{
						m_puyoCheckFlg[i][j] = false;

					}
				}
			}
		}

		for (int i = 0; i < FH; i++)
		{
			for (int j = 0; j < FW; j++)
			{
				if (m_destroyFlg[i][j])
				{
					m_field[i][j] = Empty;
					m_chainFlg = true;
				}
				m_destroyFlg[i][j] = false;
			}
		}


		if (m_chainFlg)
		{
			//����s�\���� �A�����킩��₷���Ȃ�悤�������߂�
			m_waitTimeCnt = WAIT_TIME * 2;
			//�A�����̉�
			m_chainSound.Play();
			//���ɖ炷�A�����̃s�b�`���グ��
			m_chainSound.SetPitch(m_chainSound.GetPitch() + 0.06f);
			//�A�������J�E���g����(+1)
			m_chainCnt++;
			//������Ɉڂ�
			m_eFlow = Tear;
		}
		else if (!m_chainFlg)
		{
			//����s�\���� sleep�̑��� 40�͓K��
			m_waitTimeCnt = WAIT_TIME;

			//�o�c������(2,3,4,5)�̂ǂꂩ���炪����΃Q�[���I�[�o�[
			if (m_field[0][3] == Red ||
				m_field[0][3] == Blue ||
				m_field[0][3] == Yellow ||
				m_field[0][3] == Green)
			{
				m_gameBGM.Stop();
				m_gameOverSound.Play();
				m_eFlow = GameOver;
			}
			else
			{
				//�ő�A�����Ƃ̔�r
				if (m_maxChainCnt < m_chainCnt)
				{
					m_maxChainCnt = m_chainCnt;
				}

				//�A�����ɉ����ăX�R�A�̉��Z
				for (int i = 1; i <= m_chainCnt; i++)
				{
					m_score += m_chainCnt * 100;
				}

				m_eFlow = ReStart;
			}
		}
	}
	else
	{
		m_waitTimeCnt--;
	}
}
//�Q�[���I�[�o�[�ɂȂ��Ă��Ȃ���� �ēx�Ղ���~�炷
void CGame::ReStartUpdate()
{
	//���̂Ղ�𑀍�ł���悤�A�Z�b�g����
	m_type[0][0] = m_type[1][0];
	m_type[0][1] = m_type[1][1];

	//����̂Ղ���i�[���Ă�������
	//�Ղ�̐F�������_���Ō��߂�
	m_type[1][0] = m_random.Random(Red, TypeCount);
	m_type[1][1] = m_random.Random(Red, TypeCount);

	//�F�X�����l
	m_dropTimeCnt = DROP_SPEED;
	m_chainCnt = 0;

	//�A�����̃s�b�`�̃��Z�b�g
	m_chainSound.SetPitch(1.0f);

	m_eFlow = Drop;
	m_pos.x = 200.0f;
	m_pos.y = 100.0f;
	m_spin.x = 0.0f;
	m_spin.y = -50.0f;
	m_sFldPos.x = 3;
	m_sFldPos.y = 0;
	m_eRotation = Rotation::Top;
}
//�Q�[���I�[�o�[
void CGame::GameOverUpdate()
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		fade.FadeOut();
		m_endFlg = true;

	}
}

/*
  �`��
*/
void CGame::Render(void)
{
	//�w�i
	m_BackTexture.Render(0,0);

	//�p�Y�������̔w�i
	for (int y = 0; y < FH - 1; y++)
	{
		for (int x = 1; x < FW - 1; x++)
		{
			CGraphicsUtilities::RenderFillRect(BL + x * BL, BL * 2 + y * BL, x * BL + BL * 2, y * BL + BL * 3, MOF_COLOR_WHITE);
		}
	}

	//�Q�[���I�[�o�[�́~
	m_CrossMarkTexture.Render(BL * 4, BL * 2);

	//�t�B�[���h�̕`��
	for (int y = 0; y < FH; y++)
	{
		for (int x = 0; x < FW; x++)
		{
			if (m_field[y][x] == Green)
				m_GreenPuyoTexture.Render(BL + x * BL, BL * 2 + y * BL);

			if (m_field[y][x] == Yellow)
				m_YellowPuyoTexture.Render(BL + x * BL, BL * 2 + y * BL);

			if (m_field[y][x] == Blue)
				m_BluePuyoTexture.Render(BL + x * BL, BL * 2 + y * BL);

			if (m_field[y][x] == Red)
				m_RedPuyoTexture.Render(BL + x * BL, BL * 2 + y * BL);

			if (m_field[y][x] == Wall)
				CGraphicsUtilities::RenderFillRect(BL + x * BL, BL * 2 + y * BL, x * BL + BL * 2, y * BL + BL * 3, MOF_COLOR_BLACK);

		}
	}

	//�ҋ@���̂Ղ�
	CGraphicsUtilities::RenderString(490, 100, "NEXT");
	CGraphicsUtilities::RenderFillRect(480, 130, 550, 250, MOF_COLOR_CBLACK);
	if (m_type[1][1] == Red)
		m_RedPuyoTexture.Render(490, 140);

	else if (m_type[1][1] == Blue)
		m_BluePuyoTexture.Render(490, 140);

	else if (m_type[1][1] == Yellow)
		m_YellowPuyoTexture.Render(490, 140);

	else if (m_type[1][1] == Green)
		m_GreenPuyoTexture.Render(490, 140);

	if (m_type[1][0] == Red)
		m_RedPuyoTexture.Render(490, 190);

	else if (m_type[1][0] == Blue)
		m_BluePuyoTexture.Render(490, 190);

	else if (m_type[1][0] == Yellow)
		m_YellowPuyoTexture.Render(490, 190);

	else if (m_type[1][0] == Green)
		m_GreenPuyoTexture.Render(490, 190);


	//���쒆�̂Ղ�̕`��
	if (m_eFlow == Drop || m_eFlow == Pause) {
		//�{��
		if (m_type[0][0] == Red)
			m_RedPuyoTexture.Render(m_pos.x, m_pos.y);

		if (m_type[0][0] == Blue)
			m_BluePuyoTexture.Render(m_pos.x, m_pos.y);

		if (m_type[0][0] == Yellow)
			m_YellowPuyoTexture.Render(m_pos.x, m_pos.y);

		if (m_type[0][0] == Green)
			m_GreenPuyoTexture.Render(m_pos.x, m_pos.y);

		//�T�u
		if (m_type[0][1] == Red)	
			m_RedPuyoTexture.Render(m_pos.x + m_spin.x, m_pos.y + m_spin.y);

		if (m_type[0][1] == Blue)
			m_BluePuyoTexture.Render(m_pos.x + m_spin.x, m_pos.y + m_spin.y);

		if (m_type[0][1] == Yellow)
			m_YellowPuyoTexture.Render(m_pos.x + m_spin.x, m_pos.y + m_spin.y);

		if (m_type[0][1] == Green)
			m_GreenPuyoTexture.Render(m_pos.x + m_spin.x, m_pos.y + m_spin.y);
	}

	// �Q�[���I�[�o�[���b�Z�[�W
	if (m_eFlow == GameOver)
	{
		m_GameOverTexture.Render(100, 100);
		//CGraphicsUtilities::RenderString(500, 320, MOF_COLOR_BLACK, "�Q�[���I�[�o�[");
		CGraphicsUtilities::RenderString(500, 370, MOF_COLOR_BLACK, "�^�C�g���ɖ߂�[Enter]");
	}

	//�J�E���g�_�E���\��
	if (m_eFlow == Ready)
	{
		if (m_readyTimeCnt >= 110)
			CGraphicsUtilities::RenderString(210, 350, MOF_COLOR_BLACK, "Ready");
		else if(m_readyTimeCnt >= 20)
			CGraphicsUtilities::RenderString(220, 350, MOF_COLOR_BLACK, "Go");
	}

	//�A���\��
	if (m_chainCnt >= 1)
	{
		CGraphicsUtilities::RenderFillRect(210,350,280,380, MOF_COLOR_WHITE);
		CGraphicsUtilities::RenderString(210, 350, MOF_COLOR_BLACK, "%d�A��", m_chainCnt);
	}

	//�X�R�A
	CGraphicsUtilities::RenderString(800, 138, MOF_COLOR_BLACK, "%d",m_score);

	//�ő�A����
	CGraphicsUtilities::RenderString(900, 210, MOF_COLOR_BLACK, "%d", m_maxChainCnt);

	//�J���Ƀu���b�N�������Ȃ��悤�ɁA��ʏ㕔���B��
	//CGraphicsUtilities::RenderFillRect(BL, 50, BL * 9, BL * 2, MOF_COLOR_BLACK);

	//esc�Ń|�[�Y
	CGraphicsUtilities::RenderString(885, 12, MOF_COLOR_BLACK, "Pause[Esc]");

	//�|�[�Y
	if (m_eFlow == Pause)
	{
		//�����Â�����
		CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_ARGB(150, 0, 0, 0));
		//�|�[�Y��ʂ̕`��
		m_PauseTexture.Render(256, 167);
	}

	fade.Render();
}

/*
  ���
*/
void CGame::Release(void)
{
	//�e�N�X�`���̉��
	m_RedPuyoTexture.Release();
	m_BluePuyoTexture.Release();
	m_YellowPuyoTexture.Release();
	m_GreenPuyoTexture.Release();
	m_BackTexture.Release();
	m_CrossMarkTexture.Release();
	m_GameOverTexture.Release();
	m_PauseTexture.Release();

	//���̉��
	m_chainSound.Release();
	m_moveSound.Release();
	m_setSound.Release();
	m_rotateSound.Release();
	m_gameBGM.Release();
	m_pauseSound.Release();
	m_gameOverSound.Release();

}