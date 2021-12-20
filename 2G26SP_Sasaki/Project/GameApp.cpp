/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include    "Player.h"
#include    "Stage.h"
#include    "Enemy.h"
#include    "Stage1.h"

//プレイヤー
CPlayer     g_Player;

//ステージ
CStage     g_Stage;

#define ENEMY_COUNT 40
//CTexture m_EnemyTexture;
CEnemy   g_EnemyArray[ENEMY_COUNT];

bool g_bclear = false;

//デバッグ表示フラグ
bool g_bDebug = false;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");
	
	//プレイヤー素材の読み込み
	g_Player.Load();
	
	//ステージ素材の読み込み
	g_Stage.Load();
	
	//敵素材の読み込み
	/*if (!m_EnemyTexture.Load("Enemy1.png"))
	{
		return FALSE;
	}*/

	//プレイヤーの状態初期化
	g_Player.Initialize();
	
	//ステージの状態初期化
	g_Stage.Initialize(g_Stg1EnemyStart, g_Stg1EnemyCount);
	
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].Initialize();
	}

	//デバック用
	//ステージのスクロール値
	g_Stage.MoveScroll(1600);

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();
	
	//ステージの更新
	g_Stage.Update(g_EnemyArray,ENEMY_COUNT);
	
	//プレイヤーの更新
	g_Player.Update();
	
	//敵の更新
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].Update();
	}

	if (!g_bclear && g_Stage.IsAllEnemy())
	{
		//敵が一体でも画面上に出ていればfalseに
		bool btmp = true;
		//出現中のすべての敵に対して繰り返し
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			//敵が出ているかどうかの確認
			if (g_EnemyArray[i].GetShow())
			{
				btmp = false;
				//敵が一体でもなので、2体目以降の出ている敵がいるかは問題にならない。
				break;
			}
		}
		//敵が一体も出ていなければtrue,一体でも出ていればfalse
		g_bclear = btmp;
	}

	//デバッグ表示の切り替え
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = ((g_bDebug) ? false : true);
	}
	if (g_bDebug)
	{
		if (g_pInput->IsKeyPush(MOFKEY_1))
		{
			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				g_EnemyArray[i].Damage(5);
			}
		}
	}
	
	//ゲームオーバー表示またはゲームクリアの時にEnterで初期値
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && (g_Player.IsDead()||g_bclear))
	{
		g_bclear = false;
		//ゲーム内のオブジェクトを全て初期値
		g_Player.Initialize();
		g_Stage.Initialize( g_Stg1EnemyStart, g_Stg1EnemyCount);
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			g_EnemyArray[i].Initialize();
		}
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);
	
	//ステージの描画
	g_Stage.Render();
	
	//プレイヤーの描画
	g_Player.Render();

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_EnemyArray[i].Render();
	}
	
	if (g_Player.IsPlayerColor() == 1)
	{
		CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_BLACK, "Zキーで色変換");
	}
	else
	{
		CGraphicsUtilities::RenderString(0, 0, MOF_COLOR_WHITE, "Zキーで色変換");
	}

	/*if (g_pInput->IsKeyPush(MOFKEY_E))
	{
		if (!g_EnemyArray[0].GetShow())
		{
			g_EnemyArray[0].SetTexture(&m_EnemyTexture);
			g_EnemyArray[0].Start(100, 100);
		}
	}*/
	
	
	//デバッグ表示をする場合の処理
	if (g_bDebug)
	{
		g_Stage.RenderDebug();
		g_Player.RenderDebug();
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			g_EnemyArray[i].RenderDebug(i);
		}
	}

	//当たり判定の実行
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_Player.Collision(g_EnemyArray[i]);
	}
	
	if (g_Player.IsDead())
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームオーバー  :  Enterキーでもう一度最初から");
	}
	else if (g_bclear)
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームクリア: ENTERキーでもう一度最初から");
	}


	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void){
	//プレイヤーの解放
	g_Player.Release();
	
	//ステージの解放
	g_Stage.Release();
	
	//m_EnemyTexture.Release();

	return TRUE;
}