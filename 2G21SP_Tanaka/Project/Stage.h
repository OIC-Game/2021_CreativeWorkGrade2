#pragma once
#include	"Player.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"GameDefine.h"
#include	"PoPItemManager.h"

#define		COINBLOCK		0
#define		BLOCK			1
#define		FLAG1			2
#define		FLAG2			3
#define		FLAG3			14
#define		KINOKOBLOCK		22
#define		GOALPOOL		25
#define		CCOINBLOCK		33
#define		HIDENBLOCK		34
#define		CASTE			41
#define		CASLE			52
#define		WALL1			39
#define		WALL2			40
#define		WALL3			50
#define		WALL4			51

class CStage{
private:
	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;

	float					m_ChipSize;
	int						m_XCount;
	int						m_YCount;
	char*					m_pChipData;

	float					m_ScrollX;
	float					m_ScrollY;

	int						m_EnemyTextureCount;
	CTexture*				m_pEnemyTexture;
	char*					m_pEnemyData;
	int						m_EnemyCount;

	int						m_ItemTextureCount;
	CTexture*				m_pItemTexture;
	char*					m_pItemData;
	int						m_ItemCount;
	
	CPoPItemManager*		m_pPoPItemManager;
	CPoPItem*				m_pPoPItem;

	int						m_CoinCount;
	CSoundBuffer			m_bleakblockSound;

public:
	CStage();
	~CStage();
	bool Load(char* pName);
	void Initialize(char* pName, CEnemy* pEnemy, CItem* pItem);
	void Update(CPlayer& pl);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	float GetScrollX() { return m_ScrollX; }
	float GetScrollY() { return m_ScrollY; }
	bool Collision(CRectangle r, CPlayer& pl, float& ox, float& oy,int& popItemNo);
	int GetEnemyCount() { return m_EnemyCount; }
	int GetItemCount() { return m_ItemCount; }
	void SetPoPItemManager(CPoPItemManager* pmng) { m_pPoPItemManager = pmng; }
};

