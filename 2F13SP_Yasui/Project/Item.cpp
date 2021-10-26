#include "Item.h"


/**
 * コンストラクタ
 *
 */
CItem::CItem() :
	item_pTexture(NULL),
	item_Position(0, 0),
	item_Move(0, 0),
	item_Show(false),
	item_BlockJump(false),
	item_Appear(false),
	item_CoinCount(0),
	item_SrcRect(){
}

/**
 * デストラクタ
 *
 */
CItem::~CItem() {
	//delete[] で解放されるようにReleaseをデストラクタで実行する
	Release();
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 *
 * 引数
 * [in]			px					X座標
 * [in]			py					Y座標
 * [in]			type				敵タイプ
 */
void CItem::Initialize(float px, float py, int type) {
	item_Type = type;
	item_Position.x = px;
	item_Position.y = py;
	item_Move = Vector2(-2.0f, 0.0f);
	item_Show = true;
	item_Appear = false;
	item_BlockJump = false;
	switch (item_Type)
	{
		case ITEM_MUSH:
		{
			//アニメーションを作成
			SpriteAnimationCreate anime[] = {
				{
					"キノコ",
					0,0,
					32,32,
					FALSE,{{5,0,0}}
				},
			};
			item_Motion.Create(anime,1);
			break;
		}
		case ITEM_COIN:
		{
			//アニメーションを作成
			SpriteAnimationCreate anime[] = {
				{
					"コイン",
					0,0,
					32,32,
					TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
				},
			};
			item_Motion.Create(anime, 1);
			break;
		}
	}

}

/**
 * 更新
 *
 */
void CItem::Update(void) {
	//取得時非表示
	if (!item_Show)
	{
		return;
	}
	//アニメーションの更新
	item_Motion.AddTimer(CUtilities::GetFrameSecond());
	item_SrcRect = item_Motion.GetSrcRect();
	if (item_Type == ITEM_COIN)
	{
		item_SrcRect.Bottom -= 5;
	}
	switch (item_Type)
	{
		case ITEM_MUSH:
		{
			//叩いたブロックと同じ位置ならジャンプ処理
			if (item_BlockJump)
			{
				if (item_Appear)
				{
					item_Move.y = -ITEM_BLOCKJUMP;
					item_BlockJump = false;
				}
				item_Appear = true;
			}

			//出現前非表示（当たり判定は残す（ステージと判定があるため））
			if (!item_Appear)
			{
				return;
			}

			//重力により下に少しずつ下がる
			item_Move.y += ITEM_GRAVITY;
			if (item_Move.y >= 20.0f)
			{
				item_Move.y = 20.0f;
			}
			if (item_Position.y > 800)
			{
				item_Show = false;
			}
			//実際に座標を移動させる
			item_Position.x += item_Move.x;
			item_Position.y += item_Move.y;
			break;
		}
		case ITEM_COIN:
		{
			break;
		}


	}
	
	
	
	
}

/**
 * ステージとの当たり
 *
 * 引数
 * [in]			ox					X埋まり量
 * [in]			oy					Y埋まり量
 */
void CItem::CollisionStage(float ox, float oy) {

		item_Position.x += ox;
		item_Position.y += oy;
		//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
		if (oy < 0 && item_Move.y > 0)
		{
			item_Move.y = 0;
		}
		else if (oy > 0 && item_Move.y < 0)
		{
			item_Move.y = 0;
		}
		//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
		if (ox < 0 && item_Move.x > 0)
		{
			item_Move.x *= -1;
		}
		else if (ox > 0 && item_Move.x < 0)
		{
			item_Move.x *= -1;
		}
}

 

/**
 * 描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CItem::Render(float wx, float wy) {
	//非表示
	if (!item_Show)
	{
		return;
	}
	if (!item_Appear && item_Type == ITEM_MUSH)
	{
		return;
	}
	//テクスチャの描画
	item_pTexture->Render(item_Position.x - wx, item_Position.y - wy,item_SrcRect);
}

/**
 * デバッグ描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CItem::RenderDebug(float wx, float wy) {
	//非表示
	if (!item_Show)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
}

/**
 * 解放
 *
 */
void CItem::Release(void) {
	item_Motion.Release();
}


void CItem::BlockJump(bool jumpFlg)
{
	item_BlockJump = jumpFlg;
}