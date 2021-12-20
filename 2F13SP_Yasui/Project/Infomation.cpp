#include "Infomation.h"

#include	"GameApp.h"
#include	"Player.h"




//�v���C���[�c�@
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
	return false;
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
		CGraphicsUtilities::RenderString(600, 50, "�P�[�P");
		break;
	}
	case STAGE_2_1:
	{
		CGraphicsUtilities::RenderString(600, 50, "�Q�[�P");
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
	CGraphicsUtilities::RenderString(460, 350, "LIFE �~ %d", player_Life);
}

void CInfomation::RenderDebug(void)
{
}

void CInfomation::Release(void)
{
}
