#pragma once

#include "Mof.h"
#include "Enemy.h"
#include "PlayerShot.h"

//移動速度
#define      PLAYER_SPEED 3

#define      PLAYERSHOT_COUNT  20

#define      PLAYERSHOT_WAIT 20
class CPlayer
{
private:
	CTexture	m_Texture;
	CTexture    m_pTextureBlack;
	CTexture    m_pTextureWhite;
	float       m_PosX;
	float       m_PosY;
	CTexture    m_ShotTexture;
	CPlayerShot m_ShotArray[PLAYERSHOT_COUNT];
	int m_ShotWait;

	int		m_PlayerColor;

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

	//プレイヤーの
	/*CRectangle GetRect()
	{
		return CRectangle(m_PosX, m_PosY, m_PosX + m_Texture.GetWidth(), m_PosY + m_Texture.GetHeight());
	}*/


	CRectangle GetRect()
	{
		return CRectangle(m_PosX, m_PosY, m_PosX + m_Texture.GetWidth(), m_PosY + m_Texture.GetHeight());
	}

};