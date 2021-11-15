#include "Player.h"
#include "GlobalDefine.h"
#include <thread>

extern  int		player_Life = PLAYER_INITIALLIFE;

//スコア
extern	int		score;
extern	bool	scoreDisplayFlg;
extern	bool	player1UpDisplayFlg;
extern	int		getScore;
extern	int		scoreDesplayTime;
extern	int		enemyDeadCount = 0;
extern  int     getCoinCount;




//コンストラクタ
CPlayer::CPlayer() :
	player_Position(0, 0),
	player_Move(0.0f),
	player_Jump(0.0f),
	player_JumpFlg(false),
	player_CheckGround(false),
	player_Texture(),
	player_RectTexture(),
	player_Reverse(false),
	player_Motion(),
	player_MoveFlg(false),
	player_JumpSE(),
	player_StepEnemySE(),
	player_ChangeBigSE(),
	player_ChangeSmallSE(),
	player_1upSE(),
	player_GoalFlagSE(),
	player_DeadFlg(false),
	player_DeadTransitionFlg(false),
	player_a(false),
	player_TimeWait(0),
	player_ClearFlg(false),
	player_ClearTransitionFlg(false),
	player_HP(0),
	player_DamageWait(0),
	player_ChangeBig(false),
	player_ChangeWait(0),
	player_ChangeWaitFlg(false),
	player_ChangeSizeFlg(false),
	player_DamageFlg(false),
	player_TempPositionX(0),
	player_TempPositionY(0),
	player_GoalMoveFlg(false),
	player_WarpFlg(false),
	player_tmpWarpFlg(false),
	player_playSEFlg(false),
	player_MarioDead(false),
	player_BossClearFlg(false),
	player_Scroll(false),
	player_BossClearTransitionFlg(false)
{
}


//デストラクタ
CPlayer::~CPlayer()
{

}

bool CPlayer::Load(void)
{
	if (!player_Texture.Load("Player.png"))
	{
		return false;
	}
	if (!player_JumpSE.Load("Jump.wav"))
	{
		return false;
	}
	if (!player_StepEnemySE.Load("StepEnemy.mp3"))
	{
		return false;
	}
	if (!player_ChangeBigSE.Load("ChangeBigSE.wav"))
	{
		return false;
	}
	if (!player_ChangeSmallSE.Load("ChangeSmallSE.mp3"))
	{
		return false;
	}
	if (!player_1upSE.Load("1UP.wav"))
	{
		return false;
	}
	if (!player_GoalFlagSE.Load("GoalFlag.mp3"))
	{
		return false;
	}
	if (!player_GetCoinSE.Load("GetCoin.wav"))
	{
		return false;
	}
	
	//アニメーション作成
	CreateAnimation();

	return true;
}

void CPlayer::Initialize(void)
{
	player_Position = Vector2(100, 500);
	player_Move = 0.0f;
	player_Jump = 0.0f;
	player_JumpFlg = false;
	player_CheckGround = false;
	player_Reverse = false;
	player_MoveFlg = false;
	player_DeadFlg = false;
	player_DeadTransitionFlg = false;
	player_a = false;
	player_ClearFlg = false;
	player_ClearTransitionFlg = false;
	player_HP = PLAYER_HP;
	player_DamageWait = 0;
	player_ChangeWait = 0;
	player_ChangeWaitFlg = false;
	player_ChangeBig = false;
	player_ChangeSizeFlg = false;
	player_DamageFlg = false;
	player_GoalMoveFlg = false;
	if (player_Motion.GetMotionNo() != MOTION_SMALL_WAIT)
	{
		player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
	}

	player_TempPositionX = 0.0f;
	player_TempPositionY = 0.0f;
	player_WarpFlg = false;
	player_tmpWarpFlg = false;
	player_playSEFlg = false;
	player_MarioDead = false;
	player_BossClearFlg = false;
	player_BossClearTransitionFlg = false;
}

