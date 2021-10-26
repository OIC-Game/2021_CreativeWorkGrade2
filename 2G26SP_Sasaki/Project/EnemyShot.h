#pragma once

#include	"Mof.h"

class CEnemyShot {
private:
	CTexture*				m_pTexture;
	float					m_PosX;
	float					m_PosY;
	float					m_SpdX;
	float					m_SpdY;
	bool					m_bShow;
	int						m_EnemyShotColor;
public:
	CEnemyShot();
	~CEnemyShot();
	void Initialize(void);
	void Fire(float px,float py,float sx,float sy);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
	void SetShow(bool bs){ m_bShow = bs; }
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight()); }
};