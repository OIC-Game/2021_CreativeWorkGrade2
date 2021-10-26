#include "CharaBase.h"

CCharaBase::CCharaBase() :
	m_Texture(NULL),
	m_PosX(0),
	m_PosY(0),
	m_MoveX(0),
	m_MoveY(0),
	m_bReverse(false),
	m_JumpSp(0),
	m_JumpStatus(0)
{
}

CCharaBase::~CCharaBase()
{
}

bool CCharaBase::Load(CTexture* tex, SpriteAnimationCreate anim[], int animCount)
{
	m_Texture = tex;
	m_Motion.Create(anim, animCount);
	return true;
}

void CCharaBase::Initialize(Vector2 pos)
{
	m_PosX = pos.x;
	m_PosY = pos.y;
	m_MoveX = 0;
	m_MoveY = 0;
	m_bReverse = false;
	m_JumpSp = 0;
	m_JumpStatus = 0;
}

void CCharaBase::CollisionStage(CCollisionData coll)
{
	//�v���C���[�̈ʒu���C������
	m_PosX += coll.ox;
	m_PosY += coll.oy;

	//���������������ւ̖��܂�
	if (coll.oy < 0 && m_MoveY > 0) {
		//�㉺�����̑��x�𖳂���
		m_MoveY = 0;
		//�X�e�[�^�X���W�����v��Ԃ̏ꍇ�A�ڒn��Ԃɂ���
		if (m_JumpStatus == Jumping) {
			m_JumpStatus = OnGround;
		}
	}
	//�㏸����������ւ̖��܂�
	else if (coll.oy > 0 && m_MoveY < 0) {
		//�㉺�����̑��x�𖳂���
		m_MoveY = 0;
	}

	//�E�ړ����E�����ւ̖��܂�
	if (coll.ox < 0 && m_MoveX > 0) {
		//�������̑��x�𖳂���
		m_MoveX = 0;
	}
	//���ړ����������ւ̖��܂�
	else if (coll.ox > 0 && m_MoveX < 0) {
		//�������̑��x�𖳂���
		m_MoveX = 0;
	}

	if (!coll.og && m_JumpStatus == OnGround) {
		//�X�e�[�^�X���W�����v��Ԃɂ���
		m_JumpStatus = Jumping;
	}
}
