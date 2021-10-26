#include "PoPItemManager.h"

CPoPItemManager::CPoPItemManager(){
}

CPoPItemManager::~CPoPItemManager(){
}

bool CPoPItemManager::Load(void){
	char* name[] = {
		"Item03.png",
		"Item01.png",
	};
	for (int i = 0; i < POP_TYPECOUNT; i++)
	{
		if (!m_Texture[i].Load(name[i]))
		{
			return false;
		}
	}
	return true;
}

void CPoPItemManager::Initialize(void){
	for (int j = 0; j < POP_TYPECOUNT; j++)
	{
		for (int i = 0; i < ITEMCOUNT; i++)
		{
			m_PoPItem[i][j].SetTexture(&m_Texture[j]);
			m_PoPItem[i][j].Initialize(j);
		}
	}
}

CPoPItem* CPoPItemManager::Start(float px, float py, int type){
	for (int i = 0; i < ITEMCOUNT; i++)
	{
		//未使用かどうか確認
		if (m_PoPItem[i][type].GetShow())
		{
			continue;
		}
		
		m_PoPItem[i][type].Start(px, py);
		return &m_PoPItem[i][type];
	}
	return NULL;
}

void CPoPItemManager::Update(void){
	for (int j = 0; j < POP_TYPECOUNT; j++)
	{
		for (int i = 0; i < ITEMCOUNT; i++)
		{
			m_PoPItem[i][j].Update();
		}
	}
}

void CPoPItemManager::Render(float wx, float wy){
	for (int j = 0; j < POP_TYPECOUNT; j++)
	{
		for (int i = 0; i < ITEMCOUNT; i++)
		{
			m_PoPItem[i][j].Render(wx, wy);
		}
	}
}

void CPoPItemManager::RenderDebug(float wx, float wy){
	for (int j = 0; j < POP_TYPECOUNT; j++)
	{
		for (int i = 0; i < ITEMCOUNT; i++)
		{
			m_PoPItem[i][j].RenderDebug(wx, wy);
		}
	}
}

void CPoPItemManager::Release(void){
	for (int j = 0; j < POP_TYPECOUNT; j++)
	{
		for (int i = 0; i < ITEMCOUNT; i++)
		{
			m_PoPItem[i][j].Release();
		}
		m_Texture[j].Release();
	}
}
