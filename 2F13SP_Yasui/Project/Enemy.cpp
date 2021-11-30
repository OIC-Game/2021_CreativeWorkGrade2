#include "Enemy.h"

extern int	score;



CEnemy::CEnemy() :
	enemy_Type(0),
	enemy_Position(0, 0),
	enemy_Move(0, 0),
	enemy_Reverse(false),
	enemy_Show(false),
	enemy_pTexture(NULL),
	enemy_Motion(),
	enemy_RectTexture(),
	enemy_Dead(false),
	enemy_DisappearTime(0),
	enemy_BlockJump(false),
	enemy_DeadJump(false),
	enemy_srcDeadJump(false),
	m_ShotArray(),
	enemy_ShotWait(0),
	enemy_AttackFlg(false),
	enemy_DistanceBetweenToPlayer(0.0f),
	enemy_MarioHP(0),
	enemy_MarioNowAttackPettern(0),
	tmp_playerPositionX(0),
	tmp_playerMoveX(0),
	tmp_DistanceBetweenPlayer(0.0f),
	tmp_playerJumpFlg(false),
	tmp_playerWarpFlg(false),
	one(false),
	loop(0),
	jumpFlg(false),
	enemy_MarioDamageFlg(false),
	enemy_MarioDamageWait(0),
	enemy_MarioChangeFlg(false),
	changeFireMode(false),
	fire(false),
	fireWait(0),
	otherAttack(0),
	dashCount(0),
	enemy_MarioDead(false),
	enemy_FireSE()
{
}

CEnemy::~CEnemy()
{
	Release();
}

bool CEnemy::Load(void)
{
	return true;
}

/*

	px		X座標
	py		Y座標
	type	敵タイプ


*/
void CEnemy::Initialize(float px, float py, int type)
{
	enemy_Type = type;
	enemy_Position.x = px;
	enemy_Position.y = py;
	enemy_MarioHP = 0;
	enemy_Move.y = 0.0f;
	enemy_Reverse = true;
	enemy_Show = true;
	enemy_BlockJump = false;
	enemy_Dead = false;
	enemy_DeadJump = false;
	enemy_srcDeadJump = false;
	enemy_DisappearTime = ENEMY_DISAPPEARTIME;
	enemy_ShotWait = 0;
	enemy_AttackFlg = false;
	enemy_DistanceBetweenToPlayer = 0.0f;
	enemy_MarioNowAttackPettern = 0;
	tmp_playerPositionX = 0;
	tmp_playerMoveX = 0;
	tmp_DistanceBetweenPlayer = 0.0f;
	tmp_playerJumpFlg = false;
	tmp_playerWarpFlg = false;
	one = false;
	loop = 0;
	jumpFlg = false;
	enemy_MarioDamageFlg = false;
	enemy_MarioDamageWait = 0;
	enemy_MarioChangeFlg = false;
	changeFireMode = false;
	fire = false;
	fireWait = 0;
	otherAttack = 0;
	enemy_MarioDead = false;
	debug_MarioAttackPettern = 0;
	debugModeFlg = false;
	dashCount = 0;

	switch (enemy_Type)
	{
	case ENEMY_MUSH:
	{
		enemy_Move.x = -1.0f;
		break;
	}
	case ENEMY_SKELETON:
	{
		enemy_Move.x = -0.5f;
		break;
	}
	case ENEMY_MARIO:
	{
		enemy_Move.x = -3.0f;
		enemy_MarioHP = ENEMY_MARIOHP;

		break;
	}
	case ENEMY_FISH:
	{
		enemy_Move.x = 0;
		enemy_Move.y = 0;

		break;
	}
	}



	//アニメーションを作成
	switch (enemy_Type)
	{
	case ENEMY_MUSH:
	{
		SpriteAnimationCreate anime[] = {
			{
				"移動",
				0,0,
				32,32,
				TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
			},
			{
				"死亡",
				0,32,
				32,32,
				FALSE,{{5,0,0}}
			},
		};
		enemy_Motion.Create(anime, MUSHMOTION_COUNT);
		break;
	}
	case ENEMY_SKELETON:
	{
		SpriteAnimationCreate anime[] = {
			{
				"待機",
				0,0,
				32,64,
				TRUE,{{5,0,0}}
			},
			{
				"移動",
				0,0,
				32,64,
				TRUE,{{6,0,0},{4,1,0},{2,2,0},{4,3,0},{6,4,0},{3,5,0}}
			},
			{
				"死亡",
				32,128,
				32,64,
				FALSE,{{5,0,0}}
			},
			{
				"復活",
				0,128,
				32,64,
				FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0}}
			},
			{
				"攻撃",
				0,64,
				32,64,
				FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0}}
			},
		};
		enemy_Motion.Create(anime, SKELETONMOTION_COUNT);
		break;
	}
	case ENEMY_MARIO:
	{
		SpriteAnimationCreate anime[] = {

			{
				"通常移動",
				72,0,
				36,68,
				TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
			},
			{
				"通常待機",
				0,0,
				36,68,
				TRUE,{{5,0,0}}
			},
			{
				"通常ジャンプ開始",
				252,0,
				36,68,
				FALSE,{{5,0,0}}
			},
			{
				"通常ジャンプ着地",
				252,0,
				36,68,
				FALSE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},{4,6,0},{4,7,0}}
			},
			{
				"通常ヒップドロップ",
				504,0,
				36,68,
				FALSE,{{5,1,0},{4,0,0}}
			},
			{
				"通常ブレーキ",
				216,0,
				36,68,
				FALSE,{{30,0,0}}
			},
			{
				"通常ダメージ",
				36,0,
				36,68,
				FALSE,{{5,0,0}}
			},
			{
				"進化移動",
				72,68,
				36,68,
				TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
			},
			{
				"進化待機",
				0,68,
				36,68,
				TRUE,{{5,0,0}}
			},
			{
				"進化ジャンプ開始",
				252,68,
				36,68,
				FALSE,{{5,0,0}}
			},
			{
				"進化ジャンプ着地",
				288,68,
				36,68,
				FALSE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{2,4,0},{2,5,0},{1,6,0},{1,7,0}}
			},
			{
				"進化ヒップドロップ",
				504,68,
				36,68,
				FALSE,{{5,1,0},{4,0,0}}
			},
			{
				"進化ブレーキ",
				216,68,
				36,68,
				FALSE,{{30,0,0}}
			},
			{
				"進化攻撃",
				576,68,
				36,68,
				FALSE,{{8,0,0},{4,1,0}}
			},
			{
				"進化ダメージ",
				36,68,
				36,68,
				FALSE,{{5,0,0}}
			},
			{
				"進化死亡",
				648,68,
				36,68,
				FALSE,{{5,0,0}}
			},


		};
		enemy_Motion.Create(anime, MARIOMOTION_COUNT);
		break;
	}
	case ENEMY_FISH:
	{
		SpriteAnimationCreate anime[] = {
			{
				"移動",
				0,0,
				32,32,
				TRUE,{{5,0,0},{5,1,0}}
			},
		};
		enemy_Motion.Create(anime, 1);
		break;
	}
	}
	if (enemy_Type == ENEMY_SKELETON || enemy_Type == ENEMY_MARIO)
	{
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			if (enemy_Type == ENEMY_SKELETON)
			{
				m_ShotArray[i].Initialize(0);
			}
			else
			{
				m_ShotArray[i].Initialize(1);
			}

		}
	}

}

