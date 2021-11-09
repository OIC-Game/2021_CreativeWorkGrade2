#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include    "Enemy.h"
#include    "EffectManager.h"
#include    "Item.h"
//移動速度
#define		PLAYER_SPEED			0.3f

//移動最大速度
#define		PLAYER_MAXSPEED			10.0f

//ジャンプ初速
#define		PLAYER_JUMP				-15.0f

//攻撃幅
#define		PLAYER_ATTACKWIDTH		30

//当たり判定減衰幅
#define		PLAYER_RECTDECREASE		12

class CPlayer {
private:
	int m_HP;
	int m_DamageWait;
	CEffect* m_pEndEffect;
	bool m_bEnd;
	CEffectManager* m_pEffectManager;
	CTexture m_FrameTexture;
	CTexture m_HPTexture;
	CTexture				m_Texture;
	CSpriteMotionController	m_Motion;
	float					m_PosX;
	float					m_PosY;
	bool					m_bMove;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bJump;
	bool					m_bReverse;
	CRectangle				m_SrcRect;

	//モーション種類定義
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMPSTART,
		MOTION_JUMPEND,
		MOTION_ATTACK,
		MOTION_DAMAGE,
		MOTION_COUNT,
	};
public:
	CPlayer();
	~CPlayer();
	void RenderStatus(void);
	void CollisionStage(float ox, float oy);
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void UpdateKey(void);
	void UpdateMove(void);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	bool IsAttack(){ return m_Motion.GetMotionNo() == MOTION_ATTACK; }
	bool CollisionEnemy(CEnemy& ene);
	bool CollisionItem(CItem& itm);
	bool IsEnd(void) { return m_bEnd; }
	CRectangle GetRect(){
		if(IsAttack())
		{
			return CRectangle(m_PosX + PLAYER_RECTDECREASE,m_PosY + PLAYER_RECTDECREASE,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,m_PosY + m_SrcRect.GetHeight());
		}
		return CRectangle(m_PosX + PLAYER_RECTDECREASE,m_PosY + PLAYER_RECTDECREASE,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
	}
	CRectangle GetAttackRect(){
		//反転中
		if(m_bReverse)
		{
			return CRectangle(m_PosX - PLAYER_ATTACKWIDTH,m_PosY,m_PosX + PLAYER_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
		}
		return CRectangle(m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,m_PosY,m_PosX + m_SrcRect.GetWidth(),m_PosY + m_SrcRect.GetHeight());
	}
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }
};