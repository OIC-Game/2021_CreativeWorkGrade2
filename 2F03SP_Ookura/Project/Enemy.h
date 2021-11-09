#pragma once

#include	"Mof.h"
#include	"EnemyShot.h"

//íeÇÃî≠éÀå¿äEêî
#define		ENEMYSHOT_COUNT					50

class CEnemy {
private:
	CTexture*				m_pTexture;
	float					m_PosX;
	float					m_PosY;
	float					m_SpeedX;
	float					m_SpeedY;
	bool					m_bShow;

	int						m_HP;
	
	CEnemyShot				m_ShotArray[ENEMYSHOT_COUNT];
	int						m_ShotWait;
	int						m_ShotWaitSet;

	float					m_TargetPosX;
	float					m_TargetPosY;
	int						m_Type;
public:
	CEnemy();
	~CEnemy();
	void Initialize(void);
	void Start(float px,float py,int t);
	void Update(void);
	void Damage(int dmg);
	void Render(void);
	void RenderDebug(int i);
	void SetTexture(CTexture* pt,CTexture* st){ m_pTexture = pt; for(int i = 0;i < ENEMYSHOT_COUNT;i++){ m_ShotArray[i].SetTexture(st); } }
	void SetTargetPos(float tx,float ty){ m_TargetPosX = tx; m_TargetPosY = ty; }
	void UpdateType0(void);
	void UpdateType1(void);
	bool GetShow(void){ return m_bShow; }
	CEnemyShot& GetShot(int n){ return m_ShotArray[n]; }
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight()); }
	bool IsShow(void){ return m_bShow; }
};