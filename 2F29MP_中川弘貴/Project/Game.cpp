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
				field[y][x] = 1;
			else if (y == FH - 1)
				field[y][x] = 1;
			else
				field[y][x] = 0;
		}
	}

	random.SetSeed(time(NULL));
	//�Ղ�̐F�������_���Ō��߂�
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			type[i][j] = random.Random(2, 6);
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
	wait = DROP_SPEED;
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
}

void CGame::ChainCheck(int y, int x)
{
	if (field[y][x] != 0 && field[y][x] != 1 &&
		!bCheck[y][x])
	{
		bCheck[y][x] = true;
		bondCnt++;
		if (field[y][x] == field[y - 1][x])
		{
			ChainCheck(y - 1, x);
		}
		if (field[y][x] == field[y][x + 1])
		{
			ChainCheck(y, x + 1);
		}
		if (field[y][x] == field[y + 1][x])
		{
			ChainCheck(y + 1, x);
		}
		if (field[y][x] == field[y][x - 1])
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
			m_gameBGM.Stop();
			gChangeScene = SCENENO_TITLE;
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
		if (wait < 0)
		{
			//�m�肵�Ă��邩
			if ((field[sFPos.y + 1][sFPos.x] != 0 && eStep == Top) ||
				(field[sFPos.y + 2][sFPos.x] != 0 && eStep == Bottom) ||
				((field[sFPos.y + 1][sFPos.x - 1] != 0 ||
					field[sFPos.y + 1][sFPos.x] != 0) && eStep == Left) ||
					((field[sFPos.y + 1][sFPos.x + 1] != 0 ||
						field[sFPos.y + 1][sFPos.x] != 0) && eStep == Right))
			{

				//��ʊO�ɐݒu���Ȃ��悤��
				if (sFPos.y >= 0) {
					//���C���̂Ղ���i�[
					field[sFPos.y][sFPos.x] = type[0][0];
				}
				//�T�u�̂Ղ���i�[
				if (eStep == Top && sFPos.y - 1 >= 0)
					field[sFPos.y - 1][sFPos.x] = type[0][1];
				if (eStep == Left && sFPos.y >= 0)
					field[sFPos.y][sFPos.x - 1] = type[0][1];
				if (eStep == Right && sFPos.y >= 0)
					field[sFPos.y][sFPos.x + 1] = type[0][1];
				if (eStep == Bottom && sFPos.y + 1 >= 0)
					field[sFPos.y + 1][sFPos.x] = type[0][1];

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
			wait = DROP_SPEED;
		}
		else
		{
			wait--;
		}

		//���Ɉړ�
		if (g_pInput->IsKeyPush(MOFKEY_A) &&
			((field[sFPos.y][sFPos.x - 1] == 0 &&
				field[sFPos.y - 1][sFPos.x - 1] == 0 && eStep == Top) ||
				(field[sFPos.y][sFPos.x - 1] == 0 &&
					field[sFPos.y + 1][sFPos.x - 1] == 0 && eStep == Bottom) ||
					(field[sFPos.y][sFPos.x - 1] == 0 && eStep == Right) ||
				(field[sFPos.y][sFPos.x - 2] == 0 && eStep == Left)))
		{
			//�ړ���
			m_moveSound.Play();

			m_leftHoldTime = 10;
			//���Ɉ�}�X������
			pos.x -= PUYO_SIZE;
			sFPos.x -= 1;
		}
		else if (g_pInput->IsKeyHold(MOFKEY_A) &&
			((field[sFPos.y][sFPos.x - 1] == 0 &&
				field[sFPos.y - 1][sFPos.x - 1] == 0 && eStep == Top) ||
				(field[sFPos.y][sFPos.x - 1] == 0 &&
					field[sFPos.y + 1][sFPos.x - 1] == 0 && eStep == Bottom) ||
					(field[sFPos.y][sFPos.x - 1] == 0 && eStep == Right) ||
				(field[sFPos.y][sFPos.x - 2] == 0 && eStep == Left)))
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
			((field[sFPos.y][sFPos.x + 1] == 0 &&
				field[sFPos.y - 1][sFPos.x + 1] == 0 && eStep == Top) ||
				(field[sFPos.y][sFPos.x + 1] == 0 &&
					field[sFPos.y + 1][sFPos.x + 1] == 0 && eStep == Bottom) ||
					(field[sFPos.y][sFPos.x + 1] == 0 && eStep == Left) ||
				(field[sFPos.y][sFPos.x + 2] == 0 && eStep == Right)))
		{
			//�ړ���
			m_moveSound.Play();

			m_rightHoldTime = 10;
			//�E�Ɉ�}�X������
			pos.x += PUYO_SIZE;
			sFPos.x += 1;
		}
		else if (g_pInput->IsKeyHold(MOFKEY_D) &&
			((field[sFPos.y][sFPos.x + 1] == 0 &&
				field[sFPos.y - 1][sFPos.x + 1] == 0 && eStep == Top) ||
				(field[sFPos.y][sFPos.x + 1] == 0 &&
					field[sFPos.y + 1][sFPos.x + 1] == 0 && eStep == Bottom) ||
					(field[sFPos.y][sFPos.x + 1] == 0 && eStep == Left) ||
				(field[sFPos.y][sFPos.x + 2] == 0 && eStep == Right)))
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
			wait = -1;
		}
		//�L�[�ɂ���ĉ��Ɉړ�(�����~��)
		else if (g_pInput->IsKeyHold(MOFKEY_S))
		{	
			if (m_downHoldTime <= 0) {
				//�������ō����~��
				wait -= 15;
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
				if (field[sFPos.y][sFPos.x - 1] == 0 ||
					field[sFPos.y][sFPos.x + 1] == 0)
				{
					if (field[sFPos.y][sFPos.x - 1] != 0)
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
				if (field[sFPos.y + 1][sFPos.x] != 0)
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
				if (field[sFPos.y][sFPos.x - 1] == 0 ||
					field[sFPos.y][sFPos.x + 1] == 0)
				{
					if (field[sFPos.y][sFPos.x + 1] != 0)
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

			//��]��
			m_rotateSound.Play();
		}

		//��]�E�E����
		if (g_pInput->IsKeyPush(MOFKEY_K))
		{
			if (eStep == Top)
			{
				if (field[sFPos.y][sFPos.x - 1] == 0 ||
					field[sFPos.y][sFPos.x + 1] == 0)
				{
					if (field[sFPos.y][sFPos.x + 1] != 0)
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
				if (field[sFPos.y + 1][sFPos.x] != 0)
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
				if (field[sFPos.y][sFPos.x - 1] == 0 ||
					field[sFPos.y][sFPos.x + 1] == 0)
				{
					if (field[sFPos.y][sFPos.x - 1] != 0)
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
					if (field[y][x] != 0 &&
						field[y + 1][x] == 0)
					{

						for (int i = y; i <= FH - 2; i++) 
						{
							field[i + 1][x] = field[i][x];
							field[i][x] = 0;
							if (field[i + 2][x] != 0)
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
			//�A�����s��ꂽ�ꍇ�͂�����ɖ߂��x���n����B���̍ہA�A�����͂ǂ�������̕ϐ��ɂƂ��Ă���
			//�A�����s���Ȃ������ꍇ�A���X�^�[�g��
			bChain = false;

			for (int y = 0; y < FH; y++)
			{
				for (int x = 0; x < FW; x++)
				{
					ChainCheck(y, x);
					if (bondCnt >= 4)
					{
						for (int i = 0; i < FH; i++)
						{
							for (int j = 0; j < FW; j++)
							{
								if (bCheck[i][j])
								{
									bDestroy[i][j] = true;
								}

							}
						}
					}
					bondCnt = 0;
					for (int i = 0; i < FH; i++)
					{
						for (int j = 0; j < FW; j++)
						{
							bCheck[i][j] = false;

						}
					}
				}
			}

			for (int i = 0; i < FH; i++)
			{
				for (int j = 0; j < FW; j++)
				{
					if (bDestroy[i][j])
					{
						field[i][j] = 0;
						bChain = true;
					}
					bDestroy[i][j] = false;
				}
			}
			

			if (bChain)
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
			else if (!bChain)
			{
				//����s�\���� sleep�̑��� 40�͓K��
				m_sleepTime = 20;

				//�o�c������(2,3,4,5)�̂ǂꂩ���炪����΃Q�[���I�[�o�[
				if (field[0][3] == 2 ||
					field[0][3] == 3 ||
					field[0][3] == 4 ||
					field[0][3] == 5)
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
		type[0][0] = type[1][0];
		type[0][1] = type[1][1];

		//����̂Ղ���i�[���Ă�������
		//�Ղ�̐F�������_���Ō��߂�
		type[1][0] = random.Random(2, 6);
		type[1][1] = random.Random(2, 6);

		//�F�X�����l
		wait = DROP_SPEED;
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
			m_gameOverSound.Stop();
			gChangeScene = SCENENO_TITLE;
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
			if (field[y][x] == 5)
				//CGraphicsUtilities::RenderFillRect(BL + x * BL, BL + y * BL, x * BL + BL * 2, y * BL + BL * 2, MOF_COLOR_GREEN);
				m_GreenPuyoTexture.Render(BL + x * BL, BL * 2 + y * BL);

			if (field[y][x] == 4)
				//CGraphicsUtilities::RenderFillRect(BL + x * BL, BL + y * BL, x * BL + BL * 2, y * BL + BL * 2, MOF_COLOR_YELLOW);
				m_YellowPuyoTexture.Render(BL + x * BL, BL * 2 + y * BL);

			if (field[y][x] == 3)
				//CGraphicsUtilities::RenderFillRect(BL + x * BL, BL + y * BL, x * BL + BL * 2, y * BL + BL * 2, MOF_COLOR_BLUE);
				m_BluePuyoTexture.Render(BL + x * BL, BL * 2 + y * BL);

			if (field[y][x] == 2)
				//CGraphicsUtilities::RenderFillRect(BL + x * BL, BL + y * BL, x * BL + BL * 2, y * BL + BL * 2, MOF_COLOR_RED);
				m_RedPuyoTexture.Render(BL + x * BL, BL * 2 + y * BL);

			if (field[y][x] == 1)
				CGraphicsUtilities::RenderFillRect(BL + x * BL, BL * 2 + y * BL, x * BL + BL * 2, y * BL + BL * 3, MOF_COLOR_BLACK);

			//if (field[y][x] == 0)
				//CGraphicsUtilities::RenderFillRect(BL + x * BL, BL + y * BL, x * BL + BL * 2, y * BL + BL * 2, MOF_COLOR_WHITE);

		}
	}

	//�ҋ@���̂Ղ�
	CGraphicsUtilities::RenderString(490, 100, "NEXT");
	CGraphicsUtilities::RenderFillRect(480, 130, 550, 250, MOF_COLOR_CBLACK);
	if (type[1][1] == 2)
		m_RedPuyoTexture.Render(490, 140);

	else if (type[1][1] == 3)
		m_BluePuyoTexture.Render(490, 140);

	else if (type[1][1] == 4)
		m_YellowPuyoTexture.Render(490, 140);

	else if (type[1][1] == 5)
		m_GreenPuyoTexture.Render(490, 140);

	if (type[1][0] == 2)
		m_RedPuyoTexture.Render(490, 190);

	else if (type[1][0] == 3)
		m_BluePuyoTexture.Render(490, 190);

	else if (type[1][0] == 4)
		m_YellowPuyoTexture.Render(490, 190);

	else if (type[1][0] == 5)
		m_GreenPuyoTexture.Render(490, 190);


	//���쒆�̂Ղ�̕`��
	if (eFlow == drop || eFlow == pause) {
		//�{��
		if (type[0][0] == 2)
			m_RedPuyoTexture.Render(pos.x, pos.y);

		if (type[0][0] == 3)
			m_BluePuyoTexture.Render(pos.x, pos.y);

		if (type[0][0] == 4)
			m_YellowPuyoTexture.Render(pos.x, pos.y);

		if (type[0][0] == 5)
			m_GreenPuyoTexture.Render(pos.x, pos.y);

		//�T�u
		if (type[0][1] == 2)
			
			m_RedPuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);
		if (type[0][1] == 3)
			//CGraphicsUtilities::RenderFillRect(pos.x + spin.x, pos.y + spin.y, pos.x + spin.x + PUYO_SIZE, pos.y + spin.y + PUYO_SIZE, MOF_COLOR_BLUE);
			m_BluePuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);
		if (type[0][1] == 4)
			//CGraphicsUtilities::RenderFillRect(pos.x + spin.x, pos.y + spin.y, pos.x + spin.x + PUYO_SIZE, pos.y + spin.y + PUYO_SIZE, MOF_COLOR_YELLOW);
			m_YellowPuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);
		if (type[0][1] == 5)
			//CGraphicsUtilities::RenderFillRect(pos.x + spin.x, pos.y + spin.y, pos.x + spin.x + PUYO_SIZE, pos.y + spin.y + PUYO_SIZE, MOF_COLOR_GREEN);
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