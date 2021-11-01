#pragma once

#include "GameApp.h"
#include "Mof.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Pipe.h"

class CStageParent				//複数のステージを管理する
{
private:
	char*		m_StageName;
	CPipe*		m_PipeArray;		//土管の配列
	int			m_PipeCount;
	CStage*		m_StageArray;		//ステージの配列
	int			m_StageCount;
	int			m_StageCursor;
	int			m_GoalIdx; 
	int			m_GoalType;
	int			m_GoalX;
	int			m_GoalTop;
	int			m_GoalBottom;

	//bool		m_DebugFlg;

	bool		m_GoalFlg;
	bool		m_SceneChangeFlg;
	int			m_SceneNext;

	DWORD m_updTime;
public:
	CStageParent();
	~CStageParent();

	bool Load(std::string fname);

	void Initialize();

	void Update(CPlayer& pl, CRectangle prec_b, CRectangle prec_a, bool clearBgmPlay);

	void Render();

	void RenderDebug();

	void Release();

	bool GoalCheck(CPlayer& pl, float& ox, int gtype, int gx);

	Vector2 GetStartPos() { return m_StageArray[m_StageCursor].GetStartPos(); };

	float GetGoalBottom() { return CHIPSIZE * m_GoalBottom; };

	float GetScrollX() { return m_StageArray[m_StageCursor].GetScrollX(); };

	float GetScrollY() { return m_StageArray[m_StageCursor].GetScrollY(); };

	float GetStageWidth() { return m_StageArray[m_StageCursor].GetStageWidth(); };

	float GetStageHeight() { return m_StageArray[m_StageCursor].GetStageHeight(); };

	bool IsGoal() { return m_GoalFlg; };

	bool IsSceneChange() { return m_SceneChangeFlg; };

	int GetSceneNext() { return m_SceneNext; };

	char* GetStageName() { return m_StageName; };
};

