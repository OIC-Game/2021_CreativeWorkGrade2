#pragma once

#include "Enemy.h"
#include "Item.h"
#include "Pipe.h"
#include "SkillObj.h"

class CPlayer
{
private:
	const float		MoveSpeed = 0.35f;							//横方向の移動の加速度
	const float		MoveMaxSpeed = 3.0f;						//横方向の上限速度
	const float		RunSpeed = 0.22f;							//ダッシュ時の加速度
	const float		RunMaxSpeed = 6.0f;							//ダッシュ時の上限速度
	const float		JumpSSpeed[3] = { -10.3f, -10.66f , -11.0f };	//ジャンプの初速度の配列
	const float		JumpUSp = 0.4f;								//ジャンプの上昇時の加速度（減速度）
	const float		JumpFSp = 0.7f;							//ジャンプの落下時の加速度（減速度）
	const float		JumpMaxSpeed = 8.0f;						//落下の上限速度

	enum t_ANIM_TYPE {
		ANIM_STAND,
		ANIM_DASH,
		ANIM_JUMP,

		ANIM_COUNT,
	};

	SpriteAnimationCreate pl_anim[ANIM_COUNT * MARIO_COUNT] = {
		{"待機", 0, 0, 32, 32, TRUE, {5, 0, 0}},
		{"ダッシュ", 0, 32, 32, 32, TRUE, {5, 0, 0}},
		{"ジャンプ", 0, 64, 32, 32, TRUE, {5, 0, 0}},
		{"スーパーマリオ待機", 0, 96, 32, 64, TRUE, {5, 0, 0}},
		{"スーパーマリオダッシュ", 0, 160, 32, 64, TRUE, {5, 0, 0}},
		{"スーパーマリオジャンプ", 0, 224, 32, 64, TRUE, {5, 0, 0}},
		{"ファイアーマリオ待機", 0, 288, 32, 64, TRUE, {5, 0, 0}},
		{"ファイアーマリオダッシュ", 0, 352, 32, 64, TRUE, {5, 0, 0}},
		{"ファイアーマリオジャンプ", 0, 416, 32, 64, TRUE, {5, 0, 0}},
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

	CTexture*		m_Texture;		//画像
	CTexture*		m_SkillTexture; //ファイアーボールなどの画像
	CVector2		m_Pos;			//位置
	CVector2		m_Move;			//移動速度
	CRectangle		m_BRect;		//前フレームの矩形(Updateが実行された時に更新される)
	CSkillObj		m_SkillObj[2];

	bool			m_bReverse;
	int				m_JumpStatus;
	float			m_JumpSp;
	float			m_sth;			//ステージの縦幅
	int				m_TypeIdx;		//マリオの状態のインデックス
	bool			m_bDead;		//死亡フラグ
	float			m_DeadWait;
	int				m_bDeadEnd;
	bool			m_bPipe;
	bool			m_bGoal;		//ゴールフラグ
	float			m_DmgTime;		//ダメージを受けた場合の無敵時間
	int				m_Life;			//マリオのライフ

	/// <summary>
	/// ジャンプ処理開始時の初期化設定
	/// </summary>
	/// <param name="SSpeed">初速度の設定</param>
	void JumpStart(float SSpeed);
	void JumpStart();

	/// <summary>
	/// ジャンプ中の処理
	/// </summary>
	/// <param name="btnPull">そのフレームでジャンプボタンが離されたかどうか</param>
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
	/// 敵との判定
	/// </summary>
	/// <param name="ene">判定する敵</param>
	void CollisionEnemy(CEnemy& ene);

	void CollisionItem(CItem& item);

	void Damage(bool death);

	/// <summary>
	/// ゴール時の処理
	/// </summary>
	/// <param name="ox">ゴールポールへの埋まり具合</param>
	/// <param name="gType">ゴールの種類(0=ゴールポール,1=ボス撃破)</param>
	/// <param name="glb">ゴールの一番下のY座標</param>
	/// <param name="stw">ステージの幅</param>
	/// <param name="clearBgmPlay">クリアBGMの再生状態</param>
	/// <returns>ゴールの処理が終わったどうか</returns>
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

