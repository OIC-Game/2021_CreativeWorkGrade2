#include "Game.h"
#include "GameDefine.h"

//変更するシーン
extern int						gChangeScene;

int								gStage = STAGENO_01;
CGame::CGame(){
}

CGame::~CGame(){
}

bool CGame::Load(void){
	//プレイヤー素材の読み込み
	m_Player.Load();
	//ステージの素材読み込み
	switch (gStage)
	{
		case STAGENO_01:
		m_Stage.Load("Stage03.txt");
		break;
		case STAGENO_02:
		m_Stage.Load("Stage02.txt");
		break;
	}
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//アイテムメモリ確保
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//ポップアイテムの素材読み込み
	m_PoPItemManager.Load();
	//UIの素材読み込み
	m_UI.Load();
	return true;
}

void CGame::Initialize(void){
	//プレイヤーの状態初期化
	m_Player.Initialize();
	//ステージの状態初期化
	switch (gStage)
	{
		case STAGENO_01:
			m_Stage.Initialize("Stage03.txt", m_EnemyArray, m_ItemArray);
			break;
		case STAGENO_02:
			m_Stage.Initialize("Stage02.txt", m_EnemyArray, m_ItemArray);
			break;
	}
	m_PoPItemManager.Initialize();
	m_Stage.SetPoPItemManager(&m_PoPItemManager);
}

void CGame::Update(void){
	//プレイヤーの更新
	m_Player.Update(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//ステージとプレイヤーの当たり判定
	float ox = 0, oy = 0;
	int popItemNo = 0;
	if (m_Stage.Collision(m_Player.GetRect(),m_Player, ox, oy,popItemNo))
	{
		m_Player.CollisionStage(ox, oy);
		for (int i = 0; i < m_Stage.GetItemCount(); i++)
		{
			m_ItemArray[i].PoPItem(popItemNo);
		}
	}
	//敵の更新
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update(m_Stage.GetScrollX(), m_Stage.GetScrollY());
		float ox = 0, oy = 0;
		int popItemNo = 0;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), m_Player, ox, oy,popItemNo))
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
		int PopItemNo = 0;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), m_Player, ox, oy,popItemNo))
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
	//ポップアイテムの更新
	m_PoPItemManager.Update();

	//プレイヤーのフラグでリトライ画面、ゲームオーバー画面へ
	if (m_Player.IsDead())
	{
		if (m_Player.Retry())
		{
			gChangeScene = SCENENO_GAMERETRY;
		}
		else if(!m_Player.Retry())
		{
			gChangeScene = SCENENO_GAMEOVER;
		}
	}
	//ゴールフラグでクリア画面に
	if (m_Player.IsClear())
	{
		if (!gStage == STAGENO_02)
		{
			gStage++;
			gChangeScene = SCENENO_GAMERETRY;
		}
		else
		{
			gChangeScene = SCENENO_GAMECLEAR;
		}
	}
}

void CGame::Render(void){
	//ステージの描画
	m_Stage.Render();
	//プレイヤーの描画
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
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
	//ポップアイテムの描画
	m_PoPItemManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//UIの描画
	m_UI.Render();
}

void CGame::RenderDebug(void){
	//ステージのデバッグ描画
	m_Stage.RenderDebug();
	//プレイヤーのデバッグ描画
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//敵のデバッグ描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//アイテムのデバッグ描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//ポップアイテムのデバッグ描画
	m_PoPItemManager.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

void CGame::Release(void){
	//ステージの解放
	m_Stage.Release();
	//プレイヤーの解放
	m_Player.Release();
	//敵の解放
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//アイテムの解放
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//ポップアイテムの解放
	m_PoPItemManager.Release();
	//UIの解放
	m_UI.Release();
}

