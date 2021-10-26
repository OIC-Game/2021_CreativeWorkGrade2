#pragma once

#include "Mof.h"
#include "Player.h"

class CBlock
{
private:

	CTexture*		m_Texture;		//�u���b�N�̉摜
	CRectangle		m_Rect;			//�摜�̕\���ʒu
	CItem*			m_Item;			//�A�C�e��
	int				m_Type;			//�u���b�N�̎��
	CVector2		m_SPos;			//�u���b�N�̏����ʒu
	CVector2		m_Pos;			//�u���b�N�̈ʒu
	CVector2		m_Move;			//�u���b�N�̈ړ����x
	CBlockDefine*	m_define;		
	int				m_Broken;		//�󂷂��Ƃ��o����L����
	int				m_Dirction;		//�����蔻����s������
	bool			m_BAttacked;
	bool			m_Attacked;
	

public:
	CBlock();
	~CBlock();

	bool Load(CTexture* tex, Vector2 pos, CRectangle rec, CItem* item, int type, int broken, CBlockDefine* define);

	//void Initialize();

	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="wx">�������̃X�N���[���ʒu</param>
	/// <param name="wy">�c�����̃X�N���[���ʒu</param>
	void Render(float wx, float wy);

	void AttackBlock(CPlayer* pl, CTexture* itemTextures);

	bool CheckDirection(int dir) { return (m_Dirction & dir) == dir; };

	bool IsAttacked() { return m_Attacked; };

	int GetType() { return m_Type; };

	CVector2 GetMove() { return m_Move; };

	bool CheckDamageFlg(int flg) {
		if (m_define == NULL) return false;
		return (m_define->damageFlg & flg) == flg;
	};
	bool CheckDamageDirection(int dir) {
		if (m_define == NULL) return false;
		return (m_define->damageDirection & dir) == dir;
	};

	CRectangle GetRect() { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_Rect.GetWidth(), m_Pos.y + m_Rect.GetHeight()); };
};

