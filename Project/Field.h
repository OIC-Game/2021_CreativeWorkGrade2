#pragma once
#include "Mof.h"
#include "Puyo.h"

class CField
{
private:
	CSoundBuffer gSound[5];
	CRandom random;

	CPuyo mainField[6][13];

	//int field[6][13];						//主配列　画面描写/ぷよ保持用
	int altField[6][13];					//副配列　連結数計算に使用
	int drop[2][3];							//操作中のぷよの座標・色を保持
	int next[2][2];							//２個先までのぷよの色を保持
	int stock[2];							//ストック中のぷよの色を保持

	int link = 0;							//連結数
	int combo = 0;							//連鎖数
	bool isDropOnce = false;				//落下加速を次ぷよに持ち越させない
	bool isFirst = true;					//同時消しで連鎖数を増やさない
	int obstacle = 0;						//おじゃまぷよのストック数
	int shuffle[6] = { 0,1,2,3,4,5 };

	int score = 0;									//得点

	MofU32 color[6] =
	{
		MOF_XRGB(220,35,45),	//red
		MOF_XRGB(12,215,72) ,	//green
		MOF_XRGB(24,150,230) ,	//blue
		MOF_XRGB(220,205,5) ,	//yellow
		MOF_XRGB(144,6,170) ,	//purple
		MOF_XRGB(108,110,135)	//gray
	};

	float dropTime = 2.0f;							//落下周期
	int accelNum = 1500;							//dropTimeが減るスコアの倍数(数値*10で最高速)

	float obstacleTime = 10.0f;						//おじゃまぷよの生成周期
	int obstacleAmount = 2;							//生成数

	int nowState;
	float stopCnt = 0;
	float waitTime = 0;
	int invCnt = 0;
	bool isInv = false;


	//int deletePuyo[5] = { 0 };
	//float buffTime[5] = { 0 };
	//float checkTime = 30.0f;

	//int specialMove = 0;

public:
	enum tag_State { eDrop, eFall, eDelete, eBanish, eSet, eGameover };

	void Initialize();
	void Render();
	void Release();

	void Right();
	void Left();
	void Down();
	void RRotate();
	void LRotate();
	void Stock();

	bool CheckDelete(bool isCheck);
	void LinkManipulation(int x, int y, bool isMain);
	void ObstacleDelete(int x, int y);
	void CheckHollow();

	void Set(int x, int y, int c);

	void AddPuyo();
	void SpeedCheck();
	bool CheckStop();
	bool CheckBottom(int x, int y);
	void Wait();


	bool CheckGameOver() { return !mainField[2][1].GetIsHide(); }
	bool CheckObstacle() { return obstacle > 0; }

	bool GetDropOnce() { return isDropOnce; }
	void SetDropOnce(bool a) { isDropOnce = a; }
	float GetDropTime() { return dropTime; }
	int GetNowState() { return nowState; }
	void SetObstacle();
	void AddObstacle(int num) { obstacle += num; }
	float GetObstacleTime() { return obstacleTime; }
	int GetObstacleAmount() { return obstacleAmount; }
	int GetScore() { return score; }
	void Banish();
};
