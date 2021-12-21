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
	//�v���C���[
	CPlayer				m_Player;

	CPlayerFire			m_WorkFire;
	//�X�e�[�W
	CStage				m_Stage;
	//�G
	CEnemy*				m_EnemyArray;
	//�A�C�e��
	CItem*				m_ItemArray;
	//�|�b�v�A�C�e��
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

