#pragma once

#include "GameApp.h"

class CTitle
{
private:
	CTexture*			m_PlTexture;
	int					m_StageCursor;
	int					m_StageCount;
	int					m_ClearStageCursor;
	std::string*		m_StageList;
	std::string*		m_StageNameList;

	CRectangle			m_PlRect = CRectangle(0, 0, 32, 32);

	CFont				m_font;

public:
	CTitle();
	~CTitle();

	bool Load(CTexture* playerTex);

	void Initialize();

	void Update();

	void Render();

	void Release();

	void SetClearStage(int stageIdx) { m_ClearStageCursor = stageIdx; }

	int GetClearStageIdx() {
		return m_ClearStageCursor;
	}

	std::string GetCurrentStage() { 
		if (m_StageCount > 0) {
			return m_StageList[m_StageCursor];
		}

		return "";
	};

	int GetCurrentStageIdx() {
		return m_StageCursor;
	}
};

