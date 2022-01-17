#pragma once

#include	"GameApp.h"
#include    "SettingWin.h"
#include	"StageParent.h"
#include	"Player.h"
#include	"Enemy.h"
#include	"Item.h"

constexpr int pllifeDefault = 5;
constexpr float gameOverTime = 200;

class CGame
{
private:

	CTexture*		m_PlTexture;
	CTexture		m_SkillTexture;
	CStageParent	m_Stage;
	CPlayer			m_Player;
	int				m_SoundCount;
	CSoundBuffer*	m_SoundArray;
	CSoundBuffer	m_BGM;
	CSoundBuffer	m_BGMClear;
	CSoundBuffer	m_BGMFailed;
	CSoundBuffer	m_SkillSound;
	CSoundBuffer	m_PipeSound;
	bool			m_ClearBgmFlg;
	bool			m_FailedBgmFlg;
	int				m_Life;
	int				m_Coin;
	int				m_nScene;
	float			m_SceneChangeTime;
	int				m_nStageIdx;
	float			m_Time;


	DWORD m_updTime;
	DWORD m_renderTime;

public:
	CGame();
	~CGame();

	bool Load(CTexture* playerTex);

	bool Initialize(std::string fname, int stageIdx);

	void Update();

	void Render();

	void RenderDebug();

	void Release();

	bool IsStageClear() { return m_ClearBgmFlg; }

	int GetStageIdx() { return m_nStageIdx; }

	void SetSoundVolume(float v) {
		for (int i = 0; i < m_SoundCount; i++) {
			m_SoundArray[i].SetVolume(v);
		}
		m_BGM.SetVolume(v);
		m_BGMClear.SetVolume(v);
		m_BGMFailed.SetVolume(v);
		m_SkillSound.SetVolume(v);
		m_PipeSound.SetVolume(v);
	}
};

