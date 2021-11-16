#include	"GameApp.h"
#include	"Game.h"
#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include"GameOver.h"
#include"Stage1.h"
//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;
//プレイヤー
CPlayer		g_Player;
//敵
#define		ENEMY_COUNT					20
CEnemy		g_EnemyArray[ENEMY_COUNT];
//ステージ
CStage		g_Stage;
//ステージクリアフラグ
bool		g_bClear = false;
//デバッグ表示フラグ
bool		g_bDebug = false;
CGame::CGame():
a(0)
{	
}
CGame::~CGame() {
}
bool CGame::Load(void)
{
	//プレイヤーの素材読み込み
	g_Player.Load();
	//ステージの素材読み込み
	g_Stage.Load();
	
	return true;
}
void CGame::Initialize(void)
{
	//プレイヤーの状態初期化
	g_Player.Initialize();
	//ステージの状態初期化
	g_Stage.Initialize(&g_Stg1EnemyStart, g_Stg1EnemyCount);
	//敵の初期化
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].Initialize();
	}
}

void CGame::Update(void)
{
	//ステージの更新
	g_Stage.Update(g_EnemyArray, ENEMY_COUNT);
	//プレイヤーの更新
	g_Player.Update();
	//敵の更新
	CRectangle prec = g_Player.GetRect();
	Vector2 cv = prec.GetCenter();
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].SetTargetPos(cv.x, cv.y);
		g_EnemyArray[i].Update();
	}
	//当たり判定の実行
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_Player.Collision(g_EnemyArray[i]);
	}
	//ゲームクリア判定
	if (!g_bClear && g_Stage.IsAllEnemy())
	{
		bool btmp = true;
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			if (g_EnemyArray[i].IsShow())
			{
				btmp = false;
			}
		}
		g_bClear = btmp;
	}
	//デバッグ表示の切り替え
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = ((g_bDebug) ? false : true);
	}
	//ゲームオーバー表示後にEnterで初期化を行う
	//ゲームクリア表示後もEnterで初期化を行う
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && (g_Player.IsDead() || g_bClear))
	{
		//クリアフラグを戻す
		g_bClear = false;
		//ゲーム内のオブジェクトを全て初期化する
		g_Player.Initialize();
		g_Stage.Initialize(&g_Stg1EnemyStart, g_Stg1EnemyCount);
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			g_EnemyArray[i].Initialize();
		}
	}if (g_pInput->GetGamePadCount())
	{
		LPGamePad pPad = g_pInput->GetGamePad(0);
		pPad->GetPadState();

		if (pPad != nullptr)
		{
			if (pPad->IsKeyPush(2) && (g_Player.IsDead() || g_bClear))
			{
				//クリアフラグを戻す
				g_bClear = false;
				//ゲーム内のオブジェクトを全て初期化する
				g_Player.Initialize();
				g_Stage.Initialize(&g_Stg1EnemyStart, g_Stg1EnemyCount);
				for (int i = 0; i < ENEMY_COUNT; i++)
				{
					g_EnemyArray[i].Initialize();
				}
			}
		}
	}
	//ゲームオーバー画面遷移
	if (!g_Player.IsDead() == false)
	{
			gChangeScene = SCENENO_GAMEOVER;
	}
	else if (g_bClear)
	{
		gChangeScene = SCENENO_GAMECLEAR;
	}
}

void CGame::Render(void)
{
	//ステージの描画
	g_Stage.Render();
	//プレイヤーの描画
	g_Player.Render();
	//敵の描画
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].Render();
	}

	//デバッグ表示をする場合
	if (g_bDebug)
	{
		//ステージのデバッグ描画
		g_Stage.RenderDebug();
		//プレイヤーのデバッグ描画
		g_Player.RenderDebug();
		//敵のデバッグ描画
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			g_EnemyArray[i].RenderDebug(i);
		}
	}

	/*/ゲームオーバー表示
	if (g_Player.IsDead())
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームオーバー　：　Enterキーでもう一度最初から");
	}*/
	//ゲームクリア表示
	/*else if (g_bClear)
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームクリア　：　Enterキーでもう一度最初から");
	}*/
}

void CGame::RenderDebug(void)
{
}

void CGame::Release(void)
{
	//プレイヤーの解放
	g_Player.Release();
	//ステージの解放
	g_Stage.Release();
}
