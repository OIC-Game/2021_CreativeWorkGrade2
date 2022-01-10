#pragma once
#include "Effect.h"

#define EFFECTCOUNT 10

class CEffectManager
{
private:
	CEffect		m_Effect[EFFECTCOUNT][EFFECT_TYPECOUNT];

	CTexture	m_Texture[EFFECT_TYPECOUNT];

public:
	CEffectManager();
	~CEffectManager();
	bool Load();
	void Initialize();
	CEffect* Start(CVector2 pos, int type,float scale);
	void Update();
	void Render(Vector2 scroll);
	void RenderDebug();
	void Release();

};

