#pragma once

#include "Mof.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Block.h"
#include "CollisionData.h"

class CStage
{
private:
	CTexture	m_BgTexture;		//背景画像
	CTexture	m_ChipTexture;		//マップチップ画像
	CTexture* m_pEnemyTexture;	//敵画像
	CTexture* m_pItemTexture;		//アイテム画像
	CEnemy* m_EnemyArray;
	CItem* m_ItemArray;
	CBlock* m_BlockArray;

	int			m_EnemyTextureCount;//敵画像の数
	char* m_pEnemyData;		//敵の配置情報
	int			m_EnemyCount;		//敵の総数
	int			m_ItemTextureCount;	//アイテム画像の数
	char* m_pItemData;		//アイテムの配置情報
	int			m_ItemCount;		//アイテムの総数
	//float		m_ChipSize;			//チップ一つのサイズ
	int			m_XSize;			//マップの横方向のマスの数
	int			m_YSize;			//マップの縦方向のマスの数
	int* m_ChipData;			//マップの各マスの情報
	int			m_BlockCount;		//
	int			m_StartX;			//プレイヤーの初期位置
	int			m_StartY;			//プレイヤーの初期位置
	int			m_StageType;

	float		m_ScrollX;			//横方向のスクロール位置
	float		m_ScrollY;			//縦方向のスクロール位置

public:
	CStage();
	~CStage();

	bool Load(char* fname, int sx, int sy, int sType);

	void Initialize(bool bGoal, int gType, int gx, int gy, CSoundBuffer* skillSound);
	void StageFlash(); //ステージ内の敵などのステータスを表示状態にする

	void Update(CPlayer& pl);
	void UpdateScroll(CPlayer& pl);

	void Render();
	void RenderLayerOver();

	void RenderDebug_Enemy();

	void Release();

	/// <summary>
	/// ステージとの接触判定（めり込んでいるかどうか）
	/// </summary>
	/// <param name="r">判定するもの（キャラクターなど）の矩形</param>
	/// <param name="ox">ステージへの左右の埋まり具合を入れる</param>
	/// <param name="oy">ステージへの上下の埋まり具合を入れる</param>
	/// <param name="og">接地（着地）しているかどうかを入れる</param>
	/// <returns>接触情報を返す</returns>
	CCollisionData Collision(CPlayer* pl, CEnemy* ene, CRectangle rb, CRectangle ra, CVector2 move);
	void Collision_Dir(CPlayer* pl, CEnemy* ene, CRectangle* rb, CRectangle* ra, CVector2 move, CBlock* block, CRectangle blockRect, CCollisionData* coll, bool& leftFallFlg, bool& rightFallFlg, int direction);

	void CheckPointThrough(CRectangle rect);

	bool DoorAnimation(CRectangle rect, float animTime, bool isIn);
	void EndDoorAnimation(CRectangle rect);

	Vector2 GetStartPos() { return Vector2(CHIPSIZE * m_StartX, CHIPSIZE * m_StartY); }

	bool IsGEnemy() {
		for (int i = 0; i < m_EnemyCount; i++) {
			if (m_EnemyArray[i].IsGEnemy()) {
				return true;
			}
		}
		return false;
	};

	float GetScrollX() { return m_ScrollX; };

	float GetScrollY() { return m_ScrollY; };

	float GetStageWidth() { return CHIPSIZE * m_XSize; };

	float GetStageHeight() { return CHIPSIZE * m_YSize; };

	int GetEnemyCount() { return m_EnemyCount; };

	int GetItemCount() { return m_ItemCount; };

	int GetBlockCount() { return m_BlockCount; };
};

