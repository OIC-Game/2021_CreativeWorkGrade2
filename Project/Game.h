#pragma once

#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include    "Item.h"

class CGame
{	
	private:
		//プレイヤー
		CPlayer		m_Player;

		//ステージ
		CStage		m_Stage;

		//敵
		CEnemy*		m_EnemyArray;
		//アイテム
		CItem*		m_ItemArray;

		CSoundBuffer	GameBGM;

		

		
		
	public:
		CGame();
		~CGame();
		bool Load(void);
		void Initialize(void);
		void Update(void);
		void Render(void);
		void RenderDebug(void);
		void Release(void);

		

		

};

