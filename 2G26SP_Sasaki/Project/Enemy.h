#pragma once

#include	"Mof.h"
#include    "EnemyShot.h"

#define		ENEMY_MOVESPEED		1

#define		ENEMYSHOT_TYPE		2
//敵の射撃本数
#define		ENEMYSHOT_LINE		20
#define     ENEMYSHOT_COUNT		80

#define		ENEMY_DEADALPHA		0
#define		ENEMY_DEADALPHASPEED		40

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
	CEnemyShot              m_ShotArray[ENEMYSHOT_TYPE][ENEMYSHOT_LINE][ENEMYSHOT_COUNT];
	int                     m_ShotWait;
	int                     m_ShotWaitSet;
	int						m_EnemyColor;
	int						m_EnemyShotColor;
	int						m_EnemyType;

	int						Secondcount;
	int						freeSecond;
	int						second;
	bool					m_bStart;

	BYTE					m_Alpha;

	float					ShotScaleX;
	float					ShotScaleY;

public:
	CEnemy();
	~CEnemy();
	void Initialize(void);				//初期化処理
	void Start(float px,float py,int encol,int type,int hp);		//出現処理（px,pyの位置から出現させる）
	void Update(void);					//移動等の更新処理
	void Render(void);					//描画処理
	void RenderDebug(int i);			//デバッグ描画処理
	void SetTexture(CTexture* pt){ m_pTexture = pt; }	//画像の設定。必ず呼び出すこと！
	bool GetShow(void){ return m_bShow; }				//表示状態の取得
	int	 GetEnemyType(void) { return m_EnemyType; }
	void EnemyDead();
	void EnemyDeadAlpha() { m_Alpha = 0; }

	CRectangle GetRect()
	{
		return CRectangle(m_PosX, m_PosY, m_PosX + m_pTexture->GetWidth(), m_PosY + m_pTexture->GetHeight());
	}

	//敵の色を返す
	int GetEnemyColor(void) { return m_EnemyColor; }
	int GetEnemyShotColor(void) { return m_EnemyShotColor; }

	void Damage(int dmg);

	void SetTexture(CTexture* pt, CTexture* st, CTexture* st2)
	{
		m_pTexture = pt;
		for (int t = 0; t < ENEMYSHOT_TYPE; t++)
		{
			for (int i = 0; i < ENEMYSHOT_LINE; i++)
			{
				for (int j = 0; j < ENEMYSHOT_COUNT; j++)
				{
					if(t==0)
						m_ShotArray[t][i][j].SetTexture(st);
					if(t ==1)
						m_ShotArray[1][i][j].SetTexture(st2);
				}
			}
		}
	}

	//n番目の弾を取得（弾の参照を返す）
	CEnemyShot& GetShot(int t,int n,int m) { return m_ShotArray[t][n][m]; }

	//真下
	void NomalEnemyMove();
	//止まって動く
	void StopAndStartMove();
	//斜め右移動
	void SlantMove(bool left);
	//回転
	void HardEnemyMove(bool left);
	//ボス黒左
	void BossMoveBlackLeft();
	//ボス黒右
	void BossMoveBlackRight();
	//ボス白
	void BossMoveWhite();
	//死なない出現
	void ShowMove();

	
	void ShotSelect(int j);


	//真下
	void DownBullet(int j);

	void SlantRightBullet1(int j);
	void SlantRightBullet2(int j);
	void SlantRightBullet3(int j);
	void SlantRightBullet4(int j);
	void SlantRightBullet5(int j);
	void SlantRightBullet6(int j);

	void SlowBullet(int j);
	
	void SlantLeftBullet1(int j);
	void SlantLeftBullet2(int j);
	void SlantLeftBullet3(int j);
	void SlantLeftBullet4(int j);
	void SlantLeftBullet5(int j);
	void SlantLeftBullet6(int j);
	
	//右
	void RightBullet(int j);
	//左
	void LeftBullet(int j);

	void WallBullet(int j);
};