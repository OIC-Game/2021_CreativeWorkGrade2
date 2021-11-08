#pragma once

#include	"Mof.h"
#include	"CollisionData.h"
#include	"GameDefine.h"
#include	"SkillObj.h"

class CEnemy
{
private:
	const float		MoveSpeed = 1.4f;							//�������̈ړ��̉����x
	const float		JumpFSp = 0.7f;								//�������̉����x�i�����x�j
	const float		JumpMaxSpeed = 8.0f;						//�����̏�����x

	enum t_ANIM_COUNT {
		ANIM_STAND,

		ANIM_COUNT,
	};

	CSpriteMotionController	m_Motion;

	CSoundBuffer* m_SkillSound;

	CTexture* m_Texture;		//�摜
	CVector2		m_sPos;			//�����ʒu
	CVector2		m_Pos;			//�ʒu
	CVector2		m_Move;			//�ړ����x
	float			m_JumpSp;
	int				m_stgh;
	bool			m_bShow;		//�G�g�p�t���O
	bool			m_bReverse;
	int				m_JumpStatus;
	int				m_ShowState;
	bool			m_JustTrampled;	//���񂾒���@�d�Ȃ肪���������܂�
	CEnemyDefine* m_define;
	bool			m_Damaged; //Collision�֐��p
	bool			m_bGoal;
	int				m_hp;

public:
	CEnemy();
	~CEnemy();

	bool Load(CTexture* tex, CEnemyDefine* ed, CSoundBuffer* skillSound);

	void Initialize(Vector2 pos, bool bGoal, int stgh);

	void Update(float wx, float wy, CRectangle prec);

	/// <summary>
	/// �G�摜�̕`��
	/// </summary>
	/// <param name="wx">�������̃X�N���[���ʒu</param>
	/// <param name="wy">�c�����̃X�N���[���ʒu</param>
	void Render(float wx, float wy);

	void Release();

	/// <summary>
	/// �X�e�[�W�ւ̖��܂����������
	/// </summary>
	/// <param name="coll">���܂��̏��</param>
	void CollisionStage(CCollisionData coll);

	/// <summary>
	/// �G�Ƃ̔���
	/// </summary>
	/// <param name="ene">���肷��G</param>
	void CollisionEnemy(CEnemy& ene);
	void CollisionSkill(CSkillObj& sObj);
	bool CollisionObj(CRectangle erec, CVector2 eMove, int eDmgFlg, int eDmgDir);

	/// <summary>
	/// �v���C���[�ɓ��݂���ꂽ���̏���
	/// </summary>
	void Trampled(CRectangle prec);

	void Damage(bool death);

	bool Touched(CRectangle prec, bool sence);

	void PushedUp();

	void SlideMove(CVector2 v);

	void SetTexture(CTexture* tex) { m_Texture = tex; };

	bool GetShow() { return m_bShow; };
	bool GetDisplay() { return m_ShowState == STATE_SHOW; };
	void SetShow(bool bShow) { m_bShow = bShow; };

	CVector2 GetMove() { return m_Move; };

	CRectangle GetRect() {
		return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_Motion.GetSrcRect().GetWidth(), m_Pos.y + m_Motion.GetSrcRect().GetHeight());
	};

	int GetDamageFlg() { return m_define->damageFlg; };
	int GetDamageDirection() { return m_define->damageDirection; };
	int GetChangeFlg() { return m_define->changeFlg; };

	void SetJustTrampled(bool bjt) { m_JustTrampled = bjt; };
	bool GetJustTrampled() { return m_JustTrampled; };

	bool IsGEnemy() { return m_bGoal && (m_ShowState == STATE_DISAPPEAR); };
};

