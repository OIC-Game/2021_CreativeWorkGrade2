#include "Game.h"

extern CSettingWin	g_SettingWin;
extern int			g_nSceneChange;

CGame::CGame() :
	m_PlTexture(),
	m_SkillTexture(),
	m_Player(),
	m_SoundCount(0),
	m_SoundArray(),
	m_BGMFailed(),
	m_BGMClear(),
	m_BGM(),
	m_ClearBgmFlg(false),
	m_FailedBgmFlg(false),
	m_Life(0),
	m_nScene(0),
	m_nStageIdx(0),
	m_SceneChangeTime(0),
	m_Time(0)
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

	if (!m_BGMFailed.Load("failed.wav")) {
		return false;
	}
	m_BGMFailed.SetLoop(false);
	m_BGMFailed.SetVolume(g_SettingWin.GetSoundVolume());

	if (!m_SkillSound.Load("firedown.mp3")) {
		return false;
	}
	m_SkillSound.SetLoop(false);
	m_SkillSound.SetVolume(g_SettingWin.GetSoundVolume());

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


	m_Life = pllifeDefault; //ébíËìIÇ…ÉâÉCÉtÇÃèâä˙ílÇÃê›íË

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
	if (!m_Stage.Load(fname, &m_SkillSound)) {
		return false;
	}

	m_Stage.Initialize();

	m_Player.Initialize(m_Stage.GetStartPos(), m_Life);
	m_Player.SetStageHeight(m_Stage.GetStageHeight());

	m_nScene = G_SCENE_LIFE;
	m_SceneChangeTime = 3.0f;
	m_ClearBgmFlg = false;
	m_FailedBgmFlg = false;
	m_nStageIdx = stageIdx;
	m_Time = gameOverTime;
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
			m_Stage.ResetCheckPoint();

			m_nScene = G_SCENE_LIFE;
		}
	}
	else if (m_nScene == G_SCENE_LIFE) {
		m_SceneChangeTime -= CUtilities::GetFrameSecond();
		if (m_SceneChangeTime <= 0) {
			m_SceneChangeTime = 3.0f;
			m_FailedBgmFlg = false;
			m_Time = gameOverTime;
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

		m_Stage.Update(m_Player, m_Player.GetBRect(true), m_Player.GetRect(true), m_BGMClear.IsPlay());

		if (m_Stage.IsGoal()) {
			if (!m_ClearBgmFlg) {
				if (m_BGM.IsPlay()) {
					m_BGM.Stop();
				}
				m_BGMClear.Play();
				m_ClearBgmFlg = true;
			}
		}
		else {
			if (m_Time > 0 && !m_Player.GetDead()) {
				m_Time -= CUtilities::GetFrameSecond();
				if (m_Time < 0) {
					m_Time = 0;
					m_Player.Damage(true);
				}
				if (!m_BGM.IsPlay()) {
					m_BGM.Play();
				}
			}
			else {
				if (!m_FailedBgmFlg) {
					if (m_BGM.IsPlay()) {
						m_BGM.Stop();
					}
					m_BGMFailed.Play();
					m_FailedBgmFlg = true;
				}
			}
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
	CRectangle tRect;
	m_renderTime = timeGetTime();
	if (m_nScene == G_SCENE_GAMEOVER) {
		CGraphicsUtilities::RenderString(10, 10, m_Stage.GetStageName());
		CGraphicsUtilities::RenderString(300, 150, "GAME OVER");

		CGraphicsUtilities::RenderString(300, 200, "EscapeÉLÅ[Ç≈èIÇÌÇÈ");
		CGraphicsUtilities::RenderString(300, 230, "EnterÉLÅ[Ç≈ÉäÉgÉâÉC");
	}
	else if (m_nScene == G_SCENE_LIFE || m_nScene == G_SCENE_GAMEOVER) {
		CGraphicsUtilities::RenderString(10, 10, m_Stage.GetStageName());
		CGraphicsUtilities::RenderString(300, 200, "LIFEÅ~%d", m_Player.GetLife());
	}
	else if (m_nScene == G_SCENE_GAME) {
		m_Stage.Render();

		m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

		m_Stage.RenderLayerOver();//ï`âÊèáÇ™ÉvÉåÉCÉÑÅ[ÇÊÇËè„ÇÃï`âÊ

		CGraphicsUtilities::RenderString(10, 10, "ÉQÅ[ÉÄ");

		CGraphicsUtilities::CalculateStringRect(0, 0, "LIFEÅ~000 TIME 000", tRect);

		CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() - tRect.Right - 150, 10, "LIFEÅ~%3d TIME %3.0f", m_Player.GetLife(), m_Time);

		if (m_Time <= 0) {
			CGraphicsUtilities::CalculateStringRect(0, 0, "TIME UP", tRect);
			CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2 - tRect.Right / 2, g_pGraphics->GetTargetHeight() / 2 - tRect.Bottom / 2, "TIME UP");
		}
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
	m_SkillSound.Release();

	if (m_SoundArray) {
		for (int i = 0; i < m_SoundCount; i++) {
			m_SoundArray[i].Release();
		}
		delete[] m_SoundArray;
		m_SoundArray = NULL;
	}

	m_BGM.Release();
	m_BGMClear.Release();
	m_BGMFailed.Release();
}
