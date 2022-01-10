#include	"GameApp.h"
#include	"Game.h"
#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"

extern int	stage_number;
//変更するシーン(外部参照、実体はGameApp.cpp)

//プレイヤー残機(外部参照、実体はInfomation.cpp)
extern int						player_Life;

//スコア
int						score = 0;
int						getScore = 0;
bool					scoreDisplayFlg = false;
int						scoreDesplayTime = 0;
bool					player1UpDisplayFlg = false;
extern int				enemyDeadCount;
int						getCoinCount = 0;
extern bool				bossWarpFlg;



CPlayer		g_Player;
CStage		g_Stage;

 

/**
 * コンストラクタ
 *
 */
CGame::CGame():
m_EnemyArray(NULL),
m_ItemArray(NULL),
game_BGM(),
game_LAST_BGM(),
game_BOSS_BGM(),
game_GameOverSE(),
game_GameClearSE(),
game_playSoundFlg(false),
game_playBGMFlg(false),
game_Time(0.0f),
game_TimeWait(0.0f),
game_ScoreFlg(false),
game_ScoreDesplayFlg(false),
game_tempPlayerPositionX(0),
game_tempPlayerPositionY(0),
game_NowStage(0),
game_playMarioSEFlg(false),
game_MarioDeadSE(),
game_ab(false)

{
}

/**
 * デストラクタ
 *
 */
CGame::~CGame() {
}

bool CGame::Load(void)
{
	//プレイヤーロード
	g_Player.Load();
	//ステージロード
	switch (m_StageNumber)
	{
	case STAGE_1_1:
	{
		if (!game_BGM.Load("BGM.mp3"))
		{
			return false;
		}
		g_Stage.Load("Stage1.txt");
		break;
	}
	case STAGE_2_1:
	{
		if (!game_BGM.Load("BGM2.mp3"))
		{
			return false;
		}
		g_Stage.Load("Stage2.txt");
		break;
	}
	case STAGE_3_1:
	{
		if (!game_BGM.Load("BGM.mp3"))
		{
			return false;
		}
		g_Stage.Load("Stage3.txt");
		break;
	}
	case STAGE_LAST:
	{
		g_Stage.Load("Stage_Boss.txt");
		if (!game_LAST_BGM.Load("LAST_BGM.mp3"))
		{
			return false;
		}
		if (!game_BOSS_BGM.Load("BOSS_BGM.mp3"))
		{
			return false;
		}
		break;
	}
	default:
		if (!game_BGM.Load("BGM.mp3"))
		{
			return false;
		}
		break;
	}
	


	//BGMロード
	
	
	
	//ゲームオーバーSEロード
	if (!game_GameOverSE.Load("GameOver.mp3"))
	{
		return false;
	}
	//ゲームクリアSEロード
	if (!game_GameClearSE.Load("GameClear.wav"))
	{
		return false;
	}
	if (!game_MarioDeadSE.Load("MarioDead.mp3"))
	{
		return false;
	}
	if (!game_BossClearSE.Load("BossClear.wav"))
	{
		return false;
	}

	//敵メモリ確保
	m_EnemyArray = new CEnemy[g_Stage.GetEnemyCount()];
	//アイテムメモリ確保
	m_ItemArray = new CItem[g_Stage.GetItemCount()];

	game_EffectManager.Load();

	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGame::Initialize(void) {
	
	//プレイヤー初期化
	switch (m_StageNumber)
	{
	case STAGE_1_1:
	{
		game_StageState = STAGESTATE_GROUND;
		game_PlayerInitializePosition = Vector2(100, 700);
		break;
	}
	case STAGE_2_1:
	{
		game_StageState = STAGESTATE_WATER;
		game_PlayerInitializePosition = Vector2(50, 150);
		//game_PlayerInitializePosition = Vector2(6100, 450);
		break;
	}
	case STAGE_3_1:
	{
		game_StageState = STAGESTATE_SKY;
		game_PlayerInitializePosition = Vector2(140, 420);
		break;
	}
	case STAGE_LAST:
	{
		game_StageState = STAGESTATE_GROUND;
		game_PlayerInitializePosition = Vector2(100, 600);
		break;
	}
	default:
		game_StageState = STAGESTATE_GROUND;
		game_PlayerInitializePosition = Vector2(100, 600);
		break;
	}
	if (m_StageNumber != STAGE_LAST)
	{
		bossWarpFlg = false;
	}
	g_Player.Initialize(game_PlayerInitializePosition, game_StageState);
	//ステージ初期化
	g_Stage.Initialize(m_EnemyArray,m_ItemArray, game_StageState);
	
	game_NowStage = m_StageNumber;
	//BGM再生
	switch (game_NowStage)
	{
		case STAGE_1_1:
		{
			game_BGM.SetLoop(TRUE);
			game_BGM.Play();
			break;
		}
		case STAGE_LAST:
		{
			game_LAST_BGM.SetLoop(TRUE);
			game_LAST_BGM.Play();
			break;
		}
		default:
		{
			game_BGM.SetLoop(TRUE);
			game_BGM.Play();
			break;
		}

	}
	game_playSoundFlg = false;
	game_playBGMFlg = false;
	switch (game_NowStage)
	{
	case STAGE_1_1:
	{
		game_Time = GAME_TIMELIMIT;
		break;
	}
	case STAGE_LAST:
	{
		game_Time = GAME_TIMELIMIT_BOSS;
		break;
	}
	default:
		game_Time = GAME_TIMELIMIT;
		break;
	}
	game_TimeWait = 0.0f;
	game_ScoreFlg = false;
	game_tempPlayerPositionX = 0.0f;
	game_tempPlayerPositionY = 0.0f;
	game_playMarioSEFlg = false;
	game_ab = false;
	game_EffectManager.Initialize();
	for (int i = 0; i < g_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].SetEffectManager(&game_EffectManager);
	}

}

