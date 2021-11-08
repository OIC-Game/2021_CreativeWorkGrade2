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
	void Initialize();
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
		//�ی�
		fadeOutFlg = false;
	}
	void FadeOut()
	{
		fadeOutFlg = true;
		//�ی�
		fadeInFlg = false;
	}
};

