#pragma once

#include "Mof.h"
#include "GameDefine.h"
#include "CollisionData.h"

class CItem
{
private:
	const float		JumpFSp = 0.7f;							//�������̉����x�i�����x�j
	const float		JumpMaxSpeed = 8.0f;						//�����̏�����x
	const float		BShowAnimTime = 1.0f;

	enum JumpStatus {
		OnGround,
		Jumping
	};
	bool		m_animShow;
	float		m_animShowTime;

	CTexture*		m_Texture;		//�摜
	CRectangle		m_Rect;			//�摜�\���ʒu
	CItemDefine*	m_Define;
	int				m_DfX;			//�����ʒuX
	int				m_DfY;			//�����ʒuY
	CVector2		m_Pos;			//�ʒu
	CVector2		m_Spd;			//�ړ����x
	int				m_Type;			//�A�C�e���̎��
	bool			m_bShow;		//�\���t���O
	int				m_ShowState;	//�\�����
	int				m_stgh;
	int				m_JumpStatus;	//���

public:
	CItem();
	~CItem();

	bool Load(CTexture* tex, CRectangle rec);

	void Initialize(CVector2 pos, CVector2 spd, CItemDefine* def, int type, int dfX, int dfY, bool dfShow, int stgh);

	void Render(float wx, float wy);

	void Update(float wx, float wy);

	/// <summary>
	/// �X�e�[�W�ւ̖��܂����������
	/// </summary>
	/// <param name="coll">���܂��̏��</param>
	void CollisionStage(CCollisionData coll);

	void Get();

	int GetDfX() { return m_DfX; };
	int GetDfY() { return m_DfY; };

	int GetType() { return m_Type; };

	CVector2 GetMove() { return m_Spd; };

	CRectangle GetRect() { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_Rect.GetWidth(), m_Pos.y + m_Rect.GetHeight()); };

	void BShow(CVector2 pos, int marioType, CTexture* itemTextures);

	bool GetShow() { return m_bShow; };
	bool GetDisplay() { return m_ShowState == STATE_SHOW; };
	void SetDisplay(int state) { if (m_ShowState != STATE_DISAPPEAR) m_ShowState = state; }
};

