#pragma once

#include "Mof.h"
#include "Enemy.h"

//スクロール速度
#define		SCROLL_SPEED	1

//敵の出現情報の構造体
typedef struct tag_ENEMYSTART
{
	float PosX;
	float Scroll;
	int	  Color;
}ENEMYSTART;

class CStage
{
private:
	CTexture	m_Texture;		//背景画像の変数
	float		m_Scroll;		//スクロール量
	ENEMYSTART*  m_pEnemyStart;
	int         m_EnemyCount;
	CTexture    m_EnemyTexture;
	CTexture    m_EnemyTextureWhite;
	int         m_EnemyNo;
	int			m_EnemyShotColor;
	CTexture    m_EnemyShotTexture;

public:
	CStage();
	~CStage();
	bool Load();						//リソースの読み込み
	void Initialize(ENEMYSTART* pSt,int cnt);					//パラメタ等の初期化
	void Update(CEnemy* ene,int ecnt);						//更新処理
	void Render();						//描画処理
	void Release();						//リソース等の解放処理
	void RenderDebug(void);
	bool IsAllEnemy(void) { return m_EnemyNo >= m_EnemyCount; }
	int  EnemyShotColorBack(){ return m_EnemyShotColor; }
};

