#pragma once
#include	"GameApp.h"

class CTitle {
private:
	CTexture		m_backTexture;
	CTexture		m_TitleLogoTexture;
	CTexture		m_MenuBarTexture;
	CTexture		m_ButtonVsMode1;
	CTexture		m_ButtonVsMode2;
	CTexture		m_ButtonFreeMode1;
	CTexture		m_ButtonFreeMode2;
	CTexture		m_ButtonHowToPlay1;
	CTexture		m_ButtonHowToPlay2;
	CTexture	    m_RuleTexture;

	CTexture		m_CloseTexture1;
	CTexture		m_CloseTexture2;

	CRectangle		m_VsModeRect;
	CRectangle		m_FreeModeRect;
	CRectangle		m_HowToPlayRect;
	CRectangle		m_CloseRect;

	bool			m_CursorOnVsModeFlg;
	bool			m_CursorOnFreeModeFlg;
	bool			m_CursorOnHowToPlayFlg;
	bool			m_CursorOnCloseFlg;

	bool			m_RulePopUpShowFlg;

	Vector2			m_mousePos;

	bool			m_startFlg;

	CSoundBuffer	m_titleBGM;
	CSoundBuffer	m_clickSound;
	CSoundBuffer	m_cursorSound;

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