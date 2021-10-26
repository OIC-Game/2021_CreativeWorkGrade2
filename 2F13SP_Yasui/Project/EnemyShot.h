#pragma once

#include	"Mof.h"
#include	"GlobalDefine.h"

class CEnemyShot
{
private:
	CTexture*	m_pTexture;
	CVector2	enemyShot_Position;
	CVector2	enemyShot_Speed;
	bool		m_bShow;
	CSpriteMotionController enemyShot_Motion;
	CRectangle				enemyShot_RectTexture;
	bool		tmpEnemy_Reverse;
	bool		enemyShot_AddSpeed;
	int			enemyShot_Type;
	bool		enemyShot_FireBound;
	enum tag_SHOT
	{
		ENEMYSHOT_BONE,
		ENEMYSHOT_FIRE,
		ENEMYSHOT_KURIBO,
		ENEMYSHOT_MUSH,

	};
public:
	CEnemyShot();
	~CEnemyShot();
	void Initialize(int type);
	void Fire(float px, float py,float sx,float sy,bool Reverse);
	void Update(void);
	void Render(float wx,float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	void SetShow(bool bs) { m_bShow = bs; }
	CRectangle GetRect() {
		return CRectangle(enemyShot_Position.x, enemyShot_Position.y,
			enemyShot_Position.x + enemyShot_RectTexture.GetWidth()+10, enemyShot_Position.y + enemyShot_RectTexture.GetHeight());
	}
	float GetPositionX(void) { return enemyShot_Position.x; }
	void  SetPositionX(float px) { enemyShot_Position.x = px; }
	float GetPositionY(void) { return enemyShot_Position.y; }
	void  SetPositionY(float py) { enemyShot_Position.y = py; }
	float GetSpeedY(void) { return enemyShot_Speed.y; }
	void  SetSpeedY(float sy) { enemyShot_Speed.y = sy; }
};

