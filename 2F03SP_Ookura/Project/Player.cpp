#include	"Player.h"
#include"Game.h"
/**
 * コンストラクタ
 *
 */
CPlayer::CPlayer() :
m_Texture() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bDead(false) ,
m_ShotTexture() ,
m_ShotArray() ,
m_ShotWait() {
}

/**
 * デストラクタ
 *
 */
CPlayer::~CPlayer(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CPlayer::Load(void){
	//テクスチャの読み込み
	if(!m_Texture.Load("Player.png"))
	{
		return false;
	}
	//弾のテクスチャ（読み込みは一つですべての弾にポインタを設定）
	if(!m_ShotTexture.Load("P_missile.png"))
	{
		return false;
	}
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		m_ShotArray[i].SetTexture(&m_ShotTexture);
	}
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * プレイヤーの位置など状態を初期化したいときに実行する。
 */
void CPlayer::Initialize(void){
	m_PosX = g_pGraphics->GetTargetWidth() * 0.5f - m_Texture.GetWidth() * 0.5f;
	m_PosY = g_pGraphics->GetTargetHeight() - m_Texture.GetHeight();
	m_bDead = false;
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		m_ShotArray[i].Initialize();
	}
}
//void CPlayer::GetGamePadCount(void) {
	

/**
 * 更新
 *
 */
void CPlayer::Update(void) {
	if (m_bDead)
	{
		return;
	}
	//キーボードでの移動
	if(g_pInput->IsKeyHold(MOFKEY_A))
	{
		m_PosX -= PLAYER_SPEED;
	}
	else if(g_pInput->IsKeyHold(MOFKEY_D))
	{
		m_PosX += PLAYER_SPEED;
	}
	if(g_pInput->IsKeyHold(MOFKEY_W))
	{
		m_PosY -= PLAYER_SPEED;
	}
	else if(g_pInput->IsKeyHold(MOFKEY_S))
	{
		m_PosY += PLAYER_SPEED;
	}
	//void CPlayer::GetGamePadCount(void) {
	if (g_pInput->GetGamePadCount())
	{
		LPGamePad pPad = g_pInput->GetGamePad(0);
		pPad->GetPadState();

		if (pPad != nullptr)
		{
			if (m_ShotWait <= 0) {
				if (pPad->IsKeyHold(2))
				{
					for (int i = 0; i < PLAYERSHOT_COUNT; i++)
					{
						if (m_ShotArray[i].GetShow())
						{
							continue;
						}
						m_ShotWait = PLAYERSHOT_WAIT;
						m_ShotArray[i].Fire(m_PosX + m_Texture.GetWidth() * 0.5f, m_PosY);
						break;
					}
				}
			}
		}
		else
		{
			m_ShotWait--;
		}
		//弾の更新
		for (int i = 0; i < PLAYERSHOT_COUNT; i++)
		{
			m_ShotArray[i].Update();
		}

		m_PosX += pPad->GetStickHorizontal() * 10;
		m_PosY += pPad->GetStickVertical() * 10;

	}
	
	//弾の発射
	if(m_ShotWait <= 0)
	{
		if(g_pInput->IsKeyHold(MOFKEY_RETURN))
		{
			for(int i = 0;i < PLAYERSHOT_COUNT;i++)
			{
				if(m_ShotArray[i].GetShow())
				{
					continue;
				}
				m_ShotWait = PLAYERSHOT_WAIT;
				m_ShotArray[i].Fire(m_PosX + m_Texture.GetWidth() * 0.5f,m_PosY);
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}
	//弾の更新
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		m_ShotArray[i].Update();
	}
	if (m_PosX + m_Texture.GetWidth() > g_pGraphics->GetTargetWidth())
	{
		m_PosX = 1/*g_pGraphics->GetTargetWidth() - m_Texture.GetWidth()*/;
	}
	else if (m_PosX < 0)
	{
		m_PosX = g_pGraphics->GetTargetWidth() - m_Texture.GetWidth();
	}
}

/**
 * 当たり判定
 * 引数の敵に対して矩形同士の当たり判定を実行する。
 * 当たっていた場合はプレイヤーの状態を変更する
 *
 * 引数
 * [in]			ene				判定を行う敵
 *
 * 戻り値
 * 当たっている場合はtrue、当たっていなければfalseを返す
 */
bool CPlayer::Collision(CEnemy& ene){
	CRectangle prec = GetRect();
	//敵の弾と自分の判定
	for(int i = 0;i < ENEMYSHOT_COUNT;i++)
	{
		if(!ene.GetShot(i).GetShow())
		{
			continue;
		}
		CRectangle srec = ene.GetShot(i).GetRect();
		if(srec.CollisionRect(prec))
		{
			m_bDead = true;
			ene.GetShot(i).SetShow(false);
			break;
		}
	}
	if(!ene.GetShow())
	{
		return false;
	}
	CRectangle erec = ene.GetRect();
	if(prec.CollisionRect(erec))
	{
		m_bDead = true;
	}
	//弾との判定
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		if(!m_ShotArray[i].GetShow())
		{
			continue;
		}
		CRectangle srec = m_ShotArray[i].GetRect();
		if(srec.CollisionRect(erec))
		{
			ene.Damage(1);
			m_ShotArray[i].SetShow(false);
			break;
		}
	}
	return false;
}

/**
 * 描画
 *
 */
void CPlayer::Render(void){
	if(m_bDead)
	{
		return;
	}
	//テクスチャの描画
	m_Texture.Render(m_PosX,m_PosY);
	//弾の描画
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		m_ShotArray[i].Render();
	}
}

/**
 * デバッグ描画
 *
 */
void CPlayer::RenderDebug(void){
	//位置の描画
	CGraphicsUtilities::RenderString(10,40,MOF_XRGB(0,0,0),"プレイヤー位置 X : %.0f , Y : %.0f",m_PosX,m_PosY);
	//当たり判定の表示
	CGraphicsUtilities::RenderRect(m_PosX,m_PosY,m_PosX + m_Texture.GetWidth(),m_PosY + m_Texture.GetHeight(),MOF_XRGB(0,255,0));
	//弾の描画
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		m_ShotArray[i].RenderDebug();
	}
}

/**
 * 解放
 *
 */
void CPlayer::Release(void){
	m_Texture.Release();
	m_ShotTexture.Release();
}