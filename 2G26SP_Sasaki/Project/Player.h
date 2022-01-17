#pragma once

#include "Mof.h"
#include "Enemy.h"
#include "PlayerShot.h"

//プレイヤーの当たり判定の幅
#define		PLAYER_WIDTHRECT 6

#define		PLAYER_HEIGHTRECT 4

//移動速度
#define      PLAYER_SPEED 6

#define      PLAYERSHOT_COUNT  20

#define      PLAYERSHOT_WAIT 20

#define		 PLAYERCOLOR_WAIT 15

#define		PLAYER_DEADALPHA		0
#define		PLAYER_DEADALPHASPEED	5

class CPlayer
{
private:
	CTexture	m_Texture;
	CTexture    m_pTextureBlack;
	CTexture    m_pTextureWhite;
	float       m_PosX;
	float       m_PosY;
	CTexture    m_ShotTexture;
	CTexture    m_pShotTextureBlack;
	CTexture    m_pShotTextureWhite;
	CPlayerShot m_ShotArray[PLAYERSHOT_COUNT];
	int m_ShotWait;
	int m_ColorChangeWait;

	int		m_PlayerColor;
	int		m_PlayerShotColor;

	BYTE	m_Alpha;

	bool  m_bDead;
public:
	CPlayer();
	~CPlayer();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);
	void RenderDebug(void);

	bool Collision(CEnemy & ene);

	bool IsDead(void)
	{
		return m_bDead;
	}

	int IsPlayerColor(){ return m_PlayerColor; }

	void PlayerColorChange(void);

	//プレイヤーの
	/*CRectangle GetRect()
	{
		return CRectangle(m_PosX, m_PosY, m_PosX + m_Texture.GetWidth(), m_PosY + m_Texture.GetHeight());
	}*/

	int GetPlayerPosX() { return m_PosX; }
	int GetPlayerPosY() { return m_PosY; }

	CRectangle GetRect()
	{
		return CRectangle(m_PosX + PLAYER_WIDTHRECT, m_PosY + PLAYER_HEIGHTRECT, m_PosX + m_Texture.GetWidth() - PLAYER_WIDTHRECT, m_PosY + m_Texture.GetHeight() - PLAYER_HEIGHTRECT);
	}
};