void CEnemy::Update(float wx)
{
	//画面外で動かない
	if (wx > enemy_Position.x + 16 || wx + g_pGraphics->GetTargetWidth() < enemy_Position.x)
	{
		return;
	}
	//非表示
	if (!enemy_Show)
	{
		return;
	}
	if (enemy_Type == ENEMY_MARIO && !tmp_playerWarpFlg)
	{
		return;
	}
	//アニメーションの更新
	enemy_Motion.AddTimer(CUtilities::GetFrameSecond());
	enemy_RectTexture = enemy_Motion.GetSrcRect();

	//叩かれたブロックと同じ位置ならばジャンプ
	if (enemy_BlockJump)
	{
		enemy_Move.y = -ENEMY_BLOCKJUMP;
		enemy_BlockJump = false;
	}

	//重力処理
	enemy_Move.y += ENEMY_GRAVITY;
	if (enemy_Move.y >= 20.0f)
	{
		enemy_Move.y = 20.0f;
	}
	//攻撃処理
	switch (enemy_Type)
	{
	case ENEMY_SKELETON:
	{
		//スケルトン
		SkeletonShot();
		break;
	}
	case ENEMY_MARIO:
	{
		//マリオ
		if (tmp_playerWarpFlg)
			MarioAttack();
		break;
	}
	case ENEMY_FISH:
	{
		if (enemy_Motion.GetMotionNo() != FISHMOTION_MOVE)
		{
			enemy_Motion.ChangeMotion(FISHMOTION_MOVE);
		}
		return;
		break;
	}
	}


	if (!enemy_Dead)
	{
		//座標を移動
		enemy_Position.x += enemy_Move.x;

		enemy_Position.y += enemy_Move.y;

	}
	else
	{


		//敵が叩いたブロックと同じ位置にいた時
		if (enemy_DeadJump)
		{
			//一度だけ実行
			if (enemy_DisappearTime == ENEMY_DISAPPEARTIME)
			{
				enemy_Move.y = -7.0f;
				enemy_Move.x = -2.0f;
			}
			//座標を移動
			enemy_Position.x += enemy_Move.x;
			enemy_Position.y += enemy_Move.y;
		}

		//敵が消えるまでのウェイト
		enemy_DisappearTime--;
		if (enemy_DisappearTime <= 0)
		{
			enemy_DeadJump = false;
			enemy_srcDeadJump = false;
			//スケルトン以外は非表示
			if (enemy_Type != ENEMY_SKELETON)
			{
				enemy_Show = false;
			}
			else
			{
				//スケルトン復活処理
				if (enemy_Motion.GetMotionNo() != SKELETONMOTION_REVIVAL)
				{
					enemy_Motion.ChangeMotion(SKELETONMOTION_REVIVAL);
				}
				if (enemy_Motion.IsEndMotion())
				{
					enemy_Dead = false;
					enemy_Motion.ChangeMotion(SKELETONMOTION_WAIT);
					enemy_DisappearTime = ENEMY_DISAPPEARTIME;
				}
			}
		}
	}

	////敵の落下判定
	//if (enemy_Position.y > 1000)
	//{
	//	enemy_Show = false;
	//}
}

