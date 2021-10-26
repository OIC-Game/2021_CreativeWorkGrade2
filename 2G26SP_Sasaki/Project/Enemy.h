#pragma once

#include	"Mof.h"
#include    "EnemyShot.h"

#define      ENEMYSHOT_COUNT   50
//敵１体分の情報を管理するクラス
class CEnemy {
private:
	CTexture*				m_pTexture;	//敵画像へのポインタ。実体はCStageで用意。
	float					m_PosX;		//ｘ座標
	float					m_PosY;		//ｙ座標
	float					m_SpeedX;	//ｘ方向の移動量
	float					m_SpeedY;	//ｙ方向の移動量
	bool					m_bShow;	//表示（出現）している場合はtrue
	int                     m_HP;       //敵のHP
	CEnemyShot              m_ShotArray[ENEMYSHOT_COUNT];
	int                     m_ShotWait;
	int                     m_ShotWaitSet;
	int						m_EnemyColor;

public:
	CEnemy();
	~CEnemy();
	void Initialize(void);				//初期化処理
	void Start(float px,float py);		//出現処理（px,pyの位置から出現させる）
	void Update(void);					//移動等の更新処理
	void Render(void);					//描画処理
	void RenderDebug(int i);			//デバッグ描画処理
	void SetTexture(CTexture* pt){ m_pTexture = pt; }	//画像の設定。必ず呼び出すこと！
	bool GetShow(void){ return m_bShow; }				//表示状態の取得

	CRectangle GetRect()
	{
		return CRectangle(m_PosX, m_PosY, m_PosX + m_pTexture->GetWidth(), m_PosY + m_pTexture->GetHeight());
	}

	//敵の色を返す
	int GetEnemyColor(void) { return m_EnemyColor; }

	void Damage(int dmg);

	void SetTexture(CTexture* pt, CTexture* st)
	{
		m_pTexture = pt;
		for (int i = 0; i < ENEMYSHOT_COUNT; i++) { m_ShotArray[i].SetTexture(st); }
	}
	//n番目の弾を取得（弾の参照を返す）
	CEnemyShot& GetShot(int n) { return m_ShotArray[n]; }
};