void CPlayer::Update(void)
{
	//プレイヤー死亡判定
	DeadJudge();

	//画面外に出ないようにする
	if (player_Position.x < 0)
	{
		player_Move = 0;
		player_Position.x = 0;
	}
	if (player_Position.x > 7500 && !player_BossClearFlg)
	{
		
		player_BossClearFlg = true;
	}
	//死亡,クリアフラグがfalseの時プレイヤーを動かす
	if (!player_DeadFlg && !player_ClearFlg && !player_BossClearFlg)
	{
		if (player_WarpFlg && player_Position.x < 6000)
		{
			player_tmpWarpFlg = player_WarpFlg;
			player_Position.x = 6400;
			player_Position.y = 400;
		}

		if (player_ChangeWait > 0 && !player_ChangeWaitFlg)
		{
			player_ChangeWaitFlg = true;
		}
		else if (player_ChangeWait <= 0 && player_ChangeWaitFlg)
		{
			player_ChangeWaitFlg = false;
		}
		//プレイヤーサイズ変化(boolで切り替え)
		ChangeSize();
		//プレイヤーがサイズ変化していないときに処理
		if (player_ChangeWait <= 0)
		{
			//プレイヤー移動
			PlayerMove();

			//プレイヤージャンプ(プレイヤーが地面に接触しているならジャンプ)
			if (player_CheckGround)
			{
				PlayerJump();

			}
			//プレイヤーの速度に重力を与え続ける
			player_Jump += PLAYER_GRAVITY;
			player_Position.y += player_Jump;

		}
		////落下した時死亡フラグをTRUE
		//if (player_Position.y > 800)
		//{
		//	player_DeadFlg = true;
		//}

	}
	else if (player_DeadFlg)
	{
		//プレイヤーが死んだときの処理(1回だけ実行)
		if (!player_a)
		{
			if (!player_ChangeBig)
			{
				if (player_Motion.GetMotionNo() != MOTION_SMALL_DAMAGE)
				{
					player_Motion.ChangeMotion(MOTION_SMALL_DAMAGE);
				}
			}
			else
			{
				if (player_Motion.GetMotionNo() != MOTION_BIG_DAMAGE)
				{
					player_Motion.ChangeMotion(MOTION_BIG_DAMAGE);
				}
			}
			player_Life--;
			Sleep(300);
			player_Jump = -PLAYER_JUMPSPEED;
			player_a = true;
		}
		//落ちる処理
		player_Jump += PLAYER_GRAVITY;
		if (player_Jump > 20.0f)
		{
			player_Jump = 20.0f;
		}
		player_Position.y += player_Jump;
	}
	else if (player_ClearFlg)
	{
		if (player_Reverse)
		{
			player_Reverse = false;
		}
		
		//プレイヤーがゴールフラッグを落ち切った時
		if (!player_JumpFlg && player_CheckGround)
		{
			if (player_GoalFlagSE.IsPlay())
			{
				player_GoalFlagSE.Stop();
			}

			if (!player_ChangeBig)
			{
				if (player_Motion.GetMotionNo() == MOTION_SMALL_WAIT)
				{
					player_Motion.ChangeMotion(MOTION_SMALL_MOVE);
				}
			}
			else
			{
				if (player_Motion.GetMotionNo() == MOTION_BIG_WAIT)
				{
					player_Motion.ChangeMotion(MOTION_BIG_MOVE);
				}
			}
			
			if (!player_ClearTransitionFlg)
			{
				player_Position.x += 5;
			}

		}
		else
		{
			if (!player_GoalMoveFlg)
			{
				player_GoalFlagSE.Play();
				player_GoalMoveFlg = true;
			}

			if (!player_ChangeBig)
			{
				if (player_Motion.GetMotionNo() != MOTION_SMALL_WAIT)
				{
					player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
				}
			}
			else
			{
				if (player_Motion.GetMotionNo() != MOTION_BIG_WAIT)
				{
					player_Motion.ChangeMotion(MOTION_BIG_WAIT);
				}
			}
			player_Position.y += 5;
		}
	}
	else if (player_BossClearFlg && !player_BossClearTransitionFlg)
	{
		player_Jump = 5;
		player_Move = 1;
		player_Position.x += player_Move;
		player_Position.y += player_Jump;
		if (!player_ChangeBig)
		{
			if (player_Motion.GetMotionNo() != MOTION_SMALL_MOVE)
			{
				player_Motion.ChangeMotion(MOTION_SMALL_MOVE);
			}
		}
		else
		{
			if (player_Motion.GetMotionNo() != MOTION_BIG_MOVE)
			{
				player_Motion.ChangeMotion(MOTION_BIG_MOVE);
			}
		}

	}

	//ダメージのインターバルを減らす
	if (player_DamageWait > 0)
	{
		player_DamageWait--;
	}
	//アニメーションの更新
	player_Motion.AddTimer(CUtilities::GetFrameSecond());
	//プレイヤー矩形
	player_RectTexture = player_Motion.GetSrcRect();

}

