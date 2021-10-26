#pragma once
#include	"Player.h"
#include	"Enemy.h"
#include	"Item.h"
#define		FLAG	22
#define		GOALPOINT	21
#define		FLAGTOP		27
#define		GOALBAR	28
#define     CASTLEWALL 2
#define		CASTLEGATE 9
#define		CASTLEDARK 15
#define		CASTLEFENCE 8
#define		CASTLEWALLFENCE 10
#define		CASTLELWINDOW 14
#define		CASTLERWINDOW 15
#define		NCHIPSIZE 16
class CStage {
private:
	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;
	CTexture				m_InfoTexture;
	CTexture				m_NumberTexture;
	CRectangle m_tPipe;
	CRectangle m_bPipe;
	CRectangle m_lPipe;
	CRectangle m_rPipe;
	CRectangle m_uPipe;

	float					m_ChipSize;
	int						m_XCount;
	int						m_YCount;
	char*					m_pChipData;

	float					m_ScrollX;
	float					m_ScrollY;

	int						m_EnemyTextureCount;
	CTexture*				m_pEnemyTexture;
	char*					m_pEnemyData;
	int						m_EnemyCount;

	int						m_ItemTextureCount;
	CTexture* m_pItemTexture;
	char* m_pItemData;
	int						m_ItemCount;

	bool					m_bGoal;

	int						m_bGoalX;
	int						m_bGoalTop;
	int						m_bGoalBottom;
	int						m_bCastle;

	bool					m_bUnder;
	bool					m_bOn;

	int						m_bCoinCount;
	int						m_bTimeCount;

	int						m_bcten;
	int						m_bcone;

	int						m_bthun;
	int                     m_btten;
	int						m_btone;

	int						timecount;
public:
	CStage();
	~CStage();
	bool Load(char* pName, char* gpName);
	void Initialize(CEnemy* pEnemy,CItem* pItem);
	void Update(CPlayer& pl);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	float GetScrollX(){ return m_ScrollX; }
	float GetScrollY(){ return m_ScrollY; }
	bool Collision(CRectangle  r, float& ox, float& oy);
	int GetEnemyCount() { return m_EnemyCount; }
	bool GetGoal(CPlayer& pl, float& ox);
	float GetChipSize() { return m_ChipSize; }
	float GetGoalBottom() { return m_ChipSize * m_bGoalBottom; };
	float GetStageWidth() { return m_ChipSize * m_XCount; };
	float GetCastle() { return m_ChipSize * m_bCastle; };
	int GetItemCount() { return m_ItemCount; }
	CRectangle GettPipe(void) { return m_tPipe; }
	CRectangle GetbPipe(void) { return m_bPipe; }
	CRectangle GetlPipe(void) { return m_lPipe; }
	CRectangle GetrPipe(void) { return m_rPipe; }
	CRectangle GetuPipe(void) { return m_uPipe; }
	void PipeRender(void);
	void UnderGround(void) { m_ScrollX = m_ChipSize * 48; m_ScrollY = m_ChipSize * 15; m_bUnder = true; };
	void OnGround(void) { m_ScrollX = m_ChipSize * 160; m_ScrollY = 0; m_bUnder = false; m_bOn = true; };
	bool GetUnder(void) { return m_bUnder; };
	bool GetOn(void) { return m_bOn; };
	float GetTime(void) { return m_bTimeCount; };
};