void CEnemy::Render(float wx, float wy)
{
	//非表示
	if (!enemy_Show)
	{
		return;
	}

	if (enemy_Type == ENEMY_MARIO && enemy_MarioDamageWait % 4 >= 2)
	{
		return;
	}
	//描画矩形
	CRectangle dr = enemy_RectTexture;
	//反転フラグがONの場合描画矩形を反転させる
	if (enemy_Reverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//テクスチャの描画
	enemy_pTexture->Render(enemy_Position.x - wx, enemy_Position.y - wy, dr);
	if (enemy_Dead)
	{
		return;
	}
	if (enemy_Type == ENEMY_SKELETON)
	{
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			m_ShotArray[i].Render(wx, wy);
		}
	}
	else if (enemy_Type == ENEMY_MARIO)
	{
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			m_ShotArray[i].Render(wx, wy);
		}
	}

}

void CEnemy::RenderDebug(float wx, float wy)
{
	//非表示
	if (!enemy_Show)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
	if (enemy_Type == ENEMY_MARIO)
	{
		CGraphicsUtilities::RenderString(600, 200, "ワープフラグ:%d", tmp_playerWarpFlg);
		CGraphicsUtilities::RenderString(600, 250, "POS:%f", tmp_playerPositionX);
		CGraphicsUtilities::RenderString(600, 300, "SPEED:%f", tmp_playerMoveX);
		CGraphicsUtilities::RenderString(600, 350, "JUMP:%d", tmp_playerJumpFlg);
		CGraphicsUtilities::RenderString(600, 400, "MARIO_JUMP:%d", jumpFlg);
		CGraphicsUtilities::RenderString(600, 450, "MARIO_NOW:%d", enemy_MarioNowAttackPettern);
		CGraphicsUtilities::RenderString(600, 500, "MARIO_ONNE:%d", one);
		CGraphicsUtilities::RenderString(600, 550, "MARIO_LOOP:%d", loop);
		CGraphicsUtilities::RenderString(600, 600, "MARIO_HP:%d", enemy_MarioHP);
		CGraphicsUtilities::RenderString(600, 650, "MARIO_DASHCOUNT:%d", dashCount);

	}
	if (enemy_Type == ENEMY_SKELETON)
		CGraphicsUtilities::RenderString(100, 700, "プレイヤーとの距離%f", enemy_DistanceBetweenToPlayer);
	if (enemy_Dead)
	{
		return;
	}
	if (enemy_Type == ENEMY_SKELETON)
	{
		//弾の描画
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			m_ShotArray[i].RenderDebug(wx, wy);
		}
		CRectangle ar = GetAttackRangeRect();
		CGraphicsUtilities::RenderRect(ar.Left - wx, ar.Top - wy, ar.Right - wx, ar.Bottom - wy, MOF_XRGB(0, 10, 255));
	}
	else if (enemy_Type == ENEMY_MARIO)
	{
		//弾の描画
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			m_ShotArray[i].RenderDebug(wx, wy);
		}
		CRectangle ar = GetAttackRangeRect();
		CGraphicsUtilities::RenderRect(ar.Left - wx, ar.Top - wy, ar.Right - wx, ar.Bottom - wy, MOF_XRGB(0, 10, 255));
	}
}


void CEnemy::Release(void)
{
	enemy_Motion.Release();
	m_ShotArray->Release();

}

