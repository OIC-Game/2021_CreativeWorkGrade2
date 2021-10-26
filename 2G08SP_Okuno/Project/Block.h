#pragma once

#include "Mof.h"
#include "Player.h"

class CBlock
{
private:

	CTexture*		m_Texture;		//ブロックの画像
	CRectangle		m_Rect;			//画像の表示位置
	CItem*			m_Item;			//アイテム
	int				m_Type;			//ブロックの種類
	CVector2		m_SPos;			//ブロックの初期位置
	CVector2		m_Pos;			//ブロックの位置
	CVector2		m_Move;			//ブロックの移動速度
	CBlockDefine*	m_define;		
	int				m_Broken;		//壊すことが出来るキャラ
	int				m_Dirction;		//当たり判定を行う方向
	bool			m_BAttacked;
	bool			m_Attacked;
	

public:
	CBlock();
	~CBlock();

	bool Load(CTexture* tex, Vector2 pos, CRectangle rec, CItem* item, int type, int broken, CBlockDefine* define);

	//void Initialize();

	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="wx">横方向のスクロール位置</param>
	/// <param name="wy">縦方向のスクロール位置</param>
	void Render(float wx, float wy);

	void AttackBlock(CPlayer* pl, CTexture* itemTextures);

	bool CheckDirection(int dir) { return (m_Dirction & dir) == dir; };

	bool IsAttacked() { return m_Attacked; };

	int GetType() { return m_Type; };

	CVector2 GetMove() { return m_Move; };

	bool CheckDamageFlg(int flg) {
		if (m_define == NULL) return false;
		return (m_define->damageFlg & flg) == flg;
	};
	bool CheckDamageDirection(int dir) {
		if (m_define == NULL) return false;
		return (m_define->damageDirection & dir) == dir;
	};

	CRectangle GetRect() { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_Rect.GetWidth(), m_Pos.y + m_Rect.GetHeight()); };
};

