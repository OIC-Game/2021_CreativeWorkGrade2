#pragma once
#include "Mof.h"
class CSEManager
{
private:
	
	enum tag_BGM
	{
		Titel_BGM,
		Stage_BGM,
		GameOver_BGM,
		GameClear,

		BGMCOUNT,
	};
	CSoundBuffer   m_Sound[BGMCOUNT];
public:
	CSEManager();
	~CSEManager();
	bool Load();
	void Initalize();
	void Play(tag_BGM);
	void Release(void);
};

