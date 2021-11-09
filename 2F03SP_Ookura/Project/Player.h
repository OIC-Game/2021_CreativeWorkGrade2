#pragma once

#include	"Mof.h"
#include	"Enemy.h"
#include	"PlayerShot.h"

//à⁄ìÆë¨ìx
#define		PLAYER_SPEED			8

//íeÇÃî≠éÀå¿äEêî
#define		PLAYERSHOT_COUNT		20

//íeÇÃî≠éÀä‘äu
#define		PLAYERSHOT_WAIT			20

class CPlayer {
private:
	CTexture				m_Texture;
	float					m_PosX;
	float					m_PosY;

	bool					m_bDead;
	
	CTexture				m_ShotTexture;
	CPlayerShot				m_ShotArray[PLAYERSHOT_COUNT];
	int						m_ShotWait;
public:
	CPlayer();
	~CPlayer();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	bool Collision(CEnemy& ene);
	void Render(void);
	void RenderDebug(void);
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,m_PosX + m_Texture.GetWidth(),m_PosY + m_Texture.GetHeight()); }
	bool IsDead(void){ return m_bDead; }
	void Release(void);
};