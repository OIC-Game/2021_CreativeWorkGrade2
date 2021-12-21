#pragma once


#include	"Mof.h"
#include	"GameDefine.h"



//当たり判定減衰幅
#define		ENEMY_RECTDECREASE	5

class CEnemy
{
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	float					m_PosX;
	float					m_PosY;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bShow;

	bool					m_bReverse;
	CRectangle				m_SrcRect;
	int						m_DamageWait;

	bool					m_DeadFlg;
	float Count ;

	



	//モーション種類定義
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};


public:
	CEnemy();
	~CEnemy();

	void Initialize(float px, float py, int type);
	void Update(void);
	void CollisionStage(float ox, float oy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	CRectangle GetRect() {
		return CRectangle(m_PosX + ENEMY_RECTDECREASE, m_PosY + ENEMY_RECTDECREASE,
			m_PosX + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE, m_PosY + m_SrcRect.GetHeight());
	}

	//敵の頭の矩形
	CRectangle  GetHedRect() {
		return CRectangle(m_PosX - 5, m_PosY - 1, m_PosX + m_SrcRect.GetWidth() - 5, m_PosY);
	}

	int GetDamageWait(void) { return m_DamageWait;}

		//敵の頭とプレイヤーの足元との当たり判定
	   bool CollisionPlayer();
	   void Damage();
   
};

