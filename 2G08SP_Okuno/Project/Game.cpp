#include "Game.h"

extern CSettingWin	g_SettingWin;
extern int			g_nSceneChange;

CGame::CGame() :
	m_PlTexture(),
	m_SkillTexture(),
	m_Player(),
	m_SoundCount(0),
	m_SoundArray(),
	m_BGMClear(),
	m_BGM(),
	m_ClearBgmFlg(false),
	m_Life(0),
	m_nScene(0),
	m_nStageIdx(0),
	m_SceneChangeTime(0)
{
}

CGame::~CGame()
{
}

bool CGame::Load(CTexture* playerTex)
{
	m_PlTexture = playerTex;

	if (!m_SkillTexture.Load("fireball.png")) {
		return false;
	}

	if (!m_BGM.Load("bgm.mp3")) {
		return false;
	}
	m_BGM.SetLoop(true);
	m_BGM.SetVolume(g_SettingWin.GetSoundVolume());

	if (!m_BGMClear.Load("gameClear.mp3")) {
		return false;
	}
	m_BGMClear.SetLoop(false);
	m_BGMClear.SetVolume(g_SettingWin.GetSoundVolume());

	m_SoundCount = m_Player.GetSoundCount();
	m_SoundArray = new CSoundBuffer[m_SoundCount];
	std::string* soundFiles = m_Player.GetSoundFiles();
	for (int i = 0; i < m_SoundCount; i++) {
		if (!m_SoundArray[i].Load(soundFiles[i].c_str())) {
			return false;
		}
	}
	for (int i = 0; i < m_SoundCount; i++) {
		m_SoundArray[i].SetLoop(false);
		m_SoundArray[i].SetVolume(g_SettingWin.GetSoundVolume());
	}

	
	m_Life = pllifeDefault; //暫定的にライフの初期値の設定

	//if (!m_Stage.Load("Stage1.txt", "Stage1Values.txt")) {
	//	return false;
	//}

	//if (!m_Player.Load(&m_PlTexture, CRectangle(0,0,m_Stage.GetChipSize(), m_Stage.GetChipSize()))) {
	//	return false;
	//}

	if (!m_Player.Load(m_PlTexture, &m_SkillTexture, m_SoundArray)) {
		return false;
	}

	return true;
}

bool CGame::Initialize(std::string fname, int stageIdx)
{
	m_Stage.Release();
	if (!m_Stage.Load(fname)) {
		return false;
	}

	m_Stage.Initialize();

	m_Player.Initialize(m_Stage.GetStartPos(), m_Life);
	m_Player.SetStageHeight(m_Stage.GetStageHeight());

	m_nScene = G_SCENE_LIFE;
	m_SceneChangeTime = 3.0f;
	m_ClearBgmFlg = false;
	m_nStageIdx = stageIdx;
	return true;
}

void CGame::Update()
{
	m_updTime = timeGetTime();
	if (m_Life < 0 && m_nScene != G_SCENE_GAMEOVER) {
		m_nScene = G_SCENE_GAMEOVER;
	}

	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
		if (g_pInput->IsKeyHold(MOFKEY_LSHIFT)) {
			m_ClearBgmFlg = true;
		}
		g_nSceneChange = SCENE_TITLE;
		if (m_BGM.IsPlay()) {
			m_BGM.Stop();
		}
		return;
	}
	if (m_nScene == G_SCENE_GAMEOVER) {
		if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
			m_Life = pllifeDefault;
			m_Player.SetLife(m_Life);

			m_nScene = G_SCENE_LIFE;
		}
	}
	else if (m_nScene == G_SCENE_LIFE) {
		m_SceneChangeTime -= CUtilities::GetFrameSecond();
		if (m_SceneChangeTime <= 0) {
			m_SceneChangeTime = 3.0f;
			m_nScene = G_SCENE_GAME;

			m_Stage.Initialize();

			if (!m_BGM.IsPlay()) {
				m_BGM.Play();
			}

			m_Player.Initialize(m_Stage.GetStartPos(), m_Life);
			m_Player.SetStageHeight(m_Stage.GetStageHeight());
		}
	}
	else if (m_nScene == G_SCENE_GAME) {
		m_Player.Update(m_Stage.GetScrollX(), m_Stage.GetScrollY());

		m_Stage.Update(m_Player, m_Player.GetBRect(true), m_Player.GetRect(true));

		if (m_Stage.IsGoal()) {
			if (!m_ClearBgmFlg) {
				if (m_BGM.IsPlay()) {
					m_BGM.Stop();
				}
				m_BGMClear.Play();
				m_ClearBgmFlg = true;
			}
		}
		else if (!m_BGM.IsPlay()) {
			m_BGM.Play();
		}

		if (m_Stage.IsSceneChange() && !m_BGMClear.IsPlay()) {
			int nextScene = m_Stage.GetSceneNext();
			if (m_BGM.IsPlay()) {
				m_BGM.Stop();
			}
			m_Life = m_Player.GetLife();
			if (m_Life < 0) {
				m_nScene = G_SCENE_GAMEOVER;
			}
			else if (nextScene == G_SCENE_GAMECLEAR) {
				g_nSceneChange = SCENE_TITLE;
			}
			else {
				m_nScene = G_SCENE_LIFE;
			}
		}
	}
	m_updTime = timeGetTime() - m_updTime;
}

void CGame::Render()
{
	m_renderTime = timeGetTime();
	if (m_nScene == G_SCENE_GAMEOVER) {
		CGraphicsUtilities::RenderString(10, 10, m_Stage.GetStageName());
		CGraphicsUtilities::RenderString(300, 150, "GAME OVER");

		CGraphicsUtilities::RenderString(300, 200, "Escapeキーで終わる");
		CGraphicsUtilities::RenderString(300, 230, "Enterキーでリトライ");
	}
	else if (m_nScene == G_SCENE_LIFE || m_nScene == G_SCENE_GAMEOVER) {
		CGraphicsUtilities::RenderString(10, 10, m_Stage.GetStageName());
		CGraphicsUtilities::RenderString(300, 200, "LIFE×%d", m_Player.GetLife());
	}
	else if (m_nScene == G_SCENE_GAME) {
		m_Stage.Render();

		m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

		CGraphicsUtilities::RenderString(10, 10, "ゲーム");
		CGraphicsUtilities::RenderString(300, 10, "LIFE×%d", m_Player.GetLife());
	}
	m_renderTime = timeGetTime() - m_renderTime;
}

void CGame::RenderDebug()
{
	if (m_nScene == G_SCENE_GAME) {
		m_Stage.RenderDebug();
	}
	CGraphicsUtilities::RenderString(400, 10, "upd :%3d render :%3d fps:%2d", m_updTime, m_renderTime, CUtilities::GetFPS());
}

void CGame::Release()
{
	m_Stage.Release();

	m_SkillTexture.Release();

	if (m_SoundArray) {
		for (int i = 0; i < m_SoundCount; i++) {
			m_SoundArray[i].Release();
		}
		delete[] m_SoundArray;
		m_SoundArray = NULL;
	}

	m_BGM.Release();
	m_BGMClear.Release();
}
