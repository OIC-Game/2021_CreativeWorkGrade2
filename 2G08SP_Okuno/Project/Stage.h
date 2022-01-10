#pragma once

#include "Mof.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Block.h"
#include "CollisionData.h"

class CStage
{
private:
	CTexture	m_BgTexture;		//�w�i�摜
	CTexture	m_ChipTexture;		//�}�b�v�`�b�v�摜
	CTexture* m_pEnemyTexture;	//�G�摜
	CTexture* m_pItemTexture;		//�A�C�e���摜
	CEnemy* m_EnemyArray;
	CItem* m_ItemArray;
	CBlock* m_BlockArray;

	int			m_EnemyTextureCount;//�G�摜�̐�
	char* m_pEnemyData;		//�G�̔z�u���
	int			m_EnemyCount;		//�G�̑���
	int			m_ItemTextureCount;	//�A�C�e���摜�̐�
	char* m_pItemData;		//�A�C�e���̔z�u���
	int			m_ItemCount;		//�A�C�e���̑���
	//float		m_ChipSize;			//�`�b�v��̃T�C�Y
	int			m_XSize;			//�}�b�v�̉������̃}�X�̐�
	int			m_YSize;			//�}�b�v�̏c�����̃}�X�̐�
	int* m_ChipData;			//�}�b�v�̊e�}�X�̏��
	int			m_BlockCount;		//
	int			m_StartX;			//�v���C���[�̏����ʒu
	int			m_StartY;			//�v���C���[�̏����ʒu
	int			m_StageType;

	float		m_ScrollX;			//�������̃X�N���[���ʒu
	float		m_ScrollY;			//�c�����̃X�N���[���ʒu

public:
	CStage();
	~CStage();

	bool Load(char* fname, int sx, int sy, int sType);

	void Initialize(bool bGoal, int gType, int gx, int gy, CSoundBuffer* skillSound);
	void StageFlash(); //�X�e�[�W���̓G�Ȃǂ̃X�e�[�^�X��\����Ԃɂ���

	void Update(CPlayer& pl);
	void UpdateScroll(CPlayer& pl);

	void Render();
	void RenderLayerOver();

	void RenderDebug_Enemy();

	void Release();

	/// <summary>
	/// �X�e�[�W�Ƃ̐ڐG����i�߂荞��ł��邩�ǂ����j
	/// </summary>
	/// <param name="r">���肷����́i�L�����N�^�[�Ȃǁj�̋�`</param>
	/// <param name="ox">�X�e�[�W�ւ̍��E�̖��܂�������</param>
	/// <param name="oy">�X�e�[�W�ւ̏㉺�̖��܂�������</param>
	/// <param name="og">�ڒn�i���n�j���Ă��邩�ǂ���������</param>
	/// <returns>�ڐG����Ԃ�</returns>
	CCollisionData Collision(CPlayer* pl, CEnemy* ene, CRectangle rb, CRectangle ra, CVector2 move);
	void Collision_Dir(CPlayer* pl, CEnemy* ene, CRectangle* rb, CRectangle* ra, CVector2 move, CBlock* block, CRectangle blockRect, CCollisionData* coll, bool& leftFallFlg, bool& rightFallFlg, int direction);

	void CheckPointThrough(CRectangle rect);

	bool DoorAnimation(CRectangle rect, float animTime, bool isIn);
	void EndDoorAnimation(CRectangle rect);

	Vector2 GetStartPos() { return Vector2(CHIPSIZE * m_StartX, CHIPSIZE * m_StartY); }

	bool IsGEnemy() {
		for (int i = 0; i < m_EnemyCount; i++) {
			if (m_EnemyArray[i].IsGEnemy()) {
				return true;
			}
		}
		return false;
	};

	float GetScrollX() { return m_ScrollX; };

	float GetScrollY() { return m_ScrollY; };

	float GetStageWidth() { return CHIPSIZE * m_XSize; };

	float GetStageHeight() { return CHIPSIZE * m_YSize; };

	int GetEnemyCount() { return m_EnemyCount; };

	int GetItemCount() { return m_ItemCount; };

	int GetBlockCount() { return m_BlockCount; };
};

