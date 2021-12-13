#pragma once

#include "Mof.h"
#include "GameDefine.h"
#include "CollisionData.h"

class CItem
{
private:
	const float		JumpFSp = 0.7f;							//落下時の加速度（減速度）
	const float		JumpMaxSpeed = 8.0f;						//落下の上限速度
	const float		BShowAnimTime = 1.0f;

	enum JumpStatus {
		OnGround,
		Jumping
	};
	bool		m_animShow;
	float		m_animShowTime;

	CTexture*		m_Texture;		//画像
	CRectangle		m_Rect;			//画像表示位置
	CItemDefine*	m_Define;
	int				m_DfX;			//初期位置X
	int				m_DfY;			//初期位置Y
	CVector2		m_Pos;			//位置
	CVector2		m_Spd;			//移動速度
	int				m_Type;			//アイテムの種類
	bool			m_bShow;		//表示フラグ
	int				m_ShowState;	//表示状態
	int				m_stgh;
	int				m_JumpStatus;	//状態

public:
	CItem();
	~CItem();

	bool Load(CTexture* tex, CRectangle rec);

	void Initialize(CVector2 pos, CVector2 spd, CItemDefine* def, int type, int dfX, int dfY, bool dfShow, int stgh);

	void Render(float wx, float wy);

	void Update(float wx, float wy);

	/// <summary>
	/// ステージへの埋まりを解消する
	/// </summary>
	/// <param name="coll">埋まり具合の情報</param>
	void CollisionStage(CCollisionData coll);

	void Get();

	int GetDfX() { return m_DfX; };
	int GetDfY() { return m_DfY; };

	int GetType() { return m_Type; };

	CVector2 GetMove() { return m_Spd; };

	CRectangle GetRect() { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_Rect.GetWidth(), m_Pos.y + m_Rect.GetHeight()); };

	void BShow(CVector2 pos, int marioType, CTexture* itemTextures);

	bool GetShow() { return m_bShow; };
	bool GetDisplay() { return m_ShowState == STATE_SHOW; };
	void SetDisplay(int state) { if (m_ShowState != STATE_DISAPPEAR) m_ShowState = state; }
};

