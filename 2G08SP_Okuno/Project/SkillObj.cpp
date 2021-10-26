#include "SkillObj.h"

CSkillObj::CSkillObj() :
	m_Texture(),
	m_BRect(),
	m_DamageFlg(0),
	m_Pos(),
	m_Move(),
	m_bShowNow(false),
	m_bReverse(false)
{
}

CSkillObj::~CSkillObj()
{
}

bool CSkillObj::Load(CTexture* tex, int dmgFlg)
{
	m_Texture = tex;
	m_DamageFlg = dmgFlg;
	m_Motion.Create(skill_anim, SKILL_COUNT);
	m_bShowNow = false;
	m_bReverse = false;
	return true;
}

bool CSkillObj::Fire(Vector2 pos, CVector2 move)
{
	if (m_bShowNow) return false;
	m_bShowNow = true;
	m_Pos = pos;
	m_Move = move;
	m_BRect = GetRect();
	return true;
}

void CSkillObj::Update(float wx, float wy)
{
	if (!m_bShowNow) return;
	if (!CGameDefine::GetGameDefine()->GetGameScreenRect(wx, wy).CollisionRect(GetRect())) {
		m_bShowNow = false;
		return;
	}
	m_BRect = GetRect();

	m_Move.y += m_fSp;
	if (m_Move.y > m_MaxFSp) {
		m_Move.y = m_MaxFSp;
	}
	m_bReverse = m_Move.x < 0;

	m_Pos += m_Move;
}

void CSkillObj::Render(float wx, float wy)
{
	if (!m_bShowNow) return;

	CRectangle cr = m_Motion.GetSrcRect();
	//���]�t���O���L���̎��͉摜�𔽓]����
	if (m_bReverse) {
		float tmp = cr.Left;
		cr.Left = cr.Right;
		cr.Right = tmp;
	}
	m_Texture->Render(m_Pos.x - wx, m_Pos.y - wy, cr);
}

void CSkillObj::CollisionStage(CCollisionData coll)
{
	//�ʒu���C������
	m_Pos.x += coll.ox;
	m_Pos.y += coll.oy;

	//���������������ւ̖��܂�
	if (coll.oy < 0 && m_Move.y > 0) {
		//�㉺�����̑��x�𖳂���
		m_Move.y = -7;
		return;
	}
	//�㏸����������ւ̖��܂�
	else if (coll.oy > 0 && m_Move.y < 0) {
		//������
		m_bShowNow = false;
	}

	//�E�ړ����E�����ւ̖��܂�
	if (coll.ox < 0 && m_Move.x > 0) {
		//������
		m_bShowNow = false;
	}
	//���ړ����������ւ̖��܂�
	else if (coll.ox > 0 && m_Move.x < 0) {
		//������
		m_bShowNow = false;
	}
}
