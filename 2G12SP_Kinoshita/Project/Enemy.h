#pragma once


#include "Mof.h"
#include "GameDefine.h"
#include"QuestionBlock.h"
#include"breakBlock.h"
//#include <vector>

enum tag_EnemtType
{
	Enemy_kuribo,       //クリボ
	Enemy_nokonoko,      //ノコノコ

	Enemy_TYPECOUNT,
};

#define ENEMY_RECTDECREASEE  10
class CEnemy
{

private:
	CTexture* m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	
	Mof::CVector2 m_Pos;
	Mof::CVector2 m_Move;

	/*float					m_MoveX;
	float					m_MoveY;*/
	
	bool					m_bShow;
	bool					m_bReverse;
	CRectangle				m_SrcRect;

	int						m_HP;
	int						m_DamageWait;

	//CStage                 m_Stage;

	//モーション種類定義
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};
public:
	CEnemy();
	~CEnemy();
	void Initialize(float px, float py, int type);
	void Update();
	void Damage(int dmg, bool bRev);
	void CollisionStage(float ox, float oy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	int GetDamageWait(void) { return m_DamageWait; }

	//敵の体の矩形
	CRectangle GetRect() {
		//return CRectangle(m_Pos.x + ENEMY_RECTDECREASEE, m_Pos.y + ENEMY_RECTDECREASEE, m_Pos.x + m_SrcRect.GetWidth() - ENEMY_RECTDECREASEE, m_Pos.y + m_SrcRect.GetHeight());
		return CRectangle(m_Pos.x+5 , m_Pos.y+10 , m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight()-5);
	}
	//敵の頭の矩形
	CRectangle  Gethed() {
		
		return CRectangle(m_Pos.x , m_Pos.y , m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight() - 20);
	}
	bool IsScreen(float wx, float wy)
	{
		float sx = m_Pos.x - wx;
		float sy = m_Pos.y - wy;
		constexpr float marginSize = 100;

		if (sx<-marginSize || sy<-marginSize || sx>g_pGraphics->GetTargetWidth() + marginSize || sy>g_pGraphics->GetTargetHeight() + marginSize)
		{
			return false;
		}
		return true;
	}
	bool CollisionQBlock(CQuestionBlock& QBlock, float ox, float oy);
	bool CollisionbreakBlock(CbreakBlock& blo, float ox, float oy);
};