/**
 * 更新
 *
 */
void CGame::Update(void) {
	//プレイヤー更新
	g_Player.Update();
	//ステージとプレイヤーの当たり判定
	float ox = 0, oy = 0;
	bool og = false;
	bool enemyDead = false;
	bool jumpFlg = false;
	bool scoreFlg = false;
	bool magmaDead = false;
	if (g_Stage.Collision(g_Player.GetRectPlayer(), ox, oy, og,enemyDead,jumpFlg,g_Player,magmaDead))
	{
		if (magmaDead)
		{
			g_Player.Setplayer_DeadFlg(true);
		}
		g_Player.CollisionStage(ox, oy);
	}
	g_Player.FallCheck(og);

	//ステージの更新
	g_Stage.Update(g_Player);


	if (g_Player.GetTmpWorpFlg() == true && !game_playBGMFlg)
	{
		if (game_LAST_BGM.IsPlay())
		{
			game_LAST_BGM.Stop();
		}
		game_BOSS_BGM.SetLoop(TRUE);
		game_BOSS_BGM.Play();
		game_playBGMFlg = true;
	}
	
	//敵の更新
	for (int i = 0; i < g_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		//プレイヤーサイズが変化中の時動かなくする
		if (g_Player.Getplayer_ChangeWaitFlg())
		{
			return;
		}
		if (m_EnemyArray[i].GetType() == ENEMY_MARIO)
		{



			if (!game_playSoundFlg && m_EnemyArray[i].GetMarioDeadFlg())
			{
				game_BOSS_BGM.Stop();
				game_MarioDeadSE.Play();
				game_playSoundFlg = true;
			}
			if (m_EnemyArray[i].GetEnemyDead())
			{
				g_Player.SetMarioDead(true);
			}

		}
			m_EnemyArray[i].Update(g_Stage.GetScrollX(), g_Stage.GetScrollY());
			ox = 0, oy = 0;
			enemyDead = false;
			jumpFlg = false;
			magmaDead = false;
			//敵[i]の死亡フラグがfalseの時
			if (!m_EnemyArray[i].GetEnemyDead())
			{
				if (m_EnemyArray[i].GetType() == ENEMY_MAGURO || m_EnemyArray[i].GetType() == ENEMY_IKA || m_EnemyArray[i].GetType() == ENEMY_KAZIKI)
				{
					continue;
				}
				if (g_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy, og, enemyDead, jumpFlg, g_Player, magmaDead))
				{
					if (magmaDead)
					{
						m_EnemyArray[i].Dead(magmaDead);
						m_EnemyArray[i].DeadJump(true);
					}
						m_EnemyArray[i].CollisionStage(ox, oy);
					
					if (jumpFlg && !g_Player.Getplayer_BigFlg())
					{
						m_EnemyArray[i].BlockJump(jumpFlg);
					}
					else if (jumpFlg && g_Player.Getplayer_BigFlg())
					{
						//ブロック越しに倒されたとき
						if (enemyDead)
						{
							//スコア加算
							score += SCORE_ENEMYSTEP;
							getScore = SCORE_ENEMYSTEP;
							scoreDisplayFlg = true;
							scoreDesplayTime = SCORE_DISPLAYTIME;
							m_EnemyArray[i].Dead(enemyDead);
						}
						m_EnemyArray[i].DeadJump(jumpFlg);
					}
				}
				if (m_EnemyArray[i].GetType() == ENEMY_MARIO )
				{
					for (int j = 0; j < ENEMYSHOT_COUNT; j++)
					{
						if (!m_EnemyArray[i].GetShotShow(j))
						{
							continue;
						}
						if (g_Stage.Collision(m_EnemyArray[i].GetShotRect(j), ox, oy, og, enemyDead, jumpFlg, g_Player, magmaDead))
						{
							m_EnemyArray[i].ShotCollisionStage(ox, oy, j);
						}
					}
					
				}
			}
		

	}
	//アイテムの更新
	for (int i = 0; i < g_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		//プレイヤーサイズが変化中の時動かなくする
		if (g_Player.Getplayer_ChangeWaitFlg())
		{
			return;
		}
		if (m_ItemArray[i].GetType() == ITEM_BIG_MAGURO && g_Player.GetPlayerMaguroFly())
		{
			m_ItemArray[i].SetMaguroFly(g_Player.GetPlayerMaguroFly());
		}
		m_ItemArray[i].Update(g_Stage.GetScrollX(), g_Stage.GetScrollY());
		if (m_ItemArray[i].GetType() == ITEM_BIG_MAGURO && m_ItemArray[i].GetMaguroExplosion() && !m_ItemArray[i].GetShow())
		{
			g_Stage.ExplotionCastle();
		}
		float ox = 0, oy = 0;
		jumpFlg = false;
		magmaDead = false;
		if (m_ItemArray[i].GetType() == ITEM_FOAM_COIN || m_ItemArray[i].GetType() == ITEM_FOAM_MUSH || m_ItemArray[i].GetType() == ITEM_BIG_MAGURO)
		{
			continue;
		}
		
		if (g_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy,og,enemyDead,jumpFlg,g_Player,magmaDead))
		{
			if (magmaDead)
			{
				m_ItemArray[i].SetShow(false);
			}
				m_ItemArray[i].CollisionStage(ox, oy);
				m_ItemArray[i].BlockJump(jumpFlg);
		}
	}
	
	for (int i = 0; i < g_Stage.GetEnemyCount(); i++)
	{
			if (m_EnemyArray[i].GetType() == ENEMY_MARIO)
			{
				m_EnemyArray[i].GetPlayerInfo(g_Player.Getplayer_PositionX(), g_Player.GetPlayer_MoveX(),
					g_Player.Getplayer_JumpFlg(), g_Player.GetTmpWorpFlg());
			}
			//当たり判定の実行
			g_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for (int i = 0; i < g_Stage.GetItemCount(); i++)
	{
			g_Player.CollisionItem(m_ItemArray[i]);
	}
	//タイマー処理
	if (g_Player.Getplayer_DeadFlg() == false && g_Player.Getplayer_ClearFlg() == false)
	{
		//クリア&ゲームオーバーをしていないとき
		game_Time -= 1 * CUtilities::GetFrameSecond();
	}
	else if (game_Time <= 0 && !g_Player.Getplayer_ClearFlg())
	{
		game_Time = 0.0f;
		g_Player.Setplayer_DeadFlg(true);
	}

	game_EffectManager.Update();

	//連続で敵を倒し中、途中で地面に着いたとき、敵の死亡カウントを0にする
	if (!g_Player.Getplayer_JumpFlg() && g_Player.Getplayer_FallFlg())
	{
		enemyDeadCount = 0;
	}
	//獲得スコア表示時間処理
		scoreDesplayTime--;
		if (scoreDesplayTime < 0)
		{
			scoreDesplayTime = 0;
			getScore = 0;
			scoreDisplayFlg = false;
			player1UpDisplayFlg = false;
		}
	


	//死亡フラグがONの時、ゲームオーバーSEを再生
	if (g_Player.Getplayer_DeadFlg() == true && !game_playSoundFlg)
	{
		if(game_BGM.IsPlay())
		{
			game_BGM.Stop();
		}
		else if(game_LAST_BGM.IsPlay())
		{
			game_LAST_BGM.Stop();
		}
		else if (game_BOSS_BGM.IsPlay())
		{
			game_BOSS_BGM.Stop();
		}
		game_GameOverSE.Play();
		game_playSoundFlg = true;
	}
	//クリアフラグがONの時、ゲームクリアSEを再生
	else if (g_Player.Getplayer_ClearFlg() == true)
	{
		if (game_BGM.IsPlay())
		{
			game_BGM.Stop();
		}
	}
	if (g_Player.Getplayer_DeadFlg() == true && !game_GameOverSE.IsPlay())
	{
		g_Player.Setplayer_DeadTransitionFlg(true);
	}
	//ゲームオーバー画面遷移
	if (g_Player.Getplayer_DeadTransitionFlg() == true)
	{
		//死亡時スコアを0にする
		score = 0;

		//残機が0未満のときゲームオーバー画面へ遷移
		if (player_Life < 0)
		{
			Sleep(1000);
			m_NextScene = SCENENO_GAMEOVER;
			m_bEnd = true;
		}
		//インフォメーション画面へ遷移
		else
		{
			Sleep(1000);
			m_NextScene = SCENENO_INFOMATION;
			m_bEnd = true;
		}
	}
	//ゲームクリア画面遷移
	else if(g_Player.Getplayer_ClearTransitionFlg() == true)
	{
		if (!game_playSoundFlg)
		{
			game_GameClearSE.Play();
			game_playSoundFlg = true;
		}
		if (game_Time > 0)
		{

			score += SCORE_TIME;
			game_Time--;
		}
		else
		{
			game_Time = 0.0f;

			
			if (!game_GameClearSE.IsPlay())
			{
				player_Life += (int)floor(score / 20000);
				score = 0;
				m_NextScene = SCENENO_INFOMATION;
				stage_number++;
				if (stage_number >= STAGE_COUNT)
				{
					stage_number = STAGE_COUNT - 1;
				}
				m_bEnd = true;
			}
			
		}
		
	}
	//ゲームクリア画面遷移
	else if (g_Player.GetBossClearFlg())
	{
		if (!game_ab)
		{
			game_BossClearSE.Play();
			game_ab = true;
		}
	}
	if (g_Player.GetBossClearTrantionFlg() == true)
	{

		if (!game_BossClearSE.IsPlay())
		{
			m_NextScene = SCENENO_TITLE;
			stage_number = STAGE_1_1;
			m_bEnd = true;
		}
	}
}