void CEnemy::CollisionStage(float ox, float oy)
{
	if (enemy_Type == ENEMY_MARIO && enemy_MarioDead)
	{
		return;
	}
	enemy_Position.x += ox;
	enemy_Position.y += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (oy < 0)
	{
		enemy_Move.y = 0;
		if (enemy_Type == ENEMY_MARIO)
		{
			jumpFlg = false;
		}
	}
	else if (oy > 0 && enemy_Move.y < 0)
	{
		enemy_Move.y = 0;

	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (ox < 0 && enemy_Move.x > 0)
	{

		enemy_Move.x *= -1;
		enemy_Reverse = true;

	}
	else if (ox > 0 && enemy_Move.x < 0)
	{

		enemy_Move.x *= -1;
		enemy_Reverse = false;
	}

}

void CEnemy::ShotCollisionStage(float ox, float oy,int n)
{

		CVector2 shotPosition = Vector2(m_ShotArray[n].GetPositionX(), m_ShotArray[n].GetPositionY());
		shotPosition.x += ox;
		shotPosition.y += oy;
		m_ShotArray[n].SetPositionX(shotPosition.x);
		m_ShotArray[n].SetPositionY(shotPosition.y);
		float shotSpeed = m_ShotArray[n].GetSpeedY();
		float randomSpeed = CUtilities::RandomFloat();
		//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
		if (oy < 0)
		{

			shotSpeed *= -(1.0f + randomSpeed) ;

		}
		else if (oy > 0 && shotSpeed < 0)
		{
			shotSpeed *= -1.5;

		}
		if (ox < -2)
		{
			m_ShotArray[n].SetShow(false);
		}
		else if (ox > 2)
		{
			m_ShotArray[n].SetShow(false);
		}
		m_ShotArray[n].SetSpeedY(shotSpeed);
	
	
}

void CEnemy::Dead(bool bDead)
{
	enemy_Dead = bDead;
	if (enemy_Dead)
	{
		switch (enemy_Type)
		{
		case ENEMY_MUSH:
		{
			enemy_Motion.ChangeMotion(MUSHMOTION_DEAD);
			break;
		}
		case ENEMY_SKELETON:
		{
			enemy_Motion.ChangeMotion(SKELETONMOTION_DEAD);
			break;
		}
		case ENEMY_MARIO:
		{
			enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_DEAD);
			break;
		}
		}

	}
}

void CEnemy::DeadJump(bool jumpFlg)
{
	enemy_DeadJump = jumpFlg;
}

void CEnemy::SkeletonShot(void)
{
	if (enemy_Dead)
	{
		return;
	}
	if (enemy_AttackFlg)
	{
		enemy_Move.x = 0;
		//弾の発射
		if (enemy_ShotWait <= 0)
		{
			for (int i = 0; i < ENEMYSHOT_COUNT; i++)
			{
				if (m_ShotArray[i].GetShow())
				{
					continue;
				}
				if (!enemy_Dead)
				{
					enemy_ShotWait = 70;
					enemy_Motion.ChangeMotion(SKELETONMOTION_ATTACK);
				}
				if (enemy_Reverse)
				{
					m_ShotArray[i].Fire(GetRect().Left - 15, GetRect().Top + 10,
						(enemy_DistanceBetweenToPlayer * 0.015f) + 1.0f, (enemy_DistanceBetweenToPlayer * 0.015f) + 7.0f, enemy_Reverse);
				}
				else
				{
					m_ShotArray[i].Fire(GetRect().Right - 15, GetRect().Top + 10,
						(enemy_DistanceBetweenToPlayer * 0.015f) + 1.0f, (enemy_DistanceBetweenToPlayer * 0.015f) + 7.0f, enemy_Reverse);
				}

				break;
			}
		}
		else
		{
			if (enemy_Motion.GetMotionNo() == SKELETONMOTION_MOVE)
			{
				enemy_Motion.ChangeMotion(SKELETONMOTION_WAIT);
			}
			enemy_ShotWait--;
		}
	}
	else if (!enemy_Dead)
	{
		if (enemy_Motion.GetMotionNo() != SKELETONMOTION_MOVE)
		{
			enemy_Motion.ChangeMotion(SKELETONMOTION_MOVE);
		}
		if (enemy_Reverse)
		{
			enemy_Move.x = -0.5;
		}
		else
		{
			enemy_Move.x = 0.5;
		}
		enemy_ShotWait = 25;

	}
	//弾の更新
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}
}

void CEnemy::DistanceBetweenPlayer(float px)
{
	if (enemy_Type == ENEMY_SKELETON)
	{
		if (enemy_Position.x > px)
		{
			enemy_Reverse = true;
			enemy_DistanceBetweenToPlayer = enemy_Position.x - px;
		}
		else if (enemy_Position.x < px)
		{
			enemy_Reverse = false;
			enemy_DistanceBetweenToPlayer = px - enemy_Position.x;
		}
	}

}

