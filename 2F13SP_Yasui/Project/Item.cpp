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
void CItem::Initialize(float px, float py, int type,int stageState) {
	item_Type = type;
	item_Position.x = px;
	item_Position.y = py;
	item_StageState = stageState;
	item_Move = Vector2(-2.0f, 0.0f);
	item_Show = true;
	item_Appear = false;
	item_BlockJump = false;
	item_ReverseFlg = false;
	item_TopReverseFlg = false;
	item_MaguroFlyFlg = false;
	item_AppearTime = 0;
	item_EffectEndFlg = false;
	item_MaguroExplosionFlg = false;
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
		case ITEM_FOAM_MUSH:
		{
			//アニメーションを作成
			SpriteAnimationCreate anime[] = {
				{
					"泡キノコ",
					0,0,
					32,32,
					TRUE,{{15,0,0},{15,1,0},{15,2,0},{15,1,0}}
				},
			};
			item_Motion.Create(anime, 1);
			break;
		}
		case ITEM_FOAM_COIN:
		{
			//アニメーションを作成
			SpriteAnimationCreate anime[] = {
				{
					"泡コイン",
					0,0,
					32,32,
					TRUE,{{10,0,0},{10,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
				},
			};
			item_Motion.Create(anime, 1);
			break;
		}
		case ITEM_BIG_MAGURO:
		{
			item_Move.x = 0;
			item_ReverseFlg = true;


			//アニメーションを作成
			SpriteAnimationCreate anime[] = {
				{
					"マグロ",
					0,0,
					128,60,
					FALSE,{{5,0,0}}
				},
			};
			item_Motion.Create(anime, 1);
			break;
		}
		default :
		{
			//アニメーションを作成
			SpriteAnimationCreate anime[] = {
				{
					"コイン",
					0,0,
					32,32,
					FALSE,{{5,0,0}}
				},
			};
			item_Motion.Create(anime, 1);
			break;
		}
	}

	switch (item_Type)
	{
		case ITEM_MUSH:
		{

			break;
		}
		case ITEM_COIN:
		{
			item_Move = Vector2(0, 0);
			break;
		}
		case ITEM_FOAM_MUSH:
		{

			break;
		}
		case ITEM_FOAM_COIN:
		{

			break;
		}
		case ITEM_BIG_MAGURO:
		{
			item_Move.x = 0;
			item_ReverseFlg = true;
			if (stageState == STAGESTATE_SKY)
			{
				item_Move.x = 5;//2;
			}

			break;
		}
		default:
		{
			break;
		}
	}

}

/**
 * 更新
 *
 */
void CItem::Update(float wx,float wy) {
	//取得時非表示
	if (!item_Show)
	{
		return;
	}
	if (wx > item_Position.x + item_pTexture->GetWidth() || wx + g_pGraphics->GetTargetWidth() < item_Position.x)
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
			//実際に座標を移動させる
			item_Position.x += item_Move.x;
			item_Position.y += item_Move.y;
			break;
		}
		case ITEM_COIN:
		{
			
			break;
		}
		case ITEM_FOAM_MUSH:
		{
			item_Move.x += CUtilities::GetFrameSecond();

			//ふわふわ浮かせる
			item_Move.y = sin(item_Move.x) * 1.0f;

			//実際に座標を移動させる
			item_Position.x += -1;
			item_Position.y += item_Move.y;
			break;
		}
		case ITEM_FOAM_COIN:
		{
			item_Move.x += CUtilities::GetFrameSecond();
			//ふわふわ浮かせる
			item_Move.y = sin(item_Move.x) * 1.0f;
			
			//実際に座標を移動させる
			item_Position.x += -1;
			item_Position.y += item_Move.y;
			break;
		}
		case ITEM_BIG_MAGURO:
		{
			if (item_MaguroFlyFlg)
			{
				item_Move.y -= 0.5f;
			}
			else if (item_StageState == STAGESTATE_SKY)
			{
				if (item_EffectEndFlg)
				{
					item_AppearTime--;
					if(item_AppearTime <= 0)
					{
						item_Show = false;
						
					}
				}
				if (item_Position.x > 1500 && item_Position.x < 3200)
				{
					if (item_Position.y > 128)
					{
						item_Move.y = -2.5f;
					}
					else
					{
						item_Move.y = 0;
					}
				}
				else if (item_Position.x > 4200 && item_Position.x < 6500)
				{
					if (item_Position.y < 450)
					{
						item_Move.y = 2.5f;
					}
					else
					{
						item_Move.y = 0;
					}
				}
				if (item_Position.x > 8200)
				{
					if (item_Position.y > 128)
					{
						item_Move.y -= 0.5f;
					}
					else
					{
						item_Move.y = 0;
						item_Move.x += 0.5f;
					}
				}


				if (item_Position.x > 9408 && !item_EffectEndFlg)
				{
					item_EndEffect = item_pEffectManager->Start(Vector2(item_Position.x + 150, item_Position.y - 10), EFFECT_EXPLOSITON, 5.0f);
					item_AppearTime = 10;
					item_Move = Vector2(0, 0);
					item_EffectEndFlg = true;
					item_MaguroExplosionFlg = true;
				}
				 
			}


			item_Position.x += item_Move.x;
			item_Position.y += item_Move.y;
			break;
		}
		default:
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
	if (item_Type == ITEM_FOAM_MUSH || item_Type == ITEM_FOAM_COIN || item_Type == ITEM_BIG_MAGURO)
	{
		return;
	}

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
	if (!item_Show || item_EffectEndFlg)
	{
		return;
	}
	if (wx > item_Position.x + item_pTexture->GetWidth() || wx + g_pGraphics->GetTargetWidth() < item_Position.x)
	{
		return;
	}
	if (!item_Appear && item_Type == ITEM_MUSH)
	{
		return;
	}

	if (item_ReverseFlg)
	{
		float temp;
		temp = item_SrcRect.Right;
		item_SrcRect.Right = item_SrcRect.Left;
		item_SrcRect.Left = temp;
	}


	//テクスチャの描画
	if (item_Type == ITEM_BIG_MAGURO && item_StageState == STAGESTATE_WATER)
	{
		if(item_MaguroFlyFlg)
		item_pTexture->RenderRotate(item_Position.x - wx, item_Position.y - wy,MOF_ToRadian(-90), item_SrcRect,TEXALIGN_CENTERCENTER);
	}
	else
	{
		item_pTexture->Render(item_Position.x - wx, item_Position.y - wy,item_SrcRect);
	}
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
	if (wx > item_Position.x + item_pTexture->GetWidth() || wx + g_pGraphics->GetTargetWidth() > item_Position.x)
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

void CItem::CollisionMaguro(CRectangle r,Vector2& offset, bool& jumpFlg, Vector2& addPos)
{

	CRectangle itemRect = GetRect();

	
	CRectangle grec = r;
	grec.Top = grec.Bottom;
	grec.Bottom = grec.Top + 1;
	grec.Expansion(-6, 0);
	if (itemRect.CollisionRect(grec)) {
		jumpFlg = true;
	}
	//当たり判定用のキャラクタ矩形
	//下で範囲を限定した専用の矩形を作成する
	CRectangle bottomRect = r;
	bottomRect.Top = bottomRect.Bottom - 1;
	bottomRect.Expansion(-6, 0);
	//下と当たり判定
	if (itemRect.CollisionRect(bottomRect)) {
		//下の埋まりなのでチップ上端から矩形の下端の値を引いた値が埋まりの値
		//ボトムの矩形を追加しているのでその分だけマイナス
		offset.y += itemRect.Top - (bottomRect.Bottom - PLAYER_ADD_BUTTOMRECT);
		r.Top += itemRect.Top - bottomRect.Bottom;
		r.Bottom += itemRect.Top - bottomRect.Bottom;
		addPos += item_Move;
	}
	//当たり判定用のキャラクタ矩形
	//上で範囲を限定した専用の矩形を作成する
	CRectangle topRect = r;
	topRect.Bottom = topRect.Top + 1;		//上の矩形は下側を上と同じ値にする
	topRect.Expansion(-6, 0);				//横の範囲を少し狭める
	//上と当たり判定
	if (itemRect.CollisionRect(topRect)) {

		//上の埋まりなのでチップ下端から矩形の上の値を引いた値が埋まりの値
		//ボトムの矩形を追加しているのでその分だけマイナス
		offset.y += (bottomRect.Bottom - PLAYER_ADD_BUTTOMRECT) - topRect.Top;
		r.Top += itemRect.Bottom - topRect.Top;
		r.Bottom += itemRect.Bottom - topRect.Top;
		addPos += item_Move;
	}
	//当たり判定用のキャラクタ矩形
	//左、右それぞれで範囲を限定した専用の矩形を作成する
	CRectangle leftRect = r;
	leftRect.Right = leftRect.Left + 1;		//左の矩形は右側を左と同じ値にする
	leftRect.Expansion(0, -6);			//縦の範囲を少し狭める
	CRectangle rightRect = r;
	rightRect.Left = rightRect.Right - 1;		//右の矩形は左側を右と同じ値にする
	rightRect.Expansion(0, -6);			//縦の範囲を少し狭める
	//左と当たり判定
	if (itemRect.CollisionRect(leftRect)) {

		offset.x += itemRect.Right - leftRect.Left;
		r.Left += itemRect.Right - leftRect.Left;
		r.Right += itemRect.Right - leftRect.Left;

	}
	//右と当たり判定
	else if (itemRect.CollisionRect(rightRect)) {

		offset.x += itemRect.Left - rightRect.Right;
		r.Left += itemRect.Left - rightRect.Right;
		r.Right += itemRect.Left - rightRect.Right;
	}


}
