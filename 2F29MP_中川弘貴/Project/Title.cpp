#include	"Title.h"

//変更するシーン(外部参照)
extern int		gChangeScene;

/*
  コンストラクタ
*/
CTitle::CTitle():
m_backTexture(),
m_startFlg(false),
m_titleBGM()
{
}

/*
  デストラクタ
*/
CTitle::~CTitle() {
}

/*  
  読み込み
*/
bool CTitle::Load(void)
{
	//テクスチャの読み込み
	if (!m_backTexture.Load("背景.png"))
	{
		return false;
	}
	if (!m_TitleLogoTexture.Load("ロゴ透過.png"))
	{
		return false;
	}
	if (!m_MenuBarTexture.Load("MenuBar.png"))
	{
		return false;
	}
	if (!m_ButtonVsMode1.Load("ButtonVSMode1.png"))
	{
		return false;
	}
	if (!m_ButtonFreeMode1.Load("ButtonFreeMode1.png"))
	{
		return false;
	}
	if (!m_ButtonHowToPlay1.Load("ButtonHowToPlay1.png"))
	{
		return false;
	}
	if (!m_ButtonVsMode2.Load("ButtonVSMode2.png"))
	{
		return false;
	}
	if (!m_ButtonFreeMode2.Load("ButtonFreeMode2.png"))
	{
		return false;
	}
	if (!m_ButtonHowToPlay2.Load("ButtonHowToPlay2.png"))
	{
		return false;
	}
	if (!m_RuleTexture.Load("Rule.png"))
	{
		return false;
	}
	if (!m_CloseTexture1.Load("Close1.png"))
	{
		return false;
	}
	if (!m_CloseTexture2.Load("Close2.png"))
	{
		return false;
	}
	//音の読み込み
	if (!m_titleBGM.Load("TitleBGM.mp3"))
	{
		return false;
	}
	if (!m_clickSound.Load("ButtonClickSound.mp3"))
	{
		return false;
	}
	if (!m_cursorSound.Load("CursorOnButtonSound.mp3"))
	{
		return false;
	}
	//ループ設定
	m_titleBGM.SetLoop(TRUE);


	return true;
}

/*
  初期化
*/
void CTitle::Initialize(void)
{
	//BGMの再生
	m_titleBGM.Play();

	//音量の調整
	m_titleBGM.SetVolume(0.06f);
	m_clickSound.SetVolume(0.35f);
	m_cursorSound.SetVolume(0.45f);

	//開始フラグを初期化
	m_startFlg = false;

	m_vsAiFlg = false;

	m_CursorOnVsModeFlg = false;
	m_CursorOnFreeModeFlg = false;
	m_CursorOnHowToPlayFlg = false;
	m_CursorOnCloseFlg = false;
	m_RulePopUpShowFlg = false;


	m_VsModeRect = CRectangle(700, 230, 950, 330);
	m_FreeModeRect = CRectangle(700, 360, 950, 460);
	m_HowToPlayRect = CRectangle(700, 490, 950, 590);
	m_CloseRect = CRectangle(745, 105, 825, 185);

	//フェードイン
	m_fade.FadeIn();
}