void CEnemy::MarioAttack(void)
{
	if (enemy_Position.y > 800)
	{
		enemy_Dead = true;
		return;
	}
	//プレイヤーとマリオとの距離計算
	tmp_DistanceBetweenPlayer = 0;
	if (enemy_Position.x > tmp_playerPositionX)
	{
		tmp_DistanceBetweenPlayer = enemy_Position.x - tmp_playerPositionX;
	}
	else if (enemy_Position.x < tmp_playerPositionX)
	{
		tmp_DistanceBetweenPlayer = tmp_playerPositionX - enemy_Position.x;
	}
	if (g_pInput->IsKeyPush(MOFKEY_R))
	{
		debugModeFlg = ((debugModeFlg) ? false : true);
		if (debugModeFlg)
		{
			enemy_MarioNowAttackPettern = 0;
			loop = 0;
			one = false;
			enemy_Move.x = 0;
			enemy_Move.y = 0;
		}
	}
	if (debugModeFlg)
	{
		if (g_pInput->IsKeyPush(MOFKEY_1))
		{
			loop = 0;
			one = false;
			enemy_Move.x = 0;
			enemy_Move.y = 0;
			enemy_MarioNowAttackPettern = 1;
		}
		if (g_pInput->IsKeyPush(MOFKEY_2))
		{
			loop = 0;
			one = false;
			enemy_Move.x = 0;
			enemy_Move.y = 0;
			enemy_MarioNowAttackPettern = 2;
		}
		if (g_pInput->IsKeyPush(MOFKEY_3))
		{
			loop = 0;
			one = false;
			enemy_Move.x = 0;
			enemy_Move.y = 0;
			enemy_MarioNowAttackPettern = 3;
		}
		if (g_pInput->IsKeyPush(MOFKEY_4))
		{
			loop = 0;
			one = false;
			enemy_Move.x = 0;
			enemy_Move.y = 0;
			enemy_MarioNowAttackPettern = 4;
		}
		if (g_pInput->IsKeyPush(MOFKEY_5))
		{
			loop = 0;
			one = false;
			enemy_Move.x = 0;
			enemy_Move.y = 0;
			enemy_MarioNowAttackPettern = 5;
		}
		if (g_pInput->IsKeyPush(MOFKEY_6))
		{
			loop = 0;
			one = false;
			enemy_Move.x = 0;
			enemy_Move.y = 0;
			enemy_MarioNowAttackPettern = 6;
		}
		if (g_pInput->IsKeyPush(MOFKEY_7))
		{
			loop = 0;
			one = false;
			enemy_Move.x = 0;
			enemy_Move.y = 0;
			enemy_MarioNowAttackPettern = 7;
		}
		if (g_pInput->IsKeyPush(MOFKEY_8))
		{
			loop = 0;
			one = false;
			enemy_Move.x = 0;
			enemy_Move.y = 0;
			enemy_MarioNowAttackPettern = 8;
		}
	}

	//行動条件
	if (enemy_MarioNowAttackPettern > 0 && enemy_MarioNowAttackPettern != MARIOATTACK_DASH)
	{
		dashCount = 0;
	}
	if (enemy_MarioNowAttackPettern == 0 && !debugModeFlg)
	{
		MarioActionConditions();
	}
	


	
	//行動処理
	switch (enemy_MarioNowAttackPettern)
	{
			//ダッシュ攻撃
		case MARIOATTACK_DASH:
		{
			MarioActionModeDash();
			break;
		}
		//ヒップドロップ
		case MARIOATTACK_HIPDROP:
		{
			MarioActionModeHipDrop();
			break;
		}
		//ターン
		case MARIOATTACK_TURN:
		{
			MarioActionModeTurn();
			break;
		}
		//ジャンプ攻撃
		case MARIOATTACK_JUMP:
		{
			MarioActionModeJump();
			break;
		}
		//ホップジャンプ攻撃
		case MARIOATTACK_HOPJUMP:
		{
			MarioActionModeHopJump();
			break;
		}
		//ファイア
		case MARIOATTACK_FIRE:
		{
			MarioActionModeFire();
			break;
		}
		//ダメージ
		case MARIOATTACK_DAMAGE:
		{
			MarioActionModeDamage();
			break;
		}
		//死亡
		case MARIOATTACK_DEAD:
		{
			MarioActionModeDead();
			break;
		}
		//移動
		default:
		{
			MarioActionModeMove();
			break;
		}

	}

	//弾の更新
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}
	
}

