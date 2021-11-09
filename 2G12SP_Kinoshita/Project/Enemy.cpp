#include "Enemy.h"



CEnemy::CEnemy() :
	m_pTexture(NULL),
	m_Motion(),
	m_Pos(),
	m_Move(),
	
	//m_bShow(false),
	m_bReverse(false),
	m_SrcRect(),
	m_HP(0),
	m_DamageWait(0) {
}

/**
 * デストラクタ
 *
 */
CEnemy::~CEnemy() {
	//delete[] で解放されるようにReleaseをデストラクタで実行する
	//Release();
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 *
 * 引数
 * [in]			px					X座標
 * [in]			py					Y座標
 * [in]			type				敵タイプ
 */
void CEnemy::Initialize(float px, float py, int type) {
	//m_Type = type;
	m_Pos.x = px;
	m_Pos.y = py;
	m_Move.x = -2.0f;
	m_Move.y = 0.0f;
	m_bReverse = false;
	m_bShow = true;
	m_HP = 1;
	m_DamageWait = 0;
	//アニメーションを作成
	std::vector<SpriteAnimationCreate> anim = {
		//移動
		SpriteAnimationCreate{
			"移動",
			0,0,
			30,32,
			TRUE,{{7,0,0},{7,1,0}}
		},

		SpriteAnimationCreate{

			"死亡",
			0,32,
			30,32,
			FALSE,{{5,0,0}}
        }
		
	};
	m_Motion.Create(anim.data(),anim.size());

	
}

/**
 * 更新
 *
 */
void CEnemy::Update() {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//ダメージ中の動作
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
			if (m_HP <= 0)
			{
				m_bShow = false;
				

			}
			/*if (m_Stage.GetScrollX < 1000)
			{
				m_Move.x = true;
			}*/
			if (m_bReverse)
			{
				m_Move.x = -3.0f;
			}
			else
			{
				m_Move.x = 3.0f;
			}
		}
		else
		{
			if (m_Move.x > 0)
			{
				m_Move.x -= 0.2f;
				if (m_Move.x <= 0)
				{
					m_Move.x = 0;
				}
			}
			else if (m_Move.x < 0)
			{
				m_Move.x += 0.2f;
				if (m_Move.x >= 0)
				{
					m_Move.x = 0;
				}
			}
		}
	}
	//重力により下に少しずつ下がる
	m_Move.y += GRAVITY;
	if (m_Move.y >= 20.0f)
	{
		m_Move.y = 20.0f;
	}
	//実際に座標を移動させる
	m_Pos += m_Move;
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//ダメージのインターバルを減らす
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

/**
 * ダメージ処理
 * 引数分のＨＰを減らしＨＰが０以下になれば敵を消去する
 *
 * 引数
 * [in]			dmg				ダメージ
 * [in]			bRev			反転フラグ
 */
 void CEnemy::Damage(int dmg, bool bRev) {
 	m_HP -= dmg;
 	m_DamageWait = 60;
	
 	/*if (bRev)
 	{
 		m_Move.x = -5.0f;
 		m_bReverse = false;
 	}
 	else
 	{
 		m_Move.x = 5.0f;
 		m_bReverse = true;
 	}*/
 	m_Motion.ChangeMotion(MOTION_DAMAGE);
	
 	
 }

 /**
  * ステージとの当たり
  *
  * 引数
  * [in]			ox					X埋まり量
  * [in]			oy					Y埋まり量
  */
void CEnemy::CollisionStage(float ox, float oy) {
	m_Pos.x += ox;
	m_Pos.y += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (oy < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if (oy > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (ox < 0 && m_Move.x > 0)
	{
		if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
		{
			m_Move.x = 0;
		}
		else
		{
			m_Move.x *= -1;
			m_bReverse = true;
		}
	}
	else if (ox > 0 && m_Move.x < 0)
	{
		if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
		{
			m_Move.x = 0;
		}
		else
		{
			m_Move.x *= -1;
			m_bReverse = false;
		}
	}
}

/**
 * 描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CEnemy::Render(float wx, float wy) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//インターバル2フレームごとに描画をしない
	/*if (m_DamageWait % 4 >= 2)
	{
		return;
	}*/
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
	m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
}

/*
 * デバッグ描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CEnemy::RenderDebug(float wx, float wy) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
	CRectangle bo = Gethed();
	CGraphicsUtilities::RenderRect(bo.Left - wx, bo.Top - wy, bo.Right - wx, bo.Bottom - wy, MOF_XRGB(255, 0, 0));
}

/**
 * 解放
 *
 */
void CEnemy::Release(void) {
	m_Motion.Release();
}

bool CEnemy::CollisionQBlock(CQuestionBlock& QBlock, float ox, float oy)
{
	CRectangle prlg = GetRect();
	CRectangle bl = QBlock.GetRect();
	if (prlg.CollisionRect(bl))
	{
		m_Pos.x += ox;
		m_Pos.y += oy - 0.3;

		if (oy < 40 && m_Move.y>0)
		{
			m_Move.y = 0;
		}
		else if (oy > 0 && m_Move.y < 30)
		{
			m_Move.y = 0;

		}

		if (ox < 0 && m_Move.x >40)
		{
			m_Move.x = 0;
		}
		else if (ox > 0 && m_Move.x < 40)
		{
			m_Move.x = 0;
		}
	}
	return false;
}

bool CEnemy::CollisionbreakBlock(CbreakBlock& blo, float ox, float oy)
{
	CRectangle prlg = GetRect();
	CRectangle bl = blo.GetRect();
	if (prlg.CollisionRect(bl))
	{
		m_Pos.x += ox;
		m_Pos.y += oy - 0.3;

		if (oy < 40 && m_Move.y>0)
		{
			m_Move.y = 0;
		}
		else if (oy > 0 && m_Move.y < 0)
		{
			m_Move.y = 0;

		}

		if (ox < 0 && m_Move.x >0)
		{
			m_Move.x = 0;
		}
		else if (ox > 0 && m_Move.x < 0)
		{
			m_Move.x = 0;
		}
	}
	return false;
}



