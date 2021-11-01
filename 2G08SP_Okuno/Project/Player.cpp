#include "Player.h"

CPlayer::CPlayer() :
	m_sth(0),
	m_TypeIdx(0),
	m_bDead(false),
	m_bGoal(false),
	m_DmgTime(false),
	m_Life(0),
	m_Pos(),
	m_Move(),
	m_BRect(),
	m_JumpStatus(0),
	m_bReverse(false),
	m_JumpSp(0),
	m_Texture(),
	m_SkillTexture()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load(CTexture* tex, CTexture* skillTex, CSoundBuffer* sounds)
{
	m_Texture = tex;
	m_SkillTexture = skillTex;
	m_SoundArray = sounds;
	m_Motion.Create(pl_anim, ANIM_COUNT * MARIO_COUNT);
	for (int i = 0; i < 2; i++) {
		m_SkillObj[i].Load(skillTex, DAMAGE_ONLY_ENEMY);
	}
	return true;
}

void CPlayer::Initialize(Vector2 pos, int life)
{
	m_Pos = pos;
	m_JumpStatus = OnGround;
	m_TypeIdx = 0;
	m_JumpSp = 0;
	m_Move.x = 0;
	m_Move.y = 0;
	m_bReverse = false;
	m_bDead = false;
	m_bGoal = false;
	m_DmgTime = 0;
	m_Life = life;
	m_BRect = GetRect(false);
	m_Motion.ChangeMotion(0);
}

void CPlayer::JumpStart() {
	JumpStart(0);
}

void CPlayer::JumpStart(float SSpeed) {
	//ステータスをジャンプ中に設定
	m_JumpStatus = Jumping;

	//ジャンプによる上下方向の加速度を設定
	m_JumpSp = JumpUSp;

	//初速度のインデックス
	int ix = 0;

	if (SSpeed < 0) {
		m_Move.y = SSpeed;
	}
	//横方向への移動速度でジャンプの高さを変える
	else {
		if (m_Move.x >= MoveMaxSpeed) ix++;
		if (m_Move.x > MoveMaxSpeed) ix++;
		m_Move.y = JumpSSpeed[ix];
	}

	m_SoundArray[SOUND_JUMP].Play();
}

void CPlayer::JumpingFn(bool btnPull)
{
	//上下方向の速度が下方向、もしくはジャンプボタンが離された場合
	if (m_Move.y >= 0 || btnPull) {
		//上下方向の加速度を落下時の加速度に変える
		m_JumpSp = JumpFSp;
	}

	//上下方向の速度に加速度分加算する
	m_Move.y += m_JumpSp;

	//落下上限速度で制限する
	if (m_Move.y >= JumpMaxSpeed) {
		m_Move.y = JumpMaxSpeed;
	}
}

void CPlayer::Damage(bool death)
{
	if (m_DmgTime > 0 && !death) return;
	if (m_TypeIdx == 0 || death) {
		m_TypeIdx = 0;
		m_bDead = true;
		return;
	}

	m_TypeIdx--;
	float dh = m_Motion.GetSrcRect().GetHeight();
	m_Motion.ChangeMotion(m_Motion.GetMotionNo() % ANIM_COUNT + m_TypeIdx * ANIM_COUNT);

	dh -= m_Motion.GetSrcRect().GetHeight();
	m_Pos.y += dh;

	m_DmgTime = 2.8f;
}

