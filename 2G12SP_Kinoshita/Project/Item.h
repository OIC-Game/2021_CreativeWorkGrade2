#pragma once

#include "GameDefine.h"
#include "Item.h"
#include "QuestionBlock.h"
#include "breakBlock.h"


#define Item_RECTDECREASE		100
#define Item_Speed    1
//ƒAƒCƒeƒ€Ží—Þ
//enum  tag_ITEMTYP
//{
//	ITEM_POWERUP,
//	ITEM_1UP,
//
//	ITEM_TYPECOUNT,
//};
class CItem
{
private:
	CTexture*               m_pTexture;

	int						m_Type;

	Mof::Vector2            m_Pos;
	
	Mof::Vector2            m_Move;
	bool					m_bShow;
	CRectangle				m_SrcRect;
	bool                    m_bReverse;

	CQuestionBlock*         m_Quesrt;

public:
	CItem();
	~CItem();
	void Initialize(void);
	void Fire(float px, float py);
	void Update();
	void CollisionStage(float ox, float oy);
	void Render(float wx,float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }

	int GetType(void) { return m_Type; }
	
	CRectangle GetRect()
	{
		return CRectangle(m_Pos.x , m_Pos.y , m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight() );
	}

	void showItem();

	bool CollisionQBlock(CQuestionBlock& QBlock, float ox, float oy);
	bool CollisionbreakBlock(CbreakBlock& blo, float ox, float oy);
};

