#pragma once
#include "SceneBase.h"

class CGame : public CSceneBase
{
private:
	float dropDTime = 0.0f;							//dropTime�܂Ő��l��������Η�������
	float obstacleDTime = 0.0f;
	float obstacleCreateTime = 10.0f;
	CSoundBuffer gSound[2];
public:
	CGame();
	~CGame();
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);

};

