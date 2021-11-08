#pragma once
#include "Fade.h"

class CTitle {
private:
	CTexture	m_BackTexture;
	int			m_fade;
	bool		m_bStart;
	CSoundBuffer	m_titleBGM;
public:
	CTitle();
	~CTitle();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);
};