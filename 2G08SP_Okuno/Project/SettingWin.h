#pragma once

#include	"GameApp.h"
#include	<string>

class CSettingWin
{
private:
	static const int SOUNDSET_SIZE = 2;
	static const int WINSET_SIZE = 5;
	static const int SET_SIZE = 3;

	const std::string	soundset[SOUNDSET_SIZE] = { "���E�L�[�ŉ��ʒ���:%2.0f%%" };
	const std::string	winset[WINSET_SIZE] = { "800�~600", "1280�~720", "1366�~768", "1920�~1080", "�t���X�N���[��" };
 	const int			winsize[WINSET_SIZE][2] = { {800, 600}, {1280, 720}, {1366, 768}, {1920, 1080} };
	const std::string	set[SET_SIZE] = { "�߂�" , "��ʃT�C�Y�ؑ�", "���ʐݒ�" };

	bool		isFull;
	std::string s_fname;
	int			wincursor;		//��ʃT�C�Y�ؑւ̃J�[�\���ʒu
	int			winNIdx;		//���݂̉�ʃT�C�Y
	int			soundcursor;		//���ʐݒ�̃J�[�\���ʒu
	float		soundVolume;
	bool		bChangeVolume;
	int			setcursor;		//�ݒ荀�ڂ̃J�[�\���ʒu
	
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

