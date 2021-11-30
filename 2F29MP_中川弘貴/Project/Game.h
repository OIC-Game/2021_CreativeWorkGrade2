#pragma once
#include "Fade.h"

//�Ղ�̃T�C�Y
#define		PUYO_SIZE	50
//�t�B�[���h�̃}�X��
#define		FH 13
#define		FW 8
//�u���b�N�T�C�Y
#define		BL 50
//���R�����̑��x
#define		DROP_SPEED				80
//�Ղ悪����ɂ���Ĉړ����鑬�x
#define		PUYO_SPEED				5
//�����ʒu
#define		INIT_POSITION_X			200.0f
#define		INIT_POSITION_Y			100.0f
//�t�B�[���h���W
#define		INIT_FIELD_POSITION_X	3
#define		INIT_FIELD_POSITION_Y	0
//�X�s�������l
#define		INIT_SPIN_X				0
#define		INIT_SPIN_Y				-50.0f
//���f�B�J�E���g���\������鎞��
#define		READY_TIME				200
//�Ղ悪�������ɂ���Ă��΂₭�ړ�����悤�ɂȂ�܂łɂ����鎞��
#define		INIT_HOLD_TIME			10
//����s�\�҂�����
#define		WAIT_TIME				20

enum Type
{
	Empty,
	Wall,
	Red,
	Blue,
	Yellow,
	Green,

	TypeCount,
};

//���쒆�̃T�u�Ղ�̈ʒu
enum Rotation
{
	Top,
	Right,
	Bottom,
	Left,
};

//�S�̗̂���
enum Flow
{
	Ready,
	Pause,
	Drop,
	Tear,
	Chain,
	ReStart,
	GameOver,
};

struct FieldPos
{
	int x;
	int y;
};

class CGame {
private:

	//�Ղ�i�[�p�z��
	int			m_field[FH][FW];
	//���삵�Ă���A���ɍ~���Ă���Ղ�̐F
	int			m_type[2][2];


	//�^�C�}�[

	//���������܂ő҂ϐ�
	int			m_dropTimeCnt;
	int			m_leftRotateTimeCnt;
	//�܂���Ŗ��O�ς���@�@�Ԃ𐶂ݏo�����߃^�C���ϐ�
	int			m_waitTimeCnt;
	//ready�J�E���g
	int			m_readyTimeCnt;
	//�Ղ�𒷉����ɂ���Ĉړ�������ۂɓ�����}�����邽�߂̃^�C��
	int			m_downHoldTimeCnt;
	int			m_leftHoldTimeCnt;
	int			m_rightHoldTimeCnt;

	//�X�R�A
	int			m_maxChainCnt;
	int			m_score;


	//�A��

	//�Ղ悪���ł���
	bool		m_chainFlg;
	//��ł��ǂł��Ȃ��Ղ�ł���
	bool		m_puyoCheckFlg[FH][FW];
	//���ł�����Ղ�
	bool		m_destroyFlg[FH][FW];
	//�����F�����q�����Ă��邩
	int			m_bondCnt;
	//�A����
	int			m_chainCnt;

	bool		m_endFlg;
	
	//���삷��Ղ���W
	Vector2		m_pos;
	//��]�ɂ����W�̕ω�
	Vector2		m_spin;
	//�t�B�[���h�z��Ɋi�[���邽�߂̍��W
	FieldPos	m_sFldPos;
	//�Ղ�̌���
	Rotation	m_eRotation;
	//����𐧌�
	Flow		m_eFlow;
	//����
	CRandom		m_random;

	//�Ղ�f��
	CTexture    m_RedPuyoTexture;
	CTexture    m_BluePuyoTexture;
	CTexture    m_YellowPuyoTexture;
	CTexture    m_GreenPuyoTexture;
	//�w�i
	CTexture	m_BackTexture;
	//�Q�[���I�[�o�[�̃o�c����
	CTexture	m_CrossMarkTexture;
	//�Q�[���I�[�o�[���̔w�i
	CTexture	m_GameOverTexture;
	//�|�[�Y���
	CTexture    m_PauseTexture;

	//���f��
	CSoundBuffer	m_chainSound;
	CSoundBuffer	m_moveSound;
	CSoundBuffer	m_setSound;
	CSoundBuffer	m_rotateSound;
	CSoundBuffer	m_gameBGM;
	CSoundBuffer	m_pauseSound;
	CSoundBuffer	m_gameOverSound;

	//�t�F�[�h�p
	CFade			fade;

public:
	CGame();
	~CGame();
	bool Load(void);
	void Initialize(void);
	void ChainCheck(int y, int x);
	void Update(void);
	void ReadyUpdate();
	void PauseUpdate();
	void DropUpdate();
	void TearUpdate();
	void ChainUpdate();
	void ReStartUpdate();
	void GameOverUpdate();
	void Render(void);
	void Release(void);
};