void CPlayer::Render(float wx, float wy)
{
	//プレイヤー矩形
	CRectangle player_drow = player_RectTexture;

	//描画位置
	float px = player_Position.x - wx;
	float py = player_Position.y - wy;
	//スコア用退避変数
	player_TempPositionX = px;
	player_TempPositionY = py;


	if (player_ChangeBig)
	{
		if (player_Motion.GetMotionNo() == MOTION_SMALL_WAIT)
		{
			py += 32;
		}
	}
	else if (!player_ChangeBig && player_DamageFlg)
	{
		if (player_Motion.GetMotionNo() == MOTION_SMALL_WAIT)
		{
			py += 32;
		}
	}
	if (player_Reverse)
	{
		float temp = player_drow.Right;
		player_drow.Right = player_drow.Left;
		player_drow.Left = temp;
	}
	player_Texture.Render(px, py, player_drow);

}

void CPlayer::RenderDebug(float wx, float wy)
{
	//当たり判定描画
	CGraphicsUtilities::RenderRect(player_Position.x + 5 - wx, player_Position.y - wy, (player_Position.x + player_RectTexture.GetWidth() - 5) - wx, (player_Position.y + player_RectTexture.GetHeight()) - wy, MOF_XRGB(0, 255, 0));

	CGraphicsUtilities::RenderString(100, 100, "ジャンプフラグ：%d", player_JumpFlg);
	CGraphicsUtilities::RenderString(100, 150, "地面接触フラグ%d", player_CheckGround);
	CGraphicsUtilities::RenderString(100, 200, "ジャンプ:%f", player_Jump);
	CGraphicsUtilities::RenderString(100, 250, "残機：%d", player_Life);
	CGraphicsUtilities::RenderString(100, 300, "PX：%f", player_Position.x);
	CGraphicsUtilities::RenderString(100, 350, "PY：%f", player_Position.y);
	CGraphicsUtilities::RenderString(100, 400, "変化ウェイト：%d", player_ChangeWait);
	CGraphicsUtilities::RenderString(100, 600, "クリアーフラグ%d", player_ClearFlg);
}

void CPlayer::Release(void)
{
	player_Texture.Release();
	player_Motion.Release();
	player_JumpSE.Release();
	player_StepEnemySE.Release();
	player_ChangeBigSE.Release();
	player_ChangeSmallSE.Release();
	player_1upSE.Release();
	player_GoalFlagSE.Release();
	player_GetCoinSE.Release();
}








//プレイヤー移動
void CPlayer::PlayerMove(void)
{
	//プレイヤー移動
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		player_Move += PLAYER_SPEED;
		player_MoveFlg = true;
		//ジャンプしてないとき向きを変えられる
		if (!player_JumpFlg)
		{
			player_Reverse = false;
		}
		//最高速度
		if (player_Move > PLAYER_TOPSPEED)
		{
			player_Move = PLAYER_TOPSPEED;
		}
		//移動モーションに切り替え
		if (!player_ChangeBig)
		{
			if (player_Motion.GetMotionNo() == MOTION_SMALL_WAIT)
			{
				player_Motion.ChangeMotion(MOTION_SMALL_MOVE);
			}
		}
		else
		{
			if (player_Motion.GetMotionNo() == MOTION_BIG_WAIT)
			{
				player_Motion.ChangeMotion(MOTION_BIG_MOVE);
			}
		}

	}
	else if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		player_Move -= PLAYER_SPEED;
		player_MoveFlg = true;
		//ジャンプしてないとき向きを変えられる
		if (!player_JumpFlg)
		{
			player_Reverse = true;
		}
		//最高速度
		if (player_Move < -PLAYER_TOPSPEED)
		{
			player_Move = -PLAYER_TOPSPEED;
		}
		//移動モーションに切り替え
		if (!player_ChangeBig)
		{
			if (player_Motion.GetMotionNo() == MOTION_SMALL_WAIT)
			{
				player_Motion.ChangeMotion(MOTION_SMALL_MOVE);
			}
		}
		else
		{
			if (player_Motion.GetMotionNo() == MOTION_BIG_WAIT)
			{
				player_Motion.ChangeMotion(MOTION_BIG_MOVE);
			}
		}
	}
	else
	{

		//キー入力がない場合は速度を減衰させる
		if (player_Move < 0)
		{
			player_Move += PLAYER_SPEED;
			if (player_Move >= 0)
			{
				player_Move = 0;
			}
		}
		else if (player_Move > 0)
		{
			player_Move -= PLAYER_SPEED;
			if (player_Move <= 0)
			{
				player_Move = 0;
			}
		}
		player_MoveFlg = false;
		if (!player_ChangeBig)
		{
			if (player_Motion.GetMotionNo() == MOTION_SMALL_MOVE)
			{
				player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
			}
		}
		else
		{
			if (player_Motion.GetMotionNo() == MOTION_BIG_MOVE)
			{
				player_Motion.ChangeMotion(MOTION_BIG_WAIT);
			}
		}
	}
	//X座標の変化
	player_Position.x += player_Move;
}

