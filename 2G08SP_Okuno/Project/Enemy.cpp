#include "Enemy.h"

CEnemy::CEnemy() :
	m_stgh(0),
	m_bShow(false),
	m_ShowState(0),
	m_sPos(),
	m_Pos(),
	m_Move(),
	m_JumpStatus(0),
	m_bReverse(false),
	m_JumpSp(0),
	m_JustTrampled(false),
	m_Texture(),
	m_Damaged(false),
	m_bGoal(false),
	m_hp(0)
{
}

CEnemy::~CEnemy()
{
}

bool CEnemy::Load(CTexture* tex, CEnemyDefine* ed, CSoundBuffer* skillSound)
{
	m_Texture = tex;
	m_define = ed;
	m_SkillSound = skillSound;

	m_Motion.Create(ed->anim, ed->animCount);
	return true;
}

void CEnemy::Initialize(Vector2 pos, bool bGoal, int stgh)
{
	m_sPos = pos;
	m_Pos = pos;
	m_JumpStatus = OnGround;
	m_stgh = stgh;
	m_bReverse = false;
	m_Move.x = m_define->x_ext1;
	m_hp = m_define->hp;
	if ((m_define->move & MOVE_LEFT) == MOVE_LEFT) {
		m_Move.x *= -1;
		m_bReverse = true;
	}
	m_Damaged = false;
	m_bGoal = bGoal;
	m_bShow = true;
	m_JumpSp = 0;
	m_ShowState = STATE_YET;
}

void CEnemy::Update(float wx, float wy, CRectangle prec)
{
	if (!m_bShow || m_ShowState == STATE_DISAPPEAR) {
		return;
	}
	if (m_ShowState == STATE_DISSHOW) {
		CRectangle rect = GetRect();
		if (rect.Right >= wx && rect.Left <= wx + g_pGraphics->GetTargetWidth()) {
			m_ShowState = STATE_SHOW;
		}
		else {
			return;
		}
	}
	else if (m_ShowState == STATE_SHOW) {
		CRectangle rect = GetRect();
		if (rect.Right < wx || rect.Left > wx + g_pGraphics->GetTargetWidth()) {
			m_ShowState = STATE_DISSHOW;
			return;
		}
	}

	if (m_ShowState == STATE_YET) {
		if ((m_define->move & MOVE_SENSE) == MOVE_SENSE) {
			m_Move.x = m_define->x_ext1;
			CRectangle erec = GetRect();
			if ((prec.Left + prec.Right) / 2 > (erec.Left + erec.Right) / 2) {
				m_Move.x *= -1;
			}
		}
		m_ShowState = STATE_SHOW;
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());


	if (m_JumpStatus == Jumping) {
		m_Move.y += JumpFSp;
		if (m_Move.y > JumpMaxSpeed) {
			m_Move.y = JumpMaxSpeed;
		}
	}

	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;

	//落下時の処理
	if (m_Pos.y > m_stgh) {
		Damage(true);
	}
}

void CEnemy::Render(float wx, float wy)
{
	if (!m_bShow || m_ShowState != STATE_SHOW) {
		return;
	}

	CRectangle cr = m_Motion.GetSrcRect();
	//反転フラグが有効の時は画像を反転する
	if (m_bReverse) {
		float tmp = cr.Left;
		cr.Left = cr.Right;
		cr.Right = tmp;
	}
	m_Texture[m_define->idx - 1].Render(m_Pos.x - wx, m_Pos.y - wy, cr);
}

void CEnemy::Release()
{
	m_Motion.Release();
}

