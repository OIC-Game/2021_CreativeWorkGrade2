#pragma once

class CGameRetry{
private:
	
public:
	CGameRetry();
	~CGameRetry();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

