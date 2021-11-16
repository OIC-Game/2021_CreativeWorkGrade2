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

	random.SetSeed(time(NULL));
	//ぷよの色をランダムで決める
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_type[i][j] = random.Random(Red, TypeCount);
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

	//ReadyGo カウントダウン の処理
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

	//ポーズ(一時停止)中の処理
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

	//プレイヤーがぷよを操作する工程
	else if (eFlow == drop) {
		
		//ポーズ
		if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
		{
			m_pauseSound.Play();
			m_gameBGM.SetVolume(0.01f);
			eFlow = pause;
		}

		//自由落下
		if (m_dropTimeCnt < 0)
		{
			//確定しているか
			if ((m_field[sFPos.y + 1][sFPos.x] != Empty && eStep == Top) ||
				(m_field[sFPos.y + 2][sFPos.x] != Empty && eStep == Bottom) ||
				((m_field[sFPos.y + 1][sFPos.x - 1] != Empty ||
					m_field[sFPos.y + 1][sFPos.x] != Empty) && eStep == Left) ||
					((m_field[sFPos.y + 1][sFPos.x + 1] != Empty ||
						m_field[sFPos.y + 1][sFPos.x] != Empty) && eStep == Right))
			{

				//画面外に設置しないように
				if (sFPos.y >= 0) {
					//メインのぷよを格納
					m_field[sFPos.y][sFPos.x] = m_type[0][0];
				}
				//サブのぷよを格納
				if (eStep == Top && sFPos.y - 1 >= 0)
					m_field[sFPos.y - 1][sFPos.x] = m_type[0][1];
				if (eStep == Left && sFPos.y >= 0)
					m_field[sFPos.y][sFPos.x - 1] = m_type[0][1];
				if (eStep == Right && sFPos.y >= 0)
					m_field[sFPos.y][sFPos.x + 1] = m_type[0][1];
				if (eStep == Bottom && sFPos.y + 1 >= 0)
					m_field[sFPos.y + 1][sFPos.x] = m_type[0][1];

				//スコア加算
				m_score += 10;

				//設置音
				m_setSound.Play();

				//ちぎりの工程に移る
				eFlow = tear;

				return;
			}

			//確定してなければ一マス落ちる
			pos.y += PUYO_SIZE;
			sFPos.y += 1;
			m_dropTimeCnt = DROP_SPEED;
		}
		else
		{
			m_dropTimeCnt--;
		}

		//左に移動
		if (g_pInput->IsKeyPush(MOFKEY_A) &&
			((m_field[sFPos.y][sFPos.x - 1] == Empty &&
				m_field[sFPos.y - 1][sFPos.x - 1] == Empty && eStep == Top) ||
				(m_field[sFPos.y][sFPos.x - 1] == Empty &&
					m_field[sFPos.y + 1][sFPos.x - 1] == Empty && eStep == Bottom) ||
					(m_field[sFPos.y][sFPos.x - 1] == Empty && eStep == Right) ||
				(m_field[sFPos.y][sFPos.x - 2] == Empty && eStep == Left)))
		{
			//移動音
			m_moveSound.Play();

			m_leftHoldTime = 10;
			//左に一マス動かす
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
				//移動音
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

		//右に移動
		if (g_pInput->IsKeyPush(MOFKEY_D) &&
			((m_field[sFPos.y][sFPos.x + 1] == Empty &&
				m_field[sFPos.y - 1][sFPos.x + 1] == Empty && eStep == Top) ||
				(m_field[sFPos.y][sFPos.x + 1] == Empty &&
					m_field[sFPos.y + 1][sFPos.x + 1] == Empty && eStep == Bottom) ||
					(m_field[sFPos.y][sFPos.x + 1] == Empty && eStep == Left) ||
				(m_field[sFPos.y][sFPos.x + 2] == Empty && eStep == Right)))
		{
			//移動音
			m_moveSound.Play();

			m_rightHoldTime = 10;
			//右に一マス動かす
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
				//移動音
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

		//キーによって下に移動(1マス)
		if (g_pInput->IsKeyPush(MOFKEY_S))
		{
			m_downHoldTime = 10;
			//押したときに1マス落とす
			m_dropTimeCnt = -1;
		}
		//キーによって下に移動(高速降下)
		else if (g_pInput->IsKeyHold(MOFKEY_S))
		{	
			if (m_downHoldTime <= 0) {
				//長押しで高速降下
				m_dropTimeCnt -= 15;
			}
			else
			{
				m_downHoldTime--;
			}
		}

		//回転・左方向
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

			//回転音
			m_rotateSound.Play();
		}

	}

	//ちぎり　浮いているぷよへの対処
	else if (eFlow == tear)
	{
		
		if (m_sleepTime < 0) {
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
			m_sleepTime = 20;
			eFlow = chain;
		}
		else
		{
			m_sleepTime--;
		}
	}

	//連鎖
	else if (eFlow == chain)
	{
		if (m_sleepTime < 0) {
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
				//操作不能時間 sleepの代わり 40は適当
				m_sleepTime = 40;
				//連鎖時の音
				m_chainSound.Play();
				//次に鳴らす連鎖音のピッチを上げる
				m_chainSound.SetPitch(m_chainSound.GetPitch() + 0.06f);
				//連鎖数をカウントする(+1)
				m_chainCnt++;
				//ちぎりに移る
				eFlow = tear;
			}
			else if (!m_chainFlg)
			{
				//操作不能時間 sleepの代わり 40は適当
				m_sleepTime = 20;

				//バツ部分に(2,3,4,5)のどれかしらがあればゲームオーバー
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

					eFlow = reStart;
				}
			}
		}
		else
		{
			m_sleepTime--;
		}
	}

	//ゲームオーバーになっていなければ 再度ぷよを降らす
	else if (eFlow == reStart)
	{
		//次のぷよを操作できるよう、セットする
		m_type[0][0] = m_type[1][0];
		m_type[0][1] = m_type[1][1];

		//次回のぷよを格納しておくため
		//ぷよの色をランダムで決める
		m_type[1][0] = random.Random(Red, TypeCount);
		m_type[1][1] = random.Random(Red, TypeCount);

		//色々初期値
		m_dropTimeCnt = DROP_SPEED;
		m_chainCnt = 0;

		//連鎖音のピッチのリセット
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

	//ゲームオーバー
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
	if (eFlow == drop || eFlow == pause) {
		//本体
		if (m_type[0][0] == Red)
			m_RedPuyoTexture.Render(pos.x, pos.y);

		if (m_type[0][0] == Blue)
			m_BluePuyoTexture.Render(pos.x, pos.y);

		if (m_type[0][0] == Yellow)
			m_YellowPuyoTexture.Render(pos.x, pos.y);

		if (m_type[0][0] == Green)
			m_GreenPuyoTexture.Render(pos.x, pos.y);

		//サブ
		if (m_type[0][1] == Red)	
			m_RedPuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);

		if (m_type[0][1] == Blue)
			m_BluePuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);

		if (m_type[0][1] == Yellow)
			m_YellowPuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);

		if (m_type[0][1] == Green)
			m_GreenPuyoTexture.Render(pos.x + spin.x, pos.y + spin.y);
	}

	// ゲームオーバーメッセージ
	if (eFlow == gameOver)
	{
		m_GameOverTexture.Render(100, 100);
		//CGraphicsUtilities::RenderString(500, 320, MOF_COLOR_BLACK, "ゲームオーバー");
		CGraphicsUtilities::RenderString(500, 370, MOF_COLOR_BLACK, "タイトルに戻る[Enter]");
	}

	//カウントダウン表示
	if (eFlow == ready)
	{
		if (m_readyTime >= 110)
			CGraphicsUtilities::RenderString(210, 350, MOF_COLOR_BLACK, "Ready");
		else if(m_readyTime >= 20)
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
	CGraphicsUtilities::RenderFillRect(BL, 50, BL * 9, BL * 2, MOF_COLOR_BLACK);

	//escでポーズ
	CGraphicsUtilities::RenderString(885, 12, MOF_COLOR_BLACK, "Pause[Esc]");

	//ポーズ
	if (eFlow == pause)
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