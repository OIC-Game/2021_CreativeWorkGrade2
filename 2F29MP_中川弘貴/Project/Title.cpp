#include	"GameApp.h"
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
	if (!m_backTexture.Load("TitleBack.png"))
	{
		return false;
	}
	//音の読み込み
	if (!m_titleBGM.Load("TitleBGM.mp3"))
	{
		return false;
	}
	//ループ設定
	m_titleBGM.SetLoop(TRUE);
	//BGMの再生
	m_titleBGM.Play();

	return true;
}

/*
  初期化
*/
void CTitle::Initialize(void)
{
	Load();

	//音量の調整
	m_titleBGM.SetVolume(0.06f);
	//開始フラグを初期化
	m_startFlg = false;
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

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_startFlg = true;
		//フェードアウト
		m_fade.FadeOut();
	}

	
}

/*
  描画
*/
void CTitle::Render(void)
{
	//背景の描画
	m_backTexture.Render(0, 0);
	//説明文
	CGraphicsUtilities::RenderString(340, 400, MOF_COLOR_BLACK, "ゲームを開始する[Enter]");

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
}

