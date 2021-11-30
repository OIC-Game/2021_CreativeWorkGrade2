#include "StageParent.h"

CStageParent::CStageParent() :
	m_StageName(),
	m_PipeArray(),
	m_PipeCount(0),
	m_StageArray(),
	m_StageCount(0),
	m_StageCursor(0),
	m_CheckPointCount(0),
	m_CheckPointArray(),
	m_ThroughPipe(),
	m_PipeFlg(false),
	m_GoalFlg(false)
	//m_DebugFlg(false)
{
}

CStageParent::~CStageParent()
{
}

bool CStageParent::Load(std::string fname, CSoundBuffer* skillSound)
{
	FILE* f = fopen(fname.c_str(), "rt");
	if (f == NULL) {
		return false;
	}
	fseek(f, 0, SEEK_END);
	long fSize = ftell(f);
	fseek(f, 0, SEEK_SET);

	//メモリ確保
	char* buffer = (char*)malloc(fSize + 1);
	fSize = fread(buffer, 1, fSize, f);
	buffer[fSize] = '\0';
	char* pstr;

	MOF_PRINTLOG(buffer);

	std::string sname = strtok(buffer, ",");
	m_StageName = (char*)malloc(sname.size() + 1);
	sname.copy(m_StageName, sname.size());
	m_StageName[sname.size()] = '\0';

	m_StageCount = atoi(strtok(NULL, ","));

	m_StageArray = new CStage[m_StageCount];

	char* wk = strtok(NULL, "");
	for (int i = 0; i < m_StageCount; i++) {
		pstr = strtok(wk, ",");
		int sx = atoi(strtok(NULL, ","));
		int sy = atoi(strtok(NULL, ","));

		wk = strtok(NULL, "");
		if (!m_StageArray[i].Load(pstr, sx, sy)) {
			return false;
		}
	}

	m_CheckPointCount = atoi(strtok(wk, ","));
	m_CheckPointArray = new CCheckPoint[m_CheckPointCount];

	for (int i = 0; i < m_CheckPointCount; i++) {
		int idx = atoi(strtok(NULL, ","));
		float x = atof(strtok(NULL, ",")) * CHIPSIZE;
		float y = atof(strtok(NULL, ",")) * CHIPSIZE;

		m_CheckPointArray[i].SetStageIdx(idx);
		m_CheckPointArray[i].SetRect(CRectangle(x, y, x + CHIPSIZE, y + CHIPSIZE));
	}

	m_GoalIdx = atoi(strtok(NULL, ","));
	m_GoalType = atoi(strtok(NULL, ","));
	m_GoalX = atoi(strtok(NULL, ","));
	m_GoalTop = atoi(strtok(NULL, ","));
	m_GoalBottom = atoi(strtok(NULL, ","));

	m_PipeCount = atoi(strtok(NULL, ","));

	m_PipeArray = new CPipe[m_PipeCount];
	for (int i = 0; i < m_PipeCount; i++) {
		int inType = atoi(strtok(NULL, ","));
		int inId = atoi(strtok(NULL, ","));
		float inX = atof(strtok(NULL, ",")) * CHIPSIZE;
		float inY = atof(strtok(NULL, ",")) * CHIPSIZE;
		int inDir = atoi(strtok(NULL, ","));

		int outType = atoi(strtok(NULL, ","));
		int outId = atoi(strtok(NULL, ","));
		float outX = atof(strtok(NULL, ",")) * CHIPSIZE;
		float outY = atof(strtok(NULL, ",")) * CHIPSIZE;
		int outDir = atoi(strtok(NULL, ","));

		m_PipeArray[i] = CPipe(false,
			inType, inId, inDir, CRectangle(inX, inY, inX + CHIPSIZE, inY + CHIPSIZE),
			outType, outId, outDir, CRectangle(outX, outY, outX + CHIPSIZE, outY + CHIPSIZE));

	}

	fclose(f);
	free(buffer);

	m_pSkillSound = skillSound;

	return true;
}

