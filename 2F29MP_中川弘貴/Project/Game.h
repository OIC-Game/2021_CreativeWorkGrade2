#pragma once
#include	"GameApp.h"
#include	"Player.h"

class CGame {
private:
	CPlayer pl;
	CPlayer ai;
public:
	CGame();
	~CGame();
	void Load();
	void Initialize(bool vsAiFlg);
	void Update(bool vsAiFlg);
	void Render(bool vsAiFlg);
	void Release();
};