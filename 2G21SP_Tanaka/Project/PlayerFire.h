#pragma once
#include		"Mof.h"

//ˆÚ“®‘¬“x
#define			PLAYERSHOT_SPEED		6

class CPlayerFire{
private:
	CTexture* m_pTexture;
	float		m_PosX;
	float		m_PosY;
	float		m_MoveX;
	float		m_MoveY;
	bool		m_bShow;
	bool		m_bReverse;
public:
	CPlayerFire();
	~CPlayerFire();
	void Initialize(void);
	void Fire(float px, float py, bool reverse);
	void Update(void);
	void CollisionStage();
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	void SetShow(bool bs) { m_bShow = bs; }
	CRectangle GetRect() { return CRectangle(m_PosX, m_PosY, m_PosX + m_pTexture->GetWidth(), m_PosY + m_pTexture->GetHeight()); }
};

