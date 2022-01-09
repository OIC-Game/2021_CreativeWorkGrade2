#include "GameDefine.h"
#include "Title.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;


CTitle::CTitle() :
	TitleTexture() {
	
}


CTitle::~CTitle() {
}

bool CTitle::Load(void) {

	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	//テクスチャの読み込み
	if (!TitleTexture.Load("GameTitle.png"))
	{
		return false;
	}
	return true;
}

void CTitle::Initialize(void) {
	Load();
}

void CTitle::Update(void) {
	

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		switch (m_Select) {
		case 0:
			gChangeScene = SCENENO_GAME;
			break;
		case 1:
			gChangeScene = SCENENO_GAMEOVER;
			break;
		case 2:
			gChangeScene = SCENENO_GAMECLEAR;
			break;

		}

	}

	//ウェイト０のときだけ動く
	if (m_KeyWait <= 0)
	{
		//上下キーHoldで選択
		if (g_pInput->IsKeyHold(MOFKEY_UP))
		{
			m_KeyWait = 15;		//ウェイトを設定このフレーム間は再入力不可
			m_Select--;
			if (m_Select < 0)
			{
				m_Select = SELECTITEMCOUNT + m_Select;
			}
		}
		else if (g_pInput->IsKeyHold(MOFKEY_DOWN))
		{
			m_KeyWait = 15;		//ウェイトを設定このフレーム間は再入力不可
			m_Select++;
			if (m_Select >= SELECTITEMCOUNT)
			{
				m_Select = m_Select - SELECTITEMCOUNT;
			}
		}
	}
	else
	{
		m_KeyWait--;
	}
}

void CTitle::Render(void) {
	TitleTexture.RenderScale(0, 0,1.3f);

	//選択項目
	const char* selectItem[] = {

		"ゲーム開始",
		"操作説明",
		"オプション"
	};
	//for文で繰り返しで表示
	for (int i = 0; i < SELECTITEMCOUNT; i++)
	{
		CGraphicsUtilities::RenderString(560, 340 + i * 40, i == m_Select ?
			MOF_COLOR_RED : MOF_COLOR_HWHITE, selectItem[i]);
	}
}


void CTitle::RenderDebug(void) {
}


void CTitle::Release(void) {
	TitleTexture.Release();
}