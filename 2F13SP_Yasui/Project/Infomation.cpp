#include "Infomation.h"

#include	"GameApp.h"
#include	"Player.h"




//プレイヤー残機
extern int				player_Life;

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
	CGraphicsUtilities::RenderString(460, 350, "LIFE × %d", player_Life);
}

void CInfomation::RenderDebug(void)
{
}

void CInfomation::Release(void)
{
}
