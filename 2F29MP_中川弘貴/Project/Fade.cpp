#include "Fade.h"
#include "GameApp.h"

CFade::CFade() :
	alpha(255),
	fadeInFlg(false),
	fadeOutFlg(false)
{
}

CFade::~CFade()
{
}

void CFade::Initialize()
{
	alpha = 255;
	fadeInFlg = false;
	fadeOutFlg = false;
}

void CFade::Update()
{
	if (fadeInFlg)
	{
		if (alpha <= 0)
		{
			alpha = 0;
			fadeInFlg = false;
		}
		else
		{
			alpha -= 3;
		}
	}
	else if (fadeOutFlg)
	{
		if (alpha >= 255)
		{
			alpha = 255;
			fadeOutFlg = false;
		}
		else
		{
			alpha += 3;
		}
	}
}

void CFade::Render()
{
	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(alpha, 0, 0, 0));
}
