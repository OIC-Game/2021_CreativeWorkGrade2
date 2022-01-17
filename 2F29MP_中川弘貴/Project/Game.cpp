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
void CGame::Load(void)
{
	pl.Load();
	ai.Load();

	//画像

	m_BackTexture.Load("背景.png");

	m_PauseTexture.Load("Pause.png");

	m_ReadyTexture.Load("Ready.png");

	m_FightTexture.Load("Fight.png");

	m_GameOverTexture.Load("GameOverBack.png");

	m_WinTexture.Load("Win.png");

	m_LoseTexture.Load("Lose.png");

	m_HowMoveTexture.Load("HowMove.png");

	//音
	m_gameBGM.Load("GameBGM.mp3");

	m_pauseSound.Load("PauseSound.mp3");

	m_gameOverSound.Load("GameOverSound.mp3");

	m_victorySound.Load("VictorySound.mp3");

	m_readySound.Load("ReadySound.mp3");

	m_fightSound.Load("FightSound.mp3");

	//ループ設定
	m_gameBGM.SetLoop(TRUE);
}


/*
  初期化
*/
void CGame::Initialize(bool vsAiFlg)
{
	pl.Initialize(false);
	ai.Initialize(true);

	m_pauseFlg = false;
	m_readyFlg = false;
	m_endFlg = false;
	m_deadFlg = false;

	//音量調整
	m_pauseSound.SetVolume(0.5f);
	m_gameBGM.SetVolume(0.05f);
	m_gameOverSound.SetVolume(0.3f);
	m_victorySound.SetVolume(0.62f);
	m_readySound.SetVolume(0.4f);
	m_fightSound.SetVolume(0.5f);

	m_readyTimeCnt = READY_TIME;
	m_toTitleTimeCnt = TO_TITLE_TIME;

	m_readyStep = 0;
	m_plReceiveObstacleCnt = 0;
	m_aiReceiveObstacleCnt = 0;

	font.Create(48, "MS ゴシック");

	//再生
	m_gameBGM.Play();

	fade.FadeIn();
}

/*
  更新
*/
void CGame::Update(bool vsAiFlg)
{
	//フェードの処理
	fade.Update();

	//フェード処理が終わった後endflgがtrueなら遷移
	if (fade.GetFadeIn() || fade.GetFadeOut())
	{
		return;
	}
	else if (m_endFlg)
	{
		m_gameOverSound.Stop();
		gChangeScene = SCENENO_TITLE;
	}

	if (m_pauseFlg)
	{
		if (g_pInput->IsKeyPush(MOFKEY_RETURN))
		{
			m_gameBGM.Stop();
			fade.FadeOut();
			m_endFlg = true;
		}
	}

	//ゲームオーバー(死んで)からタイトルに行くまで
	if (m_deadFlg)
	{
		if (m_toTitleTimeCnt <= 0)
		{
			m_gameBGM.Stop();
			fade.FadeOut();
			m_endFlg = true;
		}
		else
		{
			m_toTitleTimeCnt--;
		}
	}

	if (m_deadFlg)
	{
		return;
	}

	//死んだあと
	if (pl.GetDead() || ai.GetDead())
	{
		m_gameBGM.Stop();
		m_deadFlg = true;
		if (pl.GetDead())
		{
			m_gameOverSound.Play();
		}
		else
		{
			m_victorySound.Play();
		}
	}

	//readyfightの処理
	if (m_readyTimeCnt <= 0)
	{
		m_readyFlg = true;
	}
	else
	{
		if (m_readyTimeCnt >= READY_TIME && m_readyStep == 0)
		{
			m_readyStep = 1;
			m_readySound.Play();
		}
		if (m_readyTimeCnt <= READY_TIME / 2 && m_readyStep == 1)
		{
			m_readyStep = 2;
			m_fightSound.Play();
		}

		m_readyTimeCnt--;
		return;
	}

	//Escでポーズ切り替え
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
	{
		if (m_pauseFlg)
		{
			m_pauseSound.Play();
			m_gameBGM.SetVolume(0.05f);
			m_pauseFlg = false;
		}
		else
		{
			m_pauseSound.Play();
			m_gameBGM.SetVolume(0.01f);
			m_pauseFlg = true;
		}
	}

	if (m_pauseFlg)
	{
		return;
	}

	//おじゃまぷよ
	//降った後
	if (pl.GetReceive())
	{
		m_plReceiveObstacleCnt = 0;
		ai.SetSendObstacleCnt(0);
	}
	if (ai.GetReceive())
	{
		m_aiReceiveObstacleCnt = 0;
		pl.SetSendObstacleCnt(0);
	}

	//数が同じなら両方打ち消し合う
	if (pl.GetSendObstacleCnt() == ai.GetSendObstacleCnt() &&
		pl.GetSendObstacleCnt() != 0 && ai.GetSendObstacleCnt() != 0)
	{
		m_plReceiveObstacleCnt = 0;
		m_aiReceiveObstacleCnt = 0;
		pl.SetSendObstacleCnt(0);
		ai.SetSendObstacleCnt(0);
	}
	//引き算して残った分をAI側に降らす
	else if (pl.GetSendObstacleCnt() > ai.GetSendObstacleCnt())
	{
		pl.SetSendObstacleCnt(pl.GetSendObstacleCnt() - ai.GetSendObstacleCnt());
		ai.SetSendObstacleCnt(0);
		m_aiReceiveObstacleCnt = pl.GetSendObstacleCnt();
	}
	//引き算して残った分をPlayer側に降らす
	else if (pl.GetSendObstacleCnt() < ai.GetSendObstacleCnt())
	{
		ai.SetSendObstacleCnt(ai.GetSendObstacleCnt() - pl.GetSendObstacleCnt());
		pl.SetSendObstacleCnt(0);
		m_plReceiveObstacleCnt = ai.GetSendObstacleCnt();
	}


	pl.Update(false, m_plReceiveObstacleCnt);
	if (vsAiFlg)
	{
		ai.Update(true, m_aiReceiveObstacleCnt);
	}

}

