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

	random.SetSeed(time(NULL));
	//�Ղ�̐F�������_���Ō��߂�
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_type[i][j] = random.Random(Red, TypeCount);
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
	m_readyTime = 200;
	m_sleepTime = 20;
	m_downHoldTime = 10;
	m_leftHoldTime = 10;
	m_rightHoldTime = 10;
	eFlow = ready;
	pos.x = 200.0f;
	pos.y = 100.0f;
	spin.x = 0.0f;
	spin.y = -50.0f;
	sFPos.x = 3;
	sFPos.y = 0;
	eStep = E_Rotation::Top;
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

	//ReadyGo �J�E���g�_�E�� �̏���
	if (eFlow == ready)
	{

		if (m_readyTime <= 0)
		{
			eFlow = drop;
		}
		else
		{
			m_readyTime--;
		}
	}

	//�|�[�Y(�ꎞ��~)���̏���
	else if (eFlow == pause)
	{
		if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
		{
			m_pauseSound.Play();
			m_gameBGM.SetVolume(0.05f);
			eFlow = drop;
		}
		if (g_pInput->IsKeyPush(MOFKEY_RETURN))
		{
			fade.FadeOut();
			m_endFlg = true;

		}
	}

	//�v���C���[���Ղ�𑀍삷��H��
	else if (eFlow == drop) {
		
		//�|�[�Y
		if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
		{
			m_pauseSound.Play();
			m_gameBGM.SetVolume(0.01f);
			eFlow = pause;
		}

		//���R����
		if (m_dropTimeCnt < 0)
		{
			//�m�肵�Ă��邩
			if ((m_field[sFPos.y + 1][sFPos.x] != Empty && eStep == Top) ||
				(m_field[sFPos.y + 2][sFPos.x] != Empty && eStep == Bottom) ||
				((m_field[sFPos.y + 1][sFPos.x - 1] != Empty ||
					m_field[sFPos.y + 1][sFPos.x] != Empty) && eStep == Left) ||
					((m_field[sFPos.y + 1][sFPos.x + 1] != Empty ||
						m_field[sFPos.y + 1][sFPos.x] != Empty) && eStep == Right))
			{

				//��ʊO�ɐݒu���Ȃ��悤��
				if (sFPos.y >= 0) {
					//���C���̂Ղ���i�[
					m_field[sFPos.y][sFPos.x] = m_type[0][0];
				}
				//�T�u�̂Ղ���i�[
				if (eStep == Top && sFPos.y - 1 >= 0)
					m_field[sFPos.y - 1][sFPos.x] = m_type[0][1];
				if (eStep == Left && sFPos.y >= 0)
					m_field[sFPos.y][sFPos.x - 1] = m_type[0][1];
				if (eStep == Right && sFPos.y >= 0)
					m_field[sFPos.y][sFPos.x + 1] = m_type[0][1];
				if (eStep == Bottom && sFPos.y + 1 >= 0)
					m_field[sFPos.y + 1][sFPos.x] = m_type[0][1];

				//�X�R�A���Z
				m_score += 10;

				//�ݒu��
				m_setSound.Play();

				//������̍H���Ɉڂ�
				eFlow = tear;

				return;
			}

			//�m�肵�ĂȂ���Έ�}�X������
			pos.y += PUYO_SIZE;
			sFPos.y += 1;
			m_dropTimeCnt = DROP_SPEED;
		}
		else
		{
			m_dropTimeCnt--;
		}

		//���Ɉړ�
		if (g_pInput->IsKeyPush(MOFKEY_A) &&
			((m_field[sFPos.y][sFPos.x - 1] == Empty &&
				m_field[sFPos.y - 1][sFPos.x - 1] == Empty && eStep == Top) ||
				(m_field[sFPos.y][sFPos.x - 1] == Empty &&
					m_field[sFPos.y + 1][sFPos.x - 1] == Empty && eStep == Bottom) ||
					(m_field[sFPos.y][sFPos.x - 1] == Empty && eStep == Right) ||
				(m_field[sFPos.y][sFPos.x - 2] == Empty && eStep == Left)))
		{
			//�ړ���
			m_moveSound.Play();

			m_leftHoldTime = 10;
			//���Ɉ�}�X������
			pos.x -= PUYO_SIZE;
			sFPos.x -= 1;
		}
		else if (g_pInput->IsKeyHold(MOFKEY_A) &&
			((m_field[sFPos.y][sFPos.x - 1] == Empty &&
				m_field[sFPos.y - 1][sFPos.x - 1] == Empty && eStep == Top) ||
				(m_field[sFPos.y][sFPos.x - 1] == Empty &&
					m_field[sFPos.y + 1][sFPos.x - 1] == Empty && eStep == Bottom) ||
					(m_field[sFPos.y][sFPos.x - 1] == Empty && eStep == Right) ||
				(m_field[sFPos.y][sFPos.x - 2] == Empty && eStep == Left)))
		{
			if (m_leftHoldTime <= 0)
			{
				//�ړ���
				m_moveSound.Play();

				pos.x -= PUYO_SIZE;
				sFPos.x -= 1;
				m_leftHoldTime = 5;
			}
			else
			{
				m_leftHoldTime--;
			}
		}

		//�E�Ɉړ�
		if (g_pInput->IsKeyPush(MOFKEY_D) &&
			((m_field[sFPos.y][sFPos.x + 1] == Empty &&
				m_field[sFPos.y - 1][sFPos.x + 1] == Empty && eStep == Top) ||
				(m_field[sFPos.y][sFPos.x + 1] == Empty &&
					m_field[sFPos.y + 1][sFPos.x + 1] == Empty && eStep == Bottom) ||
					(m_field[sFPos.y][sFPos.x + 1] == Empty && eStep == Left) ||
				(m_field[sFPos.y][sFPos.x + 2] == Empty && eStep == Right)))
		{
			//�ړ���
			m_moveSound.Play();

			m_rightHoldTime = 10;
			//�E�Ɉ�}�X������
			pos.x += PUYO_SIZE;
			sFPos.x += 1;
		}
		else if (g_pInput->IsKeyHold(MOFKEY_D) &&
			((m_field[sFPos.y][sFPos.x + 1] == Empty &&
				m_field[sFPos.y - 1][sFPos.x + 1] == Empty && eStep == Top) ||
				(m_field[sFPos.y][sFPos.x + 1] == Empty &&
					m_field[sFPos.y + 1][sFPos.x + 1] == Empty && eStep == Bottom) ||
					(m_field[sFPos.y][sFPos.x + 1] == Empty && eStep == Left) ||
				(m_field[sFPos.y][sFPos.x + 2] == Empty && eStep == Right)))
		{
			if (m_rightHoldTime <= 0)
			{
				//�ړ���
				m_moveSound.Play();

				pos.x += PUYO_SIZE;
				sFPos.x += 1;
				m_rightHoldTime = 5;
			}
			else
			{
				m_rightHoldTime--;
			}
		}

		//�L�[�ɂ���ĉ��Ɉړ�(1�}�X)
		if (g_pInput->IsKeyPush(MOFKEY_S))
		{
			m_downHoldTime = 10;
			//�������Ƃ���1�}�X���Ƃ�
			m_dropTimeCnt = -1;
		}
		//�L�[�ɂ���ĉ��Ɉړ�(�����~��)
		else if (g_pInput->IsKeyHold(MOFKEY_S))
		{	
			if (m_downHoldTime <= 0) {
				//�������ō����~��
				m_dropTimeCnt -= 15;
			}
			else
			{
				m_downHoldTime--;
			}
		}

		//��]�E������
		if (g_pInput->IsKeyPush(MOFKEY_J))
		{
			if (eStep == Top)
			{
				if (m_field[sFPos.y][sFPos.x - 1] == Empty ||
					m_field[sFPos.y][sFPos.x + 1] == Empty)
				{
					if (m_field[sFPos.y][sFPos.x - 1] != Empty)
					{
						pos.x += PUYO_SIZE;
						sFPos.x += 1;
					}
					eStep = Left;
					spin.x = -PUYO_SIZE;
					spin.y = 0;
				}

			}
			else if (eStep == Left)
			{
				if (m_field[sFPos.y + 1][sFPos.x] != Empty)
				{
					pos.y -= PUYO_SIZE;
					sFPos.y -= 1;
				}
				eStep = Bottom;
				spin.x = 0;
				spin.y = PUYO_SIZE;
			}
			else if (eStep == Bottom)
			{
				if (m_field[sFPos.y][sFPos.x - 1] == Empty ||
					m_field[sFPos.y][sFPos.x + 1] == Empty)
				{
					if (m_field[sFPos.y][sFPos.x + 1] != Empty)
					{
						pos.x -= PUYO_SIZE;
						sFPos.x -= 1;
					}
					eStep = Right;
					spin.x = PUYO_SIZE;
					spin.y = 0;
				}
			}
			else if (eStep == Right)
			{
				eStep = Top;
				spin.x = 0;
				spin.y = -PUYO_SIZE;
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
			if (eStep == Top)
			{
				if (m_field[sFPos.y][sFPos.x - 1] == Empty ||
					m_field[sFPos.y][sFPos.x + 1] == Empty)
				{
					if (m_field[sFPos.y][sFPos.x + 1] != Empty)
					{
						pos.x -= PUYO_SIZE;
						sFPos.x -= 1;
					}
					eStep = Right;
					spin.x = PUYO_SIZE;
					spin.y = 0;
				}
			}
			else if (eStep == Right)
			{
				if (m_field[sFPos.y + 1][sFPos.x] != Empty)
				{
					pos.y -= PUYO_SIZE;
					sFPos.y -= 1;
				}
				eStep = Bottom;
				spin.x = 0;
				spin.y = PUYO_SIZE;
			}
			else if (eStep == Bottom)
			{
				if (m_field[sFPos.y][sFPos.x - 1] == Empty ||
					m_field[sFPos.y][sFPos.x + 1] == Empty)
				{
					if (m_field[sFPos.y][sFPos.x - 1] != Empty)
					{
						pos.x += PUYO_SIZE;
						sFPos.x += 1;
					}
					eStep = Left;
					spin.x = -PUYO_SIZE;
					spin.y = 0;
				}
			}
			else if (eStep == Left)
			{
				eStep = Top;
				spin.x = 0;
				spin.y = -PUYO_SIZE;
			}

			//��]��
			m_rotateSound.Play();
		}

	}

	//������@�����Ă���Ղ�ւ̑Ώ�
	else if (eFlow == tear)
	{
		
		if (m_sleepTime < 0) {
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
			m_sleepTime = 20;
			eFlow = chain;
		}
		else
		{
			m_sleepTime--;
		}
	}

	//�A��
	else if (eFlow == chain)
	{
		if (m_sleepTime < 0) {
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
				//����s�\���� sleep�̑��� 40�͓K��
				m_sleepTime = 40;
				//�A�����̉�
				m_chainSound.Play();
				//���ɖ炷�A�����̃s�b�`���グ��
				m_chainSound.SetPitch(m_chainSound.GetPitch() + 0.06f);
				//�A�������J�E���g����(+1)
				m_chainCnt++;
				//������Ɉڂ�
				eFlow = tear;
			}
			else if (!m_chainFlg)
			{
				//����s�\���� sleep�̑��� 40�͓K��
				m_sleepTime = 20;

				//�o�c������(2,3,4,5)�̂ǂꂩ���炪����΃Q�[���I�[�o�[
				if (m_field[0][3] == Red ||
					m_field[0][3] == Blue ||
					m_field[0][3] == Yellow ||
					m_field[0][3] == Green)
				{
					m_gameBGM.Stop();
					m_gameOverSound.Play();
					eFlow = gameOver;
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

					eFlow = reStart;
				}
			}
		}
		else
		{
			m_sleepTime--;
		}
	}

	//�Q�[���I�[�o�[�ɂȂ��Ă��Ȃ���� �ēx�Ղ���~�炷
	else if (eFlow == reStart)
	{
		//���̂Ղ�𑀍�ł���悤�A�Z�b�g����
		m_type[0][0] = m_type[1][0];
		m_type[0][1] = m_type[1][1];

		//����̂Ղ���i�[���Ă�������
		//�Ղ�̐F�������_���Ō��߂�
		m_type[1][0] = random.Random(Red, TypeCount);
		m_type[1][1] = random.Random(Red, TypeCount);

		//�F�X�����l
		m_dropTimeCnt = DROP_SPEED;
		m_chainCnt = 0;

		//�A�����̃s�b�`�̃��Z�b�g
		m_chainSound.SetPitch(1.0f);

		eFlow = drop;
		pos.x = 200.0f;
		pos.y = 100.0f;
		spin.x = 0.0f;
		spin.y = -50.0f;
		sFPos.x = 3;
		sFPos.y = 0;
		eStep = E_Rotation::Top;

	}

	//�Q�[���I�[�o�[
	else if (eFlow == gameOver)
	{
		if (g_pInput->IsKeyPush(MOFKEY_RETURN))
		{
			fade.FadeOut();
			m_endFlg = true;

		}
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
	if (eFlow == drop || eFlow == pause) {
		//�{��
		if (m_type[0][0] == Red)
			m_RedPuyoTexture.Render(pos.x, pos.y);

		if (m_type[0][0] == Blue)
			m_BluePuyoTexture.Render(pos.x, pos.y);

		if (m_type[0][0] == Yellow)
			m_YellowPuyoTexture.Render(pos.x, pos.y);

		if (m_type[0][0] == Green)
			m_GreenPuyoTexture.Render(pos.x, pos.y);

		//�T�u
		if (m_type[0][1] == Red)	
			m_RedPuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);

		if (m_type[0][1] == Blue)
			m_BluePuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);

		if (m_type[0][1] == Yellow)
			m_YellowPuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);

		if (m_type[0][1] == Green)
			m_GreenPuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);
	}

	// �Q�[���I�[�o�[���b�Z�[�W
	if (eFlow == gameOver)
	{
		m_GameOverTexture.Render(100, 100);
		//CGraphicsUtilities::RenderString(500, 320, MOF_COLOR_BLACK, "�Q�[���I�[�o�[");
		CGraphicsUtilities::RenderString(500, 370, MOF_COLOR_BLACK, "�^�C�g���ɖ߂�[Enter]");
	}

	//�J�E���g�_�E���\��
	if (eFlow == ready)
	{
		if (m_readyTime >= 110)
			CGraphicsUtilities::RenderString(210, 350, MOF_COLOR_BLACK, "Ready");
		else if(m_readyTime >= 20)
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
	CGraphicsUtilities::RenderFillRect(BL, 50, BL * 9, BL * 2, MOF_COLOR_BLACK);

	//esc�Ń|�[�Y
	CGraphicsUtilities::RenderString(885, 12, MOF_COLOR_BLACK, "Pause[Esc]");

	//�|�[�Y
	if (eFlow == pause)
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