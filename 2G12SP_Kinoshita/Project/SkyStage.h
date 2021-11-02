#pragma once
#include "Mof.h"
#include "Player.h"

#define		LEFTSLOPE							2
class CSkyStage
{
private:
	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;
	//CSoundBuffer            m_gBGM;

	float					m_ChipSize;
	int						m_XCount;
	int						m_YCount;
	char* m_pChipData;

	float					m_ScrollX;
	float					m_ScrollY;

public:
	CSkyStage();
	~CSkyStage();
	bool Load(char* pName);
	void Initialize();
	void Update(CPlayer& pl);
	bool Collision(CRectangle r, float& ox, float& oy);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	float GetScrollX() { return m_ScrollX; }
	float GetScrollY() { return m_ScrollY; }
	
};

