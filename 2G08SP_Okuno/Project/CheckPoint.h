#pragma once

#include	"Mof.h"

class CCheckPoint {
private:
	int			m_StageIdx;
	bool		m_Through;
	CRectangle	m_Rect;
public:
	CCheckPoint() :
		m_Through(false),
		m_StageIdx(-1),
		m_Rect()
	{};
	~CCheckPoint() {};

	void SetStageIdx(int idx) { m_StageIdx = idx; }
	int GetStageIdx() { return m_StageIdx; }

	void SetThrough(bool through) { m_Through = through; }
	bool IsThrough() { return m_Through; }

	void SetRect(CRectangle rect) { m_Rect = rect; }
	CRectangle GetRect() { return m_Rect; }
};
