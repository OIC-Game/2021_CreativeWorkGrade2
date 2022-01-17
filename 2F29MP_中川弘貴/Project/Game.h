#pragma once
#include	"GameApp.h"
#include	"Player.h"

//レディカウントが表示される時間
#define		READY_TIME				180
#define		TO_TITLE_TIME			240

class CGame {
private:
	CPlayer pl;
	CPlayer ai;

	//背景
	CTexture	m_BackTexture;
	//Ready
	CTexture	m_ReadyTexture;
	//Fight
	CTexture	m_FightTexture;
	//ポーズ画面
	CTexture    m_PauseTexture;
	//ゲームオーバー時の背景
	CTexture	m_GameOverTexture;
	//勝ち
	CTexture	m_WinTexture;
	//負け
	CTexture	m_LoseTexture;
	//簡単な操作説明
	CTexture	m_HowMoveTexture;

	//bgm
	CSoundBuffer	m_gameBGM;
	//効果音
	CSoundBuffer	m_pauseSound;
	CSoundBuffer	m_gameOverSound;
	CSoundBuffer	m_victorySound;
	CSoundBuffer	m_readySound;
	CSoundBuffer	m_fightSound;

	//ポーズフラグ
	bool		m_pauseFlg;
	bool		m_readyFlg;
	bool		m_endFlg;
	bool		m_deadFlg;

	//readyカウント
	int			m_readyTimeCnt;
	//ゲームオーバーからタイトル画面に行くまでかかる時間をカウント
	int			m_toTitleTimeCnt;
	//readyカウントを進める上で発生させる効果音を複数回鳴らさないための変数
	int			m_readyStep;
	//受け取るおじゃまぷよ
	int			m_plReceiveObstacleCnt;
	int			m_aiReceiveObstacleCnt;

	//フェード用
	CFade			fade;

	CFont			font;
public:
	CGame();
	~CGame();
	void Load();
	void Initialize(bool vsAiFlg);
	void Update(bool vsAiFlg);
	void Render(bool vsAiFlg);
	void Release();
};