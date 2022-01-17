#pragma once
#include "Mof.h"


class CPuyo
{
private:
	MofU32 Colors[6] =
	{
		MOF_XRGB(220,35,45),	//red
		MOF_XRGB(12,215,72) ,	//green
		MOF_XRGB(24,150,230) ,	//blue
		MOF_XRGB(220,205,5) ,	//yellow
		MOF_XRGB(144,6,170) ,	//purple
		MOF_XRGB(108,110,135)	//gray
	};

	const int offsetX = 150;
	const int offsetY = 50;
	const int blockSize = 50;

	int thisColor;
	bool isErasing;
	bool isHide;

public:
	CPuyo():
		thisColor(0),
		isErasing(false),
		isHide(true)
		{};

	~CPuyo();

	void Render(int x, int y, bool isInv, int pos);

	int GetColor() { return thisColor; }
	void SetColor(int c) { thisColor = c; }
	bool GetIsErasing() { return isErasing; }
	void SetIsErasing(bool b) { isErasing = b; }
	bool GetIsHide() { return isHide; }
	void SetIsHide(bool b) { isHide = b; }
};
