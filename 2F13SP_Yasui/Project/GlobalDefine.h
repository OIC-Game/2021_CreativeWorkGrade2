#pragma once

//存在するシーンの列挙
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_GAME,
	SCENENO_GAMEOVER,
	SCENENO_INFOMATION,
};

/*プレイヤー*/
//移動速度
#define		PLAYER_SPEED 0.3f
#define		PLAYER_WATER_SPEED 0.2f
//移動最高速度
#define		PLAYER_TOPSPEED 5
#define		PLAYER_WATER_TOPSPEED 3
//ジャンプ速度
#define		PLAYER_JUMPSPEED 12
#define		PLAYER_WATER_JUMPSPEED 6
//敵を踏みつけたときのジャンプ速度
#define		PLAYER_ENEMYSTEP_JUMPSPEED 5
//重力
#define		PLAYER_GRAVITY 0.4f
#define		PLAYER_WATER_GRAVITY 0.25f
//最大重力
#define		PLAYER_MAXGRAVITY 20.0f
#define		PLAYER_WATER_MAXGRAVITY 3.5f
//死亡時ウェイト
#define		PLAYER_DEADWAIT 30
//初期ライフ
#define		PLAYER_INITIALLIFE 3
//当たり判定サイズ
#define		PLAYER_RECTSIZE_X 32
#define		PLAYER_RECTSIZE_Y 64
//HP
#define		PLAYER_HP 1
//クリアー地点
#define		PLAYER_CLEAR_POSITIONX 4573
//無敵時間（サイズ変更時）
#define		PLAYER_INVINCIBLE 90
//移動する床用追加矩形
#define		PLAYER_ADD_BUTTOMRECT 8



/*敵*/
//重力
#define		 ENEMY_GRAVITY 0.4f
#define		 ENEMY_BLOCKJUMP 7
//消滅時間
#define		 ENEMY_DISAPPEARTIME 120
//マリオHP
#define		 ENEMY_MARIOHP 6

/*アイテム*/
#define		 ITEM_GRAVITY 0.4f
#define		 ITEM_SPEED 0.3f
#define		 ITEM_TOPSPEED 5
#define		 ITEM_BLOCKJUMP 7


/*ステージ*/
#define		STAGE_CHIPMOVE 10
enum tag_STAGENUMBER
{
	STAGE_1_1,
	STAGE_2_1,
	STAGE_3_1,
	STAGE_LAST,

	STAGE_COUNT,
};
enum tag_STAGESTATE
{
	STAGESTATE_GROUND,
	STAGESTATE_WATER,
	STAGESTATE_SKY,
};

/*マップチップ*/
//ブロック
#define		CHIP_BLOCK 19
#define		CHIP_QUESTION 12
#define		CHIP_EMOJI 4
#define		CHIP_HARDBLOCK 21
#define		CHIP_COINBLOCK 25
#define		CHIP_BLUEBLOCK 41
#define		CHIP_BLUEHARDBLOCK 42

//ゴールフラッグ
#define		CHIP_GOALFLAG_L 13
#define		CHIP_GOALFLAG_R 14
#define		CHIP_GOALBALL 6  
#define		CHIP_GOALROD 22
//クリア後遷移判定ブロック
#define		CHIP_CLEARTRANSITION 32

/*制限時間*/
#define		GAME_TIMELIMIT 150
#define		GAME_TIMELIMIT_BOSS 400

/*スコア*/
#define		SCORE_GETITEM 1000
#define		SCORE_COIN 200
#define		SCORE_ENEMYSTEP 100
#define		SCORE_BLOCKDESTRIY 50
#define		SCORE_TIME 100
//スコア表示時間
#define		SCORE_DISPLAYTIME 60

//時間と値のキーフレーム
struct KeyFrame {
	float		value;
	float		time;
};
/**
 * @brief		キーフレームの配列から現在の状態を求める
 * @param[in]	keys		キーフレームの配列
 * @param[in]	keyCount	キーフレームの配列の数
 * @param[in]	t			現在の時間
 * @return		時間[t]の時の状態
 */
static float KeyFrameAnimation(KeyFrame* keys, int keyCount, float t) {
	//結果
	float re = 0;
	//スタートしていない
	if (t < keys[0].time)
	{
		re = keys[0].value;
	}
	//ゴール済み
	else if (t >= keys[keyCount - 1].time)
	{
		re = keys[keyCount - 1].value;
	}
	//間の位置を求める
	else
	{
		for (int i = 1; i < keyCount; i++)
		{
			//キーの時間より時間が手前なら
			if (t < keys[i].time)
			{
				//補間した値を計算する
				//この区間の開始の状態
				float start = keys[i - 1].value;
				//この区間で変化する量
				float cval = keys[i].value - keys[i - 1].value;
				//この区間にかかる時間
				float ctime = keys[i].time - keys[i - 1].time;
				//この区間を進んだ時間
				float now = t - keys[i - 1].time;
				re = start + cval * (now / ctime);
				break;
			}
		}
	}
	//結果を返す
	return re;
}