void CPlayer::Update(float wx, float wy)
{
	m_BRect = GetRect(false);

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	if (m_DmgTime > 0) {
		m_DmgTime -= CUtilities::GetFrameSecond();
	}
	//このフレームで横移動(入力)があったかどうか
	bool bMove = false;

	if (!m_bGoal) {
		//左（マイナス）移動（←又はA）
		if (g_pInput->IsKeyHold(MOFKEY_LEFT) || g_pInput->IsKeyHold(MOFKEY_A)) {
			bMove = true;
			//左向きなので画像反転フラグを有効にする
			m_bReverse = true;
			//ダッシュ判定（左CTRL又は右クリック）
			if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) || g_pInput->IsMouseKeyHold(1)) {
				//横方向の速度に加速度分加算する
				if (m_Move.x > -MoveMaxSpeed) {
					m_Move.x -= MoveSpeed;
				}
				else {
					m_Move.x -= RunSpeed;
				}
				//左（マイナス）のダッシュ上限速度で制限する
				if (m_Move.x < -RunMaxSpeed) {
					m_Move.x = -RunMaxSpeed;
				}
			}
			else {
				if (m_Move.x > -MoveMaxSpeed) {
					//横方向の速度に加速度分加算する
					m_Move.x -= MoveSpeed;
				}
				//左（マイナス）の上限速度で制限する（上限速度まで減速する）
				if (m_Move.x < -MoveMaxSpeed) {
					m_Move.x += MoveSpeed;
					if (m_Move.x > -MoveMaxSpeed) {
						m_Move.x = -MoveMaxSpeed;
					}
				}
			}
		}
		//右（プラス）移動（→又はD）
		else if (g_pInput->IsKeyHold(MOFKEY_RIGHT) || g_pInput->IsKeyHold(MOFKEY_D)) {
			bMove = true;
			//右向きなので画像反転フラグを無効にする
			m_bReverse = false;
			//ダッシュ判定（左CTRL又は右クリック）
			if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) || g_pInput->IsMouseKeyHold(1)) {
				//横方向の速度に加速度分加算する
				if (m_Move.x < MoveMaxSpeed) {
					m_Move.x += MoveSpeed;
				}
				else {
					m_Move.x += RunSpeed;
				}
				//右（プラス）のダッシュ上限速度で制限する
				if (m_Move.x > RunMaxSpeed) {
					m_Move.x = RunMaxSpeed;
				}
			}
			else {
				if (m_Move.x < MoveMaxSpeed) {
					//横方向の速度に加速度分加算する
					m_Move.x += MoveSpeed;
				}
				//右（プラス）の上限速度で制限する（上限速度まで減速する）
				if (m_Move.x > MoveMaxSpeed) {
					m_Move.x -= MoveSpeed;
					if (m_Move.x < MoveMaxSpeed) {
						m_Move.x = MoveMaxSpeed;
					}
				}
			}
		}

		if (m_TypeIdx == CGameDefine::GetGameDefine()->GetMarioIdx(MARIO_FIRE) && 
			(g_pInput->IsKeyPush(MOFKEY_LCONTROL) || g_pInput->IsMouseKeyPush(1))) {
			CVector2 f_pos = CVector2(m_Pos.x, m_Pos.y + GetRect(false).GetHeight() / 2);
			CVector2 f_move = CVector2(-8, 4);
			if (!m_bReverse) {
				f_pos.x += GetRect(false).GetWidth() - 16;
				f_move.x *= -1;
			}
			for (int i = 0; i < 2; i++) {
				if (!m_SkillObj[i].Fire(f_pos, f_move)) continue;
				m_SoundArray[SOUND_FIRE].Play();
				break;
			}
		}

		//このフレームでジャンプボタンが押された場合
		if (g_pInput->IsKeyPush(MOFKEY_SPACE) || g_pInput->IsMouseKeyPush(0)) {
			//ステータスが接地状態（地面に足がついている）なら
			if (m_JumpStatus == OnGround) {
				//ジャンプ処理を開始する
				JumpStart();
			}
		}
	}
	//ステータスがジャンプ状態（地面に足がついていない）なら
	if (m_JumpStatus == Jumping) {
		bool btnPull = g_pInput->IsKeyPull(MOFKEY_SPACE) || g_pInput->IsMouseKeyPull(0);
		//ジャンプ処理を実行する
		JumpingFn(btnPull && !m_bGoal);

		if (m_Move.y < 0 && m_Motion.GetMotionNo() % ANIM_COUNT != ANIM_JUMP) {
			m_Motion.ChangeMotion(m_Motion.GetMotionNo() / ANIM_COUNT * ANIM_COUNT + ANIM_JUMP);
		}
	}
	else {
		if (m_Move.x != 0) {
			if (m_Motion.GetMotionNo() % ANIM_COUNT != ANIM_DASH) {
				m_Motion.ChangeMotion(m_Motion.GetMotionNo() / ANIM_COUNT * ANIM_COUNT + ANIM_DASH);
			}
		}
		else if (m_Motion.GetMotionNo() % ANIM_COUNT != ANIM_STAND) {
			m_Motion.ChangeMotion(m_Motion.GetMotionNo() / ANIM_COUNT * ANIM_COUNT + ANIM_STAND);
		}
	}

	//このフレームで横移動（入力）されなかった場合
	if (!bMove && !m_bGoal) {
		//次第に減速する
		if (m_Move.x > 0) {
			m_Move.x -= MoveSpeed;
			if (m_Move.x <= 0) {
				m_Move.x = 0;
			}
		}
		else if (m_Move.x < 0) {
			m_Move.x += MoveSpeed;
			if (m_Move.x >= 0) {
				m_Move.x = 0;
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		m_SkillObj[i].Update(wx, wy);
	}

	//プレイヤーの位置に速度分加算する
	if (m_JumpStatus != Manualing) {
		m_Pos.x += m_Move.x;
		m_Pos.y += m_Move.y;
	}

	//左端からはみ出さない
	if (m_Pos.x < wx) {
		m_Pos.x = wx;
	}

	//落下時の処理
	if (m_Pos.y > m_sth) {
		m_bDead = true;
	}
}

void CPlayer::Render(float wx, float wy)
{

	for (int i = 0; i < 2; i++) {
		m_SkillObj[i].Render(wx, wy);
	}

	if (m_DmgTime > 0) {
		float x = 0.3f;
		float m = fmod(m_DmgTime, x);
		if (m > 0.15f) return;
	}

	CRectangle cr = m_Motion.GetSrcRect();
	//反転フラグが有効の時は画像を反転する
	if (m_bReverse) {
		float tmp = cr.Left;
		cr.Left = cr.Right;
		cr.Right = tmp;
	}
	m_Texture->Render(m_Pos.x - wx, m_Pos.y - wy, cr);
}

void CPlayer::CollisionStage(CCollisionData coll)
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
		m_Move.x  = 0;
	}
	//左移動かつ左方向への埋まり
	else if (coll.ox > 0 && m_Move.x < 0) {
		m_Move.x  = 0;
	}

	//接地状態（地面に足がついている）ではなくステータスが接地状態の場合
	if (!coll.og && m_JumpStatus == OnGround) {
		//ステータスをジャンプ状態にする
		m_JumpStatus = Jumping;
	}

	if (coll.damage && !coll.og) {
		Damage(false);
	}
}

