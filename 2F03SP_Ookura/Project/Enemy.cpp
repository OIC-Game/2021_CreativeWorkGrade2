#include	"Enemy.h"

/**
 * コンストラクタ
 *
 */
CEnemy::CEnemy() :
	m_pTexture(NULL),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_SpeedX(0.0f),
	m_SpeedY(0.0f),
	m_bShow(false),
	m_HP(0),
	m_ShotArray(),
	m_ShotWait(0),
	m_ShotWaitSet(0),
	m_TargetPosX(0.0f),
	m_TargetPosY(0.0f),
	m_Type(0) {
}

/**
 * デストラクタ
 *
 */
CEnemy::~CEnemy() {
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * プレイヤーの位置など状態を初期化したいときに実行する。
 */
void CEnemy::Initialize(void) {
	m_PosX = 0;
	m_PosY = 0;
	m_SpeedX = 0;
	m_SpeedY = 0;
	m_bShow = false;
	m_HP = 1;
	m_ShotWait = 0;
	m_ShotWaitSet = 40;
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
}
/**
 * 開始
 * 引数の座標に位置を設定して、表示フラグをtrueに変更する。
 *
 * 引数
 * [in]			px				発射Ｘ座標
 * [in]			py				発射Ｙ座標
 */
void CEnemy::Start(float px, float py, int t) {
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py - m_pTexture->GetHeight();
	m_SpeedX = 5;
	m_SpeedY = 1;
	m_Type = t;
	m_bShow = true;
	m_HP = ((m_Type == 1) ? 200 : 1);
	m_ShotWaitSet = ((m_Type == 1) ? 120 : 40);
	m_ShotWait = m_ShotWaitSet;
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
}

/**
 * 更新
 *
 */
void CEnemy::Update(void) {
	//弾の更新
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}
	//非表示
	if (!m_bShow)
	{
		return;
	}
	switch (m_Type)
	{
	case 0:
		UpdateType0();
		break;
	case 1:
		UpdateType1();
		break;
	}

}
/*Type0の敵
updaateからswitchで一致した時のみ実行*/
void CEnemy::UpdateType0(void) {
	/*if (m_PosY < 1000)
	{
		m_PosY += m_SpeedY;
	}
	else
	{
		if (m_ShotWait <= 0)
		{
			int sCnt = 12;
			//kakudo
			float ad = 0.0f;
			for (int cnt = 0; cnt < sCnt; cnt++)
			{
				for (int i = 0; i < ENEMYSHOT_COUNT; i++)
				{
					if (m_ShotArray[i].GetShow())
					{
						continue;
					}
					m_ShotWait = m_ShotWaitSet;
					//hassya ichi
					float stx = m_PosX + m_pTexture->GetWidth() * 0.5f;
					float sty = m_PosY + m_pTexture->GetHeight();
					//tama susumu houkou
					m_ShotArray[i].Fire(stx, sty, cos(MOF_ToRadian(ad)) * 5, sin(MOF_ToRadian(ad)) * 5);
					break;
				}
				//360 / kazu
				ad += 360.0f / sCnt;
			}
		}
		else
		{
			m_ShotWait--;
		}
	}*/
	//画面下に向かって移動
	m_PosY += m_SpeedY;
	m_PosX += m_SpeedX;

	//画面外で消去
	if (m_PosY >= g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
	if (m_SpeedX > 0 && m_PosX + m_pTexture->GetWidth() > g_pGraphics->GetTargetWidth())
	{
		m_SpeedX *= -1;
	}
	else if (m_SpeedX < 0 && m_PosX < 100)
	{
		m_SpeedX *= -1;
	}
	if (m_PosY + m_pTexture->GetHeight() > 500)
	{
		m_SpeedY *= -1;
	}
	//弾の発射
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			if (m_ShotArray[i].GetShow())
			{
				continue;
			}
			m_ShotWait = m_ShotWaitSet;
			float stx = m_PosX + m_pTexture->GetWidth() * 0.5f;
			float sty = m_PosY + m_pTexture->GetHeight();
			float dx = m_TargetPosX - stx;
			float dy = m_TargetPosY - sty;
			float d = sqrt(dx * dx + dy * dy);
			if (d <= 0)
			{
				break;
			}
			dx /= d;
			dy /= d;
			m_ShotArray[i].Fire(stx, sty, dx * 5, dy * 5);
			//m_ShotArray[i].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f,m_PosY + m_pTexture->GetHeight(),0,5);
			break;
		}
	}
	else
	{
		m_ShotWait--;
	}
}

