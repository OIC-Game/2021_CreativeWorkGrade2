#include "Enemy.h"

CEnemy::CEnemy():
m_pTexture(NULL),
m_Type(),
m_PosX(0.0f),
m_PosY(0.0f),
m_MoveX(0.0f),
m_MoveY(0.0f),
m_bShow(false),
m_bMove(false),
m_bReverse(false),
m_bDead(false){
}

CEnemy::~CEnemy(){
}

void CEnemy::Initialize(float px, float py, int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = -1.0f;
	m_MoveY = 0.0f;
	m_MoveKameX = -6.0f;
	m_bShow = true;
	m_bMove = false;
	m_bKame = false;
	m_bDamege = true;
	m_bDead = false;
	m_DamageWait = 10;
	switch (GetType())
	{
		case ENEMY_01:
		//アニメーションを作成
		SpriteAnimationCreate anim[] = {
			{
				"移動",
				0,0,
				32,32,
				TRUE,{{5,0,0},{5,1,0}}
			},
			{
				"死亡",
				96,0,
				32,32,
				FALSE,{{5,0,0}}
			},
		};
		m_Motion.Create(anim, MOTION_COUNT);
		break;
	}

	switch (GetType())
	{
		case ENEMY_02:
		//アニメーションを作成
		SpriteAnimationCreate anim2[] = {
			{
				"移動",
				0,0,
				32,44,
				TRUE,{{5,0,0},{5,1,0}}
			},
			{
				"死亡",
				64,0,
				32,44,
				FALSE,{{5,0,0}}
			},
			{
				"カメ",
				96,0,
				32,44,
				FALSE,{{5,0,0}}
			},
		};
		m_Motion.Create(anim2, MOTION2_COUNT);
		break;
	}
}

void CEnemy::Update(float wx, float wy){
	//非表示
	if (!m_bShow)
	{
		return;
	}
	if (m_bDead)
	{
		m_DamageWait--;
		if (m_DamageWait == 0)
		{
			m_bShow = false;
		}
	}
	if (m_PosX - wx < 1100)
	{
		if (!m_bKame)
		{
			m_bMove = true;
		}
	}

	//重力により下に少しずつ下がる
	m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
	//実際に座標を移動させる
	if (m_bMove)
	{
		if (m_bKame)
		{
			m_PosX += m_MoveKameX;
		}
		else
		{
			m_PosX += m_MoveX;

		}
		m_PosY += m_MoveY;
	}
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

void CEnemy::Render(float wx, float wy){
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

void CEnemy::RenderDebug(float wx, float wy){
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));

	CRectangle le = Left();
	CGraphicsUtilities::RenderRect(le.Left - wx, le.Top - wy, le.Right - wx, le.Bottom - wy, MOF_XRGB(0, 0, 0));

	CRectangle re = Right();
	CGraphicsUtilities::RenderRect(re.Left - wx, re.Top - wy, re.Right - wx, re.Bottom - wy, MOF_XRGB(255, 255, 255));
}

void CEnemy::Release(){
	m_Motion.Release();
}

void CEnemy::CollisionStage(float ox, float oy){
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
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	else if (ox < 0 && m_MoveKameX > 0)
	{
		m_MoveKameX *= -1;
		m_bReverse = true;
	}
	else if (ox > 0 && m_MoveKameX < 0)
	{
		m_MoveKameX *= -1;
		m_bReverse = false;
	}
}

void CEnemy::Damege(void){
	switch (GetType())
	{
		case ENEMY_01:
			m_Motion.ChangeMotion(MOTION_DEATH);
			m_bDead = true;
			return;
			break;
		case ENEMY_02:
			m_Motion.ChangeMotion(MOTION_DEATH);
			m_bKame = true;
			m_bMove = false;
			m_bDamege = false;
			return;
			break;
	}
}

void CEnemy::KameMove(bool reverse){
	m_bMove = true;
	m_bDamege = true;
	m_bReverse = reverse;

}

