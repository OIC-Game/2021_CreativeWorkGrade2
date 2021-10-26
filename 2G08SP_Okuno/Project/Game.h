#pragma once

#include	"GameApp.h"
#include    "SettingWin.h"
#include	"StageParent.h"
#include	"Player.h"
#include	"Enemy.h"
#include	"Item.h"

constexpr int pllifeDefault = 5;

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
	bool			m_ClearBgmFlg;
	int				m_Life;
	int				m_nScene;
	float			m_SceneChangeTime;
	int				m_nStageIdx;


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
	}
};

