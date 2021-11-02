#include "Title.h"
#include "GameApp.h"
#include "GameDefine.h"

extern int    gChangeScene;


//コンストラクタ
CTitle::CTitle():
	m_Motion(),
	m_PlayerTexture(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_MoveX(0.0f),
	m_MoveY(0.0f)
     {
     }
	//デストラクタ
CTitle::~CTitle()
{

}

//初期化


bool CTitle::Load(void)
{
	if (! m_BackTexture.Load("haikei2.png"))
	{
		return false;
	}

	//if (!m_PlayerTexture.Load("playerchar.png"))
	//{
	//	return false;
	//}

	if (!m_PlayerTexture.Load("miniplayerchar.png"))
	{
		return false;
	}

	return true;

	SpriteAnimationCreate anim[] =
	{
		{
		"待機",
		0,0,
		60,64,
		TRUE,{{5,0,0}}
		},
		{
		"移動",
		0,0,
		60,64,
		TRUE,{{5,0,0},{5,1,0}}
		},

	};
	m_Motion.Create(anim, MOTION_COUNT);
	return true;
}

void CTitle::Initalize(void)
{
	//m_bEnd = false;
	m_PosX = 200;
	m_PosY = 660;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_Select = 0;
	m_Motion.ChangeMotion(MOTION_WAIT);
	
}

//更新
void CTitle::Update(void)
	{
	if (g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		m_Select += 1;
		if (m_Select > 1)
		{
			m_Select = 0;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_UP))
	{
		m_Select -= 1;
		if (m_Select < 0)
		{
			m_Select = 1;
		}
	}

	if (m_Select == 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_RETURN))
		{
			gChangeScene = SCENENO_GAME;
		}
	}
	else if (m_Select == 1)
	{
		if (g_pInput->IsKeyPush(MOFKEY_RETURN))
		{
			//m_bEnd = true;
			gChangeScene = SCENENO_Option;
		}
	}
	if (m_Motion.GetMotionNo())
	{
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	}

//描画
void CTitle::Render()
{
	CGraphicsUtilities::RenderFillRect(0,0,1024,768,MOF_COLOR_WHITE);

	CRectangle dr = m_SrcRect;

	/*float px = m_PosX - wx;
	float py = m_PosY - wy;*/


	/*float px = m_PosX;
	float py = m_PosY;*/

	//if (m_bReverse)
	//{
	//	float tmp = dr.Right;
	//	dr.Right = dr.Left;
	//	dr.Left = tmp;
	//}

	//m_PlayerTexture.Render(px, py, dr);

	m_BackTexture.Render(10, 0);
	m_PlayerTexture.Render(0,620);


	

	//CGraphicsUtilities::RenderString(400,500,MOF_COLOR_BLACK,"Press ENTER Key");
	if (m_Select == 0)
	{
		CGraphicsUtilities::RenderString(450, 400, MOF_COLOR_RED, "ゲーム開始");
	}
	else
	{
		CGraphicsUtilities::RenderString(450, 400, MOF_COLOR_HWHITE, "ゲーム開始");
	}
	if (m_Select == 1)
	{
		CGraphicsUtilities::RenderString(450, 450, MOF_COLOR_RED, "操作");
	}
	else
	{
		CGraphicsUtilities::RenderString(450, 450, MOF_COLOR_HWHITE, "操作");
	}
}

void CTitle::RenderDebug(void)
{
}

void CTitle::Release(void)
{
	m_BackTexture.Release();
	m_PlayerTexture.Release();
}