/*Type1の敵
switchで一致した時のみ実行*/
void CEnemy::UpdateType1(void) {

	/*m_PosY += m_SpeedY;
	m_PosX += m_SpeedX;

	//画面外で消去
	if (m_PosY >= g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
	if (m_SpeedX > 0 && m_PosX + m_pTexture->GetWidth() > g_pGraphics->GetTargetWidth())
	{
		m_SpeedX *= -1;
	}
	else if (m_SpeedX < 0 && m_PosX < 100)
	{
		m_SpeedX *= -1;
	}
	if (m_PosY + m_pTexture->GetHeight() > 500)
	{
		m_SpeedY *= -1;
	}
	//弾の発射
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			if (m_ShotArray[i].GetShow())
			{
				continue;
			}
			m_ShotWait = m_ShotWaitSet;
			float stx = m_PosX + m_pTexture->GetWidth() * 0.5f;
			float sty = m_PosY + m_pTexture->GetHeight();
			float dx = m_TargetPosX - stx;
			float dy = m_TargetPosY - sty;
			float d = sqrt(dx * dx + dy * dy);
			if (d <= 0)
			{
				break;
			}
			dx /= d;
			dy /= d;
			m_ShotArray[i].Fire(stx, sty, dx * 5, dy * 5);
			//m_ShotArray[i].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f,m_PosY + m_pTexture->GetHeight(),0,5);
			break;
		}
	}
	else
	{
		m_ShotWait--;*
	}*/
	if (m_PosY < 100)
	{
		m_PosY += m_SpeedY;
	}
	else
	{
		if (m_ShotWait <= 0)
		{
			int sCnt = 12;
			//kakudo
			float ad = 0.0f;
			for (int cnt = 0; cnt < sCnt; cnt++)
			{
				for (int i = 0; i < ENEMYSHOT_COUNT; i++)
				{
					if (m_ShotArray[i].GetShow())
					{
						continue;
					}
					m_ShotWait = m_ShotWaitSet;
					//hassya ichi
					float stx = m_PosX + m_pTexture->GetWidth() * 0.5f;
					float sty = m_PosY + m_pTexture->GetHeight();
					//tama susumu houkou
					m_ShotArray[i].Fire(stx, sty, cos(MOF_ToRadian(ad)) * 5, sin(MOF_ToRadian(ad)) * 5);
					break;
				}
				//360 / kazu
				ad += 360.0f / sCnt;
			}
		}
		else
		{
			m_ShotWait--;
		}
	}
}


/**
 * ダメージ処理
 * 引数分のＨＰを減らしＨＰが０以下になれば敵を消去する
 *
 * 引数
 * [in]			dmg				ダメージ
 *
 */
void CEnemy::Damage(int dmg) {
	m_HP -= dmg;
	if (m_HP <= 0)
	{
		m_bShow = false;
	}
}

/**
 * 描画
 *
 */
void CEnemy::Render(void) {
	//弾の描画
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render();
	}
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX, m_PosY);
}

/**
 * デバッグ描画
 *
 * 引数
 * [in]			i				敵の配列内番号
 */
void CEnemy::RenderDebug(int i) {
	//位置の描画
	CGraphicsUtilities::RenderString(10, 70 + i * 24, MOF_XRGB(0, 0, 0), "敵[%d] %s , 位置 X : %.0f , Y : %.0f", i + 1, ((m_bShow) ? "表示" : "非表示"), m_PosX, m_PosY, m_HP);

	//非表示
	if (!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CGraphicsUtilities::RenderRect(m_PosX, m_PosY, m_PosX + m_pTexture->GetWidth(), m_PosY + m_pTexture->GetHeight(), MOF_XRGB(255, 0, 0));
	//弾の描画
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].RenderDebug();
	}
}