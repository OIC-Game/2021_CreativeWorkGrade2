#pragma once
#include	"Mof.h"
#include	"GlobalDefine.h"


	//�A�C�e����ޗ�
	enum tag_ITEMTYPE {
		ITEM_MUSH,					//�L�m�R
		ITEM_COIN,					//�R�C��
		ITEM_FOAM_MUSH,				//�A�L�m�R
		ITEM_FOAM_COIN,				//�A�R�C��

		ITEM_TYPECOUNT,
	};

class CItem {
private:
	CTexture*				item_pTexture;
	CSpriteMotionController	item_Motion;
	int						item_Type;
	CVector2				item_Position;
	CVector2				item_Move;
	bool					item_Show;
	bool					item_BlockJump;
	CRectangle				item_SrcRect;
	bool					item_Appear;
	int						item_CoinCount;

public:
	CItem();
	~CItem();
	void Initialize(float px, float py, int type);
	void Update(float wx,float wy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void CollisionStage(float ox, float oy);
	void SetTexture(CTexture* pt) { item_pTexture = pt; }
	bool GetShow(void) { return item_Show; }
	void SetShow(bool bs) { item_Show = bs; }
	int GetType(void) { return item_Type; }
	CRectangle GetRect() { return CRectangle(item_Position.x + 5, item_Position.y + 5, item_Position.x + item_SrcRect.GetWidth() - 5, item_Position.y + item_SrcRect.GetHeight()); }
	void BlockJump(bool jumpFlg);
	bool GetitemAppear(void){ return item_Appear; }
	bool GetCoinCount(void) { return item_CoinCount; }
	void SetCoinCount(int coinCount) { item_CoinCount += coinCount; }
};

