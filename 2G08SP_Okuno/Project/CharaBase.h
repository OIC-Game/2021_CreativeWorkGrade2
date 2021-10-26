#pragma once

#include "Mof.h"
#include "GameDefine.h"
#include "CollisionData.h"

class CCharaBase
{
protected:
	//プレイヤーの状態を表す
	enum JumpStatus {
		OnGround,		//接地状態（地面に足がついている）
		Jumping,		//ジャンプ状態（地面に足がついていない）
		Manualing		//操作状態（重力を無視する）
	};

	CTexture*		m_Texture;		//画像
	//CRectangle		m_Rect;			//表示する箇所
	CSpriteMotionController	m_Motion;

	float			m_PosX;			//X座標
	float			m_PosY;			//Y座標
	float			m_MoveX;		//横方向の移動速度
	float			m_MoveY;		//上下方向の移動速度
	bool			m_bReverse;		//画像反転フラグ
	float			m_JumpSp;		//加速度
	int				m_JumpStatus;	//状態

public:
	CCharaBase();
	~CCharaBase();

	virtual bool Load(CTexture* tex, SpriteAnimationCreate anim[], int animCount);

	virtual void Initialize(Vector2 pos);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="wx">横方向のスクロール位置</param>
	/// <param name="wy">縦方向のスクロール位置</param>
	virtual void Render(float wx, float wy)=0;

	/// <summary>
	/// ステージへの埋まりを解消する
	/// </summary>
	/// <param name="coll">埋まり具合の情報</param>
	virtual void CollisionStage(CCollisionData coll);

	virtual CRectangle GetRect()=0;
};

