#pragma once

#include	"Mof.h"

enum mShotSelect_Tag {
	Down0,
	SlantRight45,
	SlantLeft45,
	Right90,
	Left90,

}type;

class CEnemyShot {
private:
	CTexture*				m_pTexture;
	float					m_PosX;
	float					m_PosY;
	float					m_Speed;
	bool					m_bShow;
	int						m_EnemyShotColor;
	int						m_ShotType;

public:
	CEnemyShot();
	~CEnemyShot();
	void Initialize(void);
	void Fire(float px,float py,float spd,int type);
	void Update();
	void Render(void);
	void RenderDebug(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
	void SetShow(bool bs){ m_bShow = bs; }
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight()); }
};