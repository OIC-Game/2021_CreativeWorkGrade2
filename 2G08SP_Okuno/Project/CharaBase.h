#pragma once

#include "Mof.h"
#include "GameDefine.h"
#include "CollisionData.h"

class CCharaBase
{
protected:
	//�v���C���[�̏�Ԃ�\��
	enum JumpStatus {
		OnGround,		//�ڒn��ԁi�n�ʂɑ������Ă���j
		Jumping,		//�W�����v��ԁi�n�ʂɑ������Ă��Ȃ��j
		Manualing		//�����ԁi�d�͂𖳎�����j
	};

	CTexture*		m_Texture;		//�摜
	//CRectangle		m_Rect;			//�\������ӏ�
	CSpriteMotionController	m_Motion;

	float			m_PosX;			//X���W
	float			m_PosY;			//Y���W
	float			m_MoveX;		//�������̈ړ����x
	float			m_MoveY;		//�㉺�����̈ړ����x
	bool			m_bReverse;		//�摜���]�t���O
	float			m_JumpSp;		//�����x
	int				m_JumpStatus;	//���

public:
	CCharaBase();
	~CCharaBase();

	virtual bool Load(CTexture* tex, SpriteAnimationCreate anim[], int animCount);

	virtual void Initialize(Vector2 pos);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="wx">�������̃X�N���[���ʒu</param>
	/// <param name="wy">�c�����̃X�N���[���ʒu</param>
	virtual void Render(float wx, float wy)=0;

	/// <summary>
	/// �X�e�[�W�ւ̖��܂����������
	/// </summary>
	/// <param name="coll">���܂��̏��</param>
	virtual void CollisionStage(CCollisionData coll);

	virtual CRectangle GetRect()=0;
};

