#pragma once

#include "SceneBase.h"

class CTitle : public CSceneBase{
private:
	CTexture	title_Texture;
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
