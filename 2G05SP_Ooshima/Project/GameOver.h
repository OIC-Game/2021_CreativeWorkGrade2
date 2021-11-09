#pragma once

class CGameOver {
private:
	CTexture				m_BackImage;
public:
	CGameOver();
	~CGameOver();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};