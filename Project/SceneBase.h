#pragma once
class CSceneBase
{
protected:
	bool m_bEnd;
	int m_NextScene;
public:
	CSceneBase() :
	m_bEnd(false),
	m_NextScene(0){
	}
	virtual ~CSceneBase() {};
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
	int GetNextScene(void) { return m_NextScene; }
	bool IsEnd(void) { return m_bEnd; }
};

