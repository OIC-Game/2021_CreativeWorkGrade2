#pragma once

//���݂���V�[���̗�
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_GAME,
	SCENENO_GAMEOVER,
	SCENENO_INFOMATION,
};

/*�v���C���[*/
//�ړ����x
#define		PLAYER_SPEED 0.3f
#define		PLAYER_WATER_SPEED 0.2f
//�ړ��ō����x
#define		PLAYER_TOPSPEED 5
#define		PLAYER_WATER_TOPSPEED 3
//�W�����v���x
#define		PLAYER_JUMPSPEED 12
#define		PLAYER_WATER_JUMPSPEED 6
//�G�𓥂݂����Ƃ��̃W�����v���x
#define		PLAYER_ENEMYSTEP_JUMPSPEED 5
//�d��
#define		PLAYER_GRAVITY 0.4f
#define		PLAYER_WATER_GRAVITY 0.25f
//�ő�d��
#define		PLAYER_MAXGRAVITY 20.0f
#define		PLAYER_WATER_MAXGRAVITY 3.5f
//���S���E�F�C�g
#define		PLAYER_DEADWAIT 30
//�������C�t
#define		PLAYER_INITIALLIFE 3
//�����蔻��T�C�Y
#define		PLAYER_RECTSIZE_X 32
#define		PLAYER_RECTSIZE_Y 64
//HP
#define		PLAYER_HP 1
//�N���A�[�n�_
#define		PLAYER_CLEAR_POSITIONX 4573
//���G���ԁi�T�C�Y�ύX���j
#define		PLAYER_INVINCIBLE 90



/*�G*/
//�d��
#define		 ENEMY_GRAVITY 0.4f
#define		 ENEMY_BLOCKJUMP 7
//���Ŏ���
#define		 ENEMY_DISAPPEARTIME 120
//�}���IHP
#define		 ENEMY_MARIOHP 6

/*�A�C�e��*/
#define		 ITEM_GRAVITY 0.4f
#define		 ITEM_SPEED 0.3f
#define		 ITEM_TOPSPEED 5
#define		 ITEM_BLOCKJUMP 7


/*�X�e�[�W*/
#define		STAGE_CHIPMOVE 10
enum tag_STAGENUMBER
{
	STAGE_1_1,
	STAGE_2_1,
	STAGE_LAST,

	STAGE_COUNT,
};
enum tag_STAGESTATE
{
	STAGESTATE_GROUND,
	STAGESTATE_WATER,
	STAGESTATE_SKY,
};

/*�}�b�v�`�b�v*/
//�u���b�N
#define		CHIP_BLOCK 19
#define		CHIP_QUESTION 12
#define		CHIP_EMOJI 4
#define		CHIP_HARDBLOCK 21
#define		CHIP_COINBLOCK 25
#define		CHIP_BLUEBLOCK 41
#define		CHIP_BLUEHARDBLOCK 42

//�S�[���t���b�O
#define		CHIP_GOALFLAG_L 13
#define		CHIP_GOALFLAG_R 14
#define		CHIP_GOALBALL 6  
#define		CHIP_GOALROD 22
//�N���A��J�ڔ���u���b�N
#define		CHIP_CLEARTRANSITION 32

/*��������*/
#define		GAME_TIMELIMIT 150
#define		GAME_TIMELIMIT_BOSS 300

/*�X�R�A*/
#define		SCORE_GETITEM 1000
#define		SCORE_COIN 200
#define		SCORE_ENEMYSTEP 100
#define		SCORE_BLOCKDESTRIY 50
#define		SCORE_TIME 100
//�X�R�A�\������
#define		SCORE_DISPLAYTIME 60

