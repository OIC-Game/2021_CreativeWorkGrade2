#include "Pipe.h"

CPipe::CPipe():
	m_bRoot(false),
	m_InId(0),
	m_InDir(0),
	m_In(),
	m_OutId(0),
	m_OutDir(0),
	m_Out()
{
}

CPipe::CPipe(bool _bRoot, int _InId, int _InDir, CRectangle _In, int _OutId, int _OutDir, CRectangle _Out):
	CPipe()
{
	m_bRoot = _bRoot;
	m_InId = _InId;
	m_InDir = _InDir;
	m_In = _In;
	m_OutId = _OutId;
	m_OutDir = _OutDir;
	m_Out = _Out;
}

CPipe::~CPipe()
{
}

CPipe::PipeData CPipe::CanToPassThrough(CPipe::PipeData in)
{
	CPipe::PipeData p = CPipe::PipeData();
	if (in.Id == m_InId && (in.Dir & m_InDir) == m_InDir) {
		if (in.Rect.CollisionRect(m_In)) {
			p.Root = true;
			p.Id = m_OutId;
			p.Dir = m_OutDir;
			p.Rect = m_Out;
			return p;
		}
	}

	if (m_bRoot) {
		if (in.Id == m_OutId && (in.Dir & m_OutDir) == m_OutDir) {
			if (in.Rect.CollisionRect(m_Out)) {
				p.Root = true;
				p.Id = m_InId;
				p.Dir = m_InDir;
				p.Rect = m_In;
				return p;
			}
		}
	}
	return p;
}

CPipe::PipeData CPipe::GetInPipe()
{
	CPipe::PipeData p = CPipe::PipeData();
	p.Root = true;
	p.Id = m_InId;
	p.Dir = m_InDir;
	p.Rect = m_In;
	return p;
}

CPipe::PipeData CPipe::GetOutPipe()
{
	CPipe::PipeData p = CPipe::PipeData();
	p.Root = m_bRoot;
	p.Id = m_OutId;
	p.Dir = m_OutDir;
	p.Rect = m_Out;
	return p;
}

void CPipe::RenderDebug(int id, float wx, float wy)
{
	if (m_InId == id) {
		CGraphicsUtilities::RenderRect(m_In - CVector2(wx, wy), MOF_COLOR_RED);
	}
	if (m_OutId == id) {
		CGraphicsUtilities::RenderRect(m_Out - CVector2(wx, wy), MOF_COLOR_YELLOW);
	}
}
