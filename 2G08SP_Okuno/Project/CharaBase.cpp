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
	//プレイヤーの位置を修正する
	m_PosX += coll.ox;
	m_PosY += coll.oy;

	//落下時かつ下方向への埋まり
	if (coll.oy < 0 && m_MoveY > 0) {
		//上下方向の速度を無くす
		m_MoveY = 0;
		//ステータスがジャンプ状態の場合、接地状態にする
		if (m_JumpStatus == Jumping) {
			m_JumpStatus = OnGround;
		}
	}
	//上昇時かつ上方向への埋まり
	else if (coll.oy > 0 && m_MoveY < 0) {
		//上下方向の速度を無くす
		m_MoveY = 0;
	}

	//右移動かつ右方向への埋まり
	if (coll.ox < 0 && m_MoveX > 0) {
		//横方向の速度を無くす
		m_MoveX = 0;
	}
	//左移動かつ左方向への埋まり
	else if (coll.ox > 0 && m_MoveX < 0) {
		//横方向の速度を無くす
		m_MoveX = 0;
	}

	if (!coll.og && m_JumpStatus == OnGround) {
		//ステータスをジャンプ状態にする
		m_JumpStatus = Jumping;
	}
}