void CStageParent::Initialize()
{
	m_GoalFlg = false;
	//m_DebugFlg = false;
	m_SceneChangeFlg = false;
	m_StageCursor = 0;
	for (int i = 0; i < m_StageCount; i++) {
		m_StageArray[i].Initialize(i == m_GoalIdx, m_GoalType, m_GoalX, m_GoalTop, m_pSkillSound);
	}

	for (int i = 0; i < m_CheckPointCount; i++) {
		if (!m_CheckPointArray[i].IsThrough() || m_CheckPointArray[i].GetStageIdx() >= m_StageCount) continue;

		m_StageCursor = m_CheckPointArray[i].GetStageIdx();

		m_StageArray[m_StageCursor].CheckPointThrough(m_CheckPointArray[i].GetRect());
	}
}

void CStageParent::Update(CPlayer& pl, CRectangle prec_b, CRectangle prec_a, bool clearBgmPlay)
{
	m_updTime = timeGetTime();

	if (pl.GetDead()) {
		if (pl.DeadFn()) {
			pl.SetLife(pl.GetLife() - 1);
			m_SceneChangeFlg = true;
			m_SceneNext = G_SCENE_LIFE;
		}
		return;
	}

	if (!m_GoalFlg) {
		m_StageArray[m_StageCursor].Update(pl);
	}

	float ox = 0;

	if (!m_PipeFlg) {
		//CRectangle pr = pl.GetRect();
		bool jump = pl.IsJumpingUp();
		CCollisionData coll = m_StageArray[m_StageCursor].Collision(&pl, NULL, prec_b, prec_a, pl.GetMove());
		pl.CollisionStage(coll);
	}

	if (!m_GoalFlg) {
		m_GoalFlg = GoalCheck(pl, ox);
	}

	if (m_GoalFlg) {
		if (pl.GoalFn(ox, m_GoalType, GetGoalBottom(), GetStageWidth(), clearBgmPlay)) {
			m_SceneChangeFlg = true;
			m_SceneNext = G_SCENE_GAMECLEAR;
		}
		return;
	}

	if (m_PipeFlg) {
		/*bool psFlg = m_StageCursor == m_ThroughPipe.GetOutPipe().Id && m_ThroughPipe.GetInPipe().Id != m_ThroughPipe.GetOutPipe().Id;
		if (psFlg) {
			if (pl.PipeOutFn(m_ThroughPipe.GetOutPipe())) {
				m_PipeFlg = false;
			}
		}
		else {*/
		int flg = pl.PipeInFn(m_ThroughPipe.GetInPipe());
			if (flg == PIPE_FLAG_IN_END) {
				CPipe::PipeData p = m_ThroughPipe.GetOutPipe();
				m_StageCursor = p.Id; //現在のステージを移動先のステージに

				/*マリオの大きさと土管の向きに合わせて移動先の位置を変える*/
				CVector2 v(p.Rect.Left, p.Rect.Top);
				if (p.Type == 0) {
					if ((p.Dir & BlockRight) == BlockRight) {
						v.y = p.Rect.Bottom - pl.GetRect(false).GetHeight();
					}
					else if ((p.Dir & BlockDown) == BlockDown) {
						v.y = p.Rect.Top;
					}
					else if ((p.Dir & BlockLeft) == BlockLeft) {
						v.x = p.Rect.Right - pl.GetRect(false).GetWidth();
						v.y = p.Rect.Bottom - pl.GetRect(false).GetHeight();
					}
					else {
						v.y = p.Rect.Bottom - pl.GetRect(false).GetHeight();
					}
				}
				else if (p.Type == 1) {
					v.y = p.Rect.Bottom - pl.GetRect(false).GetHeight();
				}

				//CVector2 v(200, 300); //一つのステージで作る時は位置を変える

				pl.ChangeStage(v); //プレイヤーにステージが切り替わったことを伝える
				pl.SetStageHeight(GetStageHeight()); //ステージの高さを更新する
			}
			else if (flg == PIPE_FLAG_OUT_NOW) {
				if (pl.PipeOutFn(m_ThroughPipe.GetOutPipe()) == PIPE_FLAG_OUT_END) {
					m_PipeFlg = false;
				}
			}
		//}
		return;
	}

	CPipe::PipeData plPipe = pl.GetPipeData(m_StageCursor); //
	if (plPipe.Root) { //土管に入る操作の条件を満たしているか
		for (int i = 0; i < m_PipeCount; i++) { //土管を
			CPipe::PipeData p = m_PipeArray[i].CanToPassThrough(plPipe); //プレイヤーの状態を引数として、ステージ移動の情報を取得する
			if (p.Root) { //移動できるかどうか
				m_ThroughPipe = m_PipeArray[i];
				m_PipeFlg = true;
				return;
			}
		}
	}


	for (int i = 0; i < m_CheckPointCount; i++) {
		if (m_CheckPointArray[i].IsThrough() || m_CheckPointArray[i].GetStageIdx() != m_StageCursor) continue;

		if (m_CheckPointArray[i].GetRect().CollisionRect(pl.GetRect(true))) {
			m_CheckPointArray[i].SetThrough(true);

			//チェックポイント到達時の処理
			m_StageArray[m_StageCursor].CheckPointThrough(m_CheckPointArray[i].GetRect());
		}
	}

	//if (g_pInput->IsKeyPush(MOFKEY_F3)) {
	//	m_DebugFlg = !m_DebugFlg;
	//}
	m_updTime = timeGetTime() - m_updTime;
}

