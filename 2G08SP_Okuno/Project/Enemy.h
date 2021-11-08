#pragma once

#include	"Mof.h"
#include	"CollisionData.h"
#include	"GameDefine.h"
#include	"SkillObj.h"

class CEnemy
{
private:
	const float		MoveSpeed = 1.4f;							//横方向の移動の加速度
	const float		JumpFSp = 0.7f;								//落下時の加速度（減速度）
	const float		JumpMaxSpeed = 8.0f;						//落下の上限速度

	enum t_ANIM_COUNT {
		ANIM_STAND,

		ANIM_COUNT,
	};

	CSpriteMotionController	m_Motion;

	CSoundBuffer* m_SkillSound;

	CTexture* m_Texture;		//画像
	CVector2		m_sPos;			//初期位置
	CVector2		m_Pos;			//位置
	CVector2		m_Move;			//移動速度
	float			m_JumpSp;
	int				m_stgh;
	bool			m_bShow;		//敵使用フラグ
	bool			m_bReverse;
	int				m_JumpStatus;
	int				m_ShowState;
	bool			m_JustTrampled;	//踏んだ直後　重なりが解除されるまで
	CEnemyDefine* m_define;
	bool			m_Damaged; //Collision関数用
	bool			m_bGoal;
	int				m_hp;

public:
	CEnemy();
	~CEnemy();

	bool Load(CTexture* tex, CEnemyDefine* ed, CSoundBuffer* skillSound);

	void Initialize(Vector2 pos, bool bGoal, int stgh);

	void Update(float wx, float wy, CRectangle prec);

	/// <summary>
	/// 敵画像の描画
	/// </summary>
	/// <param name="wx">横方向のスクロール位置</param>
	/// <param name="wy">縦方向のスクロール位置</param>
	void Render(float wx, float wy);

	void Release();

	/// <summary>
	/// ステージへの埋まりを解消する
	/// </summary>
	/// <param name="coll">埋まり具合の情報</param>
	void CollisionStage(CCollisionData coll);

	/// <summary>
	/// 敵との判定
	/// </summary>
	/// <param name="ene">判定する敵</param>
	void CollisionEnemy(CEnemy& ene);
	void CollisionSkill(CSkillObj& sObj);
	bool CollisionObj(CRectangle erec, CVector2 eMove, int eDmgFlg, int eDmgDir);

	/// <summary>
	/// プレイヤーに踏みつけられた時の処理
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

