#include "SettingWin.h"

extern int g_bScene;
extern int g_nSceneChange;

bool CSettingWin::WriteSettings()
{
	FILE* f = fopen(s_fname.c_str(), "wt");
	if (f == NULL) {
		return false;
	}

	int ff = isFull ? 1 : 0;
	int sw = g_pGraphics->GetTargetWidth();
	int sh = g_pGraphics->GetTargetHeight();
	char buffer[std::numeric_limits<float>::max_exponent10 + 1 + 6 + 3];
	std::sprintf(buffer, "%.2f", soundVolume);
	std::string sstr = std::to_string(ff) + "," + std::to_string(sw) + "," + std::to_string(sh) + "," +
		buffer + ",";

	fwrite(sstr.c_str(), 1, sstr.length(), f);

	fclose(f);
	return true;
}

CSettingWin::CSettingWin() :
	isFull(false),
	s_fname(),
	wincursor(0),
	winNIdx(0),
	soundcursor(0),
	soundVolume(0.0f),
	bChangeVolume(false),
	setcursor(0),
	setting(0)
{
}

CSettingWin::~CSettingWin()
{
}

bool CSettingWin::Load(std::string fname)
{
	s_fname = fname;
	FILE* f = fopen(fname.c_str(), "rt");
	if (f == NULL) {
		return false;
	}
	fseek(f, 0, SEEK_END);
	long fSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	//ƒƒ‚ƒŠŠm•Û
	char* buffer = (char*)malloc(fSize + 1);
	fSize = fread(buffer, 1, fSize, f);
	buffer[fSize] = '\0';
	char* pstr;

	int ff = atoi(strtok(buffer, ","));
	int fw = atoi(strtok(NULL, ","));
	int fh = atoi(strtok(NULL, ","));

	int sw = g_pGraphics->GetTargetWidth();
	int sh = g_pGraphics->GetTargetHeight();
	if (ff != 0) {
		if (!isFull) {
			if (g_pGraphics->SetScreenSize(1920, 1080)) {
				isFull = g_pGraphics->ChangeScreenMode();
				winNIdx = WINSET_SIZE - 1;
			}
		}
	}
	else {
		for (int i = 0; i < WINSET_SIZE - 1; i++) {
			if (winsize[i][0] == fw && winsize[i][1] == fh) {
				if ((sw == fw && sh == fh) ||g_pGraphics->SetScreenSize(winsize[i][0], winsize[i][1])) {
					winNIdx = i;
					break;
				}
			}
		}
	}
	soundVolume = atof(strtok(NULL, ","));

	fclose(f);
	free(buffer);
	return true;
}

void CSettingWin::Initialize()
{
	wincursor = 0;
	soundcursor = 0;
	setcursor = 0;
	setting = SET_MAIN;
}

void CSettingWin::Update()
{
	bChangeVolume = false;
	switch (setting)
	{
	case SET_MAIN:
		if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
			if (setcursor == 1) {
				setting = SET_WIN;
			}
			else if (setcursor == 2) {
				setting = SET_SOUND;
			}
		}
		else if (g_pInput->IsKeyPush(MOFKEY_UP)) {
			if (setcursor > 0) {
				setcursor--;
			}
		}
		else if (g_pInput->IsKeyPush(MOFKEY_DOWN)) {
			if (setcursor + 1 < SET_SIZE) {
				setcursor++;
			}
		}
		break;
	case SET_WIN:
		if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
			if (wincursor == 0) {
				setting = SET_MAIN;
				WriteSettings();
			}
			else if (wincursor == WINSET_SIZE) {
				if (!isFull) {
					if (g_pGraphics->SetScreenSize(1920, 1080)) {
						isFull = g_pGraphics->ChangeScreenMode();
						winNIdx = WINSET_SIZE - 1;
					}
				}
			}
			else if (wincursor - 1 != winNIdx) {
				if (isFull) {
					isFull = !g_pGraphics->ChangeScreenMode();
				}

				if (!isFull) {
					if (g_pGraphics->SetScreenSize(winsize[wincursor - 1][0], winsize[wincursor - 1][1])) {
						winNIdx = wincursor - 1;
					}
				}
			}
		}
		else if (g_pInput->IsKeyPush(MOFKEY_UP)) {
			if (wincursor > 0) {
				wincursor--;
			}
		}
		else if (g_pInput->IsKeyPush(MOFKEY_DOWN)) {
			if (wincursor < WINSET_SIZE) {
				wincursor++;
			}
		}
		break;
	case SET_SOUND:
		if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
			if (soundcursor == 0) {
				setting = SET_MAIN;
				WriteSettings();
			}
		}
		else if (g_pInput->IsKeyPush(MOFKEY_UP)) {
			if (soundcursor > 0) {
				soundcursor--;
			}
		}
		else if (g_pInput->IsKeyPush(MOFKEY_DOWN)) {
			if (soundcursor + 1 < SOUNDSET_SIZE) {
				soundcursor++;
			}
		}
		
		if (soundcursor > 0) {
			if (g_pInput->IsKeyHold(MOFKEY_LEFT)) {
				bChangeVolume = true;
				soundVolume -= 0.01f;
				if (soundVolume < 0) {
					soundVolume = 0;
				}
			}
			if (g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
				bChangeVolume = true;
				soundVolume += 0.01f;
				if (soundVolume > 1.0f) {
					soundVolume = 1.0f;
				}
			}
		}
		break;
	default:
		break;
	}

	bool escFlg = g_pInput->IsKeyPush(MOFKEY_ESCAPE) || (setcursor == 0 && g_pInput->IsKeyPush(MOFKEY_RETURN));
	if (escFlg) {
		g_nSceneChange = g_bScene;
	}
}

void CSettingWin::Render()
{
	switch (setting)
	{
	case SET_MAIN:
		for (int i = 0; i < SET_SIZE; i++) {
			if (setcursor == i) {
				CGraphicsUtilities::RenderString(30, 200 + 30 * i, "¨");
			}
			CGraphicsUtilities::RenderString(60, 200 + 30 * i, set[i].c_str());
		}
		break;
	case SET_WIN:
		for (int i = 0; i <= WINSET_SIZE; i++) {
			if (wincursor == i) {
				CGraphicsUtilities::RenderString(30, 200 + 30 * i, "¨");
			}

			if (i == 0) {
				CGraphicsUtilities::RenderString(60, 200 + 30 * i, "–ß‚é");
			}
			else {
			    long col = MOF_XRGB(255, 255, 255);
				if (i - 1 == winNIdx) {
					col = MOF_XRGB(255, 0, 0);
				}
				CGraphicsUtilities::RenderString(60, 200 + 30 * i, col, winset[i - 1].c_str());
			}
		}
		break;
	case SET_SOUND:
		for (int i = 0; i < SOUNDSET_SIZE; i++) {
			if (soundcursor == i) {
				CGraphicsUtilities::RenderString(30, 200 + 30 * i, "¨");
			}

			if (i == 0) {
				CGraphicsUtilities::RenderString(60, 200 + 30 * i, "–ß‚é");
			}
			else {
				float vp = soundVolume * 100;
				CGraphicsUtilities::RenderString(60, 200 + 30 * i, soundset[i - 1].c_str(), vp);
			}
		}
		break;
	default:
		break;
	}
}

float CSettingWin::GetSoundVolume()
{
	return soundVolume;
}
