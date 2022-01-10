#include "EffectManager.h"

CEffectManager::CEffectManager()
{
}

CEffectManager::~CEffectManager()
{
}

bool CEffectManager::Load()
{
	char* name[] = {
			"effect02.png"

	};
	for (int i = 0; i < EFFECT_TYPECOUNT; i++)
	{
		if (!m_Texture[i].Load(name[i]))
		{
			return false;
		}
	}
	return true;
}

void CEffectManager::Initialize()
{
	
	for (int j = 0; j < EFFECT_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].SetTexture(&m_Texture[j]);
			m_Effect[i][j].Initialize(j);
		}
	}
}

CEffect* CEffectManager::Start(CVector2 pos, int type,float scale)
{
	for (int i = 0; i < EFFECTCOUNT; i++)
	{
		if (m_Effect[i][type].GetShow())
		{
			continue;
		}
		m_Effect[i][type].Start(pos,scale);
		return &m_Effect[i][type];
	}

	return NULL;
}

void CEffectManager::Update()
{
	for (int j = 0; j < EFFECT_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Update();
		}
	}
}

void CEffectManager::Render(Vector2 scroll)
{
	for (int j = 0; j < EFFECT_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Render(scroll);
		}
	}
}

void CEffectManager::RenderDebug()
{
	for (int j = 0; j < EFFECT_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].RenderDebug();
		}
	}
}

void CEffectManager::Release()
{
	for (int j = 0; j < EFFECT_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Release();
		}
		m_Texture[j].Release();
	}
}
