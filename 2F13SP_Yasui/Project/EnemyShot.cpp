#include	"EnemyShot.h"

/**
 * コンストラクタ
 *
 */
CEnemyShot::CEnemyShot() :
	m_pTexture(NULL),
	enemyShot_Position(0.0f,0.0f),
	enemyShot_Speed(0.0f,0.0f),
	m_bShow(false),
	tmpEnemy_Reverse(false),
	enemyShot_AddSpeed(false),
	enemyShot_Type(0),
	enemyShot_FireBound(false)
{
}

/**
 * デストラクタ
 *
 */
CEnemyShot::~CEnemyShot() {
}

/**
 * 初期化
 */
void CEnemyShot::Initialize(int type) {
	enemyShot_Position = Vector2(0, 0);
	enemyShot_Speed = Vector2(0, 0);
	m_bShow = false;
	tmpEnemy_Reverse = false;
	enemyShot_Type = type;
	enemyShot_FireBound = false;
	switch (enemyShot_Type)
	{
		case ENEMYSHOT_BONE:
		{
			SpriteAnimationCreate anime[] = {
			{
				"回転",
				0,0,
				32,32,
				TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}},
			},
			};
			enemyShot_Motion.Create(anime, 1);
			break;
		}
		case ENEMYSHOT_FIRE:
		{
			SpriteAnimationCreate anime[] = {
			{
				"回転",
				0,0,
				16,16,
				TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}},
			},
			};
			enemyShot_Motion.Create(anime, 1);
			break;
		}
		case ENEMYSHOT_KURIBO:
		{
			SpriteAnimationCreate anime[] = {
			{
				"移動",
				0,0,
				32,32,
				TRUE,{{5,0,0},{5,1,0},{5,2,0}},
			},
			};
			enemyShot_Motion.Create(anime, 1);
			break;
		}
		case ENEMYSHOT_MUSH:
		{
			SpriteAnimationCreate anime[] = {
			{
				"移動",
				0,0,
				32,32,
				TRUE,{{5,0,0}},
			},
			};
			enemyShot_Motion.Create(anime, 1);
			break;
		}

		default:
			break;
	}
	
	enemyShot_AddSpeed = false;
}
/**
 * 発射
 */
void CEnemyShot::Fire(float px, float py,float sx,float sy,bool Reverse) {
	enemyShot_Position.x = px;
	enemyShot_Position.y = py;
	tmpEnemy_Reverse = Reverse;
	switch (enemyShot_Type)
	{
	case ENEMYSHOT_BONE:
	{
		if (!enemyShot_AddSpeed)
		{
			enemyShot_AddSpeed = true;
		}
		if (tmpEnemy_Reverse)
		{
			enemyShot_Speed.x = -sx;
		}
		else
		{
			enemyShot_Speed.x = sx;
		}
		enemyShot_Speed.y = -sy;

		m_bShow = true;
		
		break;
	}
	case ENEMYSHOT_FIRE:
	{
		if (tmpEnemy_Reverse)
		{
			enemyShot_Speed.x = -sx;
		}
		else
		{
			enemyShot_Speed.x = sx;
		}
		enemyShot_Speed.y = sy;

		m_bShow = true;
	}
	default:
		break;
	}
	if (enemyShot_Motion.GetMotionNo() != 0)
		enemyShot_Motion.ChangeMotion(0);


	
}

/**
 * 更新
 *
 */
void CEnemyShot::Update(void) {
	//非表示
	if (!m_bShow)
	{
		if(enemyShot_AddSpeed)
		enemyShot_AddSpeed = false;
		return;
	}
	//アニメーションの更新
	enemyShot_Motion.AddTimer(CUtilities::GetFrameSecond());
	enemyShot_RectTexture = enemyShot_Motion.GetSrcRect();
	
	//重力処理
	enemyShot_Speed.y += ENEMY_GRAVITY;
	if (enemyShot_Speed.y >= 20.0f)
	{
		enemyShot_Speed.y = 20.0f;
	}
	//速度を利用した移動
	enemyShot_Position += enemyShot_Speed;
	//画面外で消去
	if (enemyShot_Position.y < 0 || enemyShot_Position.y > 900)
	{
		m_bShow = false;
	}
}

/**
 * 描画
 *
 */
void CEnemyShot::Render(float wx, float wy) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	CRectangle dr = enemyShot_RectTexture;
	if (tmpEnemy_Reverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//テクスチャの描画
	m_pTexture->Render(enemyShot_Position.x - wx, enemyShot_Position.y - wy,dr);
}

/**
 * デバッグ描画
 *
 */
void CEnemyShot::RenderDebug(float wx, float wy) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx,hr.Top - wy,hr.Right - wx,hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	CGraphicsUtilities::RenderString(300, 600, "ショット速%f", enemyShot_Speed);
}

void CEnemyShot::Release(void)
{
	enemyShot_Motion.Release();
}