void CPlayer::CollisionEnemy(CEnemy& ene)
{
	if (!ene.GetShow() || !ene.GetDisplay()) {
		return;
	}
	
	CRectangle prec = GetRect(true);
	CRectangle erec = ene.GetRect();
	erec.Expansion(0, -3);

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

	if (elrec.CollisionRect(rrec) && m_DmgTime <= 0 && !ene.GetJustTrampled()) {
		if ((ene.GetDamageFlg() & DAMAGE_ONLY_PLAYER) == DAMAGE_ONLY_PLAYER &&
			(ene.GetDamageDirection() & BlockLeft) != BlockLeft) {
			CCollisionData coll = CCollisionData();
			coll.ox = rrec.Right - elrec.Left;
			ene.CollisionStage(coll);
			if (ene.Touched(prec)) {
				return;
			}
		}
	}
	if (errec.CollisionRect(lrec) && m_DmgTime <= 0 && !ene.GetJustTrampled()) {
		if ((ene.GetDamageFlg() & DAMAGE_ONLY_PLAYER) == DAMAGE_ONLY_PLAYER &&
			(ene.GetDamageDirection() & BlockRight) != BlockRight) {
			CCollisionData coll = CCollisionData();
			coll.ox = lrec.Left - errec.Right;
			ene.CollisionStage(coll);
			if (ene.Touched(prec)) {
				return;
			}
		}
	}

	//踏みつけ判定用
	CRectangle hrec = erec;
	hrec.Bottom = (hrec.Bottom + hrec.Top) / 2;

	CRectangle brec = prec;
	brec.Top = brec.Bottom - 1;
	brec.Expansion(-6, 0);

	//踏みつけた場合
	if (hrec.CollisionRect(brec) && (m_Move.y >= 0 || ene.GetMove().y <= 0)) {
		if (ene.GetJustTrampled()) return;
		bool tFlg = (ene.GetChangeFlg() & CHANGE_TOUCH) == CHANGE_TOUCH;

		if ((ene.GetDamageFlg() & DAMAGE_ONLY_PLAYER) == DAMAGE_ONLY_PLAYER &&
			(ene.GetDamageDirection() & BlockUp) == BlockUp && 
			(ene.GetChangeFlg() & CHANGE_TRAMPLED) != CHANGE_TRAMPLED) {
			if (m_DmgTime > 0) return;

			Damage(false);
			return;
		}
		ene.Trampled(prec);
		m_SoundArray[SOUND_TRAMPLED].Play();

		if (g_pInput->IsKeyHold(MOFKEY_SPACE) || g_pInput->IsMouseKeyHold(0)) {
			JumpStart(-10.2f);			//ジャンプする
		}
		else {
			JumpStart(-6.2f);			//ジャンプする
		}
		return;
	}

	if (m_DmgTime > 0) return;

	//上方向判定用
	CRectangle drec = erec;
	drec.Top = (drec.Bottom + drec.Top) / 2;

	CRectangle trec = prec;
	trec.Bottom = trec.Top + 1;
	trec.Expansion(-6, 0);

	if (drec.CollisionRect(trec) && (m_Move.y <= 0 || ene.GetMove().y >= 0)) {
		if ((ene.GetDamageFlg() & DAMAGE_ONLY_PLAYER) == DAMAGE_ONLY_PLAYER &&
			(ene.GetDamageDirection() & BlockDown) == BlockDown) {
			if (m_DmgTime > 0 || ene.GetJustTrampled()) return;

			Damage(false);
			return;
		}
	}


	if (elrec.CollisionRect(rrec) && (m_Move.x >= 0 || ene.GetMove().x <= 0)) {
		if ((ene.GetDamageFlg() & DAMAGE_ONLY_PLAYER) == DAMAGE_ONLY_PLAYER &&
			(ene.GetDamageDirection() & BlockLeft) == BlockLeft) {
			if (m_DmgTime > 0 || ene.GetJustTrampled()) return;

			Damage(false);
			return;
		}
	}


	if (errec.CollisionRect(lrec) && (m_Move.x <= 0 || ene.GetMove().x >= 0)) {
		if ((ene.GetDamageFlg() & DAMAGE_ONLY_PLAYER) == DAMAGE_ONLY_PLAYER &&
			(ene.GetDamageDirection() & BlockRight) == BlockRight) {
			if (m_DmgTime > 0 || ene.GetJustTrampled()) return;

			Damage(false);
			return;
		}
	}

	if (ene.GetJustTrampled()) {
		ene.SetJustTrampled(erec.CollisionRect(prec));
	}
}

