#pragma once
#include "SceneBase.h"

class CTitle : public CSceneBase
{
private:
public:
	CTitle();
	~CTitle();
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);
};

