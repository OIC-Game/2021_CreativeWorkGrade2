#include "Player.h"

//コンストラクタ

CPlayer::CPlayer():
	m_Texture(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_bDead(false),
	m_ShotTexture(),
	m_ShotArray(),
	m_ShotWait(),
	m_ColorChangeWait(0.0f)

{

}

//デストラクタ
CPlayer::~CPlayer()
{
	
}

//読み込み
//利用するテキスチャを読み込む
//読み込み成功ならTURU失敗ならFALSE
bool CPlayer::Load(void)
{
	if (!m_pTextureBlack.Load("PlayerBlack.png"))
	{
		return false;
	}

	if (!m_pTextureWhite.Load("PlayerWhite.png"))
	{
		return false;
	}

	if (!m_Texture.Load("PlayerBlack.png"))
	{
		return false;
	}

	if (!m_ShotTexture.Load("P_missileWhite.png"))
	{
		return false;
	}
	
	if (!m_pShotTextureBlack.Load("P_missileBlack.png"))
	{
		return false;
	}
	
	if (!m_pShotTextureWhite.Load("P_missileWhite.png"))
	{
		return false;
	}

	for (int i=0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].SetTexture(&m_ShotTexture);
	}
	return true;
}

//初期化
//パラメーターや座標を初期化する
//プレイヤーの位置など状態を初期化したいときに実行する
void CPlayer::Initialize(void)
{
	m_PosX = g_pGraphics->GetTargetWidth()*0.5f - m_Texture.GetWidth()*0.5f;
	m_PosY = g_pGraphics->GetTargetHeight() - m_Texture.GetHeight();
	//死亡状態リセット
	m_bDead = false;
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
	m_PlayerColor = 1;
	m_PlayerShotColor = 0;
	m_Texture = m_pTextureBlack;
}

//更新
void CPlayer::Update(void)
{
	if (m_bDead)
	{
		return;
	}

	//Zキーで色変更
	PlayerColorChange();

	//キーボードでの移動
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_PosX -= PLAYER_SPEED;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_PosX += PLAYER_SPEED;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		m_PosY -= PLAYER_SPEED;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		m_PosY += PLAYER_SPEED;
	}

	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyHold(MOFKEY_SPACE))
		{
			for (int i = 0; i < PLAYERSHOT_COUNT; i++)
			{
				if (m_ShotArray[i].GetShow())
				{
					continue;
				}
				//if (m_PlayerColor == 0)
				//{
				//	m_ShotTexture = m_pShotTextureBlack;
				//}
				//if (m_PlayerColor == 1)
				//{
				//	m_ShotTexture = m_pShotTextureWhite;
				//}
				m_ShotWait = PLAYERSHOT_WAIT;
				if (m_PlayerShotColor == 1)
				{
					m_ShotArray[i].SetTexture(&m_pShotTextureBlack);
					m_ShotArray[i].SetPlayerShotColor(1);
				}
				if (m_PlayerShotColor == 0)
				{
					m_ShotArray[i].SetTexture(&m_pShotTextureWhite);
					m_ShotArray[i].SetPlayerShotColor(0);
				}
				//m_ShotArray[i].SetShotColor(&m_PlayerShotColor);
				m_ShotArray[i].Fire(m_PosX + m_Texture.GetWidth()*0.5f, m_PosY);
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}
}

//描画
void CPlayer::Render(void)
{
	if (m_bDead)
	{
		return;
	}
	m_Texture.Render(m_PosX, m_PosY);

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render();
	}
	
	//MOF_PRINTLOG("プレイヤーの位置x:%.of,y:%.0f\n", m_PosX, m_PosY);

	//デバッグ
	/*CGraphicsUtilities::RenderString(10, 40, MOF_XRGB(0, 0, 0),
		"プレイヤーの位置x:%.0f,y:%.0f", m_PosX, m_PosY);*/
}

//解放
void CPlayer::Release(void)
{
	m_Texture.Release();
	m_pTextureBlack.Release();
	m_pTextureWhite.Release();
	m_ShotTexture.Release();
	m_pShotTextureBlack.Release();
	m_pShotTextureWhite.Release();
}

void CPlayer::RenderDebug(void)
{
	CGraphicsUtilities::RenderString(10, 40, MOF_XRGB(0, 0, 0),
		"プレイヤー位置X:%.0f,Y:%.0f", m_PosX, m_PosY);

	//当たり判定
	CGraphicsUtilities::RenderRect(GetRect(), MOF_XRGB(0, 255, 0));

	CGraphicsUtilities::RenderRect(m_PosX, m_PosY, m_PosX + m_Texture.GetWidth(), m_PosY + m_Texture.GetHeight(),MOF_XRGB(0,255,0));

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].RenderDebug();
	}
}

bool CPlayer::Collision(CEnemy& ene)
{
	if (!ene.GetShow())
	{
		return  false;
	}
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();
	int enecolor    = ene.GetEnemyColor();
	if(m_PlayerColor != enecolor)
	{ 
		//if (prec.CollisionRect(erec))
		//{
		//	m_bDead = true;
		//	return true;
		//}
	}

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_ShotArray[i].GetShow())
		{
			continue;
		}
		CRectangle srec = m_ShotArray[i].GetRect();
		//色次第で敵に弾が当たらない
		//弾の色
		int plshtcol = m_ShotArray[i].GetPlayerColorShow();
		//if (m_PlayerShotColor != enecolor)
		//{
		if (srec.CollisionRect(erec))
		{
			if (plshtcol != enecolor)
			{
				ene.Damage(1);
				m_ShotArray[i].SetShow(false);
				return true;
			}
		}
		//}
	}
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		if (!ene.GetShot(i).GetShow())
		{
			continue;
		}
		CRectangle srec = ene.GetShot(i).GetRect();
		if (m_PlayerColor != enecolor)
		{
			//if (srec.CollisionRect(prec))
			//{
			//	m_bDead = true;
			//	ene.GetShot(i).SetShow(false);
			//	return true;
			//}
		}
	}
	return false;
}

void CPlayer::PlayerColorChange(void)
{
	//色変え待機時間
	if (m_ColorChangeWait > 0)
		m_ColorChangeWait--;

	//Zキーで色変更　黒⇔白 0→白 1→黒
	if (g_pInput->IsKeyPush(MOFKEY_Z) && (m_PlayerColor == 0) && (m_ColorChangeWait == 0))
	{
		m_PlayerColor = 1;
		m_PlayerShotColor = 0;
		m_Texture = m_pTextureBlack;
		m_ColorChangeWait = PLAYERCOLOR_WAIT;
	}
	if (g_pInput->IsKeyPush(MOFKEY_Z) && (m_PlayerColor == 1) && (m_ColorChangeWait == 0))
	{
		m_PlayerColor = 0; 
		m_PlayerShotColor = 1;
		m_Texture = m_pTextureWhite;
		m_ColorChangeWait = PLAYERCOLOR_WAIT;
	}
}
