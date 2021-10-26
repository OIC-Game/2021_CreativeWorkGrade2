#include "Item.h"

CItem::CItem():
	m_pTexture(NULL),
	m_Motion(),
	m_Type(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_MoveX(0.0f),
	m_MoveY(0.0f),
	m_bShow(false){
}

CItem::~CItem(){
	//delete[] で解放されるようにReleaseをデストラクタで実行する
	Release();
}

void CItem::Initialize(float px, float py, int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	switch (GetType())
	{
		case ITEM_KINOKO:
			 m_MoveX = 2.0f;
			 m_bShow = false;
			 break;
		case ITEM_COIN:
			 m_bShow = true;
			 break;
		case ITEM_1UPKINOKO:
			m_MoveX = 2.0f;
			m_bShow = false;
	}
	//アニメーションを作成
	SpriteAnimationCreate anim = {
		"アイテム",
		0,0,
		32,32,
		TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
	};
	m_Motion.Create(anim);
}

void CItem::Update(void){
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//重力により下に少しずつ下がる
	m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
	switch (GetType())
	{
		case ITEM_KINOKO:
			 //実際に座標を移動させる
			 m_PosX += m_MoveX;
			 m_PosY += m_MoveY;
			 break;
		case ITEM_1UPKINOKO:
			//実際に座標を移動させる
			m_PosX += m_MoveX;
			m_PosY += m_MoveY;
			break;
	}
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

void CItem::Render(float wx, float wy){
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX - wx, m_PosY - wy,m_SrcRect);
}

void CItem::RenderDebug(float wx, float wy){
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	hr.Expansion(-5, -5);
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
}

void CItem::Release(void){
	m_Motion.Release();
}

void CItem::CollisionStage(float ox, float oy){
	m_PosX += ox;
	m_PosY += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX *= -1;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX *= -1;
	}
}


void CItem::PoPItem(int popItemNo){
	if (popItemNo == 1)
	{
		switch (GetType())
		{
			case ITEM_KINOKO:
				 m_bShow = true;
				 break;
		}
	}
	else if (popItemNo == 2)
	{
		switch (GetType())
		{
			case ITEM_1UPKINOKO:
				m_bShow = true;
				break;
		}
	}
}
