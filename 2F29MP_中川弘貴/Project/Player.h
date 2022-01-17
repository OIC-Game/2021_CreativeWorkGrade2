#pragma once
#include "GameApp.h"
#include "AI.h"

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
#define		INIT_POSITION_Y			150.0f
//�t�B�[���h���W
#define		INIT_FIELD_POSITION_X	3
#define		INIT_FIELD_POSITION_Y	1
//�X�s�������l
#define		INIT_SPIN_X				0
#define		INIT_SPIN_Y				-50.0f

//�Ղ悪�������ɂ���Ă��΂₭�ړ�����悤�ɂȂ�܂łɂ����鎞��
#define		INIT_HOLD_TIME			10
//����s�\�҂�����
#define		WAIT_TIME				20
//�N�C�b�N�^�[�����͎�t����
#define		QUICKTURN_RECEIPTION_TIME	20

enum Type
{
	Empty,
	Wall,
	Red,
	Blue,
	Yellow,
	Green,
	Obstacle,

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
	Drop,
	Tear,
	Chain,
	ReStart,
};

struct FieldPos
{
	int x;
	int y;
};
class CPlayer
{
private:
	//Computer
	CComputer	m_AI;

	//�Ղ�i�[�p�z��
	int			m_field[FH][FW];
	//���삵�Ă���A���ɍ~���Ă���Ղ�̐F
	int			m_type[2][2];

	//�^�C�}�[

	//���������܂ő҂ϐ�
	int			m_dropTimeCnt;
	int			m_rotateTimeCnt;
	//�܂���Ŗ��O�ς���@�@�Ԃ𐶂ݏo�����߃^�C���ϐ�
	int			m_waitTimeCnt;

	//�Ղ�𒷉����ɂ���Ĉړ�������ۂɓ�����}�����邽�߂̃^�C��
	int			m_downHoldTimeCnt;
	int			m_leftHoldTimeCnt;
	int			m_rightHoldTimeCnt;

	//�X�R�A
	int			m_maxChainCnt;
	int			m_score;

	//��]��
	int			m_rotateCnt;

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

	//������܂Ղ�
	int			m_sendObstacleCnt;
	int			m_sendObstacleCntTemp;
	bool		m_receiveFlg;

	bool		m_deadFlg;

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
	CRandom		m_obstaSetPosRandom;

	//�Ղ�f��
	CTexture    m_RedPuyoTexture;
	CTexture    m_BluePuyoTexture;
	CTexture    m_YellowPuyoTexture;
	CTexture    m_GreenPuyoTexture;
	CTexture	m_ObstaclePuyoTexture;
	//�Q�[���I�[�o�[�̃o�c����
	CTexture	m_CrossMarkTexture;

	//���f��
	CSoundBuffer	m_chainSound;
	CSoundBuffer	m_moveSound;
	CSoundBuffer	m_setSound;
	CSoundBuffer	m_rotateSound;


public:
	CPlayer();
	~CPlayer();
	void Load(void);
	void Initialize(bool vsAiFlg);
	void ChainCheck(int y, int x);
	void Update(bool vsAiFlg, int receiveObstacleCnt);
	void DropUpdate(bool vsAiFlg);
	void TearUpdate();
	void ChainUpdate(int receiveObstacleCnt);
	void ReStartUpdate(bool vsAiFlg);
	void Movement(bool vsAiFlg);
	void Rotate(bool vsAiFlg);
	void Render(bool vsAiFlg, bool readyFlg, int receiveObstacleCnt);
	void Release(void);
	void FieldRender(int initPosX);
	void NextPuyoRender(int x, int y);
	void MovingPuyoRender(bool readyFlg);
	bool IsWall(int way)
	{
		//todo:enum����Ă킩��₷������ leftwall,rightwall,�Ă���
		//����
		if (way == 0)
		{
			if (((m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty &&
				m_field[m_sFldPos.y - 1][m_sFldPos.x - 1] == Empty && m_eRotation == Top) ||
				(m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty &&
					m_field[m_sFldPos.y + 1][m_sFldPos.x - 1] == Empty && m_eRotation == Bottom) ||
				(m_field[m_sFldPos.y][m_sFldPos.x - 1] == Empty && m_eRotation == Right) ||
				(m_field[m_sFldPos.y][m_sFldPos.x - 2] == Empty && m_eRotation == Left)))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		//�E��
		if (way == 1)
		{
			if (((m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty &&
				m_field[m_sFldPos.y - 1][m_sFldPos.x + 1] == Empty && m_eRotation == Top) ||
				(m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty &&
					m_field[m_sFldPos.y + 1][m_sFldPos.x + 1] == Empty && m_eRotation == Bottom) ||
				(m_field[m_sFldPos.y][m_sFldPos.x + 1] == Empty && m_eRotation == Left) ||
				(m_field[m_sFldPos.y][m_sFldPos.x + 2] == Empty && m_eRotation == Right)))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		//����
		if (way == 2)
		{
			if ((m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty && m_eRotation == Top) ||
				(m_field[m_sFldPos.y + 2][m_sFldPos.x] != Empty && m_eRotation == Bottom) ||
				((m_field[m_sFldPos.y + 1][m_sFldPos.x - 1] != Empty ||
					m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty) && m_eRotation == Left) ||
				((m_field[m_sFldPos.y + 1][m_sFldPos.x + 1] != Empty ||
					m_field[m_sFldPos.y + 1][m_sFldPos.x] != Empty) && m_eRotation == Right))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		return false;
	}
	int GetScore()
	{
		return m_score;
	}
	int GetMaxChain()
	{
		return m_maxChainCnt;
	}
	bool GetDead() {
		return m_deadFlg;
	}
	int GetSendObstacleCnt()
	{
		return m_sendObstacleCnt;
	}
	void SetSendObstacleCnt(int num)
	{
		m_sendObstacleCnt = num;
	}
	bool GetReceive()
	{
		return m_receiveFlg;
	}
};

