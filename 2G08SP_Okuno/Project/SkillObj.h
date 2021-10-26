#pragma once

#include "GameDefine.h"
#include "CollisionData.h"

class CSkillObj
{
private:
	const float m_fSp = 0.7f;	 //自然落下速度
	const float m_MaxFSp = 7.0f; //落下上限速度

	enum t_SKILL_ANIM {
		SKILL_NORMAL,

		SKILL_COUNT,
	};
	SpriteAnimationCreate	skill_anim[SKILL_COUNT] = {
		{"スキル",0,0,16,16,TRUE,{5, 0, 0}},
	};

	CTexture*				m_Texture;		//画像
	CRectangle				m_BRect;
	CSpriteMotionController	m_Motion;
	int						m_DamageFlg;
	CVector2				m_Pos;
	CVector2				m_Move;
	bool					m_bShowNow;
	bool					m_bReverse;

public:
	CSkillObj();
	~CSkillObj();

	bool Load(CTexture* tex, int dmgFlg);

	bool Fire(Vector2 pos, CVector2 move);

	void Update(float wx, float wy);

	void Render(float wx, float wy);

	void CollisionStage(CCollisionData coll);

	void Hit() { m_bShowNow = false; };

	bool GetShowNow() { return m_bShowNow; };

	CVector2 GetMove() { return m_Move; };

	CRectangle GetBRect() { return m_BRect; };
	
	CRectangle GetRect() { 
		CRectangle cr(m_Pos.x, m_Pos.y, m_Pos.x + m_Motion.GetSrcRect().GetWidth(), m_Pos.y + m_Motion.GetSrcRect().GetHeight());
		cr.Expansion(-3, -3);
		return cr;
	};

	int GetDamageFlg() { return m_DamageFlg; };
	int GetDamageDirection() { return BlockAll; };
};

