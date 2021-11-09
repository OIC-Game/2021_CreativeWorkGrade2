#pragma once

#include	"Mof.h"
#include	"Enemy.h"
#include	"Boss.h"

//スクロール速度
#define		SCROLL_SPEED			1

//敵の出現情報構造体
typedef struct tag_ENEMYSTART {
	int						Count;
	float*					PosX;
	float*					Scroll;
	int                   *Type;
}ENEMYSTART;

/*typedef struct tag_BOSSSTART {
	int						Count;
	float*					PosX;
	float*					Scroll;
}BOSSSTART;*/

class CStage {
private:
	CTexture				m_Texture;
	float					m_Scroll;
	
	ENEMYSTART*				m_pEnemyStart;
	int						m_EnemyCount;
	CTexture				m_EnemyTexture;
	CTexture				m_EnemyShotTexture;

	int						m_EnemyNo;
public:
	CStage();
	~CStage();
	bool Load(void);
	void Initialize(ENEMYSTART* pSt, int cnt);
	void Update(CEnemy* ene,int ecnt);
	void Render(void);
	void RenderDebug(void);
	bool IsAllEnemy(void){ return m_EnemyNo >= m_pEnemyStart->Count; }
	void Release(void);
};