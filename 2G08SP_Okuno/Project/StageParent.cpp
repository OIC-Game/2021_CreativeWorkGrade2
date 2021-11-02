#include "StageParent.h"

CStageParent::CStageParent():
	m_StageName(),
	m_PipeArray(),
	m_PipeCount(0),
	m_StageArray(),
	m_StageCount(0),
	m_StageCursor(0),
	m_GoalFlg(false)
	//m_DebugFlg(false)
{
}

CStageParent::~CStageParent()
{
}

bool CStageParent::Load(std::string fname)
{
	FILE* f = fopen(fname.c_str(), "rt");
	if (f == NULL) {
		return false;
	}
	fseek(f, 0, SEEK_END);
	long fSize = ftell(f);
	fseek(f, 0, SEEK_SET);

	//�������m��
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

	m_GoalIdx = atoi(strtok(wk, ","));
	m_GoalType = atoi(strtok(NULL, ","));
	m_GoalX = atoi(strtok(NULL, ","));
	m_GoalTop = atoi(strtok(NULL, ","));
	m_GoalBottom = atoi(strtok(NULL, ","));

	m_PipeCount = atoi(strtok(NULL, ","));

	m_PipeArray = new CPipe[m_PipeCount];
	for (int i = 0; i < m_PipeCount; i++) {
		int inId = atoi(strtok(NULL, ","));
		float inX = atof(strtok(NULL, ",")) * CHIPSIZE;
		float inY = atof(strtok(NULL, ",")) * CHIPSIZE;
		int inDir = atoi(strtok(NULL, ","));

		int outId = atoi(strtok(NULL, ","));
		float outX = atof(strtok(NULL, ",")) * CHIPSIZE;
		float outY = atof(strtok(NULL, ",")) * CHIPSIZE;
		int outDir = atoi(strtok(NULL, ","));

		m_PipeArray[i] = CPipe(false,
			inId, inDir, CRectangle(inX, inY, inX + CHIPSIZE, inY + CHIPSIZE),
			outId, outDir, CRectangle(outX, outY, outX + CHIPSIZE, outY + CHIPSIZE));

	}

	fclose(f);
	free(buffer);

	return true;
}

void CStageParent::Initialize()
{
	m_GoalFlg = false;
	//m_DebugFlg = false;
	m_SceneChangeFlg = false;
	m_StageCursor = 0;
	for (int i = 0; i < m_StageCount; i++) {
		m_StageArray[i].Initialize(i == m_GoalIdx, m_GoalType, m_GoalX, m_GoalTop);
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

	//CRectangle pr = pl.GetRect();
	bool jump = pl.IsJumpingUp();
	CCollisionData coll = m_StageArray[m_StageCursor].Collision(&pl, NULL, prec_b, prec_a, pl.GetMove());
	pl.CollisionStage(coll);

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

	CPipe::PipeData plPipe = pl.GetPipeData(m_StageCursor); //
	if (plPipe.Root) { //�y�ǂɓ��鑀��̏����𖞂����Ă��邩
		for (int i = 0; i < m_PipeCount; i++) { //�y�ǂ�
			CPipe::PipeData p = m_PipeArray[i].CanToPassThrough(plPipe); //�v���C���[�̏�Ԃ������Ƃ��āA�X�e�[�W�ړ��̏����擾����
			if (p.Root) { //�ړ��ł��邩�ǂ���
				m_StageCursor = p.Id; //���݂̃X�e�[�W���ړ���̃X�e�[�W��

				/*�}���I�̑傫���Ɠy�ǂ̌����ɍ��킹�Ĉړ���̈ʒu��ς���*/
				CVector2 v(p.Rect.Left, p.Rect.Top);
				if ((p.Dir & BlockRight) == BlockRight) {
					v.x = p.Rect.Left - pl.GetRect(true).GetWidth();
					v.y = p.Rect.Bottom - pl.GetRect(true).GetHeight();
				}
				else if ((p.Dir & BlockDown) == BlockDown) {
					v.y = p.Rect.Top - pl.GetRect(true).GetHeight();
				}
				else if ((p.Dir & BlockLeft) == BlockLeft) {
					v.x = p.Rect.Right;
					v.y = p.Rect.Bottom - pl.GetRect(true).GetHeight();
				}
				else {
					v.y = p.Rect.Bottom + pl.GetRect(true).GetHeight();
				}

				//CVector2 v(200, 300); //��̃X�e�[�W�ō�鎞�͈ʒu��ς���

				pl.ChangeStage(v); //�v���C���[�ɃX�e�[�W���؂�ւ�������Ƃ�`����
				pl.SetStageHeight(GetStageHeight()); //�X�e�[�W�̍������X�V����


				/*
				* 
				* �E�G�̎�ނ𑝂₷
				* �E�X�e�[�W�I��
				* 
				 */
				return;
			}
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
