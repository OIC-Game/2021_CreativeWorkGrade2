#pragma once

#include	"Player.h"
#include    "Enemy.h"
#include    "Item.h"
//���X�΃`�b�v
#define LEFTSLOPE 2

class CStage {
private:
	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;
	int                     m_ItemTextureCount;
	CTexture*               m_pItemTexture;
	char*                   m_pItemData;
	int                     m_ItemCount;
	int m_EnemyTextureCount;//�G�̎�ސ��i���e�N�X�`���̐��j
	CTexture* m_pEnemyTexture; //�G�̎�ނ��Ƃ̃e�N�X�`�����i�[�����z��
	char* m_pEnemyData; //�G�̔z�u�f�[�^
	int m_EnemyCount; //�G�̔z�u�����v
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