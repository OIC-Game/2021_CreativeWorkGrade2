#include "Puyo.h"

CPuyo::~CPuyo() {
}

void CPuyo::Render(int x,int y,bool isInv)
{
	if (!isHide && y != 0 && !(isErasing && isInv))
	{
		//CRectangle rect = CRectangle(0, 0, blockSize, blockSize);
		//CGraphicsUtilities::RenderFillRect(rect + Vector2(offsetX + (x * blockSize), offsetY + (y * blockSize)), Colors[thisColor]);
		CGraphicsUtilities::RenderFillCircle(125 + 50 * x, 50 + 50 * (y - 1), 25, Colors[thisColor]);
	}
}