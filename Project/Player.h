#pragma once

#include "Enemy.h"

#include "mof.h"

#include "GameDefine.h"


//�ړ����x
#define		PLAYER_SPEED			0.3f

//�ړ��ő呬�x
#define		PLAYER_MAXSPEED			5.0f


//�W�����v����
#define		PLAYER_JUMP				-15.0f

class CPlayer
{
private:

	//�e�N�X�`���N���X�̐錾
	CTexture				gTexture;
	CTexture				HP1;
	CTexture				HP2;
	CTexture				HP3;

	CSpriteMotionController	m_Motion;
	//���W
	float px;			//�v���C���[��X���W
	float py;			//�v���C���[��Y���W
	float vx;			//�v���C���[�̉��ړ����x
	float JumpSpd;		//�v���C���[�̃W�����v���x
	bool JumpFlg;		//�W�����v�t���O
	bool MoveFlg;		//�ړ��t���O						
	bool m_bReverse;	//���]�t���O
	CRectangle	m_SrcRect;
	int LifeCount;
	int m_HP;
	int m_DamageWait;
	bool		m_HedCollisionFlg;

	//���[�V������ޒ�`
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
	void Render(float wx, float wy);
	void renderDebug(float wx, float wy);
	void Release(void);
	void CollisionJump(void);
	void Damage(void);

	int GetLife() {
		return LifeCount;
	}

	CRectangle GetRect() {
		return CRectangle(px+5, py, px + m_SrcRect.GetWidth()-5, py + m_SrcRect.GetHeight() - 5);
	}

	CRectangle GetLegRect(void)
	{
		return CRectangle(px+3, py + m_SrcRect.GetHeight(), px + m_SrcRect.GetWidth()-5, py + m_SrcRect.GetHeight() +5);
	}

	float GetPosX() {return px;}

	float CPlayer::GetPosY();

	bool CPlayer::CollisionEnemyBody(CEnemy& ene);

	bool CPlayer::CollisionEnemyHed(CEnemy& ene);

	bool GetCollisionFlg() {
		return m_HedCollisionFlg;
	}
};