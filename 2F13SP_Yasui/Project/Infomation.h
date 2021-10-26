#pragma once
#include "SceneBase.h"

class CInfomation : public CSceneBase
{
private:

public:
	CInfomation();
	~CInfomation();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