/*
  更新
*/
void CTitle::Update(void)
{
	//フェードの処理
	m_fade.Update();
	if (m_fade.GetFadeIn() || m_fade.GetFadeOut())
	{
		return;
	}
	//ゲームの開始フラグがTrueであり、フェードアウトが完了すれば
	else if (m_startFlg)
	{
		m_titleBGM.Stop();
		gChangeScene = SCENENO_GAME;
	}

	//if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	//{
	//	m_vsAiFlg = false;
	//	m_startFlg = true;
	//	//フェードアウト
	//	m_fade.FadeOut();
	//}

	//if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	//{
	//	m_vsAiFlg = true;
	//	m_startFlg = true;
	//	//フェードアウト
	//	m_fade.FadeOut();
	//}

	g_pInput->GetMousePos(m_mousePos);

	//閉じる
	if (m_RulePopUpShowFlg)
	{
		if (m_CloseRect.CollisionPoint(m_mousePos))
		{
			if (!m_CursorOnCloseFlg)
			{
				//音鳴らす
				m_cursorSound.Play();
			}
			m_CursorOnCloseFlg = true;

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				//音鳴らす
				m_clickSound.Play();
				//ポップアップを閉じる
				m_RulePopUpShowFlg = false;
			}
		}
		else
		{
			m_CursorOnCloseFlg = false;
		}
	}
	else
	{
		//VSモード
		if (m_VsModeRect.CollisionPoint(m_mousePos))
		{
			if (!m_CursorOnVsModeFlg)
			{
				//音鳴らす
				m_cursorSound.Play();
			}
			m_CursorOnVsModeFlg = true;

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				//音鳴らす
				m_clickSound.Play();
				//ここで遷移
				m_vsAiFlg = true;
				m_startFlg = true;
				//フェードアウト
				m_fade.FadeOut();
			}
		}
		else
		{
			m_CursorOnVsModeFlg = false;
		}

		//フリーモード
		if (m_FreeModeRect.CollisionPoint(m_mousePos))
		{
			if (!m_CursorOnFreeModeFlg)
			{
				//音鳴らす
				m_cursorSound.Play();
			}
			m_CursorOnFreeModeFlg = true;

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				//音鳴らす
				m_clickSound.Play();
				//ここで遷移
				m_vsAiFlg = false;
				m_startFlg = true;
				//フェードアウト
				m_fade.FadeOut();
			}
		}
		else
		{
			m_CursorOnFreeModeFlg = false;
		}

		//あそびかた
		if (m_HowToPlayRect.CollisionPoint(m_mousePos))
		{
			if (!m_CursorOnHowToPlayFlg)
			{
				//音鳴らす
				m_cursorSound.Play();
			}
			m_CursorOnHowToPlayFlg = true;

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				//音鳴らす
				m_clickSound.Play();
				//ポップアップ
				m_RulePopUpShowFlg = true;
			}
		}
		else
		{
			m_CursorOnHowToPlayFlg = false;
		}
	}

	
}

/*
  描画
*/
void CTitle::Render(void)
{
	//背景の描画
	m_backTexture.Render(0, 0);

	m_TitleLogoTexture.Render(0,80);

	m_MenuBarTexture.Render(650, 120);
	CGraphicsUtilities::RenderFillRect(650, 200, 1000, 630, MOF_ARGB(120, 0, 0, 0));

	if(!m_CursorOnVsModeFlg)
		m_ButtonVsMode1.Render(700, 230);
	else
		m_ButtonVsMode2.Render(700, 230);

	if (!m_CursorOnFreeModeFlg)
		m_ButtonFreeMode1.Render(700, 360);
	else
		m_ButtonFreeMode2.Render(700, 360);

	if(!m_CursorOnHowToPlayFlg)
		m_ButtonHowToPlay1.Render(700, 490);
	else
		m_ButtonHowToPlay2.Render(700, 490);


	if (m_RulePopUpShowFlg)
	{
		CGraphicsUtilities::RenderFillRect(0, 0, SW, SH, MOF_ARGB(180, 0, 0, 0));
		m_RuleTexture.Render(150,80);

		if(!m_CursorOnCloseFlg)
			m_CloseTexture1.Render(745, 105);
		else
			m_CloseTexture2.Render(745, 105);
	}

	//説明文
	//CGraphicsUtilities::RenderString(340, 400, MOF_COLOR_BLACK, "ゲームを開始する[Enter]");

	m_fade.Render();

}

/*
  解放
*/
void CTitle::Release(void)
{
	m_backTexture.Release();
	//音の解放
	m_titleBGM.Release();
	m_clickSound.Release();
	m_cursorSound.Release();

	m_TitleLogoTexture.Release();
	m_MenuBarTexture.Release();

	m_ButtonFreeMode1.Release();
	m_ButtonFreeMode2.Release();
	m_ButtonVsMode1.Release();
	m_ButtonVsMode2.Release();
	m_ButtonHowToPlay1.Release();
	m_ButtonHowToPlay2.Release();

	m_RuleTexture.Release();
	m_CloseTexture1.Release();
	m_CloseTexture2.Release();
}

