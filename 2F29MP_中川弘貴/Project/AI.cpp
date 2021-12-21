#include "AI.h"

CComputer::CComputer()
{
}

CComputer::~CComputer()
{
}

void CComputer::Initialize()
{
	m_rightMoveButtonFlg = false;
	m_leftMoveBottonFlg = false;
	m_downMoveButtonFlg = false;
	m_rightRotateButtonFlg = false;
	m_leftRotateButtonFlg = false;

	m_moveRand = MOVE_NONE;
	m_rotateRand = ROTATE_NONE;

	m_actionTimeCnt = ACTION_SPAN;
}

void CComputer::Update()
{
	if (m_actionTimeCnt < 0)
	{
		m_moveRand = m_random.Random(MOVE_NONE, MOVE_COUNT);
		m_rotateRand = m_random.Random(ROTATE_NONE, ROTATE_COUNT);

		MoveFlgSet(m_moveRand);
		RotateFlgSet(m_rotateRand);

		m_actionTimeCnt = ACTION_SPAN;
	}
	else
	{
		m_rightRotateButtonFlg = false;
		m_leftRotateButtonFlg = false;

		m_actionTimeCnt--;
	}
}
