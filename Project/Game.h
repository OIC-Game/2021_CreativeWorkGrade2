#pragma once

#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"

class CGame
{	
	private:
		//�v���C���[
		CPlayer		m_Player;

		//�X�e�[�W
		CStage		m_Stage;

		//�G
		CEnemy*		m_EnemyArray;

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

