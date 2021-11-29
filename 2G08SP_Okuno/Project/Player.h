#pragma once

#include "Enemy.h"
#include "Item.h"
#include "Pipe.h"
#include "SkillObj.h"

class CPlayer
{
private:
	const float		MoveSpeed = 0.35f;							//�������̈ړ��̉����x
	const float		MoveMaxSpeed = 3.0f;						//�������̏�����x
	const float		RunSpeed = 0.22f;							//�_�b�V�����̉����x
	const float		RunMaxSpeed = 6.0f;							//�_�b�V�����̏�����x
	const float		JumpSSpeed[3] = { -10.3f, -10.66f , -11.0f };	//�W�����v�̏����x�̔z��
	const float		JumpUSp = 0.4f;								//�W�����v�̏㏸���̉����x�i�����x�j
	const float		JumpFSp = 0.7f;							//�W�����v�̗������̉����x�i�����x�j
	const float		JumpMaxSpeed = 8.0f;						//�����̏�����x

	enum t_ANIM_TYPE {
		ANIM_STAND,
		ANIM_DASH,
		ANIM_JUMP,

		ANIM_COUNT,
	};

	SpriteAnimationCreate pl_anim[ANIM_COUNT * MARIO_COUNT] = {
		{"�ҋ@", 0, 0, 32, 32, TRUE, {5, 0, 0}},
		{"�_�b�V��", 0, 32, 32, 32, TRUE, {5, 0, 0}},
		{"�W�����v", 0, 64, 32, 32, TRUE, {5, 0, 0}},
		{"�X�[�p�[�}���I�ҋ@", 0, 96, 32, 64, TRUE, {5, 0, 0}},
		{"�X�[�p�[�}���I�_�b�V��", 0, 160, 32, 64, TRUE, {5, 0, 0}},
		{"�X�[�p�[�}���I�W�����v", 0, 224, 32, 64, TRUE, {5, 0, 0}},
		{"�t�@�C�A�[�}���I�ҋ@", 0, 288, 32, 64, TRUE, {5, 0, 0}},
		{"�t�@�C�A�[�}���I�_�b�V��", 0, 352, 32, 64, TRUE, {5, 0, 0}},
		{"�t�@�C�A�[�}���I�W�����v", 0, 416, 32, 64, TRUE, {5, 0, 0}},
	};
	CSpriteMotionController	m_Motion;

	enum t_SOUND_TYPE {
		SOUND_JUMP,
		SOUND_ITEM_NORMAL,
		SOUND_ITEM_1UP,
		SOUND_ITEM_COIN,
		SOUND_TRAMPLED,
		SOUND_FIRE,

		SOUND_COUNT,
	};

	std::string m_SoundFiles[SOUND_COUNT] = { "jump.mp3", "itemNormal.mp3", "item1up.mp3", "itemCoin.mp3", "trampled.mp3", "fire.mp3" };

	CSoundBuffer*	m_SoundArray;

	CTexture*		m_Texture;		//�摜
	CTexture*		m_SkillTexture; //�t�@�C�A�[�{�[���Ȃǂ̉摜
	CVector2		m_Pos;			//�ʒu
	CVector2		m_Move;			//�ړ����x
	CRectangle		m_BRect;		//�O�t���[���̋�`(Update�����s���ꂽ���ɍX�V�����)
	CSkillObj		m_SkillObj[2];

	bool			m_bReverse;
	int				m_JumpStatus;
	float			m_JumpSp;
	float			m_sth;			//�X�e�[�W�̏c��
	int				m_TypeIdx;		//�}���I�̏�Ԃ̃C���f�b�N�X
	bool			m_bDead;		//���S�t���O
	float			m_DeadWait;
	int				m_bDeadEnd;
	bool			m_bPipe;
	bool			m_bGoal;		//�S�[���t���O
	float			m_DmgTime;		//�_���[�W���󂯂��ꍇ�̖��G����
	int				m_Life;			//�}���I�̃��C�t

	/// <summary>
	/// �W�����v�����J�n���̏������ݒ�
	/// </summary>
	/// <param name="SSpeed">�����x�̐ݒ�</param>
	void JumpStart(float SSpeed);
	void JumpStart();

	/// <summary>
	/// �W�����v���̏���
	/// </summary>
	/// <param name="btnPull">���̃t���[���ŃW�����v�{�^���������ꂽ���ǂ���</param>
	void JumpingFn(bool btnPull);

public:
	CPlayer();
	~CPlayer();

	bool Load(CTexture* tex, CTexture* skillTex, CSoundBuffer* sounds);

	void Initialize(Vector2 pos, int life);

	void Update(float wx, float wy);

	void Render(float wx, float wy);

	void CollisionStage(CCollisionData coll);

	/// <summary>
	/// �G�Ƃ̔���
	/// </summary>
	/// <param name="ene">���肷��G</param>
	void CollisionEnemy(CEnemy& ene);

	void CollisionItem(CItem& item);

	void Damage(bool death);

	/// <summary>
	/// �S�[�����̏���
	/// </summary>
	/// <param name="ox">�S�[���|�[���ւ̖��܂�</param>
	/// <param name="gType">�S�[���̎��(0=�S�[���|�[��,1=�{�X���j)</param>
	/// <param name="glb">�S�[���̈�ԉ���Y���W</param>
	/// <param name="stw">�X�e�[�W�̕�</param>
	/// <param name="clearBgmPlay">�N���ABGM�̍Đ����</param>
	/// <returns>�S�[���̏������I������ǂ���</returns>
	bool GoalFn(float ox, int gType, float glb, float stw, bool clearBgmPlay);

	bool PipeInFn(CPipe::PipeData pipe);
	bool PipeOutFn(CPipe::PipeData pipe);

	bool DeadFn();

	void SlideMove(CVector2 v);

	CPipe::PipeData GetPipeData(int id);

	CSkillObj* GetSkillObj() { return m_SkillObj; };

	CRectangle GetBRect(bool col) {
		if (col) {
			return CRectangle(m_BRect.Left, m_BRect.Top + 10, m_BRect.Right, m_BRect.Bottom);
		}
		return m_BRect;
	};

	CRectangle GetRect(bool col) {
		if (col) {
			return CRectangle(m_Pos.x, m_Pos.y + 10, m_Pos.x + m_Motion.GetSrcRect().GetWidth(), m_Pos.y + m_Motion.GetSrcRect().GetHeight());
		}
		return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_Motion.GetSrcRect().GetWidth(), m_Pos.y + m_Motion.GetSrcRect().GetHeight());
	};

	CVector2 GetMove() { return m_Move; };

	int GetType() { return CGameDefine::GetGameDefine()->GetGameDefine()->GetMarioType(m_TypeIdx); };

	int GetTypeIdx() { return m_TypeIdx; };

	bool GetDead() { return m_bDead; };

	bool GetGoal() { return m_bGoal; };

	bool IsPipe() { return m_bPipe; }

	bool IsJumpingUp() { return m_JumpStatus == Jumping && m_Move.y < 0; };

	void SetStageHeight(float sth) { m_sth = sth; };

	void ChangeStage(Vector2 pos);

	void SetLife(int life) { m_Life = life; };

	int GetLife() { return m_Life; };

	int GetSoundCount() { return SOUND_COUNT; };

	std::string* GetSoundFiles() {
		return m_SoundFiles;
	}
};

