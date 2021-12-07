#include "Enemy.h"
#include"Game.h"



CEnemy::CEnemy():
m_Type(0),
m_pTexture(NULL),
m_Motion(),
m_PosX(0.0f),
m_PosY(0.0f),
m_MoveX(0.0f),
m_MoveY(0.0f),
m_bShow(true),
m_bReverse(false),
m_SrcRect(){
}

CGame		gGame;
CPlayer		gPlayer;

CEnemy::~CEnemy(){
}


void CEnemy::Initialize(float px, float py, int type) {

	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = -3.0f;
	m_MoveY = 0.0f;
	m_bReverse = true;
	m_bShow = true;
	m_DamageWait = 0;
	


	//アニメーションを作成
	SpriteAnimationCreate anim[] = {
		//移動
		{
			"移動",
			0,0,
			32,32,
			TRUE,{{13,0,0},{13,1,0}}
		},
		//ダメージ
		{
			"死亡",
			0,96,
			32,32,
			FALSE,{{20,3,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);

}


void CEnemy::Update(void) {


	//非表示
	if (!m_bShow)
	{
		return;
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	

	//ダメージ中の動作
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_MOVE);		
		}
		else
		{
			if (m_MoveX > 0)
			{
				m_MoveX -= 0.2f;
				if (m_MoveX <= 0)
				{
					m_MoveX = 0;
				}
			}
			else if (m_MoveX < 0)
			{
				m_MoveX += 0.2f;
				if (m_MoveX >= 0)
				{
					m_MoveX = 0;
				}
			}
		}
	}
	//重力により下に少しずつ下がる
	m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
	//実際に座標を移動させる
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();

	//ダメージのインターバルを減らす
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

}


void CEnemy::CollisionStage(float ox, float oy) {
	m_PosX += ox;
	m_PosY += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX *= -1;
		m_bReverse = true;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX *= -1;
		m_bReverse = false;
	}
}


void CEnemy::Render(float wx, float wy) {



	//非表示
	if (!m_bShow)
	{
		return;
	}
	//描画矩形
	CRectangle dr = m_SrcRect;
	//反転フラグがONの場合描画矩形を反転させる
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, dr);
}


void CEnemy::RenderDebug(float wx, float wy) {

	//非表示
	if (!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CRectangle HeadRect=GetHedRect();

	//敵の矩形のデバッグ表示
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_COLOR_RED);

	//敵の頭の矩形のデバッグ表示
	CGraphicsUtilities::RenderRect(hr.Left - wx,HeadRect.Top - wy, HeadRect.Right - wx, HeadRect.Bottom - wy, MOF_COLOR_HGREEN);

}
/**
 * 解放
 *
 */
void CEnemy::Release(void) {
	m_Motion.Release();
}


bool CEnemy::CollisionPlayer()
{
	
	if (gPlayer.GetCollisionFlg())
	{		
		return true;
	}
	return false;
}


void CEnemy::Damage()
{
	m_Motion.ChangeMotion(MOTION_DAMAGE);

		m_bShow = false;
			
}