void CPlayer::CollisionItem(CItem& item)
{
	if (!item.GetShow()) {
		return;
	}

	CRectangle prec = GetRect(true);
	CRectangle irec = item.GetRect();
	irec.Expansion(-1, -1);

	prec.Expansion(-6, -6);

	if (irec.CollisionRect(prec)) {
		CItemDefine* bd = CGameDefine::GetGameDefine()->GetItemByIdx(item.GetType() + 1);

		item.Get();
		if (bd->itemType == ITEM_NORMAL) {
			if (m_TypeIdx < bd->ext1) {
				m_TypeIdx = bd->ext1;
			}
			else {
				return;
			}
			m_SoundArray[SOUND_ITEM_NORMAL].Play();
			float dh = m_Motion.GetSrcRect().GetHeight();
			m_Motion.ChangeMotion(m_Motion.GetMotionNo() % ANIM_COUNT + m_TypeIdx * ANIM_COUNT);

			dh -= m_Motion.GetSrcRect().GetHeight();
			m_Pos.y += dh;
		}
		else if (bd->itemType == ITEM_1UP) {
			m_Life += bd->ext1;
			m_SoundArray[SOUND_ITEM_1UP].Play();
		}
		else if (bd->itemType == ITEM_COIN) {
			m_SoundArray[SOUND_ITEM_COIN].Play();
		}
		return;
	}
}

