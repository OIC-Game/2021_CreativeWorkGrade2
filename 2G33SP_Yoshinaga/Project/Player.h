#pragma once

#include "Enemy.h"

#include "mof.h"

#include "GameDefine.h"


//移動速度
#define		PLAYER_SPEED			0.3f

//移動最大速度
#define		PLAYER_MAXSPEED			5.0f


//ジャンプ初速
#define		PLAYER_JUMP				-15.0f

class CPlayer
{
private:

	//テクスチャクラスの宣言
	CTexture				gTexture;
	CTexture				HP1;
	CTexture				HP2;
	CTexture				HP3;

	CSpriteMotionController	m_Motion;
	//座標
	float px;			//プレイヤーのX座標
	float py;			//プレイヤーのY座標
	float vx;			//プレイヤーの横移動速度
	float JumpSpd;		//プレイヤーのジャンプ速度
	bool JumpFlg;		//ジャンプフラグ
	bool MoveFlg;		//移動フラグ						
	bool m_bReverse;	//反転フラグ
	CRectangle	m_SrcRect;
	int LifeCount;
	int m_HP;
	int m_DamageWait;
	bool		m_HedCollFlg;

	//モーション種類定義
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMP,
		MOTION_DAMAGE,
		MOTION_COUNT,
	};
	
public:
	CPlayer();
	~CPlayer();

	bool Load(void);
	void Initialize(void);
	void Update(void);
	void UpdateKey(void);
	void UpdateMove(void);
	void CollisionStage(float ox, float oy);
	void Render(float wx,float wy);
	void renderDebug(float wx, float wy);
	void Release(void);

	int GetLife() {
		return LifeCount;
	}

	CRectangle GetRect(){		
		return CRectangle(px , py , px + m_SrcRect.GetWidth(), py + m_SrcRect.GetHeight());
	}

	CRectangle GetLegRect(void)
	{
		return CRectangle(px, py + m_SrcRect.GetHeight(), px + m_SrcRect.GetWidth(), py + m_SrcRect.GetHeight() + 1);
	}


	float CPlayer::GetPosY();

	bool CPlayer::CollisionEnemy(CEnemy& ene);


	bool CPlayer::CollisionEneHed(CEnemy& ene);
};

