#include "Infomation.h"

#include	"GameApp.h"
#include	"Player.h"




//ÉvÉåÉCÉÑÅ[écã@
extern int				player_Life;
extern int				stage_number;
extern bool				scoreDisplayFlg;
extern	bool			player1UpDisplayFlg;

extern int				getCoinCount;


CInfomation::CInfomation()
{
}

CInfomation::~CInfomation()
{
}

bool CInfomation::Load(void)
{
	if (!m_Texture.Load("Player.png"))
	{
		return false;
	}

	return true;
}

void CInfomation::Initialize(void)
{
	scoreDisplayFlg = false;
	player1UpDisplayFlg = false;
	getCoinCount = 0;
}

void CInfomation::Update(void)
{
	Sleep(1000);
	m_NextScene = SCENENO_GAME;
	m_bEnd = true;
}

void CInfomation::Render(void)
{
	switch (stage_number)
	{
	case STAGE_1_1:
	{
		CGraphicsUtilities::RenderString(600, 50, "ÇPÅ[ÇP");
		break;
	}
	case STAGE_2_1:
	{
		CGraphicsUtilities::RenderString(600, 50, "ÇQÅ[ÇP");
		break;
	}
	case STAGE_3_1:
	{
		CGraphicsUtilities::RenderString(600, 50, "ÇRÅ[ÇP");
		break;
	}
	case STAGE_LAST:
	{
		CGraphicsUtilities::RenderString(600, 50, "BOSS");
		break;
	}

	default:
		break;
	}
	CRectangle rect(0, 96, 32, 160);
	m_Texture.Render(460, 320, rect);
	CGraphicsUtilities::RenderString(500, 350, " Å~ %d", player_Life);
}

void CInfomation::RenderDebug(void)
{
}

void CInfomation::Release(void)
{
	m_Texture.Release();
}
