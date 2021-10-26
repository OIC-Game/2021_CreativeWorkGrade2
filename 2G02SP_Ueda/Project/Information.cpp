#include "GameDefine.h"
#include "Information.h"
extern int						gChangeScene;
CInformation::CInformation() :
	m_InfoTexture(),
	m_bInfoCount(0),
	m_LIFE(5),
	m_ChipSize(0),
	m_ones(0),
	m_tens(0)
{
}

CInformation::~CInformation()
{
}

bool CInformation::Load(void)
{
	if (!m_InfoTexture.Load("information.png"))
	{
		return false;
	}
	if (!m_NumTexture.Load("number.png"))
	{
		return false;
	}
	return true;
}

void CInformation::Initialize(float life)
{
	m_bInfoCount = 150;
	m_ChipSize = 16;
	m_LIFE = 5 - life;
}

void CInformation::Update(void)
{
		if (m_bInfoCount > 0)
		{
			m_bInfoCount--;
		}
		else
		{
			gChangeScene = SCENENO_GAME;
		}
	m_tens = m_LIFE / 10;
	m_ones = m_LIFE % 10;
}

void CInformation::Render(void)
{
	int tcx = m_NumTexture.GetWidth() / m_ChipSize;
	CRectangle tr(m_ChipSize * (m_tens % tcx), m_ChipSize * (m_tens / tcx), m_ChipSize * (m_tens % tcx + 1), m_ChipSize * (m_tens / tcx + 1));
	CRectangle or(m_ChipSize * (m_ones % tcx), m_ChipSize * (m_ones / tcx), m_ChipSize * (m_ones % tcx + 1), m_ChipSize * (m_ones / tcx + 1));
	m_InfoTexture.Render(0, 0);
	if (m_tens > 0)
	{
		m_NumTexture.Render(272,208,tr);
	}
	m_NumTexture.Render(288, 208, or );
}

void CInformation::RenderDebug(void)
{
}

void CInformation::Release(void)
{
	m_InfoTexture.Release();
	m_NumTexture.Release();
}

void CInformation::DecLife(void)
{
	m_LIFE--;
}

void CInformation::InLife(void)
{
	m_LIFE = 5;
}
