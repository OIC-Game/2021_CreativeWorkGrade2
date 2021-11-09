#pragma once
#include "Player.h"
#include "Stage.h"
#include "Enemy.h"
#include "Item.h"
#include "EffectManager.h"
class CGame {
private:
	//�G
	CEnemy* m_EnemyArray;
	//�X�e�[�W
	CStage m_Stage;
	//�v���[���[
	CPlayer m_Player;
	//�A�C�e��
	CItem* m_ItemArray;
	//�G�t�F�N�g
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