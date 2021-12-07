#pragma once

#include	"GameApp.h"
#include	<string>

class CSettingWin
{
private:
	static const int SOUNDSET_SIZE = 2;
	static const int WINSET_SIZE = 5;
	static const int SET_SIZE = 3;

	const std::string	soundset[SOUNDSET_SIZE] = { "左右キーで音量調節:%2.0f%%" };
	const std::string	winset[WINSET_SIZE] = { "800×600", "1280×720", "1366×768", "1920×1080", "フルスクリーン" };
 	const int			winsize[WINSET_SIZE][2] = { {800, 600}, {1280, 720}, {1366, 768}, {1920, 1080} };
	const std::string	set[SET_SIZE] = { "戻る" , "画面サイズ切替", "音量設定" };

	bool		isFull;
	std::string s_fname;
	int			wincursor;		//画面サイズ切替のカーソル位置
	int			winNIdx;		//現在の画面サイズ
	int			soundcursor;		//音量設定のカーソル位置
	float		soundVolume;
	bool		bChangeVolume;
	int			setcursor;		//設定項目のカーソル位置
	
	enum {
		SET_MAIN,
		SET_WIN,
		SET_SOUND,
	};

	int			setting;

	bool WriteSettings();

public:
	CSettingWin();
	~CSettingWin();

	bool Load(std::string fname);

	void Initialize();

	void Update();

	void Render();

	bool IsChangeVolume() { return bChangeVolume; };

	float GetSoundVolume();
};

