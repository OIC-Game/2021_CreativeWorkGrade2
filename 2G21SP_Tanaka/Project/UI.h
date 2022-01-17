#pragma once
#include		"Mof.h"
#include		"Player.h"

class CUI{
private:
	CTexture	m_Texture;
	CTexture	m_LifeTexture;

public:
	CUI();
	~CUI();
	bool Load(void);
	void Initialize(void);
	void Render(void);
	void Release(void);
};

