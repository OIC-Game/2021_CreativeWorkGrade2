#include	"GameDefine.h"
#include	"Game.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int						gChangeScene;

/**
 * コンストラクタ
 *
 */
CGame::CGame(){
}

/**
 * デストラクタ
 *
 */
CGame::~CGame(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGame::Load(void){
	//プレイヤーの素材読み込み
	m_Player.Load();
	//ステージの素材読み込み
	m_Stage.Load("Stage1.txt");
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//アイテムメモリ確保
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//エフェクトの素材
	m_EffectManager.Load();
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGame::Initialize(void){
	//プレーヤーの状態初期化
	m_Player.Initialize();
	//ステージの状態初期化
	m_Stage.Initialize(m_EnemyArray,m_ItemArray);
	//エフェクト状態の初期化
	m_EffectManager.Initialize();
	//プレイヤーと敵にエフェクトクラスの設定
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}

}

/**
 * 更新
 *
 */
void CGame::Update(void){
	//デバッグ用
	//プレーヤーの更新
	m_Player.Update();
	//ステージとプレーヤーの当たり判定
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
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
	}
	//アイテムの更新
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy))
		{
			m_ItemArray[i].CollisionStage(ox, oy);
		}
	}
	//当たり判定の実行
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_Player.CollisionItem(m_ItemArray[i]);
	}
	//ステージの更新
	m_Stage.Update(m_Player);
	//F2Keyでゲームクリア画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		gChangeScene = SCENENO_GAMECLEAR;
	}
	//F3キーでゲームオーバー画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		gChangeScene = SCENENO_GAMEOVER;
	}
}

/**
 * 描画
 *
 */
void CGame::Render(void){
	//ステージの描画
	m_Stage.Render();
	//エフェクトの更新
	m_EffectManager.Update();
	//プレーヤーの描画
	m_Player.Render(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	//敵の描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//アイテムの描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//プレーヤーの状態描画
	m_Player.RenderStatus();
	//エフェクトの描画
	m_EffectManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	CGraphicsUtilities::RenderString(10,10,"ゲーム画面");
	CGraphicsUtilities::RenderString(10,40,"F2キーでゲームクリア、F3キーでゲームオーバー");
}

/**
 * デバッグ描画
 *
 */
void CGame::RenderDebug(void){
	//ステージのデバッグ描画
	m_Stage.RenderDebug();
	//プレーヤーのデバッグ描画
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//敵のデバッグ画面
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//アイテムのデバッグ画面
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//エフェクトのデバッグ描画
	m_EffectManager.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

/**
 * 解放
 *
 */
void CGame::Release(void){
	//ステージの解放
	m_Stage.Release();
	//プレーヤーの解放
	m_Player.Release();
	//敵の解放
	if (m_EnemyArray)
	{
		delete[]m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//アイテムの解放
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//エフェクトの解放
	m_EffectManager.Release();
}