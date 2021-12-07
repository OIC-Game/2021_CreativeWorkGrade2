#pragma once
#include "SceneBase.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <array>

class CGame : public CSceneBase
{
private:
	float dropDTime = 0.0f;							//dropTime‚Ü‚Å”’l‚ª‘‚¦‚ê‚Î—‰ºˆ—
	float obstacleDTime = 0.0f;
	float obstacleCreateTime = 10.0f;
	CSoundBuffer gSound[2];

	float aiControllTime = 0.0f;
public:
	CGame();
	~CGame();
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);

};

