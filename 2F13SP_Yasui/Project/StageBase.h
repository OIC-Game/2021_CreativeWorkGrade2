#pragma once
#include "Stage.h"

class CStageBase
{
private:
	CStage	m_Stage;
	char*	m_StageTxt;
	int		m_StageCount;

public:
	CStageBase();
	~CStageBase();
	bool Load(char* file);
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release();
};

