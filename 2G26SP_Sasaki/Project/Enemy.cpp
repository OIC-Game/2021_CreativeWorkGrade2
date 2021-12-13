#include	"Enemy.h"

/**
 * コンストラクタ
 *
 */
CEnemy::CEnemy() 
/*　初期化リスト　＝　コンストラクタでメンバ変数の初期化をする
	クラスでの宣言順に書くこと！
*/
:
m_pTexture(NULL) ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_SpeedX(0.0f) ,
m_SpeedY(0.0f) ,
m_bShow(false),
m_HP(2),
m_ShotArray(),
m_ShotWait(0),
m_ShotWaitSet(0)
{
}

/**
 * デストラクタ
 *
 */
CEnemy::~CEnemy(){
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * プレイヤーの位置など状態を初期化したいときに実行する。
 */
void CEnemy::Initialize(void){
	m_PosX = 0;
	m_PosY = 0;
	m_SpeedX = 0;
	m_SpeedY = 0;
	m_bShow = false;
	m_EnemyColor = 1;
}
/**
 * 開始
 * 引数の座標に位置を設定して、表示フラグをtrueに変更する。
 *
 * 引数
 * [in]			px				発射Ｘ座標
 * [in]			py				発射Ｙ座標
 */
void CEnemy::Start(float px,float py ,int encol,int type){
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py - m_pTexture->GetHeight();
	m_EnemyColor = encol;
	m_SpeedX = 0;
	m_SpeedY = 0.4;
	m_bShow = true;
	m_HP = 2;
	m_ShotWaitSet = 40;
	m_ShotWait = m_ShotWaitSet;
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
	m_EnemyType = type;
}

/**
 * 更新
 *
 */
void CEnemy::Update(void){
	//非表示
	if(!m_bShow)
	{
		return;	//早期リターン
	}

	if (m_EnemyType == 0)
		NomalEnemyMove();

	//画面外で消去
	if(m_PosY >= g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			if (m_ShotArray[i].GetShow())
			{
				continue;
			}
			m_ShotWait = m_ShotWaitSet;
			m_ShotArray[i].Fire(m_PosX + m_pTexture->GetWidth()*0.5f, m_PosY + m_pTexture->GetHeight(), 0, 5);
			break;
		}
	}
	else
	{
		m_ShotWait--;
	}

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}
}

/**
 * 描画
 *
 */
void CEnemy::Render(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX,m_PosY);

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render();
	}
}

/**
 * デバッグ描画
 *
 * 引数
 * [in]			i				敵の配列内番号
 */
void CEnemy::RenderDebug(int i){
	//位置の描画
	CGraphicsUtilities::RenderString(10,70 + i * 24,MOF_XRGB(0,0,0),"敵[%d] %s , 位置 X : %.0f , Y : %.0f",i + 1,((m_bShow) ? "表示" : "非表示"),m_PosX,m_PosY);

	//非表示
	if (!m_bShow)
	{
		return;
	}
	CGraphicsUtilities::RenderRect(GetRect(), MOF_XRGB(255, 0, 0));

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render();
	}
}
void CEnemy::Damage(int dmg)
{
	m_HP -= dmg;
	if (m_HP <= 0)
	{
		m_bShow = false;
	}
}

	//画面下に向かって移動
void CEnemy::NomalEnemyMove()
{
	m_PosY += m_SpeedY;
}
