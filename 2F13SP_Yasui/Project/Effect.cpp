#include "Effect.h"

CEffect::CEffect():
m_pTexture(NULL),
m_Motion(),
m_SrcRect(),
m_Position(0,0),
m_ShowFlg(false)
{
}

CEffect::~CEffect()
{
}

void CEffect::Initialize(int type)
{
	m_ShowFlg = false;
	m_Position = Vector2(0, 0);
	
	switch (type)
	{
	case EFFECT_EXPLOSITON:
	{
		SpriteAnimationCreate anim[] = {
			{
				"エフェクト",
					0,0,
					120,120,
					FALSE,{{3,0,0},{3,1,0},{3,2,0},{3,3,0},{3,4,0},{3,5,0},{3,6,0},{3,7,0},{3,8,0},{3,9,0},{3,10,0},{3,11,0},{3,12,0},{3,13,0},{3,14,0},{3,15,0}}
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
	default:
		SpriteAnimationCreate anim[] = {
			{
				"エフェクト",
				0, 0,
				256, 256,
				FALSE, {{ 1, 0, 0 }, { 1, 2, 0 }, { 1, 3, 0 },
						{ 1, 0, 1 }, { 1, 2, 1 }, { 1, 3, 1 },
						{ 1, 0, 2 }, { 1, 2, 2 }, { 1, 3, 2 },
						{ 1, 0, 3 }, { 1, 2, 3 }, { 1, 3, 3 },
						{ 1, 0, 4 }, { 1, 2, 4 }, { 1, 3, 4 },
						{ 1, 0, 5 }, { 1, 2, 5 }, { 1, 3, 5 },
						{ 1, 0, 6 }, { 1, 2, 6 }, { 1, 3, 6 },
						{ 1, 0, 7 }, { 1, 2, 7 }, { 1, 3, 7 }}
			}
		};
		m_Motion.Create(anim, 1);
		break;
	}
}

void CEffect::Start(CVector2 pos,float scale)
{
	m_SrcRect = m_Motion.GetSrcRect();

	m_Position = pos;
	m_Scale = scale;
	m_ShowFlg = true;

	//アニメーション再生
	m_Motion.ChangeMotion(0);
}

void CEffect::Update(void)
{
	if (!m_ShowFlg)
	{
		return;
	}
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//アニメーション終了後非表示
	if (m_Motion.IsEndMotion())
	{
		m_ShowFlg = false;
	}
}

void CEffect::Render(Vector2 scroll)
{
	if (!m_ShowFlg)
	{
		return;
	}
	m_pTexture->RenderScale(m_Position.x - scroll.x,m_Position.y - scroll.y,m_Scale, m_SrcRect,TEXALIGN_CENTERCENTER);
}

void CEffect::RenderDebug()
{
}

void CEffect::Release(void)
{
}
