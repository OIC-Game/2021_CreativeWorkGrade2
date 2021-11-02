#pragma once

#include	"Mof.h"

//ˆÚ“®‘¬“x
#define		PLAYERSHOT_SPEED		6

class CPlayerShot {
private:
	CTexture*				m_pTexture;
	float					m_PosX;
	float					m_PosY;
	bool					m_bShow;
	int						m_pShotColor;
public:
	CPlayerShot();
	~CPlayerShot();

	//‰Šú‰»ˆ—
	void Initialize(void);

	//’e”­ŽËˆ—
	void Fire(float px,float py);

	//’eˆÚ“®“™‚ÌXVˆ—
	void Update(void);

	//’e•`‰æˆ—
	void Render(void);

	//’eƒfƒoƒbƒO•`‰æˆ—
	void RenderDebug(void);

	//’e‚ÌƒeƒNƒXƒ`ƒƒ‚ðÝ’è
	void SetTexture(CTexture* pt){ m_pTexture = pt; }

	void SetShotColor(int* co) { m_pShotColor; }

	//’e‚ª•\Ž¦‚³‚ê‚Ä‚¢‚éê‡true‚ð•Ô‚·
	bool GetShow(void){ return m_bShow; }

	//Chapter7-8‚Å’Ç‰Á
	//’e‚Ì•\Ž¦ó‘Ô‚ðÝ’è‚·‚é
	void SetShow(bool bs){ m_bShow = bs; }

	//’e‚Ì‹éŒ`‚ð•Ô‚·
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight()); }

	
};