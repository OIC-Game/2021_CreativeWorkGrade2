#pragma once
#include "mof.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"



class CStage{
private:
	CTexture		m_ChipTexture;
	CTexture		m_BackTexture;

	float			m_ChipSize;
	int  			m_XCount;
	int 			m_YCount;
	char*			m_pChipData;
	
	float			m_ScrollX;
	float			m_ScrollY;

	int				m_EnemyTextureCount;
	CTexture*		m_pEnemyTexture;
	char*			m_pEnemyData;
	int				m_EnemyCount;

	int				m_ItemTextureCount;
	CTexture*		m_pItemTexture;
	char*			m_pItemData;
	int				m_ItemCount;

	#define			QuestionBlock	12
	//#define			Pipe			7,8

public:
	CStage();
	~CStage();
	bool Load(char* pName);
	void Initialize(CEnemy* pEnemy,CItem* pItem);
	void Update(CPlayer& pl);
	bool Collision(CRectangle r, float& ox, float& oy);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	float GetScrollX(){return m_ScrollX;}
	float GetScrollY(){return m_ScrollY;}
	int GetEnemyCount() { return m_EnemyCount; }
	int GetItemCount() { return m_ItemCount; }

};