void CEnemy::GetPlayerInfo(float positionX, float moveX, bool jumpFlg, bool warpFlg)
{
	tmp_playerPositionX = positionX;
	tmp_playerMoveX = moveX;
	tmp_playerJumpFlg = jumpFlg;
	if (warpFlg)
	{
		tmp_playerWarpFlg = warpFlg;
	}
}

void CEnemy::MarioDamage(float damage)
{
	enemy_MarioHP -= damage;
	enemy_MarioDamageFlg = true;
	enemy_MarioDamageWait = 60;
	if (enemy_MarioHP <= 3 && !enemy_MarioChangeFlg)
	{
		enemy_MarioChangeFlg = true;

	}
	else if (enemy_MarioHP <= 0)
	{
		enemy_MarioDead = true;
		enemy_MarioNowAttackPettern = MARIOATTACK_DEAD;
	}

	if (!enemy_MarioDead)
	{
		enemy_MarioNowAttackPettern = MARIOATTACK_DAMAGE;
	}
}

void CEnemy::MarioActionConditions()
{
	//行動パターン条件
	//ダッシュ
	
	if (tmp_DistanceBetweenPlayer > 550 && !tmp_playerJumpFlg && dashCount <= 1)
	{
		enemy_MarioNowAttackPettern = MARIOATTACK_DASH;
		return;
	}
	//ホップジャンプ
	if (tmp_DistanceBetweenPlayer > 550 && tmp_playerJumpFlg)
	{
		enemy_MarioNowAttackPettern = MARIOATTACK_HOPJUMP;
		return;
	}
	//ジャンプ
	if (tmp_DistanceBetweenPlayer < 150 && tmp_DistanceBetweenPlayer > 50 && !tmp_playerJumpFlg)
	{
		enemy_MarioNowAttackPettern = MARIOATTACK_JUMP;
		return;
	}
	//ファイア
	if (tmp_DistanceBetweenPlayer < 300 && tmp_DistanceBetweenPlayer > 150 && !tmp_playerJumpFlg && otherAttack > 3 && changeFireMode)
	{
		enemy_MarioNowAttackPettern = MARIOATTACK_FIRE;
		return;
	}
	//ヒップドロップ
	if (tmp_DistanceBetweenPlayer < 400 && tmp_DistanceBetweenPlayer > 350 && tmp_playerJumpFlg)
	{
		if (enemy_Position.x > tmp_playerPositionX && !enemy_Reverse)
		{
			enemy_MarioNowAttackPettern = MARIOATTACK_HIPDROP;
		}
		else if (enemy_Position.x < tmp_playerPositionX && enemy_Reverse)
		{
			enemy_MarioNowAttackPettern = MARIOATTACK_HIPDROP;
		}
		return;
	}
	//ターン
	if (tmp_DistanceBetweenPlayer < 180 && tmp_DistanceBetweenPlayer > 100 && !tmp_playerJumpFlg)
	{
		if (enemy_Position.x > tmp_playerPositionX && !enemy_Reverse)
		{
			enemy_MarioNowAttackPettern = MARIOATTACK_TURN;
		}
		else if (enemy_Position.x < tmp_playerPositionX && enemy_Reverse)
		{
			enemy_MarioNowAttackPettern = MARIOATTACK_TURN;
		}
		return;
	}

}

void CEnemy::MarioActionModeDash()
{
	//ダッシュ
	if (enemy_Position.x > tmp_playerPositionX && !one)
	{
		if (changeFireMode)
		{
			if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_MOVE)
			{
				enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_MOVE);
			}
		}
		else
		{
			if (enemy_Motion.GetMotionNo() != MARIOMOTION_MOVE)
			{
				enemy_Motion.ChangeMotion(MARIOMOTION_MOVE);
			}
		}
		enemy_Move.x = -20;
		enemy_Reverse = true;
		one = true;
	}
	else if (enemy_Position.x < tmp_playerPositionX && !one)
	{
		if (changeFireMode)
		{
			if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_MOVE)
			{
				enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_MOVE);
			}
		}
		else
		{
			if (enemy_Motion.GetMotionNo() != MARIOMOTION_MOVE)
			{
				enemy_Motion.ChangeMotion(MARIOMOTION_MOVE);
			}
		}
		enemy_Move.x = 20;
		enemy_Reverse = false;
		one = true;
	}
	//ブレーキ
	if (enemy_Position.x > 7080 && enemy_Move.x > 0 && one)
	{
		enemy_Move.x -= 10;
		if (enemy_Move.x <= 10)
		{
			enemy_Move.x = 0;
		}
		enemy_Reverse = false;
		if (changeFireMode)
		{
			if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_BRAKE)
			{
				enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_BRAKE);
			}
		}
		else
		{
			if (enemy_Motion.GetMotionNo() != MARIOMOTION_BRAKE)
			{
				enemy_Motion.ChangeMotion(MARIOMOTION_BRAKE);
			}
		}

	}
	else if (enemy_Position.x < 6220 && enemy_Move.x < 0 && one)
	{
		enemy_Move.x += 10;
		if (enemy_Move.x >= -10)
		{
			enemy_Move.x = 0;
		}
		enemy_Reverse = true;

		if (changeFireMode)
		{
			if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_BRAKE)
			{
				enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_BRAKE);
			}
		}
		else
		{
			if (enemy_Motion.GetMotionNo() != MARIOMOTION_BRAKE)
			{
				enemy_Motion.ChangeMotion(MARIOMOTION_BRAKE);
			}
		}

	}
	//折り返し
	else if (enemy_Motion.IsEndMotion() && one)
	{
		loop++;
		one = false;
		if (loop > 1)
		{
			otherAttack++;
			enemy_MarioNowAttackPettern = 0;
			dashCount++;
			loop = 0;
			return;
		}
	}

}

