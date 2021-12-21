#pragma once
#include	"Player.h"
#include	"PlayerFire.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"PoPItemManager.h"
#include	"UI.h"

class CGame{
private:
	//プレイヤー
	CPlayer				m_Player;

	CPlayerFire			m_WorkFire;
	//ステージ
	CStage				m_Stage;
	//敵
	CEnemy*				m_EnemyArray;
	//アイテム
	CItem*				m_ItemArray;
	//ポップアイテム
	CPoPItemManager		m_PoPItemManager;
	CPoPItem			m_PoPItem;

	//UI
	CUI					m_UI;

public:
	CGame();
	~CGame();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