/**
 * 描画
 *
 */
void CGame::Render(void) {
	//ステージの描画
	g_Stage.Render();
	//プレイヤーの描画
	g_Player.Render(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	//アイテムの描画
	for (int i = 0; i < g_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Render(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	}
	//敵の描画
	for (int i = 0; i < g_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	}
	game_EffectManager.Render(Vector2(g_Stage.GetScrollX(), g_Stage.GetScrollY()));
	CGraphicsUtilities::RenderString(300, 50, "COIN");
	CGraphicsUtilities::RenderString(100, 50, "%.6d", score);
	CGraphicsUtilities::RenderString(800, 50, "%.3d", (int)game_Time);
	CGraphicsUtilities::RenderString(350, 50, "×%d", getCoinCount);
	switch (game_NowStage)
	{
		case STAGE_1_1:
		{
			CGraphicsUtilities::RenderString(600, 50, "１ー１");
			break;
		}
	case STAGE_LAST:
	{
		CGraphicsUtilities::RenderString(600, 50, "BOSS");
		break;
	}

	default:
		break;
	}

	if(scoreDisplayFlg && scoreDesplayTime > 0)
	{
		game_tempPlayerPositionX = g_Player.Getplayer_DispPositionX();
		game_tempPlayerPositionY = g_Player.Getplayer_DispPositionY();
		if (!player1UpDisplayFlg)
		{
			CGraphicsUtilities::RenderString(game_tempPlayerPositionX + 30, game_tempPlayerPositionY - 30, "%d", getScore);
		}
		else
		{
			CGraphicsUtilities::RenderString(game_tempPlayerPositionX + 30, game_tempPlayerPositionY - 30, "1UP");
		}
	}
}

void CGame::RenderDebug(void) {
	//ステージのデバッグ描画
	g_Stage.RenderDebug();
	//プレイヤーのデバッグ描画
	g_Player.RenderDebug(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	//敵のデバッグ描画
	for (int i = 0; i < g_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	}
	//アイテムのデバッグ描画
	for (int i = 0; i < g_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	}
	CGraphicsUtilities::RenderString(10, 10, "ゲーム画面");
	CGraphicsUtilities::RenderString(300, 300, "敵死亡カウント%d", enemyDeadCount);
	CGraphicsUtilities::RenderString(300, 400, "獲得スコア%d", getScore);
	CGraphicsUtilities::RenderString(350, 500, "TimeWait:%0.0f", game_TimeWait);
	
	
}

void CGame::Release(void)
{
	//ステージの解放
	g_Stage.Release();
	//プレイヤーの解放
	g_Player.Release();
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
	//BGM解放
	switch (stage_number)
	{
	case STAGE_LAST:
	{
		game_BOSS_BGM.Release();
		game_LAST_BGM.Release();
		break;
	}
	default:
		game_BGM.Release();
		break;
	}
	game_EffectManager.Release();
	
	//SE解放
	game_GameOverSE.Release();
	game_GameClearSE.Release();
	game_MarioDeadSE.Release();
	game_BossClearSE.Release();
}