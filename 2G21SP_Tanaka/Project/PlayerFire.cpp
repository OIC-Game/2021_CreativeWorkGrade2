#include "PlayerFire.h"

CPlayerFire::CPlayerFire():
	m_pTexture(NULL),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_MoveX(0.0f),
	m_MoveY(0.0f),
	m_bShow(false),
	m_bReverse(false){
}

CPlayerFire::~CPlayerFire(){
}

void CPlayerFire::Initialize(void){
	m_PosX = 0;
	m_PosY = 0;
	m_MoveX = 0;
	m_MoveY = 0;
	m_bShow = false;
	m_bReverse = false;
}

void CPlayerFire::Fire(float px, float py, bool reverse){
	m_PosX = px + m_pTexture->GetWidth() * 1.0f;
	m_PosY = py + 38;
	m_bShow = true;
	m_bReverse = reverse;
}

void CPlayerFire::Update(void){
	//非表示
	if (!m_bShow)
	{
		return;
	}
	if (m_bReverse)
	{
		m_MoveX = -PLAYERSHOT_SPEED;
		m_PosX += m_MoveX;
	}
	else
	{
		m_MoveX = PLAYERSHOT_SPEED;
		m_PosX += m_MoveX;
	}
	if (m_PosX < 0)
	{
		m_bShow = false;
	}
}

void CPlayerFire::CollisionStage(){
	m_bShow = false;
}

void CPlayerFire::Render(float wx, float wy){
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//描画位置
	float px = m_PosX - wx;
	float py = m_PosY - wy;
	//テクスチャの描画
	m_pTexture->Render(px, py);
}

void CPlayerFire::RenderDebug(float wx, float wy){
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
}