//プレイヤージャンプ
void CPlayer::PlayerJump(void)
{

	//プレイヤージャンプ
	if (g_pInput->IsKeyPush(MOFKEY_UP) && !player_JumpFlg)
	{
		//ジャンプの開始、初速を設定してジャンプフラグを有効にする
		player_JumpFlg = true;
		player_Jump = -PLAYER_JUMPSPEED;
		//ジャンプモーションに切り替え
		if (player_JumpFlg)
		{
			if (!player_ChangeBig)
			{
				player_Motion.ChangeMotion(MOTION_SMALL_JUMP);
			}
			else
			{
				player_Motion.ChangeMotion(MOTION_BIG_JUMP);
			}

		}
		player_JumpSE.Play();
	}

	if (player_JumpFlg)
	{
		//途中でジャンプボタンを離した時ジャンプ速度を半減(小ジャンプ)
		if (player_Jump < 0 && g_pInput->IsKeyPull(MOFKEY_UP))
		{
			player_Jump *= 0.2f;
		}
	}
}

//描画する範囲のテクスチャ矩形を取得
CRectangle CPlayer::GetRectTexture(void)
{
	return CRectangle(0, 0, player_Texture.GetWidth(), player_Texture.GetHeight());
}

//ステージとの当たり
/*

		ox		X埋まり量
		oy		Y埋まり量
*/
void CPlayer::CollisionStage(float ox, float oy)
{

	//死亡フラグfalseの時当たり判定を行う
	if (!player_DeadFlg && !player_ClearTransitionFlg)
	{

		player_Position.x += ox;
		player_Position.y += oy;
		player_CheckGround = true;
		//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する
		if (oy < 0)
		{

			player_Jump = 0;

			if (player_JumpFlg)
			{
				player_JumpFlg = false;
				if (!player_ChangeBig)
				{
					if (player_Motion.GetMotionNo() != MOTION_SMALL_WAIT)
					{
						player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
					}
				}
				else
				{
					if (player_Motion.GetMotionNo() != MOTION_BIG_WAIT)
					{
						player_Motion.ChangeMotion(MOTION_BIG_WAIT);
					}
				}

			}
		}
		else if (oy > 0)
		{
			player_Jump = 0;

		}
		//左移動の左埋まり、右移動の右埋まりの場合は移動を初期化する
		if (ox < 0 && player_Move > 0)
		{

			player_Move = 0;

			if (!player_ChangeBig)
			{
				if (player_Motion.GetMotionNo() == MOTION_SMALL_MOVE)
				{
					player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
				}
			}
			else
			{
				if (player_Motion.GetMotionNo() == MOTION_BIG_MOVE)
				{
					player_Motion.ChangeMotion(MOTION_BIG_WAIT);
				}
			}
		}
		else if (ox > 0 && player_Move < 0)
		{
			player_Move = 0;
			if (!player_ChangeBig)
			{
				if (player_Motion.GetMotionNo() == MOTION_SMALL_MOVE)
				{
					player_Motion.ChangeMotion(MOTION_SMALL_WAIT);
				}
			}
			else
			{
				if (player_Motion.GetMotionNo() == MOTION_BIG_MOVE)
				{
					player_Motion.ChangeMotion(MOTION_BIG_WAIT);
				}
			}
		}
	}
}

void CPlayer::FallCheck(bool og)
{
	if (!og && !player_JumpFlg)
	{
		player_CheckGround = false;
	}
}

