#include "PoPItem.h"
#include "PoPItemManager.h"

CPoPItem::CPoPItem():
m_pTexture(NULL),
m_PosX(0.0f),
m_PosY(0.0f),
m_MoveX(0.0f),
m_MoveY(0.0f),
m_bShow(false),
m_bShowTime(0.0f),
m_SrcRect(){
}

CPoPItem::~CPoPItem(){
}

void CPoPItem::Initialize(int type){
	m_PosX = 0;
	m_PosY = 0;
	m_MoveX = 0;
	m_MoveY = 0;
	m_bShow = false;
	m_bShowTime = 0;
	m_Type = type;
	switch(GetType())
	{
	case POP_COIN:
	{
		SpriteAnimationCreate anim[] = {
			{
				"コイン",
				0,0,
				32,32,
				TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}

	case POP_KINOKO:
	{
		SpriteAnimationCreate anim[] = {
			{
				"キノコ",
				0, 0,
				32, 32,
				TRUE, { {5,0,0},{5,1,0},{5,2,0},{5,3,0} }
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}

	}
}

void CPoPItem::Start(float px, float py){
	//表示矩形を取得
	m_SrcRect = m_Motion.GetSrcRect();
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0;
	m_MoveY = 0;
	m_bShow = true;
	m_bShowTime = 40;

	//設定したアニメーションを再生開始
	m_Motion.ChangeMotion(0);
}

void CPoPItem::Update(void){
	//非表示
	if (!m_bShow)
	{
		return;
	}
	
	switch (GetType())
	{
	case POP_COIN:
		m_bShowTime--;
		if (m_bShowTime > 20)
		{
			m_PosY -= 4.0f;
		}
		else if (m_bShowTime > 0)
		{
			m_PosY += 4.0f;
		}
		else if (m_bShowTime <= 0)
		{
			m_bShow = false;
		}
		break;

	case POP_KINOKO:
		//実際に座標を移動させる
		m_PosX += m_MoveX;
		m_PosY += m_MoveY;
		break;
	}

	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

void CPoPItem::Render(float wx, float wy){
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, m_SrcRect);
}

void CPoPItem::RenderDebug(float wx, float wy){
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

void CPoPItem::Release(void){
	m_Motion.Release();
}

void CPoPItem::CollisionStage(float ox, float oy){
	if (!m_bShow)
	{
		return;
	}
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