/*
  描画
*/
void CGame::Render(bool vsAiFlg)
{
	//背景
	m_BackTexture.Render(0, 0);

	if (!vsAiFlg)
	{
		//スコアなどを囲む枠
		CGraphicsUtilities::RenderFillRect(550, 70, 950, 410, MOF_ARGB(220,130,160,130));
		CGraphicsUtilities::RenderRect(550, 70, 950, 410, MOF_COLOR_BLACK);
		CGraphicsUtilities::RenderRect(551, 71, 949, 409, MOF_COLOR_BLACK);
		CGraphicsUtilities::RenderRect(552, 72, 948, 408, MOF_COLOR_BLACK);

		//スコア
		font.RenderString(570, 100, MOF_COLOR_BLACK, "スコア");
		CGraphicsUtilities::RenderFillRect(570, 160, 920, 210, MOF_COLOR_WHITE);
		CGraphicsUtilities::RenderRect(570, 160, 920, 210, MOF_COLOR_BLACK);
		CGraphicsUtilities::RenderRect(571, 161, 919, 209, MOF_COLOR_BLACK);
		font.RenderFormatString(580, 164, MOF_COLOR_BLACK, "%d", pl.GetScore());


		//最大連鎖数
		font.RenderString(570, 250, MOF_COLOR_BLACK, "最大連鎖数");
		CGraphicsUtilities::RenderFillRect(570, 310, 700, 360, MOF_COLOR_WHITE);
		CGraphicsUtilities::RenderRect(570, 310, 700, 360, MOF_COLOR_BLACK);
		CGraphicsUtilities::RenderRect(571, 311, 699, 359, MOF_COLOR_BLACK);
		font.RenderFormatString(580, 314, MOF_COLOR_BLACK, "%d", pl.GetMaxChain());

		//操作説明
		m_HowMoveTexture.Render(560, 500);
		
	}

	//プレイヤー、AIのぷよやら枠組みやら
	pl.Render(false,m_readyFlg, m_plReceiveObstacleCnt);
	if (vsAiFlg)
	{
		ai.Render(true,m_readyFlg, m_aiReceiveObstacleCnt);
	}


	// ゲームオーバーメッセージ
	if (pl.GetDead())
	{
		if (vsAiFlg)
		{
			//プレイヤーの負けテクスチャ
			m_LoseTexture.Render(100, 100);
			//CPUの勝ちテクスチャ
			m_WinTexture.Render(SW - 400, 100);
		}
		else
		{
			m_GameOverTexture.Render(100, 100);
		}
	}

	// ゲームオーバーメッセージ
	if (ai.GetDead())
	{
		//プレイヤーの勝ちテクスチャ
		m_WinTexture.Render(100, 100);
		//CPUの負けテクスチャ
		m_LoseTexture.Render(SW - 400, 100);

	}

	//escでポーズ
	CGraphicsUtilities::RenderString(885, 12, MOF_COLOR_BLACK, "Pause[Esc]");

	//カウントダウン表示
	if (!m_readyFlg && !fade.GetFadeIn())
	{
		if (m_readyStep == 1)
			m_ReadyTexture.Render(280, 250);
		else if (m_readyStep == 2)
			m_FightTexture.Render(280, 250);
	}

	//ポーズ
	if (m_pauseFlg)
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
	pl.Release();
	ai.Release();

	m_BackTexture.Release();
	m_GameOverTexture.Release();
	m_PauseTexture.Release();
	m_ReadyTexture.Release();
	m_FightTexture.Release();
	m_WinTexture.Release();
	m_LoseTexture.Release();
	m_HowMoveTexture.Release();

	m_gameBGM.Release();
	m_pauseSound.Release();
	m_gameOverSound.Release();
	m_victorySound.Release();
	m_readySound.Release();
	m_fightSound.Release();
}