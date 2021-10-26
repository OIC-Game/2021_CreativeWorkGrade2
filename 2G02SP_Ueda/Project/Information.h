#pragma once
#include "mof.h"
class CInformation
{
private:
	CTexture m_InfoTexture;
	CTexture m_NumTexture;
	int m_bInfoCount;
	int m_LIFE;
	int m_ChipSize;
	int m_ones;
	int m_tens;
public:
	CInformation();
	~CInformation();
	bool Load(void);
	void Initialize(float life);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	float GetLife(void) { return m_LIFE; }
	void DecLife(void);
	void InLife(void);
};

