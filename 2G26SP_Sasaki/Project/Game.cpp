#include "Game.h"
#include    "Stage1.h"
#include    "GameApp.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;

//ステージ
CStage     g_Stage;

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Load()
{
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	zButtonBlack.Load("ZButtonBlack.png");
	zButtonWhite.Load("ZButtonWhite.png");
	zChangeCircleBlack.Load("ChangeCircleBlack.png");
	zChangeCircleWhite.Load("ChangeCircleWhite.png");
		
	//プレイヤー素材の読み込み
	g_Player.Load();

	//ステージ素材の読み込み
	g_Stage.Load();
}

void CGame::Initialize(void) {

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
	g_bclear = false;

	cnt = 0;
	//デバック用
	//ステージのスクロール値
	//g_Stage.MoveScroll(4800);
}

void CGame::Update(void) {
	if (g_pInput->IsKeyHold(MOFKEY_0))
	{
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			g_EnemyArray[i].EnemyDead();
		}

	}
	//キーの更新
	g_pInput->RefreshKey();

	//ステージの更新
	g_Stage.Update(g_EnemyArray, ENEMY_COUNT);

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
			if (g_EnemyArray[i].GetShow() && g_EnemyArray[i].GetEnemyType() != 8 && g_EnemyArray[i].GetEnemyType() != 9)
			{
				btmp = false;
				//敵が一体でもなので、2体目以降の出ている敵がいるかは問題にならない。
				break;
			}
		}
		//敵が一体も出ていなければtrue,一体でも出ていればfalse
		g_bclear = btmp;

		//ステージクリアすると敵がすべて死ぬ
		if (g_bclear)
		{
			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				g_EnemyArray[i].EnemyDead();
			}
		}
	}

	//ゲームオーバー表示またはゲームクリアの時にEnterで初期値
	if(g_Player.IsDead())
	{
		cnt++;
		if (cnt > 70)
		{
			gChangeScene = SCENENO_GAMEOVER;
			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				g_EnemyArray[i].EnemyDead();
				g_EnemyArray[i].EnemyDeadAlpha();
			}
		}
	}

	if (g_bclear)
	{
		cnt++;
		if (cnt > 70)
			gChangeScene = SCENENO_GAMECLEAR;
	}

}

void CGame::Render(void) {
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

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
		zButtonBlack.Render(g_pGraphics->GetTargetWidth() - zButtonBlack.GetWidth(), g_pGraphics->GetTargetHeight() - zButtonBlack.GetHeight());
		zChangeCircleBlack.RenderRotate(g_pGraphics->GetTargetWidth() - zChangeCircleBlack.GetWidth(), g_pGraphics->GetTargetHeight() - zChangeCircleBlack.GetHeight(),0);
	}
	else
	{
		zButtonWhite.Render(g_pGraphics->GetTargetWidth() - zButtonWhite.GetWidth(), g_pGraphics->GetTargetHeight() - zButtonWhite.GetHeight());
		zChangeCircleWhite.RenderRotate(g_pGraphics->GetTargetWidth() - zChangeCircleWhite.GetWidth(), g_pGraphics->GetTargetHeight() - zChangeCircleWhite.GetHeight(), 0);
	}

	/*if (g_pInput->IsKeyPush(MOFKEY_E))
	{
		if (!g_EnemyArray[0].GetShow())
		{
			g_EnemyArray[0].SetTexture(&m_EnemyTexture);
			g_EnemyArray[0].Start(100, 100);
		}
	}*/

	//当たり判定の実行
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		g_Player.Collision(g_EnemyArray[i]);
	}

	//if (g_Player.IsDead())
	//{
	//	CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームオーバー  :  Enterキーでもう一度最初から");
	//}
	//else if (g_bclear)
	//{
	//	CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームクリア: ENTERキーでもう一度最初から");
	//}


	//描画の終了
	g_pGraphics->RenderEnd();
}

void CGame::Release(void) {

	zButtonBlack.Release();
	zButtonWhite.Release();
	zChangeCircleBlack.Release();
	zChangeCircleWhite.Release();
	//プレイヤーの解放
	g_Player.Release();

	//ステージの解放
	g_Stage.Release();

	//m_EnemyTexture.Release();
}