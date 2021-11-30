//#include "Game.h"
//
//CGame::CGame()
//{
//}
//
//CGame::~CGame()
//{
//}
//
//void CGame::Initialize()
//{
//	//リソース配置ディレクトリの設定
//	CUtilities::SetCurrentDirectory("Resource");
//
//	//プレイヤー素材の読み込み
//	g_Player.Load();
//
//	//ステージ素材の読み込み
//	g_Stage.Load();
//
//	//プレイヤーの状態初期化
//	g_Player.Initialize();
//
//	//ステージの状態初期化
//	g_Stage.Initialize(g_Stg1EnemyStart, g_Stg1EnemyCount);
//
//	for (int i = 0; i < ENEMY_COUNT; i++)
//	{
//		g_EnemyArray[i].Initialize();
//	}
//
//	return TRUE;
//}
//
//void CGame::Update()
//{
//キーの更新
//g_pInput->RefreshKey();
//
//ステージの更新
//g_Stage.Update(g_EnemyArray, ENEMY_COUNT);
//
//プレイヤーの更新
//g_Player.Update();
//
//敵の更新
//for (int i = 0; i < ENEMY_COUNT; i++)
//{
//	g_EnemyArray[i].Update();
//}
//
//if (!g_bclear && g_Stage.IsAllEnemy())
//{
//	敵が一体でも画面上に出ていればfalseに
//	bool btmp = true;
//	出現中のすべての敵に対して繰り返し
//	for (int i = 0; i < ENEMY_COUNT; i++)
//	{
//		敵が出ているかどうかの確認
//		if (g_EnemyArray[i].GetShow())
//		{
//			btmp = false;
//			敵が一体でもなので、2体目以降の出ている敵がいるかは問題にならない。
//			break;
//		}
//	}
//	敵が一体も出ていなければtrue,一体でも出ていればfalse
//	g_bclear = btmp;
//}
//
//デバッグ表示の切り替え
//if (g_pInput->IsKeyPush(MOFKEY_F1))
//{
//	g_bDebug = ((g_bDebug) ? false : true);
//}
//if (g_bDebug)
//{
//	if (g_pInput->IsKeyPush(MOFKEY_1))
//	{
//		for (int i = 0; i < ENEMY_COUNT; i++)
//		{
//			g_EnemyArray[i].Damage(5);
//		}
//	}
//}
//
//ゲームオーバー表示またはゲームクリアの時にEnterで初期値
//if (g_pInput->IsKeyPush(MOFKEY_RETURN) && (g_Player.IsDead() || g_bclear))
//{
//	g_bclear = false;
//	ゲーム内のオブジェクトを全て初期値
//	g_Player.Initialize();
//	g_Stage.Initialize(g_Stg1EnemyStart, g_Stg1EnemyCount);
//	for (int i = 0; i < ENEMY_COUNT; i++)
//	{
//		g_EnemyArray[i].Initialize();
//	}
//}
//}
//
//void CGame::Render()
//{
//}
//
//void CGame::Release()
//{
//}
