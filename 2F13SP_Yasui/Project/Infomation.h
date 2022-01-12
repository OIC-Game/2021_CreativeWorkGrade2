#pragma once
#include "SceneBase.h"

class CInfomation : public CSceneBase
{
private:
	CTexture m_Texture;
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

