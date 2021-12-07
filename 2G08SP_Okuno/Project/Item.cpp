#include "Item.h"

CItem::CItem() :
	m_Texture(),
	m_Rect(),
	m_Pos(),
	m_Spd(),
	m_Type(0),
	m_bShow(false),
	m_ShowState(0),
	m_stgh(0),
	m_JumpStatus(0),
	m_animShow(false),
	m_animShowTime(0)
{
}

CItem::~CItem()
{
}

bool CItem::Load(CTexture* tex, CRectangle rec)
{
	m_Texture = tex;
	m_Rect = rec;
	return true;
}

void CItem::Initialize(CVector2 pos, CVector2 spd, CItemDefine* def, int type, int dfX, int dfY, bool dfShow, int stgh)
{
	m_Pos = pos;
	m_DfX = dfX;
	m_DfY = dfY;
	m_Spd = spd;
	m_Define = def;
	m_Type = type;
	m_bShow = dfShow;
	m_stgh = stgh;
	m_ShowState = STATE_SHOW;
	m_animShowTime = 0;
}

void CItem::Render(float wx, float wy)
{
	if (!m_bShow || m_ShowState != STATE_SHOW) {
		return;
	}
	CRectangle rect = m_Rect;
	float scale = g_pGraphics->GetTargetWidth() / ViewWidth;
	float sub = 0;
	if (m_animShow && m_animShowTime < BShowAnimTime) {
		sub = rect.GetHeight() - rect.GetHeight() * (m_animShowTime / BShowAnimTime);
		rect.Bottom -= sub;
	}
	m_Texture->RenderScale((m_Pos.x - wx) * scale, (m_Pos.y - wy + sub) * scale, scale, rect);
}

void CItem::Update(float wx, float wy)
{
	if (!m_bShow || m_ShowState == STATE_DISAPPEAR) {
		return;
	}
	if (m_ShowState == STATE_DISSHOW) {
		CRectangle rect = GetRect();
		if (rect.Right >= wx && rect.Left <= wx + ViewWidth) {
			m_ShowState = STATE_SHOW;
		}
		else {
			return;
		}
	}
	else if (m_ShowState == STATE_SHOW) {
		CRectangle rect = GetRect();
		if (rect.Right < wx || rect.Left > wx + ViewWidth) {
			m_ShowState = STATE_DISSHOW;
			return;
		}
	}

	if (m_ShowState == STATE_YET) {
		m_ShowState = STATE_SHOW;
	}
	if (m_animShow && m_animShowTime < BShowAnimTime) {
		m_animShowTime += CUtilities::GetFrameSecond();
		if (m_animShowTime < BShowAnimTime) return;
		else {
			m_animShow = false;
			if (m_Define->itemType == ITEM_COIN && m_Define->move == 0) {
				Get();
			}
		}
	}

	if (m_Spd.x == 0 && m_Define->move != 0) {
		m_Spd.x = 1.2f;
	}

	if (m_JumpStatus == Jumping && m_Define->move != 0) {
		m_Spd.y += JumpFSp;
		if (m_Spd.y > JumpMaxSpeed) {
			m_Spd.y = JumpMaxSpeed;
		}
	}

	m_Pos += m_Spd;

	//落下時の処理
	if (m_Pos.y > m_stgh) {
		m_ShowState = STATE_DISAPPEAR;
	}
}

void CItem::CollisionStage(CCollisionData coll)
{
	//プレイヤーの位置を修正する
	m_Pos.x += coll.ox;
	m_Pos.y += coll.oy;

	//落下時かつ下方向への埋まり
	if (coll.oy < 0 && m_Spd.y > 0) {
		//上下方向の速度を無くす
		m_Spd.y = 0;
		//ステータスがジャンプ状態の場合、接地状態にする
		if (m_JumpStatus == Jumping) {
			m_JumpStatus = OnGround;
		}
	}
	//上昇時かつ上方向への埋まり
	else if (coll.oy > 0 && m_Spd.y < 0) {
		//上下方向の速度を無くす
		m_Spd.y = 0;
	}

	//右移動かつ右方向への埋まり
	if (coll.ox < 0 && m_Spd.x > 0) {
		//横方向の速度を無くす
		m_Spd.x *= -1;
	}
	//左移動かつ左方向への埋まり
	else if (coll.ox > 0 && m_Spd.x < 0) {
		//横方向の速度を無くす
		m_Spd.x *= -1;
	}

	if (!coll.og && m_JumpStatus == OnGround) {
		//ステータスをジャンプ状態にする
		m_JumpStatus = Jumping;
	}
}

void CItem::Get()
{
	//m_bShow = false;
	m_ShowState = STATE_DISAPPEAR;
}

void CItem::BShow(CVector2 pos, int marioType, CTexture* itemTextures) {
	m_Pos = pos;
	m_Pos.y -= CHIPSIZE;
	m_bShow = true;
	m_animShow = true;
	if (m_Define->itemType == ITEM_NORMAL && m_Define->ext1 <= CGameDefine::GetGameDefine()->GetMarioIdx(marioType) && (marioType == MARIO_SUPER || marioType == MARIO_FIRE)) {
		CItemDefine* def = CGameDefine::GetGameDefine()->GetItemByIdx(m_Define->ext2);
		if (def == NULL) return;
		m_Type = def->idx - 1;
		m_Define = def;
		m_Texture = &itemTextures[m_Type];
		m_animShowTime = 0;
	}
}
