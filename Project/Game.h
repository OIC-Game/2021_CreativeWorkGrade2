#pragma once
#include "Player.h"
#include "Stage.h"
#include "Enemy.h"
#include "Item.h"
#include "Information.h"
class CGame
{
private:
	CPlayer m_Player;
	CStage m_Stage;
	CEnemy* m_EnemyArray;
	CItem* m_ItemArray;
	CInformation m_Information;
public:
	CGame();
	~CGame();
	bool Load(void);
	bool LoadStage(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

