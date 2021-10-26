#pragma once

#include "Mof.h"

enum b_Direction {
	BlockNone = 0,
	BlockUp = 1,
	BlockRight = 2,
	BlockDown = 4,
	BlockLeft = 8,

	BlockAll = BlockUp | BlockRight | BlockDown | BlockLeft,
};

enum e_JumpState {
	OnGround,
	Jumping,
	Manualing
};

enum t_MARIO_TYPE {
	MARIO_NORMAL = 1,
	MARIO_SUPER = 2,
	MARIO_FIRE = 4,

	MARIO_COUNT,

	MARIO_DEATH = 0,
};

enum t_DAMAGE_TYPE {
	DAMAGE_ONLY_PLAYER = 1,
	DAMAGE_ONLY_ENEMY = 2,

	DAMAGE_ALL = 15,

	DAMAGE_NONE = 0,
};

enum t_CHANGE_FLG {
	CHANGE_KILLED = 1,
	CHANGE_TRAMPLED = 2,
	CHANGE_TOUCH = 4,
	CHANGE_NEAR = 8,

	CHANGE_NONE = 0,
};

enum t_MOVE_TYPE {
	MOVE_LEFT = 1,
	MOVE_RIGHT = 2,
	MOVE_UP = 4,
	MOVE_DOWN = 8,
	MOVE_SENSE = 16,
};

enum t_ITEM_TYPE {
	ITEM_NORMAL = 1,
	ITEM_1UP = 2,
	ITEM_COIN = 4,

	ITEM_COUNT,
};

enum t_DISPLAY_STATE {	//表示状態
	STATE_YET,			//まだ表示されていない
	STATE_SHOW,			//表示中
	STATE_DISSHOW,		//画面外（再び表示される）
	STATE_DISAPPEAR,	//もう表示されることはない
};

constexpr int CHIPSIZE = 32;

class CItemDefine {
public:
	int idx;
	float move;
	int itemType;
	int ext1;
	int ext2;

	CItemDefine() :
		idx(0),
		move(0),
		itemType(0),
		ext1(0),
		ext2(0) {
	};

	~CItemDefine() {};
};

class CBlockDefine {
public:
	int idx;
	int block;
	int damageFlg;
	int damageDirection;
	int move;
	float x_ext1;
	float x_ext2;
	float y_ext1;
	float y_ext2;
	int broken;
	int nextIdx;
	int nextIdx_Item;

	CBlockDefine() :
		idx(0),
		block(0),
		damageFlg(0),
		damageDirection(0),
		move(0),
		x_ext1(0),
		x_ext2(0),
		y_ext1(0),
		y_ext2(0),
		broken(0),
		nextIdx(0),
		nextIdx_Item(0) {
	};

	~CBlockDefine() {};
};

class CEnemyDefine {
public:
	int idx;
	int damageFlg;
	int damageDirection;
	int move;
	float x_ext1;
	float x_ext2;
	float y_ext1;
	float y_ext2;
	int changeFlg;
	int changeIdx;
	int	animCount;
	SpriteAnimationCreate* anim;

	CEnemyDefine() :
		idx(0),
		damageFlg(0),
		damageDirection(0),
		move(0),
		x_ext1(0),
		x_ext2(0),
		y_ext1(0),
		y_ext2(0),
		changeFlg(0),
		changeIdx(0),
		animCount(0),
		anim() {
	};

	~CEnemyDefine() { Release(); };

	void Release() {
		if (anim) {
			delete[] anim;
			anim = NULL;
		}
	}
};

class CGameDefine {
private:
	static CGameDefine* m_pGameDefine;

	CGameDefine() :
		m_BlockDefineCount(0),
		m_BlockDefine(),
		m_ItemDefineCount(0),
		m_ItemDefine(),
		m_EnemyDefineCount(0),
		m_EnemyDefine() 
	{
	};
	bool Load_Block(const char* fname);
	bool Load_Item(const char* fname);
	bool Load_Enemy(const char* fname);

public:
	int m_BlockDefineCount;
	CBlockDefine* m_BlockDefine;
	int m_ItemDefineCount;
	CItemDefine* m_ItemDefine;
	int m_EnemyDefineCount;
	CEnemyDefine* m_EnemyDefine;

	~CGameDefine() {
	}

	void Release() {
		
		if (m_pGameDefine == NULL) return;
		if (m_pGameDefine->m_BlockDefine) {
			delete[] m_pGameDefine->m_BlockDefine;
			m_pGameDefine->m_BlockDefine = NULL;
		}
		if (m_pGameDefine->m_EnemyDefine) {
			delete[] m_pGameDefine->m_EnemyDefine;
			m_pGameDefine->m_EnemyDefine = NULL;
		}
		if (m_pGameDefine->m_ItemDefine) {
			delete[] m_pGameDefine->m_ItemDefine;
			m_pGameDefine->m_ItemDefine = NULL;
		}
		delete m_pGameDefine;
		m_pGameDefine = NULL;
	}

	static CGameDefine* GetGameDefine() {
		if (m_pGameDefine == NULL) {
			m_pGameDefine = new CGameDefine();
		}
		return m_pGameDefine;
	}

	bool Load() {
		if (!Load_Block("BlockDefine.txt")) {
			return false;
		}
		if (!Load_Item("ItemDefine.txt")) {
			return false;
		}
		if (!Load_Enemy("EnemyDefine.txt")) {
			return false;
		}

		return true;
	}

	int GetMarioIdx(int type) {
		int re = -1;
		if ((type & MARIO_NORMAL) == MARIO_NORMAL) {
			re = 0;
		}
		if ((type & MARIO_SUPER) == MARIO_SUPER) {
			re = 1;
		}
		if ((type & MARIO_FIRE) == MARIO_FIRE) {
			re = 2;
		}
		return re;
	}

	int GetMarioType(int idx) {
		switch (idx)
		{
		case 0:
			return MARIO_NORMAL;
		case 1:
			return MARIO_SUPER;
		case 2:
			return MARIO_FIRE;
		default:
			return MARIO_DEATH;
		}
	}

	CBlockDefine* GetBlockByIdx(int idx) {

		for (int i = 0; i < m_pGameDefine->m_BlockDefineCount; i++) {
			if (idx == m_pGameDefine->m_BlockDefine[i].idx) {
				return &m_pGameDefine->m_BlockDefine[i];
			}
		}
		return NULL;
	}

	CItemDefine* GetItemByIdx(int idx) {

		for (int i = 0; i < m_pGameDefine->m_ItemDefineCount; i++) {
			if (idx == m_pGameDefine->m_ItemDefine[i].idx) {
				return &m_pGameDefine->m_ItemDefine[i];
			}
		}
		return NULL;
	}

	CEnemyDefine* GetEnemyByIdx(int idx) {

		for (int i = 0; i < m_pGameDefine->m_EnemyDefineCount; i++) {
			if (idx == m_pGameDefine->m_EnemyDefine[i].idx) {
				return &m_pGameDefine->m_EnemyDefine[i];
			}
		}
		return NULL;
	}

	CRectangle GetGameScreenRect(float wx, float wy) {
		return CRectangle(wx - 50, wy, wx + 50 + g_pGraphics->GetTargetWidth(), wy + g_pGraphics->GetTargetHeight());
	}

};