void CEnemy::CollisionStage(CCollisionData coll)
{
	//プレイヤーの位置を修正する
	m_Pos.x += coll.ox;
	m_Pos.y += coll.oy;

	//落下時かつ下方向への埋まり
	if (coll.oy < 0 && m_Move.y > 0) {
		//上下方向の速度を無くす
		m_Move.y = 0;
		//ステータスがジャンプ状態の場合、接地状態にする
		if (m_JumpStatus == Jumping) {
			m_JumpStatus = OnGround;
		}
	}
	//上昇時かつ上方向への埋まり
	else if (coll.oy > 0 && m_Move.y < 0) {
		//上下方向の速度を無くす
		m_Move.y = 0;
	}

	//右移動かつ右方向への埋まり
	if (coll.ox < 0 && m_Move.x > 0) {
		//左移動にする
		m_Move.x *= -1;
		m_bReverse = true;
	}
	//左移動かつ左方向への埋まり
	else if (coll.ox > 0 && m_Move.x < 0) {
		//右移動にする
		m_Move.x *= -1;
		m_bReverse = false;
	}

	//接地状態（地面に足がついている）ではなくステータスが接地状態の場合
	if (!coll.og && m_JumpStatus == OnGround) {
		//ステータスをジャンプ状態にする
		m_JumpStatus = Jumping;
	}
}

void CEnemy::CollisionEnemy(CEnemy& ene)
{
	if (CollisionObj(ene.GetRect(), ene.GetMove(), ene.GetDamageFlg(), ene.GetDamageDirection())) {
		//当たった時の処理
		//m_Move.x *= -1;
		//m_bReverse = !m_bReverse;
	}
}

void CEnemy::CollisionSkill(CSkillObj& sObj)
{
	if (CollisionObj(sObj.GetRect(), sObj.GetMove(), sObj.GetDamageFlg(), sObj.GetDamageDirection())) {
		//当たった時の処理
		if (m_Damaged) {
			if (m_ShowState == STATE_DISAPPEAR) {
				m_SkillSound->Play();
			}
			sObj.Hit();
		}
	}
}

bool CEnemy::CollisionObj(CRectangle erec, CVector2 eMove, int eDmgFlg, int eDmgDir)
{
	m_Damaged = false;
	if (!GetShow() || !GetDisplay()) {
		return false;
	}

	CRectangle prec = GetRect();
	//CRectangle erec = ene.GetRect();
	erec.Expansion(-3, -3);

	bool pr_result = false;

	if (erec.CollisionRect(prec)) {
		if ((eDmgDir & BlockAll) == BlockAll) {
			if ((eDmgFlg & DAMAGE_ONLY_ENEMY) == DAMAGE_ONLY_ENEMY) {

				//m_bShow = false;

				Damage(false);
			}
		}
		pr_result = true;
	}

	//右方向判定用
	CRectangle elrec = erec;
	elrec.Right = (elrec.Left + elrec.Right) / 2;

	CRectangle rrec = prec;
	rrec.Left = rrec.Right - 1;
	rrec.Expansion(0, -6);

	//左方向判定用
	CRectangle errec = erec;
	errec.Left = (errec.Left + errec.Right) / 2;

	CRectangle lrec = prec;
	lrec.Right = lrec.Left + 1;
	lrec.Expansion(0, -6);

	//踏みつけ判定用
	CRectangle hrec = erec;
	hrec.Bottom = (hrec.Bottom + hrec.Top) / 2;

	CRectangle brec = prec;
	brec.Top = brec.Bottom - 1;
	brec.Expansion(-6, 0);

	//踏みつけた場合
	if (hrec.CollisionRect(brec) && (m_Move.y >= 0 || eMove.y <= 0)) {
		if ((eDmgDir & BlockUp) == BlockUp) {
			if ((eDmgFlg & DAMAGE_ONLY_ENEMY) == DAMAGE_ONLY_ENEMY) {

				//m_bShow = false;
				Damage(false);
			}
		}
		pr_result = true;
	}

	//上方向判定用
	CRectangle drec = erec;
	drec.Top = (drec.Bottom + drec.Top) / 2;

	CRectangle trec = prec;
	trec.Bottom = trec.Top + 1;
	trec.Expansion(-6, 0);

	if (drec.CollisionRect(trec) && (m_Move.y <= 0 || eMove.y >= 0)) {
		if ((eDmgDir & BlockDown) == BlockDown) {
			if ((eDmgFlg & DAMAGE_ONLY_ENEMY) == DAMAGE_ONLY_ENEMY) {

				//m_bShow = false;
				Damage(false);
			}
		}
		pr_result = true;
	}


	if (elrec.CollisionRect(rrec) && (m_Move.x >= 0 || eMove.x <= 0)) {
		if ((eDmgDir & BlockLeft) == BlockLeft) {
			if ((eDmgFlg & DAMAGE_ONLY_ENEMY) == DAMAGE_ONLY_ENEMY) {

				//m_bShow = false;
				Damage(false);
			}
		}
		pr_result = true;
	}


	if (errec.CollisionRect(lrec) && (m_Move.x <= 0 || eMove.x >= 0)) {
		if ((eDmgDir & BlockRight) == BlockRight) {
			if ((eDmgFlg & DAMAGE_ONLY_ENEMY) == DAMAGE_ONLY_ENEMY) {

				//m_bShow = false;
				Damage(false);
			}
		}
		pr_result = true;
	}
	return pr_result;
}