bool CPlayer::CollisionEnemy(CEnemy & ene)
{
	if (!ene.GetShow() || ene.GetEnemyDead() || player_DeadFlg || player_ClearFlg)
	{
		return false;
	}
	if (player_DamageWait > 0 || ene.GetMarioDamageWait() > 0)
	{
		return false;
	}
	CRectangle playerRect = GetRectPlayer();
	CRectangle enemyRect = ene.GetRect();
	CRectangle enemyAttackRect = ene.GetAttackRangeRect();
	if (ene.GetType() == ENEMY_MARIO && !player_playSEFlg)
	{
		if (ene.GetMarioChangeFlg())
		{
			player_ChangeBigSE.Play();
			player_playSEFlg = true;
		}
	}
	if (ene.GetMarioDeadFlg())
	{
		player_MarioDead = true;
	}
	//スケルトンの攻撃範囲判定
	if (playerRect.CollisionRect(enemyAttackRect))
	{
		ene.DistanceBetweenPlayer(player_Position.x);
		ene.Setenemy_AttackFlg(true);
	}
	else
	{
		ene.Setenemy_AttackFlg(false);
	}
	//敵との当たり判定
	if (playerRect.CollisionRect(enemyRect))
	{
		//プレイヤーのbottomが敵の上半分より高い時、踏みつけ
		if (playerRect.Bottom <= ene.Getenemy_PositionY() + 20)
		{
			//踏みつけたときの小ジャンプ
			player_Jump = -PLAYER_ENEMYSTEP_JUMPSPEED;
			player_StepEnemySE.Play();
			if (ene.GetType() == ENEMY_MARIO)
			{
				ene.MarioDamage(1);
				return true;
			}
			else
			{
				ene.Dead(true);
				score += SCORE_ENEMYSTEP;
				//連続で踏んだ時のスコア加算処理
				AddScoreEnemyStep();
				return true;
			}

		}
		//それ以外はダメージ
		else
		{
			Damage();
			return true;
		}
	}
	//敵の弾と自分の判定
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		if (!ene.GetShot(i).GetShow())
		{
			return false;
		}
		CRectangle srec = ene.GetShot(i).GetRect();
		if (srec.CollisionRect(playerRect))
		{
			Damage();
			ene.GetShot(i).SetShow(false);
			break;
		}
	}


	return false;
}

bool CPlayer::CollisionItem(CItem& item)
{
	if (!item.GetShow() || player_DeadFlg || player_ClearFlg)
	{
		return false;
	}
	if (!item.GetitemAppear() && item.GetType() == ITEM_MUSH)
	{
		return false;
	}
	//アイテムの矩形と自分の矩形で当たり判定
	CRectangle playerRect = GetRectPlayer();
	CRectangle itemRect = item.GetRect();
	if (playerRect.CollisionRect(itemRect))
	{
		item.SetShow(false);
		switch (item.GetType())
		{
		case ITEM_MUSH:
			ChangeBig();
			player_ChangeBigSE.Play();
			scoreDesplayTime = SCORE_DISPLAYTIME;
			getScore = SCORE_GETITEM;
			score += SCORE_GETITEM;
			scoreDisplayFlg = true;
			break;
		case ITEM_COIN:
			player_GetCoinSE.Play();
			getCoinCount++;
			scoreDesplayTime = SCORE_DISPLAYTIME;
			getScore = SCORE_COIN;
			score += SCORE_COIN;
			scoreDisplayFlg = true;
			break;
		}
		return true;
	}
	return false;
}

