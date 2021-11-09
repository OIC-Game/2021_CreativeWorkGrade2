#pragma once

class CFade
{
private:
	int  alpha;
	bool fadeInFlg;
	bool fadeOutFlg;
public:
	CFade();
	~CFade();
	void Update();
	void Render();
	bool GetFadeIn()
	{
		return fadeInFlg;
	}
	bool GetFadeOut()
	{
		return fadeOutFlg;
	}
	void FadeIn()
	{
		fadeInFlg = true;
		//•ÛŒ¯
		fadeOutFlg = false;
		alpha = 255;
	}
	void FadeOut()
	{
		fadeOutFlg = true;
		//•ÛŒ¯
		fadeInFlg = false;
		alpha = 0;
	}
};

