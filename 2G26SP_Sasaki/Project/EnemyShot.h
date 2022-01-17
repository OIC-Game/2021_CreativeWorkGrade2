#pragma once

#include	"Mof.h"

//enum mShotSelect_No {
//	Down0,
//	SlantRight45,
//	SlantLeft45,
//	Right90,
//	Left90,
//
//}TYPE;

class CEnemyShot {
private:
	CTexture*				m_pTexture;
	float					m_PosX;
	float					m_PosY;
	float					m_SpeedX;
	float					m_SpeedY;
	bool					m_bShow;
	int						m_EnemyShotType;

	float					m_CenterPosX;
	float					m_ScaleX;
	float					m_ScaleY;


public:
	CEnemyShot();
	~CEnemyShot();
	void Initialize(void);
	void Fire(float px,float py,float sx,float sy,int type);
	void Update();
	void Render(float xscal,float yscal,BYTE alp);
	void RenderDebug(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
	void SetShow(bool bs){ m_bShow = bs; }
	void WallMove(float speed) { m_PosX -= speed; }
	float GetPosX() { return m_PosX; }
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,(m_PosX + m_pTexture->GetWidth()) *m_ScaleX,(m_PosY + m_pTexture->GetHeight()*m_ScaleY)); }


};