void CEnemy::MarioActionModeHipDrop()
{
	if (!jumpFlg && one)
	{
		if (enemy_Position.x > tmp_playerPositionX)
		{
			enemy_Reverse = true;
		}
		if (enemy_Position.x < tmp_playerPositionX)
		{
			enemy_Reverse = false;
		}
		one = false;
		otherAttack++;
		enemy_MarioNowAttackPettern = 0;
		return;
	}
	if (!jumpFlg)
	{
		enemy_Move.y = -5;
		jumpFlg = true;
	}
	else if (!one && jumpFlg)
	{
		if (enemy_Position.x > tmp_playerPositionX)
		{
			enemy_Move.x = -15;
			enemy_Move.y = -15;
			enemy_Reverse = true;
		}
		if (enemy_Position.x < tmp_playerPositionX)
		{
			enemy_Move.x = 15;
			enemy_Move.y = -15;
			enemy_Reverse = false;
		}
		if (tmp_DistanceBetweenPlayer < 10)
		{
			enemy_Move.x = 0;
			enemy_Move.y = 9;
			one = true;
			if (changeFireMode)
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_HIPDROP)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_HIPDROP);
				}
			}
			else
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_HIPDROP)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_HIPDROP);
				}
			}
			return;
		}
		if (enemy_Move.y < 0)
		{
			if (changeFireMode)
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_JUMPSTART)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_JUMPSTART);
				}
			}
			else
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_JUMPSTART)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_JUMPSTART);
				}
			}
		}

	}
}

void CEnemy::MarioActionModeTurn()
{
	if (enemy_Position.x > tmp_playerPositionX && !enemy_Reverse)
	{
		enemy_Reverse = true;
	}
	else if (enemy_Position.x < tmp_playerPositionX && enemy_Reverse)
	{
		enemy_Reverse = false;
	}
	one = false;
	loop = 0;
	enemy_MarioNowAttackPettern = 0;
}

void CEnemy::MarioActionModeJump()
{
	if (!jumpFlg && one)
	{
		one = false;
		otherAttack++;
		enemy_MarioNowAttackPettern = 0;
		return;
	}
	if (!jumpFlg)
	{
		if (enemy_Position.x > tmp_playerPositionX && enemy_Reverse)
		{
			enemy_Move.x = -6;
			enemy_Move.y = -6;
		}
		else if (enemy_Position.x < tmp_playerPositionX && !enemy_Reverse)
		{
			enemy_Move.x = 6;
			enemy_Move.y = -6;
		}
		else
		{
			one = false;
			enemy_MarioNowAttackPettern = 0;
			return;
		}
		jumpFlg = true;
	}
	else
	{
		if (enemy_Move.y < 0)
		{
			if (changeFireMode)
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_JUMPSTART)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_JUMPSTART);
				}
			}
			else
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_JUMPSTART)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_JUMPSTART);
				}
			}
		}
		else if (enemy_Move.y > 0)
		{
			if (changeFireMode)
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_JUMPEND)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_JUMPEND);
				}
			}
			else
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_JUMPEND)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_JUMPEND);
				}
			}
		}
		one = true;
	}
}

