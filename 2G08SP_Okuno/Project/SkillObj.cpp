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
	//反転フラグが有効の時は画像を反転する
	if (m_bReverse) {
		float tmp = cr.Left;
		cr.Left = cr.Right;
		cr.Right = tmp;
	}
	m_Texture->Render(m_Pos.x - wx, m_Pos.y - wy, cr);
}

void CSkillObj::CollisionStage(CCollisionData coll)
{
	//位置を修正する
	m_Pos.x += coll.ox;
	m_Pos.y += coll.oy;

	//落下時かつ下方向への埋まり
	if (coll.oy < 0 && m_Move.y > 0) {
		//上下方向の速度を無くす
		m_Move.y = -7;
		return;
	}
	//上昇時かつ上方向への埋まり
	else if (coll.oy > 0 && m_Move.y < 0) {
		//消える
		m_bShowNow = false;
	}

	//右移動かつ右方向への埋まり
	if (coll.ox < 0 && m_Move.x > 0) {
		//消える
		m_bShowNow = false;
	}
	//左移動かつ左方向への埋まり
	else if (coll.ox > 0 && m_Move.x < 0) {
		//消える
		m_bShowNow = false;
	}
}
