#include	"GameApp.h"
#include	"Game.h"
#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"

extern int	stage_number;
//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)

//�v���C���[�c�@(�O���Q�ƁA���̂�Infomation.cpp)
extern int						player_Life;

//�X�R�A
int						score = 0;
int						getScore = 0;
bool					scoreDisplayFlg = false;
int						scoreDesplayTime = 0;
bool					player1UpDisplayFlg = false;
extern int				enemyDeadCount;
int						getCoinCount = 0;


CPlayer		g_Player;
CStage		g_Stage;

 

/**
 * �R���X�g���N�^
 *
 */
CGame::CGame():
m_EnemyArray(NULL),
m_ItemArray(NULL),
game_BGM(),
game_LAST_BGM(),
game_BOSS_BGM(),
game_GameOverSE(),
game_GameClearSE(),
game_playSoundFlg(false),
game_playBGMFlg(false),
game_Time(0.0f),
game_TimeWait(0.0f),
game_ScoreFlg(false),
game_ScoreDesplayFlg(false),
game_tempPlayerPositionX(0),
game_tempPlayerPositionY(0),
game_NowStage(0),
game_MarioJumpSE(),
game_MarioFireSE(),
game_playMarioSEFlg(false),
game_MarioDeadSE(),
game_ab(false)

{
}

/**
 * �f�X�g���N�^
 *
 */
CGame::~CGame() {
}