void CEnemy::MarioActionModeHopJump()
{
	if (!jumpFlg && loop > 2)
	{
		one = false;
		loop = 0;
		otherAttack++;
		enemy_MarioNowAttackPettern = 0;
		return;
	}
	if (!jumpFlg)
	{
		if (enemy_Position.x > tmp_playerPositionX)
		{
			enemy_Move.x = -5;
			enemy_Move.y = -10;
			enemy_Reverse = true;
		}
		else if (enemy_Position.x < tmp_playerPositionX)
		{
			enemy_Move.x = 5;
			enemy_Move.y = -10;
			enemy_Reverse = false;
		}
		else
		{
			one = false;
			enemy_MarioNowAttackPettern = 0;
			return;
		}
		loop++;
		jumpFlg = true;
	}
	else
	{
		if (enemy_Move.y < 0)
		{
			if (changeFireMode)
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_JUMPSTART)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_JUMPSTART);
				}
			}
			else
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_JUMPSTART)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_JUMPSTART);
				}
			}
		}
		else if (enemy_Move.y > 0)
		{
			if (changeFireMode)
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_JUMPEND)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_JUMPEND);
				}
			}
			else
			{
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_JUMPEND)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_JUMPEND);
				}
			}
		}

	}
}

void CEnemy::MarioActionModeFire()
{
	if (!one)
	{
		if (loop <= 3)
		{
			if (!fire)
			{
				enemy_Move.x = 0;
				if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_ATTACK)
				{
					enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_ATTACK);
				}

				if (enemy_Motion.IsEndMotion() && enemy_Motion.GetMotionNo() == MARIOMOTION_FIRE_ATTACK)
				{
					fire = true;
					

				}
			}
			else
			{
				if (enemy_Position.x > tmp_playerPositionX)
				{
					enemy_Reverse = true;
				}
				else if (enemy_Position.x < tmp_playerPositionX)
				{
					enemy_Reverse = false;
				}
				if (enemy_ShotWait < 0)
				{

					for (int i = 0; i < ENEMYSHOT_COUNT; i++)
					{
						if (m_ShotArray[i].GetShow())
						{
							continue;
						}
						if (!enemy_Dead)
						{
							enemy_ShotWait = 80;
						}
						m_ShotArray[i].Fire(enemy_Position.x + 30, enemy_Position.y + 10,
							5, 5, enemy_Reverse);
						break;
					}
					
					
				}
				else
				{
					enemy_ShotWait--;
					
				}
				if (enemy_ShotWait < 0)
				{
					loop++;
					fire = false;
					enemy_Motion.SetTime(0);
				}
			}
		}
		else if(enemy_ShotWait <= 0 && loop > 3)
		{
			one = false;
			fire = false;
			otherAttack = 0;
			loop = 0;
			enemy_MarioNowAttackPettern = 0;
			enemy_ShotWait = 0;
			return;
		}
		else if(enemy_ShotWait > 0 && loop > 3)
		{
			enemy_ShotWait--;
		}

	}
	else
	{
		one = false;
		fire = false;
		otherAttack = 0;
		loop = 0;
		enemy_MarioNowAttackPettern = 0;
		return;
	}
}

void CEnemy::MarioActionModeDamage()
{
	enemy_Move.x = 0;
	enemy_Move.y = 2;
	if (enemy_MarioChangeFlg && !changeFireMode)
	{
		one = true;
		changeFireMode = true;
	}
	if (!one)
	{
		if (changeFireMode)
		{
			if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_DAMAGE)
			{
				enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_DAMAGE);
			}
		}
		else
		{
			if (enemy_Motion.GetMotionNo() != MARIOMOTION_DAMAGE)
			{
				enemy_Motion.ChangeMotion(MARIOMOTION_DAMAGE);
			}
		}


	}
	else
	{
		if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_WAIT)
		{
			enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_WAIT);
		}
	}
	enemy_MarioDamageWait--;
	if (enemy_MarioDamageWait <= 0)
	{
		one = false;
		loop = 0;
		fire = false;
		enemy_ShotWait = 0;
		enemy_MarioDamageWait = 0;
		enemy_MarioNowAttackPettern = 0;
		enemy_MarioDamageFlg = false;
		return;
	}
}

void CEnemy::MarioActionModeDead()
{
	if (!one)
	{
		enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_DEAD);
		enemy_Move.x = 0;
		enemy_Move.y = -20;
		one = true;
	}
	else
	{
		if (enemy_Position.y > 800)
		{
			enemy_Dead = true;
			return;
		}
	}
}

void CEnemy::MarioActionModeMove()
{
	if (debugModeFlg)
	{
		return;
	}
	if (changeFireMode)
	{
		if (enemy_Motion.GetMotionNo() != MARIOMOTION_FIRE_MOVE)
		{
			enemy_Motion.ChangeMotion(MARIOMOTION_FIRE_MOVE);
		}
	}
	else
	{
		if (enemy_Motion.GetMotionNo() != MARIOMOTION_MOVE)
		{
			enemy_Motion.ChangeMotion(MARIOMOTION_MOVE);
		}
	}

	if (enemy_Reverse)
	{
		enemy_Move.x = -5;
	}
	else
	{
		enemy_Move.x = 5;
	}
}


