#pragma once

class CCollisionData {
public:
	bool		damage; //ダメージを受けるかどうか
	float		ox; //横方向の埋まり具合
	float		oy; //縦方向の埋まり具合
	bool		og; //接地状態かどうか
	bool		unfallleftflg; //非落下移動用フラグ
	bool		unfallrightflg; //非落下移動用フラグ

	CCollisionData() :
		damage(false),
		ox(0),
		oy(0),
		og(false),
		unfallleftflg(false),
		unfallrightflg(false)
	{
	}

	~CCollisionData() {
	}
};