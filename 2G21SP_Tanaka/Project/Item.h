#pragma once
#include		"GameDefine.h"

//アイテム種類列挙
enum tag_ITEMTYPE{
	ITEM_KINOKO,
	ITEM_COIN,
	ITEM_1UPKINOKO,
	ITEM_FIRE,

	ITEM_TYPECOUNT,
};

class CItem{
private:
	CTexture*					m_pTexture;
	CSpriteMotionController		m_Motion;
	int							m_Type;
	float						m_PosX;
	float						m_PosY;
	float						m_MoveX;
	float						m_MoveY;
	bool						m_bShow;
	bool						m_bPop;
	float						m_ShowTime;
	CRectangle					m_SrcRect;
	
	//モーション種類定義
	enum tag_MOTION {
		MOTION_MOVE,

		MOTION_COUNT,
	};
public:
	CItem();
	~CItem();
	void Initialize(float px, float py, int type);
	void Update(void);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void CollisionStage(float ox, float oy);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	void SetShow(bool bs) { m_bShow = bs; }
	int GetType(void) { return m_Type; }
	CRectangle GetRect() {
		return CRectangle(m_PosX, m_PosY, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight());
	}
	void PoPItem(int popItemNo);

	void Pop(float wx, float wy);
};

