#include "Title.h"

extern int g_nSceneChange;

CTitle::CTitle():
	m_StageCursor(0),
	m_StageCount(0),
	m_StageList(),
	m_StageNameList(),
	m_ClearStageCursor(-1),
	m_font()
{
}

CTitle::~CTitle()
{
}

bool CTitle::Load(CTexture* playerTex)
{
	m_font.Create(20, 2, false, "MS 明朝");
	m_PlTexture = playerTex;

	FILE* f = fopen("Stages.txt", "rt");
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

	m_StageCount = atoi(strtok(buffer, ","));
	m_StageList = new std::string[m_StageCount];
	m_StageNameList = new std::string[m_StageCount];

	char* wk = strtok(NULL, "");
	for (int i = 0; i < m_StageCount; i++) {
		char* stgFile = strtok(wk, ",");
		m_StageList[i] = stgFile;
		wk = strtok(NULL, "");

		FILE* fp = fopen(stgFile, "rt");
		if (fp == NULL) {
			m_StageList[i] = "";
			m_StageNameList[i] = "ステージファイルが見つかりません(" + std::string(stgFile) + ")";
			continue;
		}

		fseek(fp, 0, SEEK_END);
		long fpSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char* fpbuffer = (char*)malloc(fpSize + 1);
		fpSize = fread(fpbuffer, 1, fpSize, fp);
		fpbuffer[fpSize] = '\0';

		m_StageNameList[i] = strtok(fpbuffer, ",");

		fclose(fp);
		free(fpbuffer);
	}

	fclose(f);
	free(buffer);

	return true;
}

void CTitle::Initialize()
{
	m_StageCursor = 0;
}

void CTitle::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_UP)) {
		m_StageCursor--;
		if (m_StageCursor < 0) {
			m_StageCursor = 0;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_DOWN)) {
		m_StageCursor++;
		if (m_StageCursor >= m_StageCount) {
			m_StageCursor = m_StageCount - 1;
		}
		if (m_StageCursor > m_ClearStageCursor + 1) {
			m_StageCursor = m_ClearStageCursor + 1;
		}
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
		g_nSceneChange = SCENE_GAME;
	}
}

void CTitle::Render()
{
	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();

	m_font.RenderString(10, 10, "タイトル");
	m_font.RenderString(100, 70, "F1キーで設定画面");

	if (m_StageCount <= 0) {
		m_font.RenderString(100, 120, "ステージリストがありません");
	}
	else {
		int xCount = (sw - (230)) / 130 + 1;

		for (int i = 0; i < m_StageCount; i++) {
			int yNum = i / xCount;
			if ((i % xCount) > 0) {
				CGraphicsUtilities::RenderFillRect(CRectangle(CVector2(130 + (130 * ((i - 1) % xCount)), 197 + (100 * yNum)), CVector2(100 + (130 * (i % xCount)), 203 + (100 * yNum))), MOF_COLOR_WHITE);
			}
			CGraphicsUtilities::RenderFillCircle(CCircle(115 + (130 * (i % xCount)), 200 + (100 * yNum), 15), MOF_COLOR_WHITE);
			CGraphicsUtilities::RenderFillCircle(CCircle(115 + (130 * (i % xCount)), 200 + (100 * yNum), 13), ((i <= m_ClearStageCursor) ? MOF_COLOR_BLUE : ((i > m_ClearStageCursor + 1) ? MOF_COLOR_CWHITE : MOF_COLOR_RED)));
			if (i == m_StageCursor) {
				//m_font.RenderString(80, 200 + 20 * i, "→");
				m_PlTexture->Render(115 + (130 * (i % xCount)) - (m_PlRect.GetWidth() / 2), 200 + (100 * yNum) - m_PlRect.GetHeight(), m_PlRect);
				if (i <= m_ClearStageCursor) m_font.RenderString(100, 120, "★");
				m_font.RenderString(120, 120, MOF_COLOR_WHITE, m_StageNameList[i].c_str());
			}
			//long col = MOF_COLOR_WHITE;
			//if (i > m_ClearStageCursor + 1) col = MOF_COLOR_CWHITE;
			//if (i <= m_ClearStageCursor) m_font.RenderString(100, 200 + 20 * i, "★");
			//m_font.RenderString(120, 200 + 20 * i, col, m_StageNameList[i].c_str());
		}
	}
}

void CTitle::Release()
{
	m_font.Release();
	if (m_StageList) {
		delete[] m_StageList;
		m_StageList = NULL;
	}
	if (m_StageNameList) {
		delete[] m_StageNameList;
		m_StageNameList = NULL;
	}
}
