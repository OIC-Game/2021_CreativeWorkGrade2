#pragma once

#include	"Player.h"
#include    "Enemy.h"
#include    "Item.h"
//左傾斜チップ
#define LEFTSLOPE 2

class CStage {
private:
	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;
	int                     m_ItemTextureCount;
	CTexture*               m_pItemTexture;
	char*                   m_pItemData;
	int                     m_ItemCount;
	int m_EnemyTextureCount;//敵の種類数（＝テクスチャの数）
	CTexture* m_pEnemyTexture; //敵の種類ごとのテクスチャを格納した配列
	char* m_pEnemyData; //敵の配置データ
	int m_EnemyCount; //敵の配置数合計
	float					m_ChipSize;
	int						m_XCount;
	int						m_YCount;
	char*					m_pChipData;

	float					m_ScrollX;
	float					m_ScrollY;
public:
	CStage();
	~CStage();
	int GetItemCount() { return m_ItemCount; }
	int GetEnemyCount() { return m_EnemyCount; }
	bool Collision(CRectangle r, float& ox, float& oy);
	bool Load(char* pName);
	void Initialize(void);
	void Update(CPlayer& pl);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	void Initialize(CEnemy* pEnemy,CItem*pItem);
	float GetScrollX(){ return m_ScrollX; }
	float GetScrollY(){ return m_ScrollY; }
	
};