void CPlayer::ChangeSize(void)
{
	//巨大化
	if (player_ChangeBig)
	{
		player_DamageFlg = false;
		//サイズ変更ウェイト
		if (player_ChangeWait > 0)
		{

			player_ChangeWait--;


			if (player_ChangeWait == 59 || player_ChangeWait == 40 || player_ChangeWait == 20 || player_ChangeWait == 0)
			{


				if (player_Motion.GetMotionNo() != MOTION_BIG_WAIT)
				{

					player_Motion.ChangeMotion(MOTION_BIG_WAIT);

					//アニメーションの更新
					player_Motion.Refresh();
					//プレイヤー矩形
					player_RectTexture = player_Motion.GetSrcRect();
				}

			}

			else if (player_ChangeWait == 50 || player_ChangeWait == 30 || player_ChangeWait == 10)
			{

				if (player_Motion.GetMotionNo() != MOTION_SMALL_WAIT)
				{

					player_Motion.ChangeMotion(MOTION_SMALL_WAIT);

					//アニメーションの更新
					player_Motion.Refresh();
					//プレイヤー矩形
					player_RectTexture = player_Motion.GetSrcRect();
				}

			}
		}
	}
	//ダメージ（小化）
	else if (!player_ChangeBig && player_DamageFlg)
	{
		//サイズ変更ウェイト
		if (player_ChangeWait > 0)
		{

			player_ChangeWait--;

			if (player_ChangeWait == 59 || player_ChangeWait == 40 || player_ChangeWait == 20 || player_ChangeWait == 1)
			{


				if (player_Motion.GetMotionNo() != MOTION_SMALL_WAIT)
				{

					player_Motion.ChangeMotion(MOTION_SMALL_WAIT);

					//アニメーションの更新
					player_Motion.Refresh();
					//プレイヤー矩形
					player_RectTexture = player_Motion.GetSrcRect();

				}

			}
			else if (player_ChangeWait == 50 || player_ChangeWait == 30 || player_ChangeWait == 10)
			{

				if (player_Motion.GetMotionNo() != MOTION_BIG_WAIT)
				{

					player_Motion.ChangeMotion(MOTION_BIG_WAIT);

					//アニメーションの更新
					player_Motion.Refresh();
					//プレイヤー矩形
					player_RectTexture = player_Motion.GetSrcRect();

				}

			}
		}
		else if (player_ChangeWait <= 0 && player_DamageFlg)
		{
			player_DamageFlg = false;
		}
	}
}

void CPlayer::DeadJudge(void)
{
	//プレイヤー死亡判定
	if (player_HP <= 0)
	{
		player_DeadFlg = true;
	}
}


//連続で敵を踏んだ時のスコア加算処理
void CPlayer::AddScoreEnemyStep(void)
{
	//連続で敵を踏んだ数のカウント
	enemyDeadCount++;
	if (enemyDeadCount <= 1)
	{
		player1UpDisplayFlg = false;
		scoreDesplayTime = SCORE_DISPLAYTIME;
		//獲得スコア表示用
		getScore = SCORE_ENEMYSTEP;
		//獲得スコア表示フラグ
		scoreDisplayFlg = true;
	}
	//踏んだ数が2以上の時、追加でスコア加算
	if (enemyDeadCount > 1)
	{
		if (getScore < 1200)
		{
			scoreDesplayTime = SCORE_DISPLAYTIME;
			getScore *= 2;
			score += getScore;
			
			scoreDisplayFlg = true;
		}
		if (getScore >= 1400)
		{
			scoreDesplayTime = SCORE_DISPLAYTIME;
			//1UP
			player1UpDisplayFlg = true;
			player_Life++;
			player_1upSE.Play();

		}

	}
}

void CPlayer::Damage(void)
{
	if (player_HP == 1)
	{
		player_HP--;
		return;
	}
	else if (player_HP == 2)
	{
		if (player_ChangeBig)
		{
			player_DamageFlg = true;
			player_ChangeWait = 60;
			if (player_DamageWait <= 0)
			{
				player_DamageWait = PLAYER_INVINCIBLE;
			}
			player_ChangeSmallSE.Play();
			player_ChangeBig = false;
		}
		player_HP--;
		return;
	}
}

void CPlayer::ChangeBig(void)
{
	if (player_HP == 1)
	{
		if (!player_ChangeBig)
		{
			player_ChangeWait = 60;
			if (player_DamageWait <= 0)
			{
				player_DamageWait = PLAYER_INVINCIBLE;
			}
			player_HP++;
			player_ChangeBig = true;
		}
		return;
	}
}

void CPlayer::CreateAnimation()
{
	//アニメーションを作成
	SpriteAnimationCreate animation[] = {

		{
			"小待機",
			0,0,
			32,32,
			FALSE,{{5,0,0}}
		},
		{
			"小ダメージ",
			32,0,
			32,32,
			FALSE,{{5,0,0}}
		},
		{
			"小移動",
			0,32,
			32,32,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"小ジャンプ",
			0,64,
			32,32,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0}}
		},
		{
			"大待機",
			0,96,
			32,64,
			FALSE,{{5,0,0}}
		},
		{
			"大ダメージ",
			32,96,
			32,64,
			FALSE,{{5,0,0}}
		},
		{
			"小移動",
			0,160,
			32,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"小ジャンプ",
			0,224,
			32,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0}}
		},

	};
	player_Motion.Create(animation, MOTION_COUNT);
}


