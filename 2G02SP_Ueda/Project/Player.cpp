#include "Player.h"

CPlayer::CPlayer() :
	m_SrcRect(),
	m_Texture(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_bMove(false),
	m_bJump(false),
	m_bReverse(false),
	m_MoveX(0.0f),
	m_MoveY(0.0f),
	m_HP(0),
	m_DamageWait(0),
	m_bDead(false),
	m_bGoal(false),
	m_bGoalDown(false),
	m_bGoalCount(0),
	m_bCastle(false),
	m_bCastleCount(0),
	m_bPlayerSize(0),
	m_bGiant(false),
	m_bMotionGiant(false),
	m_bPlayerF(0),
	m_bPlayerS(0),
	m_bPlayerT(0),
	m_bPipeDown(false),
	m_bPipeMove(false),
	m_bUnder(false),
	m_bPipeUp(false),
	m_bCoinCount(0),
	m_way(false)
{
}


CPlayer::~CPlayer()
{
}

bool CPlayer::Load(void)
{
	if (!m_Texture.Load("mario.player.png"))
	{
		return false;
	}
	return true;
}

void CPlayer::Initialize(void)
{
	m_PosX = 80;
	m_PosY = 352;
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_bJump = false;
	m_HP = 1;
	m_DamageWait = 0;
	m_bDead = false;
	m_Motion.ChangeMotion(MOTION_WAIT);
	m_bGoal = false;
	m_bGoalCount = 48;
	m_bCastle = false;
	m_bCastleCount = 48;
	m_bPlayerSize = 32;
	m_bGiant = false;
	m_bPipeDown = false;
	m_bPlayerF = 0;
	m_bPlayerS = 32;
	m_bPlayerT = 64;
	m_bUnder = false;
	m_bPipeUp = false;
	m_bPipeMove=false;
	m_bCoinCount = 0;
	MotionRefresh();
	m_way = false;
}

void CPlayer::Update(float wx,float wy)
{
	if (m_PosX < wx)
	{
		m_PosX = wx;
	}
	m_bMove = false;
	if (m_Motion.GetMotionNo() == MOTION_GIANT)
	{
		m_bMotionGiant = true;
	}
	else 
	{
		m_bMotionGiant = false;
	}
	if (m_Motion.GetMotionNo() == MOTION_JUMPEND || m_Motion.GetMotionNo() == MOTION_GIANT || m_Motion.GetMotionNo() == MOTION_SQUAT)
	{
		if (m_Motion.IsEndMotion())
		{
			if (m_Motion.GetMotionNo() == MOTION_SQUAT)
			{
				if (!g_pInput->IsKeyHold(MOFKEY_DOWN) && !m_bPipeDown)
				{
					m_Motion.ChangeMotion(MOTION_WAIT);
				}
			}
			else
			{
				m_Motion.ChangeMotion(MOTION_WAIT);
			}
		}
	}
	else if (!m_bGoal && !m_bDead && !m_bPipeDown && !m_bPipeMove && !m_bPipeUp)
	{
		UpdateKey();
	}
	UpdateMove();
    m_PosX += m_MoveX;
	m_PosY += m_MoveY;
	if (m_PosY >= g_pGraphics->GetTargetHeight() + wy)
	{
		DeadEnd();
	}
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

void CPlayer::UpdateKey(void)
{
	
	if (!g_pInput->IsKeyHold(MOFKEY_SPACE))
	{
		if (g_pInput->IsKeyHold(MOFKEY_LEFT))
		{
			m_MoveX -= PLAYER_SPEED;
			m_bMove = true;
			m_bReverse = true;
			if (m_MoveX < -PLAYER_MAXSPEED)
			{
				m_MoveX = -PLAYER_MAXSPEED;
			}
			if ((m_Motion.GetMotionNo() == MOTION_WAIT || m_Motion.GetMotionNo() == MOTION_DASH) )
			{
				m_Motion.ChangeMotion(MOTION_MOVE);
			}
		}
		else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
		{
			m_MoveX += PLAYER_SPEED;
			m_bMove = true;
			m_bReverse = false;
			if (m_MoveX > PLAYER_MAXSPEED)
			{
				m_MoveX = PLAYER_MAXSPEED;
			}
			if ((m_Motion.GetMotionNo() == MOTION_WAIT || m_Motion.GetMotionNo() == MOTION_DASH) )
			{
				m_Motion.ChangeMotion(MOTION_MOVE);
			}
		}
	}
	else
	{
		if (g_pInput->IsKeyHold(MOFKEY_LEFT))
		{
			m_MoveX -= PLAYER_DASHSPEED;
			m_bMove = true;
			m_bReverse = true;
			if (m_MoveX < -PLAYER_DASHMAXSPEED)
			{
				m_MoveX = -PLAYER_DASHMAXSPEED;
			}
			if ((m_Motion.GetMotionNo() == MOTION_WAIT || m_Motion.GetMotionNo() == MOTION_MOVE) )
			{
				m_Motion.ChangeMotion(MOTION_DASH);
			}
		}
		else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
		{
			m_MoveX += PLAYER_DASHSPEED;
			m_bMove = true;
			m_bReverse = false;
			if (m_MoveX > PLAYER_DASHMAXSPEED)
			{
				m_MoveX = PLAYER_DASHMAXSPEED;
			}
			if ((m_Motion.GetMotionNo() == MOTION_WAIT || m_Motion.GetMotionNo() == MOTION_MOVE) )
			{
				m_Motion.ChangeMotion(MOTION_DASH);
			}
		}
	}
	
	
	if (g_pInput->IsKeyPush(MOFKEY_UP) && !m_bJump && m_MoveY == 0)
	{
		m_bJump = true;
		m_MoveY = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
	}
	if (m_bGiant && !m_bJump && (m_Motion.GetMotionNo() == MOTION_WAIT || m_Motion.GetMotionNo() == MOTION_MOVE || m_Motion.GetMotionNo() == MOTION_DASH))
	{
		if (g_pInput->IsKeyHold(MOFKEY_DOWN))
		{
			m_Motion.ChangeMotion(MOTION_SQUAT);
		}
	}
	if (g_pInput->IsKeyHold(MOFKEY_LEFT)&& !g_pInput->IsKeyHold(MOFKEY_RIGHT) && m_MoveX > 3.5f && (m_Motion.GetMotionNo() == MOTION_MOVE || m_Motion.GetMotionNo() == MOTION_DASH))
	{
		m_Motion.ChangeMotion(MOTION_TURN);
	}
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT)&& !g_pInput->IsKeyHold(MOFKEY_LEFT)&& m_MoveX < -3.5f && (m_Motion.GetMotionNo() == MOTION_MOVE || m_Motion.GetMotionNo() == MOTION_DASH))
	{
		m_Motion.ChangeMotion(MOTION_TURN);
	}
	if (m_Motion.GetMotionNo() == MOTION_TURN && m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(MOTION_WAIT);
	}
}

