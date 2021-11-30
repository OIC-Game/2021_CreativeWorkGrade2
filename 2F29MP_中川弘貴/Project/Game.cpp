#include	"GameApp.h"
#include	"Game.h"

//変更するシーン(外部参照)
extern int		gChangeScene;

/*
  コンストラクタ
*/
CGame::CGame() {

}

/*
  デストラクタ
*/
CGame::~CGame() {

}

/*
  読み込み
*/
bool CGame::Load(void)
{
	//テクスチャの読み込み
	if (!m_RedPuyoTexture.Load("RedPuyo.png"))
	{
		return false;
	}
	//テクスチャの読み込み
	if (!m_BluePuyoTexture.Load("BluePuyo.png"))
	{
		return false;
	}
	//テクスチャの読み込み
	if (!m_YellowPuyoTexture.Load("YellowPuyo.png"))
	{
		return false;
	}
	//テクスチャの読み込み
	if (!m_GreenPuyoTexture.Load("GreenPuyo.png"))
	{
		return false;
	}
	//テクスチャの読み込み
	if (!m_BackTexture.Load("GameBack.png"))
	{
		return false;
	}
	//テクスチャの読み込み
	if (!m_CrossMarkTexture.Load("Batu.png"))
	{
		return false;
	}
	//テクスチャの読み込み
	if (!m_GameOverTexture.Load("GameOverBack.png"))
	{
		return false;
	}
	//テクスチャの読み込み
	if (!m_PauseTexture.Load("Pause.png"))
	{
		return false;
	}
	//音の読み込み
	if (!m_chainSound.Load("ChainSound.mp3"))
	{
		return false;
	}
	//音の読み込み
	if (!m_moveSound.Load("MoveSound.mp3"))
	{
		return false;
	}
	//音の読み込み
	if (!m_setSound.Load("SetSound.mp3"))
	{
		return false;
	}
	//音の読み込み
	if (!m_rotateSound.Load("RotateSound.mp3"))
	{
		return false;
	}
	//音の読み込み
	if (!m_gameBGM.Load("GameBGM.mp3"))
	{
		return false;
	}
	//音の読み込み
	if (!m_pauseSound.Load("PauseSound.mp3"))
	{
		return false;
	}
	//音の読み込み
	if (!m_gameOverSound.Load("GameOverSound.mp3"))
	{
		return false;
	}

	//ループ設定
	m_gameBGM.SetLoop(TRUE);
	//再生
	m_gameBGM.Play();

	return true;
}

/*
  初期化
*/
void CGame::Initialize(void)
{
	//テクスチャの読み込み
	Load();

	//フィールドの初期配置
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
	//ぷよの色をランダムで決める
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_type[i][j] = m_random.Random(Red, TypeCount);
		}
	}

	
	//音量の調整
	m_chainSound.SetVolume(0.60f);
	m_moveSound.SetVolume(0.54f);
	m_setSound.SetVolume(0.5f);
	m_rotateSound.SetVolume(0.3f);
	m_pauseSound.SetVolume(0.5f);
	m_gameOverSound.SetVolume(0.3f);
	m_gameBGM.SetVolume(0.05f);

	//色々初期値
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
  更新