void CEnemy::Trampled(CRectangle prec)
{
	if ((m_define->changeFlg & CHANGE_TRAMPLED) == CHANGE_TRAMPLED) {

		m_define = CGameDefine::GetGameDefine()->GetEnemyByIdx(m_define->changeIdx);
		m_JustTrampled = true;

		if (m_define == NULL) {
			//m_bShow = false;
			m_ShowState = STATE_DISAPPEAR;
			return;
		}
		float bHeight = GetRect().GetHeight();
		m_Motion.Create(m_define->anim, m_define->animCount);
		m_Pos.y += bHeight - GetRect().GetHeight();
		m_Move.x = m_define->x_ext1;
		if ((m_define->move & MOVE_LEFT) == MOVE_LEFT) {
			m_Move.x *= -1;
		}
		else if ((m_define->move & MOVE_SENSE) == MOVE_SENSE) {
			CRectangle erec = GetRect();
			if ((prec.Left + prec.Right) / 2 > (erec.Left + erec.Right) / 2) {
				m_Move.x *= -1;
			}
		}
	}
	else {
		//m_bShow = false;
		m_ShowState = STATE_DISAPPEAR;
	}
}

void CEnemy::Damage(bool death)
{
	m_hp -= 1;
	if (death || m_hp <= 0) {
		m_ShowState = STATE_DISAPPEAR;
	}
	m_Damaged = true;
}

bool CEnemy::Touched(CRectangle prec, bool sence)
{
	if ((m_define->changeFlg & CHANGE_TOUCH) == CHANGE_TOUCH) {

		m_define = CGameDefine::GetGameDefine()->GetEnemyByIdx(m_define->changeIdx);

		if (m_define == NULL) {
			//m_bShow = false;
			m_ShowState = STATE_DISAPPEAR;
			return true;
		}
		m_Motion.Create(m_define->anim, m_define->animCount);
		m_Move.x = m_define->x_ext1;
		if ((m_define->move & MOVE_LEFT) == MOVE_LEFT) {
			m_Move.x *= -1;
		}
		else if ((m_define->move & MOVE_SENSE) == MOVE_SENSE) {
			if (sence) {
				CRectangle erec = GetRect();
				if ((prec.Left + prec.Right) / 2 > (erec.Left + erec.Right) / 2) {
					m_Move.x *= -1;
				}
			}
		}
		return true;
	}
	return false;
}

void CEnemy::PushedUp()
{
	//m_bShow = false;
	if ((m_define->changeFlg & CHANGE_TOUCH) == CHANGE_TOUCH) {
		Touched(CRectangle(0, 0, 0, 0), false);
	}
	else {
		m_ShowState = STATE_DISAPPEAR;
	}
}

void CEnemy::SlideMove(CVector2 v)
{
	m_Pos.x += v.x;
	m_Pos.y += v.y;
}
