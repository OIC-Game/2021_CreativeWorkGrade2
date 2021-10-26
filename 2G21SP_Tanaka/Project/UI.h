#pragma once
#include		"Mof.h"
#include		"Player.h"

class CUI{
private:
	CTexture	m_Texture;

public:
	CUI();
	~CUI();
	bool Load(void);
	void Initialize(void);
	void Render(void);
	void Release(void);
};