void CPlayer::UpdateMove(void)
{
	if (!m_bMove && !m_bGoal && !m_bDead)
	{
		if (m_MoveX > 0)
		{
			m_MoveX -= PLAYER_STOPSPEED;
			if (m_MoveX <= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_MoveX < 0)
		{
			m_MoveX += PLAYER_STOPSPEED;
			if (m_MoveX >= 0)
			{
				m_MoveX = 0;
			}
		}
		else if ((m_Motion.GetMotionNo() == MOTION_MOVE || m_Motion.GetMotionNo() == MOTION_DASH) && !m_bPipeMove)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
		
	}
	if (!m_bGoalDown && m_Motion.GetMotionNo() != MOTION_GIANT && !m_bPipeDown && !m_bPipeMove && !m_bPipeUp)
	{
		if (g_pInput->IsKeyHold(MOFKEY_UP) && m_MoveY < 0)
		{
			m_MoveY += JUMP_GRAVITY;
		}
		else
		{
			if (!m_bDead )
			{
				m_MoveY += GRAVITY;
			}
			else
			{
				m_MoveY += DEAD_GRAVITY;
			}
			
		}
		if (m_MoveY >= 9.0f)
		{
			m_MoveY = 9.0f;
		}
		if (m_PosX < 0)
		{
			m_PosX = 0;
		}
	}
}

void CPlayer::Render(float wx,float wy)
{
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}
	CRectangle dr = m_SrcRect;
	float px = m_PosX - wx;
	float py = m_PosY - wy;
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	if (m_bCastle)
	{
		return;
	}
	m_Texture.Render(px, py,dr);
	CRectangle pr = PGetRect();
	//CGraphicsUtilities::RenderRect(pr.Left-wx, pr.Top-wy, pr.Right-wx, pr.Bottom-wy, MOF_XRGB(0, 255, 0));
}

