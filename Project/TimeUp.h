#pragma once
#include "mof.h"
class CTimeUp
{
private:
	CTexture m_TimeUpTexture;
	int m_bTimeUpCount;
public:
	CTimeUp();
	~CTimeUp();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

