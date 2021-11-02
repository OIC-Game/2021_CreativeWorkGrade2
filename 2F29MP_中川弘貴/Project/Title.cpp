#include	"GameApp.h"
#include	"Title.h"

//変更するシーン(外部参照)
extern int		gChangeScene;

/*
  コンストラクタ
*/
CTitle::CTitle():
m_BackTexture(),
m_fade(0),
m_bStart(false),
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
	if (!m_BackTexture.Load("TitleBack.png"))
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

	m_fade = 0;
	m_bStart = false;
}

/*
  更新
*/
void CTitle::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bStart = true;
	}

	//ゲームの開始フラグがTrueになり次第、画面を真っ暗にする
	if (m_bStart)
	{
		m_fade += 3;
		//画面が真っ黒になったら(m_fadeが255になると真っ暗)
		if (m_fade >= 255)
		{
			m_titleBGM.Stop();
			gChangeScene = SCENENO_GAME;

		}
	}
	
	
}

/*
  描画
*/
void CTitle::Render(void)
{
	m_BackTexture.Render(0, 0);
	CGraphicsUtilities::RenderString(340, 400, MOF_COLOR_BLACK, "ゲームを開始する[Enter]");
	//フェード用の黒い四角
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_ARGB(m_fade, 0, 0, 0));
}

/*
  解放
*/
void CTitle::Release(void)
{
	m_BackTexture.Release();

	//音の解放
	m_titleBGM.Release();
}