void CStageParent::Render()
{
	m_StageArray[m_StageCursor].Render();
	//CGraphicsUtilities::RenderString(450, 10, "upd :%3d fps:%2d", m_updTime, CUtilities::GetFPS());
}

void CStageParent::RenderLayerOver()
{
	m_StageArray[m_StageCursor].RenderLayerOver();
}

void CStageParent::RenderDebug()
{
	//if (!m_DebugFlg) {
	//	return;
	//}

	for (int i = 0; i < m_PipeCount; i++) {
		m_PipeArray[i].RenderDebug(m_StageCursor, GetScrollX(), GetScrollY());
	}
	m_StageArray[m_StageCursor].RenderDebug_Enemy();
}

void CStageParent::Release()
{
	free(m_StageName);
	if (m_PipeArray) {
		delete[] m_PipeArray;
		m_PipeArray = NULL;
	}
	if (m_StageArray) {
		for (int i = 0; i < m_StageCount; i++) {
			m_StageArray[i].Release();
		}

		delete[] m_StageArray;
		m_StageArray = NULL;
	}
	if (m_CheckPointArray) {
		delete[] m_CheckPointArray;
		m_CheckPointArray = NULL;
	}
}

bool CStageParent::GoalCheck(CPlayer& pl, float& ox)
{
	if (pl.GetGoal()) {
		return true;
	}
	if (m_StageCursor != m_GoalIdx) {
		return false;
	}

	bool re = false;

	CRectangle prec = pl.GetRect(true);
	if (m_GoalType == 1) {
		if (m_StageArray[m_StageCursor].IsGEnemy()) {
			return true;
		}
		ox = prec.Right - ((m_GoalBottom + 0.5f) * CHIPSIZE);
		return ox >= 0;
	}

	ox = prec.Right - ((m_GoalX + 0.5f) * CHIPSIZE);
	if (ox >= 0) {
		re = true;
	}

	return re;
}

Vector2 CStageParent::GetStartPos()
{
	Vector2 startPos = m_StageArray[m_StageCursor].GetStartPos();
	for (int i = 0; i < m_CheckPointCount; i++) {
		if (!m_CheckPointArray[i].IsThrough() || m_CheckPointArray[i].GetStageIdx() >= m_StageCount) continue;

		startPos = Vector2(m_CheckPointArray[i].GetRect().Left, m_CheckPointArray[i].GetRect().Top);
	}
	return startPos;
}

void CStageParent::ResetCheckPoint()
{
	for (int i = 0; i < m_CheckPointCount; i++) {
		m_CheckPointArray[i].SetThrough(false);
	}
}
