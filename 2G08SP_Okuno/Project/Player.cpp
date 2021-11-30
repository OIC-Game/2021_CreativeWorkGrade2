#include "Player.h"

CPlayer::CPlayer() :
	m_sth(0),
	m_TypeIdx(0),
	m_bDead(false),
	m_DeadWait(0),
	m_bDeadEnd(0),
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
	m_bPipe = false;
	m_JumpStatus = OnGround;
	m_TypeIdx = 0;
	m_JumpSp = 0;
	m_Move.x = 0;
	m_Move.y = 0;
	m_bReverse = false;
	m_bDead = false;
	m_DeadWait = 0;
	m_bDeadEnd = 0;
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
	//�X�e�[�^�X���W�����v���ɐݒ�
	m_JumpStatus = Jumping;

	//�W�����v�ɂ��㉺�����̉����x��ݒ�
	m_JumpSp = JumpUSp;

	//�����x�̃C���f�b�N�X
	int ix = 0;

	if (SSpeed < 0) {
		m_Move.y = SSpeed;
	}
	//�������ւ̈ړ����x�ŃW�����v�̍�����ς���
	else {
		if (m_Move.x >= MoveMaxSpeed) ix++;
		if (m_Move.x > MoveMaxSpeed) ix++;
		m_Move.y = JumpSSpeed[ix];
	}

	if (!m_bDead) {
		m_SoundArray[SOUND_JUMP].Play();
	}
}

