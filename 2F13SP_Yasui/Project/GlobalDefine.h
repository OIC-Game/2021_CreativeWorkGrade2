#pragma once

/*プレイヤー*/
//移動速度
#define		PLAYER_SPEED 0.3f
//移動最高速度
#define		PLAYER_TOPSPEED 5
//ジャンプ速度
#define		PLAYER_JUMPSPEED 12
//敵を踏みつけたときのジャンプ速度
#define		PLAYER_ENEMYSTEP_JUMPSPEED 5
//重力
#define		PLAYER_GRAVITY 0.4f
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



/*敵*/
//重力
#define		 ENEMY_GRAVITY 0.4f
#define		 ENEMY_BLOCKJUMP 7
//消滅時間
#define		 ENEMY_DISAPPEARTIME 120
//マリオHP
#define		 ENEMY_MARIOHP 3

/*アイテム*/
#define		 ITEM_GRAVITY 0.4f
#define		 ITEM_SPEED 0.3f
#define		 ITEM_TOPSPEED 5
#define		 ITEM_BLOCKJUMP 7


/*ステージ*/
#define		 STAGE_CHIPMOVE 10
/*マップチップ*/
//ブロック
#define		CHIP_BLOCK 19
#define		CHIP_QUESTION 12
#define		CHIP_EMOJI 4
#define		CHIP_HARDBLOCK 21
#define		CHIP_COINBLOCK 25
//ゴールフラッグ
#define		CHIP_GOALFLAG_L 13
#define		CHIP_GOALFLAG_R 14
#define		CHIP_GOALBALL 6  
#define		CHIP_GOALROD 22
//クリア後遷移判定ブロック
#define		CHIP_CLEARTRANSITION 32

/*制限時間*/
#define		GAME_TIMELIMIT 150
#define		GAME_TIMELIMIT_BOSS 300

/*スコア*/
#define		SCORE_GETITEM 1000
#define		SCORE_COIN 200
#define		SCORE_ENEMYSTEP 100
#define		SCORE_BLOCKDESTRIY 50
#define		SCORE_TIME 100
//スコア表示時間
#define		SCORE_DISPLAYTIME 60