void CPlayer::RenderDebug(float wx, float wy)
{
	CGraphicsUtilities::RenderString(10, 70, "プレイヤー位置 X : %.0f , Y : %.0f", m_PosX, m_PosY);
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	CGraphicsUtilities::RenderRect(barec.Left - wx,barec.Top - wy, barec.Right - wx, barec.Bottom - wy, MOF_XRGB(0, 0, 0));
}

void CPlayer::Release(void)
{
	m_Texture.Release();
}

void CPlayer::CollisionStage(float ox, float oy)
{
	m_PosX += ox;
	m_PosY += oy;
	if (oy < 0 && m_MoveY>0)
	{
		m_MoveY = 0;
		if (m_bJump)
		{
			m_bJump = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	if (ox < 0 && m_MoveX>0)
	{
		m_MoveX = 0;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

void CPlayer::MotionRefresh(void)
{
	SpriteAnimationCreate anim[] = {
		{
		   "待機",
			 0,  m_bPlayerF,
			32, m_bPlayerSize,
			TRUE, { {5,0,0} }
		},
		{
		   "歩き",
			 0,  m_bPlayerF,
			32, m_bPlayerSize,
			TRUE, { {8,1,0},{8,2,0},{8,3,0} }
		},
		{
		   "移動",
			 0,  m_bPlayerF,
			32, m_bPlayerSize,
			TRUE, { {5,1,0},{5,2,0},{5,3,0} }
		},
		{
		   "ダッシュ",
			 0,  m_bPlayerF,
			32, m_bPlayerSize,
			TRUE, { {3,1,0},{3,2,0},{3,3,0} }
		},
		{
		   "ジャンプ開始",
			 0, m_bPlayerS,
			32, m_bPlayerSize,
			FALSE, { {1,0,0} }
		},
		{
		   "ジャンプ終了",
			0,  m_bPlayerF,
			32, m_bPlayerSize,
			FALSE, { {1,0,0} }
		},
		{
		   "ターン",
			0,  m_bPlayerS,
			32, m_bPlayerSize,
			FALSE, { {8,1,0} }
		},
		{
		   "ダメージ",
			0,  32,
			32, 32,
			FALSE, { {1,2,0} }
		},
		{
		   "ゴール",
			0,  m_bPlayerT,
			32, m_bPlayerSize,
			TRUE, { {3,0,0},{3,1,0} }
		},
		{
		   "ゴール終了",
			0,  m_bPlayerT,
			32, m_bPlayerSize,
			FALSE, { {32,0,0} }
		},
		{
		   "巨大化",
			0,  288,
			32, 64,
			FALSE, { {4,0,0},{4,1,0},{4,0,0},{4,1,0},{4,0,0},{4,1,0},{4,2,0},{4,0,0},{4,1,0},{4,2,0} }
		},
		{
		   "しゃがみ",
			0,  160,
			32, 64,
			FALSE, { {1,2,0} }
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
}

bool CPlayer::CollisionEnemy(CEnemy& ene)
{
	if (!ene.GetShow())
	{
		return false;
	}
	if (ene.GetDamageWait() > 0)
	{
		return false;
	}
	if (m_DamageWait > 0 && m_MoveY < 0)
	{
		return false;
	}

	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();
	erec.Expansion(-1, -1);
	
	CRectangle hrec = erec;
	hrec.Bottom = (hrec.Bottom + hrec.Top) / 2;

	CRectangle rirec = hrec;
	rirec.Left = (rirec.Left + rirec.Right) / 2;
	CRectangle lerec = hrec;
	lerec.Right = (lerec.Left + lerec.Right) / 2;
	
	CRectangle lrec = prec;
	lrec.Top = lrec.Bottom - 1;

	CRectangle wrec;
	wrec = lrec;
	wrec.Left = (wrec.Left + wrec.Right) / 2 - 1;
	wrec.Right = wrec.Left + 2;

	barec = wrec;

	if (hrec.CollisionRect(lrec))
	{
		m_bJump = true;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
		m_MoveY = -6.0f;
		if (g_pInput->IsKeyHold(MOFKEY_UP)) 
		{
			m_MoveY = -9.0f;
		}
		if (rirec.CollisionRect(wrec))
		{
			m_way = false;
		}
		if (lerec.CollisionRect(wrec))
		{
			m_way = true;
		}
		ene.Damage(1,m_way);
		return true;
	}

	if (m_DamageWait > 0)
	{
		return false;
	}

    if (prec.CollisionRect(erec))
	{
		if (m_bGiant)
		{
			m_PosY += 32;
			m_bPlayerSize = 32;
			m_bPlayerF = 0;
			m_bPlayerS = 32;
			m_bPlayerT = 64;
			MotionRefresh();
			m_Motion.ChangeMotion(MOTION_WAIT);
			m_bGiant = false;
			m_DamageWait = 150;
		}
		//m_HP -= 1;
		
		if (m_HP <= 0)
		{
			DeadEnd();
		}
		return true;
	}
	return false;
}

bool CPlayer::GoalEnd(float ox, float glb, float csw)
{
	if (!m_bGoal)
	{
		m_MoveX = 0;
		m_MoveY = 0;
		m_bGoal = true;
		m_PosX -= ox;
		m_bGoalDown = true;
		if (m_bReverse)
		{
			m_bReverse = false;
		}
		return false;
	}
	if (m_bGoalDown)
	{
		m_DamageWait = 0;
		if (m_Motion.GetMotionNo() != MOTION_GOAL && m_Motion.GetMotionNo() != MOTION_GOALEND)
		{
			m_Motion.ChangeMotion(MOTION_GOAL);
		}
		if (m_Motion.GetMotionNo()==MOTION_GOAL)
		{
			m_PosY += PLAYER_DOWNSPEED;
		}
		CRectangle pr(GetRect());
		float oy = pr.Bottom + 16 - glb;
		if (oy >= 0)
		{
				if (!m_bReverse)
				{
					m_Motion.ChangeMotion(MOTION_GOALEND);
					m_PosX += 24;
					m_bReverse = true;
				}
				if (m_Motion.GetMotionNo() == MOTION_GOALEND && m_Motion.IsEndMotion())
				{
					if (m_bReverse)
					{
						m_bReverse = false;
					}
					m_bGoalDown = false;
					m_MoveX = PLAYER_GOALEDSPEED;
					m_Motion.ChangeMotion(MOTION_WAIT);
				}
				
		}
		return false;
	}
	if (m_PosX + 32 < csw)
	{
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
		return false;
	}
	else
	{
		if (!m_bCastle)
		{
			m_MoveX = 0;
			m_MoveY = 0;
			m_bCastle = true;
		}
	}
	
	if (m_bCastleCount >= 0)
	{
		m_bCastleCount--;
		return false;
	}
	return true;
}

bool CPlayer::DeadEnd(void)
{
	if (!m_bDead)
	{
		m_MoveX = 0;
		m_MoveY = -8.0;
		m_Motion.ChangeMotion(MOTION_DEAD);
		m_bDead = true;
	}
	if (m_PosY < g_pGraphics->GetTargetHeight())
	{
		return false;
	}
	return true;
}

bool CPlayer::CollisionItem(CItem& itm)
{
	if (!itm.GetShow())
	{
		return false;
	}
    CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	if(!itm.GetSpawn())
	{
		CRectangle hrec = prec;
		CRectangle brec = irec;
		hrec.Bottom = hrec.Top + 1;
		hrec.Expansion(-6, 0);
		brec.Expansion(-6, 32);
		brec.Top = brec.Bottom - 1;
		if (hrec.CollisionRect(brec))
		{
			itm.SetSpawn(true);
		}
		return false;
	}
	
	if (!itm.GetMove())
	{
		return false;
	}
	if (itm.GetType() == ITEM_COIN) 
	{
		irec.Expansion(-6, -1);
	}
	if (prec.CollisionRect(irec))
	{
		itm.SetShow(false);
		switch (itm.GetType())
		{
		case ITEM_GIANT:
			if (!m_bGiant)
			{
				m_HP++;
				m_MoveX = 0;
				m_MoveY = 0;
				m_PosY -= 32;
				m_bPlayerSize = 64;
				m_bPlayerF = 96;
				m_bPlayerS = 160;
				m_bPlayerT = 224;
				MotionRefresh();
				m_Motion.ChangeMotion(MOTION_GIANT);
				m_DamageWait = 0;
				m_bGiant = true;
			}
			break;
		case ITEM_COIN:
			m_bCoinCount++;
			break;
		}
		return true;
	}
	return false;
}

void CPlayer::CollisionPipe(CRectangle tp,CRectangle bp, CRectangle lp, CRectangle rp, CRectangle up)
{
	CRectangle dr(PGetRect().Left, PGetRect().Top, PGetRect().Right, PGetRect().Bottom);
	CRectangle mr(GetRect().Left, GetRect().Top, GetRect().Right, GetRect().Bottom);
	CRectangle ur(GetRect().Left, GetRect().Top, GetRect().Right, GetRect().Bottom);
	if (!m_bGiant)
	{
		ur.Top = ur.Bottom - 64;
	}
	if (dr.CollisionRect(tp))
	{
		if (!m_bJump && g_pInput->IsKeyHold(MOFKEY_DOWN))
		{
			if (!m_bPipeDown)
			{
				m_MoveX = 0;
				m_MoveY = 0;
				m_DamageWait = 0;
				m_bPipeDown = true;
			}
		}
	}
	if (m_bPipeDown)
	{
		if (m_Motion.GetMotionNo() != MOTION_SQUAT && m_bGiant)
		{
			m_Motion.ChangeMotion(MOTION_SQUAT);
		}
		m_PosY += 1.5f;
		if (dr.CollisionRect(bp))
		{
			if (m_bReverse)
			{
				m_bReverse = false;
			}
			m_bUnder = true;
			m_PosX = 1584;
			m_PosY = 544;
			m_bPipeDown = false;
		}
	}
	if (mr.CollisionRect(lp))
	{
		if (!m_bJump && m_MoveY == GRAVITY && g_pInput->IsKeyHold(MOFKEY_RIGHT))
		{
			if (!m_bPipeMove)
			{
				m_MoveY = 0;
				m_MoveX = 0;
				m_Motion.ChangeMotion(MOTION_MOVE);
				m_bPipeMove = true;
			}
		}
	}
	if (m_bPipeMove)
	{
		m_PosX += 1.5f;
		if (mr.CollisionRect(rp))
		{
			if (m_bReverse)
			{
				m_bReverse = false;
			}
			m_bUnder = false;
			m_MoveX = 0;
			m_MoveY = 0;
			m_PosX = 5232;
			m_PosY = 320;
			m_bPipeUp = true;
			m_bPipeMove = false;
		}
	}
	if (m_bPipeUp)
	{
		m_PosY -= 1.5f;
		if(ur.CollisionRect(up))
		{
			m_bPipeUp = false;
		}
	}
}