void CPlayer::JumpingFn(bool btnPull)
{
	//�㉺�����̑��x���������A�������̓W�����v�{�^���������ꂽ�ꍇ
	if (m_Move.y >= 0 || btnPull) {
		//�㉺�����̉����x�𗎉����̉����x�ɕς���
		m_JumpSp = JumpFSp;
	}

	//�㉺�����̑��x�ɉ����x�����Z����
	m_Move.y += m_JumpSp;

	//����������x�Ő�������
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
	//���̃t���[���ŉ��ړ�(����)�����������ǂ���
	bool bMove = false;

	if (!m_bGoal && !m_bDead && !m_bPipe && m_JumpStatus != Manualing) {
		//���i�}�C�i�X�j�ړ��i������A�j
		if (g_pInput->IsKeyHold(MOFKEY_LEFT) || g_pInput->IsKeyHold(MOFKEY_A)) {
			bMove = true;
			//�������Ȃ̂ŉ摜���]�t���O��L���ɂ���
			m_bReverse = true;
			//�_�b�V������i��CTRL���͉E�N���b�N�j
			if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) || g_pInput->IsMouseKeyHold(1)) {
				//�������̑��x�ɉ����x�����Z����
				if (m_Move.x > -MoveMaxSpeed) {
					m_Move.x -= MoveSpeed;
				}
				else {
					m_Move.x -= RunSpeed;
				}
				//���i�}�C�i�X�j�̃_�b�V��������x�Ő�������
				if (m_Move.x < -RunMaxSpeed) {
					m_Move.x = -RunMaxSpeed;
				}
			}
			else {
				if (m_Move.x > -MoveMaxSpeed) {
					//�������̑��x�ɉ����x�����Z����
					m_Move.x -= MoveSpeed;
				}
				//���i�}�C�i�X�j�̏�����x�Ő�������i������x�܂Ō�������j
				if (m_Move.x < -MoveMaxSpeed) {
					m_Move.x += MoveSpeed;
					if (m_Move.x > -MoveMaxSpeed) {
						m_Move.x = -MoveMaxSpeed;
					}
				}
			}
		}
		//�E�i�v���X�j�ړ��i������D�j
		else if (g_pInput->IsKeyHold(MOFKEY_RIGHT) || g_pInput->IsKeyHold(MOFKEY_D)) {
			bMove = true;
			//�E�����Ȃ̂ŉ摜���]�t���O�𖳌��ɂ���
			m_bReverse = false;
			//�_�b�V������i��CTRL���͉E�N���b�N�j
			if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) || g_pInput->IsMouseKeyHold(1)) {
				//�������̑��x�ɉ����x�����Z����
				if (m_Move.x < MoveMaxSpeed) {
					m_Move.x += MoveSpeed;
				}
				else {
					m_Move.x += RunSpeed;
				}
				//�E�i�v���X�j�̃_�b�V��������x�Ő�������
				if (m_Move.x > RunMaxSpeed) {
					m_Move.x = RunMaxSpeed;
				}
			}
			else {
				if (m_Move.x < MoveMaxSpeed) {
					//�������̑��x�ɉ����x�����Z����
					m_Move.x += MoveSpeed;
				}
				//�E�i�v���X�j�̏�����x�Ő�������i������x�܂Ō�������j
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

		//���̃t���[���ŃW�����v�{�^���������ꂽ�ꍇ
		if (g_pInput->IsKeyPush(MOFKEY_SPACE) || g_pInput->IsMouseKeyPush(0)) {
			//�X�e�[�^�X���ڒn��ԁi�n�ʂɑ������Ă���j�Ȃ�
			if (m_JumpStatus == OnGround) {
				//�W�����v�������J�n����
				JumpStart();
			}
		}
	}
	//�X�e�[�^�X���W�����v��ԁi�n�ʂɑ������Ă��Ȃ��j�Ȃ�
	if (m_JumpStatus == Jumping) {
		bool btnPull = g_pInput->IsKeyPull(MOFKEY_SPACE) || g_pInput->IsMouseKeyPull(0);
		//�W�����v���������s����
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

	//���̃t���[���ŉ��ړ��i���́j����Ȃ������ꍇ
	if (!bMove && !m_bGoal && !m_bPipe && m_JumpStatus != Manualing) {
		//����Ɍ�������
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

	//�v���C���[�̈ʒu�ɑ��x�����Z����
	if (m_JumpStatus != Manualing) {
		m_Pos.x += m_Move.x;
		m_Pos.y += m_Move.y;
	}

	//���[����͂ݏo���Ȃ�
	if (m_Pos.x < wx) {
		m_Pos.x = wx;
	}

	if (m_bGoal) return;

	//�������̏���
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
	//���]�t���O���L���̎��͉摜�𔽓]����
	if (m_bReverse) {
		float tmp = cr.Left;
		cr.Left = cr.Right;
		cr.Right = tmp;
	}
	m_Texture->Render(m_Pos.x - wx, m_Pos.y - wy, cr);
}

void CPlayer::CollisionStage(CCollisionData coll)
{
	//�v���C���[�̈ʒu���C������
	m_Pos.x += coll.ox;
	m_Pos.y += coll.oy;

	//���������������ւ̖��܂�
	if (coll.oy < 0 && m_Move.y > 0) {
		//�㉺�����̑��x�𖳂���
		m_Move.y = 0;
		//�X�e�[�^�X���W�����v��Ԃ̏ꍇ�A�ڒn��Ԃɂ���
		if (m_JumpStatus == Jumping) {
			m_JumpStatus = OnGround;
		}
	}
	//�㏸����������ւ̖��܂�
	else if (coll.oy > 0 && m_Move.y < 0) {
		//�㉺�����̑��x�𖳂���
		m_Move.y = 0;
	}

	//�E�ړ����E�����ւ̖��܂�
	if (coll.ox < 0 && m_Move.x > 0) {
		m_Move.x  = 0;
	}
	//���ړ����������ւ̖��܂�
	else if (coll.ox > 0 && m_Move.x < 0) {
		m_Move.x  = 0;
	}

	//�ڒn��ԁi�n�ʂɑ������Ă���j�ł͂Ȃ��X�e�[�^�X���ڒn��Ԃ̏ꍇ
	if (!coll.og && m_JumpStatus == OnGround) {
		//�X�e�[�^�X���W�����v��Ԃɂ���
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
	
	CRectangle rb = GetBRect(true);
	CRectangle ra = GetRect(true);
	CRectangle erec = ene.GetRect();
	erec.Expansion(0, -3);

	//�E��������p
	CRectangle elrec = erec;
	elrec.Right = (elrec.Left + elrec.Right) / 2;

	CRectangle rrec = CRectangle(min(rb.Right, ra.Right), min(rb.Top, ra.Top), max(rb.Right, ra.Right), max(rb.Bottom, ra.Bottom));
	rrec.Expansion(0, -6);

	//����������p
	CRectangle errec = erec;
	errec.Left = (errec.Left + errec.Right) / 2;

	CRectangle lrec = CRectangle(min(rb.Left, ra.Left), min(rb.Top, ra.Top), max(rb.Left, ra.Left), max(rb.Bottom, ra.Bottom));
	lrec.Expansion(0, -6);

	if (elrec.CollisionRect(rrec) && m_DmgTime <= 0 && !ene.GetJustTrampled()) {
		if (ene.CheckDamageFlg(DAMAGE_ONLY_PLAYER) &&
			(ene.GetDamageDirection() & BlockLeft) != BlockLeft) {
			CCollisionData coll = CCollisionData();
			coll.ox = rrec.Right - elrec.Left;
			ene.CollisionStage(coll);
			if (ene.Touched(ra, true)) {
				return;
			}
		}
	}
	if (errec.CollisionRect(lrec) && m_DmgTime <= 0 && !ene.GetJustTrampled()) {
		if (ene.CheckDamageFlg(DAMAGE_ONLY_PLAYER) &&
			(ene.GetDamageDirection() & BlockRight) != BlockRight) {
			CCollisionData coll = CCollisionData();
			coll.ox = lrec.Left - errec.Right;
			ene.CollisionStage(coll);
			if (ene.Touched(ra, true)) {
				return;
			}
		}
	}

	//���݂�����p
	CRectangle hrec = erec;
	hrec.Bottom = (hrec.Bottom + hrec.Top) / 2;

	CRectangle brec = CRectangle(min(rb.Left, ra.Left), min(rb.Bottom, ra.Bottom), max(rb.Right, ra.Right), max(rb.Bottom, ra.Bottom));
	brec.Expansion(-6, 0);

	//���݂����ꍇ
	if (hrec.CollisionRect(brec) && (m_Move.y >= 0 || ene.GetMove().y <= 0)) {
		if (ene.GetJustTrampled()) return;
		bool tFlg = (ene.GetChangeFlg() & CHANGE_TOUCH) == CHANGE_TOUCH;

		if (ene.CheckDamageFlg(DAMAGE_ONLY_PLAYER) &&
			(ene.GetDamageDirection() & BlockUp) == BlockUp && 
			(ene.GetChangeFlg() & CHANGE_TRAMPLED) != CHANGE_TRAMPLED) {
			if (m_DmgTime > 0) return;

			Damage(false);
			return;
		}
		ene.Trampled(ra);
		m_SoundArray[SOUND_TRAMPLED].Play();

		if (g_pInput->IsKeyHold(MOFKEY_SPACE) || g_pInput->IsMouseKeyHold(0)) {
			JumpStart(-10.2f);			//�W�����v����
		}
		else {
			JumpStart(-6.2f);			//�W�����v����
		}
		return;
	}

	if (m_DmgTime > 0) return;

	//���������p
	CRectangle drec = erec;
	drec.Top = (drec.Bottom + drec.Top) / 2;

	CRectangle trec = CRectangle(min(rb.Left, ra.Left), min(rb.Top, ra.Top), max(rb.Right, ra.Right), max(rb.Top, ra.Top));
	trec.Expansion(-6, 0);

	if (drec.CollisionRect(trec) && (m_Move.y <= 0 || ene.GetMove().y >= 0)) {
		if (ene.CheckDamageFlg(DAMAGE_ONLY_PLAYER) &&
			(ene.GetDamageDirection() & BlockDown) == BlockDown) {
			if (m_DmgTime > 0 || ene.GetJustTrampled()) return;

			Damage(false);
			return;
		}
	}


	if (elrec.CollisionRect(rrec) && (m_Move.x >= 0 || ene.GetMove().x <= 0)) {
		if (ene.CheckDamageFlg(DAMAGE_ONLY_PLAYER) &&
			(ene.GetDamageDirection() & BlockLeft) == BlockLeft) {
			if (m_DmgTime > 0 || ene.GetJustTrampled()) return;

			Damage(false);
			return;
		}
	}


	if (errec.CollisionRect(lrec) && (m_Move.x <= 0 || ene.GetMove().x >= 0)) {
		if (ene.CheckDamageFlg(DAMAGE_ONLY_PLAYER) &&
			(ene.GetDamageDirection() & BlockRight) == BlockRight) {
			if (m_DmgTime > 0 || ene.GetJustTrampled()) return;

			Damage(false);
			return;
		}
	}

	if (ene.GetJustTrampled()) {
		ene.SetJustTrampled(erec.CollisionRect(ra));
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
	//�S�[�����̏�������
	if (!m_bGoal) {
		m_bGoal = true;				//�S�[���t���O��true�ɂ���
		m_JumpStatus = Manualing;	//�d�͂𖳎�����悤�ɂ���
		m_Pos.x -= ox;				//�S�[���|�[���ւ̖��܂����������
		if (gType == 1) {
			JumpStart(-8.2f);				//�W�����v����
			m_Move.x = 0;		//
		}
		return false;
	}
	if (gType == 1) {
		return !clearBgmPlay;
	}
	//�S�[���|�[�����~��Ă���Ԃ̏���
	if (m_JumpStatus == Manualing) {
		m_Pos.y += MoveMaxSpeed;			//���ɍ~���悤�Ɉʒu��ύX����
		float oy = m_Pos.y + m_Motion.GetSrcRect().GetHeight() - glb;	//�S�[���̈�ԉ��Ƃ̋���
		if (oy >= 0) {					//�S�[���̈�ԉ��܂ōs�������ǂ���
			JumpStart(-8.2f);				//�W�����v����
			m_Move.x = MoveMaxSpeed;		//�E�Ɉړ�������
		}
		return false;
	}
	if (m_Pos.x < stw) {//�X�e�[�W�O�ɍs���܂ł͏�����(FALSE)��Ԃ�
		return false;
	}
	return true;
}

int CPlayer::PipeInFn(CPipe::PipeData pipe)
{
	if (pipe.Type == 1) {
		return PipeInFn_Door(pipe);
	}
	if (!m_bPipe) {
		m_bPipe = true;
		m_bPipeIn = false;
		if ((pipe.Dir & BlockRight) == BlockRight) {
			m_Pos.x = pipe.Rect.Left - GetRect(false).GetWidth();
			m_Pos.y = pipe.Rect.Bottom - GetRect(false).GetHeight();
		}
		else if ((pipe.Dir & BlockDown) == BlockDown) {
			m_Pos.x = pipe.Rect.Left;
			m_Pos.y = pipe.Rect.Top - GetRect(false).GetHeight();
		}
		else if ((pipe.Dir & BlockLeft) == BlockLeft) {
			m_Pos.x = pipe.Rect.Right;
			m_Pos.y = pipe.Rect.Bottom - GetRect(false).GetHeight();
		}
		else {
			m_Pos.x = pipe.Rect.Left;
			m_Pos.y = pipe.Rect.Bottom;
		}
		return PIPE_FLAG_IN_NOW;
	}
	else if (m_bPipeIn) {
		return PIPE_FLAG_IN_END;
	}
	if ((pipe.Dir & BlockRight) == BlockRight) {
		if (m_Pos.x < pipe.Rect.Left) {
			m_Pos.x += 1.0f;
			return PIPE_FLAG_IN_NOW;
		}
	}
	else if ((pipe.Dir & BlockDown) == BlockDown) {
		if (m_Pos.y < pipe.Rect.Top) {
			m_Pos.y += 1.0f;
			return PIPE_FLAG_IN_NOW;
		}
	}
	else if ((pipe.Dir & BlockLeft) == BlockLeft) {
		if (m_Pos.x > pipe.Rect.Right) {
			m_Pos.x -= 1.0f;
			return PIPE_FLAG_IN_NOW;
		}
	}
	else {
		if (m_Pos.y > pipe.Rect.Bottom) {
			m_Pos.y -= 1.0f;
			return PIPE_FLAG_IN_NOW;
		}
	}

	m_bPipeIn = true;
	return PIPE_FLAG_IN_END;
}

int CPlayer::PipeInFn_Door(CPipe::PipeData pipe)
{
	if (!m_bPipe) {
		m_bPipe = true;
		m_bPipeIn = false;
		m_Pos.x = pipe.Rect.Left - GetRect(false).GetWidth();
		m_Pos.y = pipe.Rect.Bottom - GetRect(false).GetHeight();
		return PIPE_FLAG_IN_NOW;
	}
	else if (m_bPipeIn) {
		return PIPE_FLAG_OUT_NOW;
	}
	if (m_Pos.x < pipe.Rect.Left) {
		m_Pos.x += 1.0f;
		return PIPE_FLAG_IN_NOW;
	}
	m_bPipeIn = true;
	return PIPE_FLAG_IN_END;
}

int CPlayer::PipeOutFn(CPipe::PipeData pipe)
{
	if (!m_bPipe) return PIPE_FLAG_OUT_END;
	if (pipe.Type == 1) {
		return PipeOutFn_Door(pipe);
	}
	if ((pipe.Dir & BlockRight) == BlockRight) {
		if (m_Pos.x + GetRect(false).GetWidth() > pipe.Rect.Left) {
			m_Pos.x -= 1.0f;
			return PIPE_FLAG_OUT_NOW;
		}
	}
	else if ((pipe.Dir & BlockDown) == BlockDown) {
		if (m_Pos.y + GetRect(false).GetHeight() > pipe.Rect.Top) {
			m_Pos.y -= 1.0f;
			return PIPE_FLAG_OUT_NOW;
		}
	}
	else if ((pipe.Dir & BlockLeft) == BlockLeft) {
		if (m_Pos.x < pipe.Rect.Right) {
			m_Pos.x += 1.0f;
			return PIPE_FLAG_OUT_NOW;
		}
	}
	else {
		if (m_Pos.y < pipe.Rect.Bottom) {
			m_Pos.y += 1.0f;
			return PIPE_FLAG_OUT_NOW;
		}
	}
	m_bPipe = false;
	return PIPE_FLAG_OUT_END;
}

int CPlayer::PipeOutFn_Door(CPipe::PipeData pipe)
{
	m_bPipe = false;
	return PIPE_FLAG_OUT_END;
}

bool CPlayer::DeadFn()
{
	if (m_bDeadEnd == 0) {
		m_bDeadEnd = 1;
		m_JumpStatus = Manualing;
		m_Move.x = 0;
		m_Move.y = 0;
	}
	else if (m_bDeadEnd == 1) {
		m_DeadWait += CUtilities::GetFrameSecond();
		if (m_DeadWait >= 0.3f) {
			m_bDeadEnd = 2;
			JumpStart(-10.6f);
		}
		else if (m_DeadWait >= 0.1f && m_Pos.y >= m_sth) {
			m_bDeadEnd = 2;
			JumpStart(-12.6f);
		}
	}
	else if (m_bDeadEnd == 2) {
		if (m_Pos.y > m_sth + 50) {
			m_bDeadEnd = 3;
		}
	}

	return m_bDeadEnd == 3;
}

void CPlayer::SlideMove(CVector2 v)
{
	m_Pos.x += v.x;
	m_Pos.y += v.y;
}

//�v���C���[�̏�Ԃ��擾����i�y�Ǘp�j
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