bool CGame::Load(void)
{
	//�v���C���[���[�h
	g_Player.Load();
	//�X�e�[�W���[�h
	switch (m_StageNumber)
	{
	case STAGE_1_1:
	{
		g_Stage.Load("Stage1.txt");
		break;
	}
	case STAGE_LAST:
	{
		g_Stage.Load("Stage_Boss.txt");
		break;
	}
	default:
		break;
	}
	


	//BGM���[�h
	if (!game_LAST_BGM.Load("LAST_BGM.mp3"))
	{
		return false;
	}
	if (!game_BGM.Load("BGM.mp3"))
	{
		return false;
	}
	if (!game_BOSS_BGM.Load("BOSS_BGM.mp3"))
	{
		return false;
	}
	//�Q�[���I�[�o�[SE���[�h
	if (!game_GameOverSE.Load("GameOver.mp3"))
	{
		return false;
	}
	//�Q�[���N���ASE���[�h
	if (!game_GameClearSE.Load("GameClear.wav"))
	{
		return false;
	}
	if (!game_MarioJumpSE.Load("MarioJump.mp3"))
	{
		return false;
	}
	if (!game_MarioDeadSE.Load("MarioDead.mp3"))
	{
		return false;
	}
	if (!game_BossClearSE.Load("BossClear.wav"))
	{
		return false;
	}

	/*if (!game_MarioFireSE.Load("MarioFire.mp3"))
	{
		return false;
	}*/

	//�G�������m��
	m_EnemyArray = new CEnemy[g_Stage.GetEnemyCount()];
	//�A�C�e���������m��
	m_ItemArray = new CItem[g_Stage.GetItemCount()];

	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGame::Initialize(void) {
	
	//�v���C���[������
	g_Player.Initialize();
	//�X�e�[�W������
	g_Stage.Initialize(m_EnemyArray,m_ItemArray);
	
	game_NowStage = m_StageNumber;
	//BGM�Đ�
	switch (game_NowStage)
	{
		case STAGE_1_1:
		{
			game_BGM.SetLoop(TRUE);
			game_BGM.Play();
			break;
		}
		case STAGE_LAST:
		{
			game_LAST_BGM.SetLoop(TRUE);
			game_LAST_BGM.Play();
		}
	}
	game_playSoundFlg = false;
	game_playBGMFlg = false;
	switch (game_NowStage)
	{
	case STAGE_1_1:
	{
		game_Time = GAME_TIMELIMIT;
		break;
	}
	case STAGE_LAST:
	{
		game_Time = GAME_TIMELIMIT_BOSS;
	}
	default:
		break;
	}
	game_TimeWait = 0.0f;
	game_ScoreFlg = false;
	game_tempPlayerPositionX = 0.0f;
	game_tempPlayerPositionY = 0.0f;
	game_playMarioSEFlg = false;
	game_ab = false;
}

/**
 * �X�V
 *
 */
void CGame::Update(void) {
	//�v���C���[�X�V
	g_Player.Update();
	//�X�e�[�W�ƃv���C���[�̓����蔻��
	float ox = 0, oy = 0;
	bool og = false;
	bool enemyDead = false;
	bool jumpFlg = false;
	bool scoreFlg = false;
	bool magmaDead = false;
	if (g_Stage.Collision(g_Player.GetRectPlayer(), ox, oy, og,enemyDead,jumpFlg,g_Player,magmaDead))
	{
		if (magmaDead)
		{
			g_Player.Setplayer_DeadFlg(true);
		}
		g_Player.CollisionStage(ox, oy);
	}
	g_Player.FallCheck(og);

	//�X�e�[�W�̍X�V
	g_Stage.Update(g_Player);


	if (g_Player.GetTmpWorpFlg() == true && !game_playBGMFlg)
	{
		if (game_LAST_BGM.IsPlay())
		{
			game_LAST_BGM.Stop();
		}
		game_BOSS_BGM.SetLoop(TRUE);
		game_BOSS_BGM.Play();
		game_playBGMFlg = true;
	}
	
	//�G�̍X�V
	for (int i = 0; i < g_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		//�v���C���[�T�C�Y���ω����̎������Ȃ�����
		if (g_Player.Getplayer_ChangeWaitFlg())
		{
			return;
		}
		if (m_EnemyArray[i].GetType() == ENEMY_MARIO)
		{
			if (!game_playMarioSEFlg && m_EnemyArray[i].GetMarioJumpFlg())
			{
				if (game_MarioJumpSE.IsPlay())
				{
					game_MarioJumpSE.Stop();
				}
				game_MarioJumpSE.Play();
				game_playMarioSEFlg = true;
			}
			else if (game_playMarioSEFlg && !m_EnemyArray[i].GetMarioJumpFlg())
			{
				
				game_playMarioSEFlg = false;
			}

			if (!game_playSoundFlg && m_EnemyArray[i].GetMarioDeadFlg())
			{
				game_BOSS_BGM.Stop();
				game_MarioDeadSE.Play();
				game_playSoundFlg = true;
			}
			if (m_EnemyArray[i].GetEnemyDead())
			{
				g_Player.SetMarioDead(true);
			}

		}
			m_EnemyArray[i].Update();
			ox = 0, oy = 0;
			enemyDead = false;
			jumpFlg = false;
			magmaDead = false;
			//�G[i]�̎��S�t���O��false�̎�
			if (!m_EnemyArray[i].GetEnemyDead())
			{

				if (g_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy, og, enemyDead, jumpFlg, g_Player, magmaDead))
				{
					if (magmaDead)
					{
						m_EnemyArray[i].Dead(magmaDead);
						m_EnemyArray[i].DeadJump(true);
					}
						m_EnemyArray[i].CollisionStage(ox, oy);
					
					if (jumpFlg && !g_Player.Getplayer_BigFlg())
					{
						m_EnemyArray[i].BlockJump(jumpFlg);
					}
					else if (jumpFlg && g_Player.Getplayer_BigFlg())
					{
						//�u���b�N�z���ɓ|���ꂽ�Ƃ�
						if (enemyDead)
						{
							//�X�R�A���Z
							score += SCORE_ENEMYSTEP;
							getScore = SCORE_ENEMYSTEP;
							scoreDisplayFlg = true;
							scoreDesplayTime = SCORE_DISPLAYTIME;
							m_EnemyArray[i].Dead(enemyDead);
						}
						m_EnemyArray[i].DeadJump(jumpFlg);
					}
				}
				if (m_EnemyArray[i].GetType() == ENEMY_MARIO )
				{
					for (int j = 0; j < 10; j++)
					{
						if (!m_EnemyArray[i].GetShotShow(j))
						{
							continue;
						}
						if (g_Stage.Collision(m_EnemyArray[i].GetShotRect(j), ox, oy, og, enemyDead, jumpFlg, g_Player, magmaDead))
						{
							m_EnemyArray[i].ShotCollisionStage(ox, oy, j);
						}
					}
					
				}
			}
		

	}
	//�A�C�e���̍X�V
	for (int i = 0; i < g_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		//�v���C���[�T�C�Y���ω����̎������Ȃ�����
		if (g_Player.Getplayer_ChangeWaitFlg())
		{
			return;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		jumpFlg = false;
		magmaDead = false;
		if (g_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy,og,enemyDead,jumpFlg,g_Player,magmaDead))
		{
			if (magmaDead)
			{
				m_ItemArray[i].SetShow(false);
			}
				m_ItemArray[i].CollisionStage(ox, oy);
				m_ItemArray[i].BlockJump(jumpFlg);
		}
	}
	//�����蔻��̎��s
	for (int i = 0; i < g_Stage.GetEnemyCount(); i++)
	{
			if (m_EnemyArray[i].GetType() == ENEMY_MARIO)
			{
				m_EnemyArray[i].GetPlayerInfo(g_Player.Getplayer_PositionX(), g_Player.GetPlayer_MoveX(),
					g_Player.Getplayer_JumpFlg(), g_Player.GetTmpWorpFlg());
			}
			g_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for (int i = 0; i < g_Stage.GetItemCount(); i++)
	{
			g_Player.CollisionItem(m_ItemArray[i]);
	}
	//�^�C�}�[����
	if (g_Player.Getplayer_DeadFlg() == false && g_Player.Getplayer_ClearFlg() == false)
	{
		//�N���A�A�Q�[���I�[�o�[�����Ă��Ȃ��Ƃ�
		game_Time -= 1 * CUtilities::GetFrameSecond();
	}
	else if (game_Time <= 0 && !g_Player.Getplayer_ClearFlg())
	{
		g_Player.Setplayer_DeadFlg(true);
	}


	//�A���œG��|�����A�r���Œn�ʂɒ������Ƃ��A�G�̎��S�J�E���g��0�ɂ���
	if (!g_Player.Getplayer_JumpFlg() && g_Player.Getplayer_FallFlg())
	{
		enemyDeadCount = 0;
	}
	//�l���X�R�A�\�����ԏ���
		scoreDesplayTime--;
		if (scoreDesplayTime < 0)
		{
			scoreDesplayTime = 0;
			getScore = 0;
			scoreDisplayFlg = false;
			player1UpDisplayFlg = false;
		}
	


	//���S�t���O��ON�̎��A�Q�[���I�[�o�[SE���Đ�
	if (g_Player.Getplayer_DeadFlg() == true && !game_playSoundFlg)
	{
		if(game_BGM.IsPlay())
		{
			game_BGM.Stop();
		}
		else if(game_LAST_BGM.IsPlay())
		{
			game_LAST_BGM.Stop();
		}
		else if (game_BOSS_BGM.IsPlay())
		{
			game_BOSS_BGM.Stop();
		}
		game_GameOverSE.Play();
		game_playSoundFlg = true;
	}
	//�N���A�t���O��ON�̎��A�Q�[���N���ASE���Đ�
	else if (g_Player.Getplayer_ClearFlg() == true)
	{
		if (game_BGM.IsPlay())
		{
			game_BGM.Stop();
		}
	}

	//�Q�[���I�[�o�[��ʑJ��
	if (g_Player.Getplayer_DeadTransitionFlg() == true)
	{
		//���S���X�R�A��0�ɂ���
		score = 0;

		//�c�@��0�����̂Ƃ��Q�[���I�[�o�[��ʂ֑J��
		if (player_Life < 0)
		{
			Sleep(1000);
			m_NextScene = SCENENO_GAMEOVER;
			m_bEnd = true;
		}
		//�C���t�H���[�V������ʂ֑J��
		else
		{
			Sleep(1000);
			m_NextScene = SCENENO_INFOMATION;
			m_bEnd = true;
		}
	}
	//�Q�[���N���A��ʑJ��
	else if(g_Player.Getplayer_ClearTransitionFlg() == true)
	{
		if (!game_playSoundFlg)
		{
			game_GameClearSE.Play();
			game_playSoundFlg = true;
		}
		if (game_Time > 0)
		{

			score += SCORE_TIME;
			game_Time--;
		}
		else
		{
			
			if (!game_GameClearSE.IsPlay())
			{
				m_NextScene = SCENENO_INFOMATION;
				stage_number = STAGE_LAST;
				m_bEnd = true;
			}
			
		}
		
	}
	//�Q�[���N���A��ʑJ��
	else if (g_Player.GetBossClearFlg())
	{
		if (!game_ab)
		{
			game_BossClearSE.Play();
			game_ab = true;
		}
	}
	if (g_Player.GetBossClearTrantionFlg() == true)
	{

		if (!game_BossClearSE.IsPlay())
		{
			m_NextScene = SCENENO_TITLE;
			stage_number = STAGE_1_1;
			m_bEnd = true;
		}
			

		

	}

}



/**
 * �`��
 *
 */
void CGame::Render(void) {
	//�X�e�[�W�̕`��
	g_Stage.Render();
	//�v���C���[�̕`��
	g_Player.Render(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	//�A�C�e���̕`��
	for (int i = 0; i < g_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Render(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	}
	//�G�̕`��
	for (int i = 0; i < g_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	}
	CGraphicsUtilities::RenderString(300, 50, "COIN");
	CGraphicsUtilities::RenderString(100, 50, "%.6d", score);
	CGraphicsUtilities::RenderString(800, 50, "%.0f", game_Time);
	CGraphicsUtilities::RenderString(350, 50, "�~%d", getCoinCount);
	switch (game_NowStage)
	{
		case STAGE_1_1:
		{
			CGraphicsUtilities::RenderString(600, 50, "�P�[�P");
			break;
		}
	case STAGE_LAST:
	{
		CGraphicsUtilities::RenderString(600, 50, "BOSS");
		break;
	}

	default:
		break;
	}
	if (game_NowStage == STAGE_1_1)
	{

	}
	if (!scoreDisplayFlg)
	{
		
	}
	else if(scoreDesplayTime > 0)
	{
		game_tempPlayerPositionX = g_Player.Getplayer_DispPositionX();
		game_tempPlayerPositionY = g_Player.Getplayer_DispPositionY();
		if (!player1UpDisplayFlg)
		{
			CGraphicsUtilities::RenderString(game_tempPlayerPositionX + 30, game_tempPlayerPositionY - 30, "%d", getScore);
		}
		else
		{
			CGraphicsUtilities::RenderString(game_tempPlayerPositionX + 30, game_tempPlayerPositionY - 30, "1UP");
		}
	}
}

void CGame::RenderDebug(void) {
	//�X�e�[�W�̃f�o�b�O�`��
	g_Stage.RenderDebug();
	//�v���C���[�̃f�o�b�O�`��
	g_Player.RenderDebug(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	//�G�̃f�o�b�O�`��
	for (int i = 0; i < g_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	}
	//�A�C�e���̃f�o�b�O�`��
	for (int i = 0; i < g_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(g_Stage.GetScrollX(), g_Stage.GetScrollY());
	}
	CGraphicsUtilities::RenderString(10, 10, "�Q�[�����");
	CGraphicsUtilities::RenderString(300, 300, "�G���S�J�E���g%d", enemyDeadCount);
	CGraphicsUtilities::RenderString(300, 400, "�l���X�R�A%d", getScore);
	CGraphicsUtilities::RenderString(350, 500, "TimeWait:%0.0f", game_TimeWait);
	
	
}

void CGame::Release(void)
{
	//�X�e�[�W�̉��
	g_Stage.Release();
	//�v���C���[�̉��
	g_Player.Release();
	//�G�̉��
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//�A�C�e���̉��
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//BGM���
	game_BGM.Release();
	game_BOSS_BGM.Release();
	game_LAST_BGM.Release();
	//SE���
	game_GameOverSE.Release();
	game_GameClearSE.Release();
	game_MarioJumpSE.Release();
	game_MarioDeadSE.Release();
	game_BossClearSE.Release();
	//game_MarioFireSE.Release();
}