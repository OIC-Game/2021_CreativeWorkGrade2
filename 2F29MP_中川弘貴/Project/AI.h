#pragma once
#include "GameApp.h"

#define ACTION_SPAN			15
#define ACTION_MOVE_SPAN	30

enum MOVE_ACTION
{
	MOVE_NONE,
	MOVE_RIGHT,
	MOVE_LEFT,
	MOVE_DOWN,

	MOVE_COUNT,
};

enum ROTATE_ACTION
{
	ROTATE_NONE,
	ROTATE_RIGHT,
	ROTATE_LEFT,

	ROTATE_COUNT,
};
class CComputer
{
private:
	bool m_rightMoveButtonFlg;
	bool m_leftMoveBottonFlg;
	bool m_downMoveButtonFlg;
	bool m_rightRotateButtonFlg;
	bool m_leftRotateButtonFlg;

	CRandom m_random;
	int m_moveRand;
	int m_rotateRand;

	int m_actionTimeCnt;
public:
	CComputer();
	~CComputer();
	void Initialize();
	void Update();
	bool GetRightMove()
	{
		return m_rightMoveButtonFlg;
	}
	bool GetLeftMove()
	{
		return m_leftMoveBottonFlg;
	}
	bool GetDownMove()
	{
		return m_downMoveButtonFlg;
	}
	bool GetRightRotate()
	{
		return m_rightRotateButtonFlg;
	}
	bool GetLeftRotate()
	{
		return m_leftRotateButtonFlg;
	}
	void MoveFlgSet(int num)
	{
		if (num != MOVE_RIGHT)
			m_rightMoveButtonFlg = false;
		else
			m_rightMoveButtonFlg = true;

		if (num != MOVE_LEFT)
			m_leftMoveBottonFlg = false;
		else
			m_leftMoveBottonFlg = true;

		if (num != MOVE_DOWN)
			m_downMoveButtonFlg = false;
		else
			m_downMoveButtonFlg = true;

	}
	void RotateFlgSet(int num)
	{
		if (num != ROTATE_RIGHT)
			m_rightRotateButtonFlg = false;
		else
			m_rightRotateButtonFlg = true;

		if (num != ROTATE_LEFT)
			m_leftRotateButtonFlg = false;
		else
			m_leftRotateButtonFlg = true;
	}
};

