#pragma once

class CTitle{
private:
	CTexture	BackImage;

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

