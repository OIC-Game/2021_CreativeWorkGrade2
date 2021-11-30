#include "GameDefine.h"
#include "Game.h"


//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;





CGame::CGame() {
}


CGame::~CGame() {
}


bool CGame::Load(void) {

	//プレイヤー素材読み込み
	m_Player.Load();


	//ステージの素材読み込み
	m_Stage.Load("Stage1.txt");

	
	
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	return true;

	}


void CGame::Initialize(void) {

	bool HedColflg = false;

	m_Player.Initialize();

	m_Stage.Initialize(m_EnemyArray);

	//ステージの状態初期化
	m_Stage.Initialize(m_EnemyArray);

	GameBGM.Load("FantasyBGM.mp3");

	GameBGM.SetLoop(TRUE);
	GameBGM.Play();
		

}

void CGame::Update(void) {
	
	//プレイヤーの移動処理
	m_Player.Update();


	//ステージとプレイヤーの当たり判定
	float ox = 0, oy = 0;
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}	

	//敵の更新
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}

		m_EnemyArray[i].Update();

		float ox = 0, oy = 0;


		for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
		{
			//敵の頭との接触時
			if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
			{
				m_EnemyArray[i].CollisionStage(ox, oy);
			}

			/*//敵の体との接触時
			if (m_Player.CollisionEnemyBody(m_EnemyArray[i]))
			{
				m_Player.Damage();
			}*/
		}


		//
		if (m_Player.CollisionEnemyHed(m_EnemyArray[i]))
		{

			m_Player.CollisionJump();

			m_EnemyArray[i].Damage();
		}

	}


	//ステージのスクロール処理
	m_Stage.Update(m_Player);

	//F2キーでゲームクリア画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		gChangeScene = SCENENO_GAMECLEAR;
		GameBGM.Stop();
	}
	//F3キーでゲームオーバー画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		gChangeScene = SCENENO_GAMEOVER;
		GameBGM.Stop();
	}

	//穴に落ちたらゲームオーバー画面へ
	if (m_Player.GetPosY()>g_pGraphics->GetTargetHeight())
	{
		gChangeScene = SCENENO_GAMEOVER;
		GameBGM.Stop();
	}

	CRectangle e_Rect = m_EnemyArray->GetRect();
	CRectangle p_Rect = m_Player.GetRect();

	
	int PLayerLife = m_Player.GetLife();

	if (PLayerLife == 0)
	{
		gChangeScene = SCENENO_GAMEOVER;
	}

	

}

void CGame::Render(void) {
	m_Stage.Render();
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());


	//敵の描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
}

void CGame::RenderDebug(void)
{

	//ステージのデバッグ描画
	m_Stage.RenderDebug();

	m_Player.renderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());

	//敵のデバッグ描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
}

void CGame::Release(void) {
	//テクスチャの解放
	m_Stage.Release();
	m_Player.Release();
	GameBGM.Release();

	//敵の開放
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}


}








