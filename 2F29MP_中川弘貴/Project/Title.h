#pragma once
#include "Fade.h"

class CTitle {
private:
	CTexture		m_backTexture;
	bool			m_startFlg;
	CSoundBuffer	m_titleBGM;
	bool			m_vsAiFlg;

	CFade			m_fade;
public:
	CTitle();
	~CTitle();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);
	bool GetVsAiFlg()
	{
		return m_vsAiFlg;
	}
};