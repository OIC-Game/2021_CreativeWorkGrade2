#pragma once

#define		SELECTITEMCOUNT	3
class CTitle
{
private:

	CTexture				TitleTexture;
	int						m_Select;
	int						m_KeyWait;

public:
	CTitle();
	~CTitle();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