bool CPlayer::GoalFn(float ox, int gType, float glb, float stw, bool clearBgmPlay) {
	//ゴール時の初期処理
	if (!m_bGoal) {
		m_bGoal = true;				//ゴールフラグをtrueにする
		m_JumpStatus = Manualing;	//重力を無視するようにする
		m_Pos.x -= ox;				//ゴールポールへの埋まりを解消する
		if (gType == 1) {
			JumpStart(-8.2f);				//ジャンプする
			m_Move.x = 0;		//
		}
		return false;
	}
	if (gType == 1) {
		return !clearBgmPlay;
	}
	//ゴールポールを降りている間の処理
	if (m_JumpStatus == Manualing) {
		m_Pos.y += MoveMaxSpeed;			//下に降りるように位置を変更する
		float oy = m_Pos.y + m_Motion.GetSrcRect().GetHeight() - glb;	//ゴールの一番下との距離
		if (oy >= 0) {					//ゴールの一番下まで行ったかどうか
			JumpStart(-8.2f);				//ジャンプする
			m_Move.x = MoveMaxSpeed;		//右に移動させる
		}
		return false;
	}
	if (m_Pos.x < stw) {//ステージ外に行くまでは処理中(FALSE)を返す
		return false;
	}
	return true;
}

void CPlayer::SlideMove(CVector2 v)
{
	m_Pos.x += v.x;
	m_Pos.y += v.y;
}

//プレイヤーの状態を取得する（土管用）
CPipe::PipeData CPlayer::GetPipeData(int id)
{
	CPipe::PipeData p = CPipe::PipeData();
	bool keyUp = g_pInput->IsKeyHold(MOFKEY_W) || g_pInput->IsKeyHold(MOFKEY_UP);
	bool keyRight = g_pInput->IsKeyHold(MOFKEY_D) || g_pInput->IsKeyHold(MOFKEY_RIGHT);
	bool keyDown = g_pInput->IsKeyHold(MOFKEY_S) || g_pInput->IsKeyHold(MOFKEY_DOWN);
	bool keyLeft = g_pInput->IsKeyHold(MOFKEY_A) || g_pInput->IsKeyHold(MOFKEY_LEFT);
	if (keyUp && (m_JumpStatus == OnGround || (m_JumpStatus == Jumping && m_Move.y < 0))) {
		p.Root = true;
		p.Id = id;
		p.Dir = BlockUp;
		p.Rect = GetRect(true);
		p.Rect.Bottom = p.Rect.Bottom - 30;
		p.Rect.Expansion(-6, 0);
	}
	else if ((keyRight || keyDown || keyLeft) && m_JumpStatus == OnGround) {
		p.Root = true;
		p.Id = id;
		p.Rect = GetRect(true);
		p.Rect.Top = p.Rect.Bottom - 1;
		p.Rect.Bottom = p.Rect.Bottom + 1;
		if (keyRight) {
			p.Dir = BlockRight;
			p.Rect.Left = p.Rect.Right - 1;
			p.Rect.Right = p.Rect.Right + 1;
		}
		else if (keyDown) {
			p.Dir = BlockDown;
		}
		else if (keyLeft) {
			p.Dir = BlockLeft;
			p.Rect.Right = p.Rect.Left + 1;
			p.Rect.Left = p.Rect.Left - 1;
		}
	}
	return p;
}

void CPlayer::ChangeStage(Vector2 pos)
{
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	m_Move.x = 0;
	m_Move.y = 0;
	m_JumpStatus = OnGround;
}