*/
void CGame::Update(void)
{
	//フェードの処理
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

	//処理全体の流れ
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

//ReadyGo カウントダウン の処理
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
//ポーズ(一時停止)中の処理
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
//プレイヤーがぷよを操作する工程
void CGame::DropUpdate()
{
	//ポーズ
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
	{
		m_pauseSound.Play();
		m_gameBGM.SetVolume(0.01f);
		m_eFlow = Pause;
	}

	//自由落下
	if (m_dropTimeCnt < 0)
	{
		//確定しているか
		if ((m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty && m_eRotation == Top) ||
			(m_field[m_sFldPos.y + 2][m_sFldPos.x] != Empty && m_eRotation == Bottom) ||
			((m_field[m_sFldPos.y + 1][m_sFldPos.x - 1] != Empty ||
				m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty) && m_eRotation == Left) ||
				((m_field[m_sFldPos.y + 1][m_sFldPos.x + 1] != Empty ||
					m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty) && m_eRotation == Right))
		{

			//画面外に設置しないように
			if (m_sFldPos.y >= 0) {
				//メインのぷよを格納
				m_field[m_sFldPos.y][m_sFldPos.x] = m_type[0][0];
			}
			//サブのぷよを格納
			if (m_eRotation == Top && m_sFldPos.y - 1 >= 0)
				m_field[m_sFldPos.y - 1][m_sFldPos.x] = m_type[0][1];
			if (m_eRotation == Left && m_sFldPos.y >= 0)
				m_field[m_sFldPos.y][m_sFldPos.x - 1] = m_type[0][1];
			if (m_eRotation == Right && m_sFldPos.y >= 0)
				m_field[m_sFldPos.y][m_sFldPos.x + 1] = m_type[0][1];
			if (m_eRotation == Bottom && m_sFldPos.y + 1 >= 0)
				m_field[m_sFldPos.y + 1][m_sFldPos.x] = m_type[0][1];

			//スコア加算
			m_score += 10;

			//設置音
			m_setSound.Play();

			//ちぎりの工程に移る
			m_eFlow = Tear;

			return;
		}

		//確定してなければ一マス落ちる
		m_pos.y += PUYO_SIZE;
		m_sFldPos.y += 1;
		m_dropTimeCnt = DROP_SPEED;
	}
	else
	{
		m_dropTimeCnt--;
	}

	//左に移動
	if (g_pInput->IsKeyPush(MOFKEY_A) &&
		((m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty &&
			m_field[m_sFldPos.y - 1][m_sFldPos.x - 1] == Empty && m_eRotation == Top || m_sFldPos.y == 0) ||
			(m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty &&
				m_field[m_sFldPos.y + 1][m_sFldPos.x - 1] == Empty && m_eRotation == Bottom) ||
				(m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty && m_eRotation == Right) ||
			(m_field[m_sFldPos.y][m_sFldPos.x - 2] == Empty && m_eRotation == Left)))
	{
		//移動音
		m_moveSound.Play();

		m_leftHoldTimeCnt = INIT_HOLD_TIME;
		//左に一マス動かす
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
			//移動音
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

	//右に移動
	if (g_pInput->IsKeyPush(MOFKEY_D) &&
		((m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty &&
			m_field[m_sFldPos.y - 1][m_sFldPos.x + 1] == Empty && m_eRotation == Top || m_sFldPos.y == 0) ||
			(m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty &&
				m_field[m_sFldPos.y + 1][m_sFldPos.x + 1] == Empty && m_eRotation == Bottom) ||
				(m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty && m_eRotation == Left) ||
			(m_field[m_sFldPos.y][m_sFldPos.x + 2] == Empty && m_eRotation == Right)))
	{
		//移動音
		m_moveSound.Play();

		m_rightHoldTimeCnt = INIT_HOLD_TIME;
		//右に一マス動かす
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
			//移動音
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

	//キーによって下に移動(1マス)
	if (g_pInput->IsKeyPush(MOFKEY_S))
	{
		m_downHoldTimeCnt = INIT_HOLD_TIME;
		//押したときに1マス落とす
		m_dropTimeCnt = -1;
	}
	//キーによって下に移動(高速降下)
	else if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		if (m_downHoldTimeCnt <= 0) {
			//長押しで高速降下
			m_dropTimeCnt -= PUYO_SPEED * 3;
		}
		else
		{
			m_downHoldTimeCnt--;
		}
	}

	//回転・左方向
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
		//左右に壁やぷよがあり回転が行えなかった場合
		else
		{
			
		}

		//回転音
		m_rotateSound.Play();
	}

	//回転・右方向
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

		//回転音
		m_rotateSound.Play();
	}
}
//ちぎり　浮いているぷよへの対処
void CGame::TearUpdate()
{
	if (m_waitTimeCnt < 0) {
		for (int y = FH - 2; y >= 0; y--)
		{
			for (int x = FW - 1; x >= 1; x--)
			{
				//ぷよが宙に浮いているとき
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

		//操作不能時間 sleepの代わり 20は適当
		m_waitTimeCnt = WAIT_TIME;
		m_eFlow = Chain;
	}
	else
	{
		m_waitTimeCnt--;
	}
}
//連鎖
void CGame::ChainUpdate()
{
	if (m_waitTimeCnt < 0) {
		//連鎖のチェック
		//連鎖が行われた場合はちぎりに戻り一度整地する。
		//連鎖が行われなかった場合、リスタートへ
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
			//操作不能時間 連鎖がわかりやすくなるよう少し長めに
			m_waitTimeCnt = WAIT_TIME * 2;
			//連鎖時の音
			m_chainSound.Play();
			//次に鳴らす連鎖音のピッチを上げる
			m_chainSound.SetPitch(m_chainSound.GetPitch() + 0.06f);
			//連鎖数をカウントする(+1)
			m_chainCnt++;
			//ちぎりに移る
			m_eFlow = Tear;
		}
		else if (!m_chainFlg)
		{
			//操作不能時間 sleepの代わり 40は適当
			m_waitTimeCnt = WAIT_TIME;

			//バツ部分に(2,3,4,5)のどれかしらがあればゲームオーバー
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
				//最大連鎖数との比較
				if (m_maxChainCnt < m_chainCnt)
				{
					m_maxChainCnt = m_chainCnt;
				}

				//連鎖数に応じてスコアの加算
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
//ゲームオーバーになっていなければ 再度ぷよを降らす
void CGame::ReStartUpdate()
{
	//次のぷよを操作できるよう、セットする
	m_type[0][0] = m_type[1][0];
	m_type[0][1] = m_type[1][1];

	//次回のぷよを格納しておくため
	//ぷよの色をランダムで決める
	m_type[1][0] = m_random.Random(Red, TypeCount);
	m_type[1][1] = m_random.Random(Red, TypeCount);

	//色々初期値
	m_dropTimeCnt = DROP_SPEED;
	m_chainCnt = 0;

	//連鎖音のピッチのリセット
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
//ゲームオーバー
void CGame::GameOverUpdate()
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		fade.FadeOut();
		m_endFlg = true;

	}
}

/*
  描画
*/
void CGame::Render(void)
{
	//背景
	m_BackTexture.Render(0,0);

	//パズル部分の背景
	for (int y = 0; y < FH - 1; y++)
	{
		for (int x = 1; x < FW - 1; x++)
		{
			CGraphicsUtilities::RenderFillRect(BL + x * BL, BL * 2 + y * BL, x * BL + BL * 2, y * BL + BL * 3, MOF_COLOR_WHITE);
		}
	}

	//ゲームオーバーの×
	m_CrossMarkTexture.Render(BL * 4, BL * 2);

	//フィールドの描画
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

	//待機中のぷよ
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


	//操作中のぷよの描画
	if (m_eFlow == Drop || m_eFlow == Pause) {
		//本体
		if (m_type[0][0] == Red)
			m_RedPuyoTexture.Render(m_pos.x, m_pos.y);

		if (m_type[0][0] == Blue)
			m_BluePuyoTexture.Render(m_pos.x, m_pos.y);

		if (m_type[0][0] == Yellow)
			m_YellowPuyoTexture.Render(m_pos.x, m_pos.y);

		if (m_type[0][0] == Green)
			m_GreenPuyoTexture.Render(m_pos.x, m_pos.y);

		//サブ
		if (m_type[0][1] == Red)	
			m_RedPuyoTexture.Render(m_pos.x + m_spin.x, m_pos.y + m_spin.y);

		if (m_type[0][1] == Blue)
			m_BluePuyoTexture.Render(m_pos.x + m_spin.x, m_pos.y + m_spin.y);

		if (m_type[0][1] == Yellow)
			m_YellowPuyoTexture.Render(m_pos.x + m_spin.x, m_pos.y + m_spin.y);

		if (m_type[0][1] == Green)
			m_GreenPuyoTexture.Render(m_pos.x + m_spin.x, m_pos.y + m_spin.y);
	}

	// ゲームオーバーメッセージ
	if (m_eFlow == GameOver)
	{
		m_GameOverTexture.Render(100, 100);
		//CGraphicsUtilities::RenderString(500, 320, MOF_COLOR_BLACK, "ゲームオーバー");
		CGraphicsUtilities::RenderString(500, 370, MOF_COLOR_BLACK, "タイトルに戻る[Enter]");
	}

	//カウントダウン表示
	if (m_eFlow == Ready)
	{
		if (m_readyTimeCnt >= 110)
			CGraphicsUtilities::RenderString(210, 350, MOF_COLOR_BLACK, "Ready");
		else if(m_readyTimeCnt >= 20)
			CGraphicsUtilities::RenderString(220, 350, MOF_COLOR_BLACK, "Go");
	}

	//連鎖表示
	if (m_chainCnt >= 1)
	{
		CGraphicsUtilities::RenderFillRect(210,350,280,380, MOF_COLOR_WHITE);
		CGraphicsUtilities::RenderString(210, 350, MOF_COLOR_BLACK, "%d連鎖", m_chainCnt);
	}

	//スコア
	CGraphicsUtilities::RenderString(800, 138, MOF_COLOR_BLACK, "%d",m_score);

	//最大連鎖数
	CGraphicsUtilities::RenderString(900, 210, MOF_COLOR_BLACK, "%d", m_maxChainCnt);

	//開幕にブロックが見えないように、画面上部を隠す
	//CGraphicsUtilities::RenderFillRect(BL, 50, BL * 9, BL * 2, MOF_COLOR_BLACK);

	//escでポーズ
	CGraphicsUtilities::RenderString(885, 12, MOF_COLOR_BLACK, "Pause[Esc]");

	//ポーズ
	if (m_eFlow == Pause)
	{
		//後ろを暗くする
		CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_ARGB(150, 0, 0, 0));
		//ポーズ画面の描画
		m_PauseTexture.Render(256, 167);
	}

	fade.Render();
}

/*
  解放
*/
void CGame::Release(void)
{
	//テクスチャの解放
	m_RedPuyoTexture.Release();
	m_BluePuyoTexture.Release();
	m_YellowPuyoTexture.Release();
	m_GreenPuyoTexture.Release();
	m_BackTexture.Release();
	m_CrossMarkTexture.Release();
	m_GameOverTexture.Release();
	m_PauseTexture.Release();

	//音の解放
	m_chainSound.Release();
	m_moveSound.Release();
	m_setSound.Release();
	m_rotateSound.Release();
	m_gameBGM.Release();
	m_pauseSound.Release();
	m_gameOverSound.Release();

}