#pragma once
#include "Player.h"
#include "Stage.h"
#include "Enemy.h"
#include "Item.h"
#include "EffectManager.h"
class CGame {
private:
	//敵
	CEnemy* m_EnemyArray;
	//ステージ
	CStage m_Stage;
	//プレーヤー
	CPlayer m_Player;
	//アイテム
	CItem* m_ItemArray;
	//エフェクト
	CEffectManager m_EffectManager;
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