#pragma once
#include <Mof.h>



class CSceneBase {
protected:
	bool	m_bEnd;
	int		m_NextScene;
	int		m_StageNumber;
public:
	CSceneBase();
	virtual ~CSceneBase() {};
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void RenderDebug() = 0;
	virtual void Release() = 0;
	int GetNextScene(void) { return m_NextScene; }
	bool IsEnd(void) { return m_bEnd; }
	int GetStageNumber() { return m_StageNumber; }
	void SetStageNumber(int number) { m_StageNumber = number; }
};
