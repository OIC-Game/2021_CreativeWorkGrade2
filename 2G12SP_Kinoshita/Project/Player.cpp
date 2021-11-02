#include "Player.h"

CPlayer::CPlayer() :
	player(),
	m_Motion(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_bMove(false),
	m_MoveX(0.0f),
	m_MoveY(0.0f),
	m_bJump(false),
	m_bReverse(false),
	m_bDash(false),
	m_SrcRect(),
	m_bDead(false),
	m_bSky(false),
	m_ItemTexture(),
	m_ItemTextureCount(),
	m_ItemCount(0),
	m_Itemwait()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Lood(void)
{
	if (!player.Load("playerchar.png"))
	{
		return false;
	}

	if (!m_ItemTexture.Load("kinoko.png"))
	{
		return false;
	}
	for (int i = 0; i < Item_count; i++)
	{
		m_ItemArray[i].SetTexture(&m_ItemTexture);
	}

	SpriteAnimationCreate anim[] =
	{
		{
		"待機",
		0,0,
		60,64,
		TRUE,{{5,0,0}}
		},
		{
		"移動",
		0,0,
		60,64,
		TRUE,{{5,0,0},{5,1,0}}
		},
		{
			"ジャンプ開始",
		0,80,
		60,64,
		FALSE,{{5,0,0}}
		},
		{
			"ジャンプ終了",
		70,70,
		60,64,
		FALSE,{{2,0,0}}
		},
		{
			"ダッシュ",
			0,145,
			60,77,
			TRUE,{{5,0,0},{5,1,0}}
		},


		{
			"スーパー待機",
			0,240,
			60,64,
			TRUE,{{5,0,0}}
		},
		{
			"スーパー移動",
			0,240,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0}}
		},
		{
			"スーパージャンプ開始",
		0,390,
		60,72,
		FALSE,{{5,0,0}}
		},
		{
		"スーパージャンプ終了",
		70,400,
		60,64,
		FALSE,{{2,0,0}}
		},
		{
		"スーパダッシュ",
			0,310,
			60,77,
			TRUE,{{5,0,0},{5,1,0}}
		}

	};
	m_Motion.Create(anim, MOTION_COUNT);
	return true;
}

void CPlayer::Initalize()
{
	m_PosX = 200;
	m_PosY = 660;
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_bDash = false;
	m_HP = 1;
	m_Power = 0;
	m_DamageWait = 0;
	m_bJump = false;
	m_bDead = false;
	m_bSky = false;
	m_bGoal = false;
	m_Motion.ChangeMotion(MOTION_WAIT);
	for (int i = 0; i < Item_count; i++)
	{
		m_ItemArray[i].Initialize();
	}

}

void CPlayer::Update(void)
{
	if (m_HP <= 0)
	{
		m_bDead = true;
		return;
	}
	if (m_PosY < 1)
	{
		m_bSky = true;
		return;
	}

	if (m_PosX < 0)
	{
		m_PosX = 0;
	}


	m_bMove = false;

	if (m_Power == 0)
	{
			UpdateKey();
	}
	else  if (m_Power == 1)
	{
			UpdateKey();
	}

	UpdateMove();
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;

	if (m_PosY + m_SrcRect.GetHeight() >= g_pGraphics->GetTargetHeight())
	{
		m_PosY = g_pGraphics->GetTargetHeight() - m_SrcRect.GetHeight();
		m_PosY = 0;
		if (m_bJump)
		{
			m_bJump = false;
		}
	}

	if (m_PosY >= g_pGraphics->GetTargetHeight() && m_HP < 0)
	{
		m_HP = 0;
		m_bDead = true;
	}

	if (m_PosY > 670)
	{
		m_HP = 0;
		m_bDead = true;
	}

	//アニメーション更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();


	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
	for (int i = 0; i < Item_count; i++)
	{
		m_ItemArray[i].Update();
	}

}

void CPlayer::UpdateMove(void)
{
	if (!m_bMove)
	{
		if (m_MoveX > 0)
		{
			m_MoveX -= PLAYER_SPEED;
			if (m_MoveX <= 0)
			{
				m_MoveX = 0;
			}
			m_MoveX -= PLAYER_SPEED2;
			if (m_MoveX <= 0)
			{
				m_MoveX = 0;
			}
		}

		else if (m_MoveX < 0)
		{
			m_MoveX += PLAYER_SPEED;
			if (m_MoveX >= 0)
			{
				m_MoveX = 0;
			}
			m_MoveX += PLAYER_SPEED2;
			if (m_MoveX >= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE || m_Motion.GetMotionNo() == MOTION_Dash)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}

		else if (m_Motion.GetMotionNo() == MOTION_SupeerMove || m_Motion.GetMotionNo() == MOTION_SupeerDash)
		{
			m_Motion.ChangeMotion(MOTION_SupeerWAIT);
		}
	}
	m_MoveY += GRAVITY;
	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
}

void CPlayer::UpdateKey(void)
{
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_MoveX -= PLAYER_SPEED;
		m_bReverse = true;
		m_bMove = true;
		m_bDash = false;
		if (m_MoveX < -PLAYER_MAXSPEED)
		{
			m_MoveX = -PLAYER_MAXSPEED;
		}

		if (m_Power == 0)
		{
			if (m_Motion.GetMotionNo() == MOTION_WAIT)
			{
				m_Motion.ChangeMotion(MOTION_MOVE);
			}
		}
		else
		{
			if (m_Motion.GetMotionNo() == MOTION_SupeerWAIT)
			{
				m_Motion.ChangeMotion(MOTION_SupeerMove);
			}
		}

		if (g_pInput->IsKeyHold(MOFKEY_LEFT) && g_pInput->IsKeyHold(MOFKEY_B))
		{
			m_MoveX -= PLAYER_SPEED * 4;
			m_bReverse = true;
			m_bMove = true;
			m_bDash = true;
			if (m_MoveX < -PLAYER_MAXSPEED2)
			{
				m_MoveX = -PLAYER_MAXSPEED2;
			}
			if (m_Power == 0)
			{
				if (m_Motion.GetMotionNo() == MOTION_WAIT || m_Motion.GetMotionNo() == MOTION_MOVE)
				{
					m_Motion.ChangeMotion(MOTION_Dash);
				}
			}
			else
			{
				if (m_Motion.GetMotionNo() == MOTION_SupeerWAIT || m_Motion.GetMotionNo() == MOTION_SupeerMove)
				{
					m_Motion.ChangeMotion(MOTION_SupeerDash);
				}
			}
		}
	}

	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_MoveX += PLAYER_SPEED;
		m_bReverse = false;
		m_bMove = true;
		m_bDash = false;
		if (m_MoveX > PLAYER_MAXSPEED)
		{
			m_MoveX = PLAYER_MAXSPEED;
		}
		if (m_Power == 0)
		{
			if (m_Motion.GetMotionNo() == MOTION_WAIT)
			{
				m_Motion.ChangeMotion(MOTION_MOVE);
			}
		}
		else
		{
			if (m_Motion.GetMotionNo() == MOTION_SupeerWAIT)
			{
				m_Motion.ChangeMotion(MOTION_SupeerMove);
			}
		}
		if (g_pInput->IsKeyHold(MOFKEY_B))
		{

			m_MoveX += PLAYER_SPEED * 4;
			m_bReverse = false;
			m_bMove = true;
			m_bDash = true;
			if (m_MoveX > PLAYER_MAXSPEED2)
			{
				m_MoveX = PLAYER_MAXSPEED2;
			}
			if (m_Power == 0)
			{
				if (m_Motion.GetMotionNo() == MOTION_WAIT || m_Motion.GetMotionNo() == MOTION_MOVE)
				{
					m_Motion.ChangeMotion(MOTION_Dash);
				}
			}
			else if (m_Power == 1)
			{
				if (m_Motion.GetMotionNo() == MOTION_SupeerWAIT || m_Motion.GetMotionNo() == MOTION_SupeerMove)
				{
					m_Motion.ChangeMotion(MOTION_SupeerDash);
				}
			}
		}
	}

	if (g_pInput->IsKeyHold(MOFKEY_UP) && !m_bJump)
	{
		m_bJump = true;
		m_MoveY = PLAYER_JUMP;
		if (m_Power == 0)
		{
			m_Motion.ChangeMotion(MOTION_JUMPSTART);
		}
		else
		{
			m_Motion.ChangeMotion(MOTION_SupeerJUMPSTART);
		}
	}
}

void CPlayer::Render(float wx, float wy)
{

	if (m_DamageWait % 4 >= 2)
	{
		return;;
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
	player.Render(px, py, dr);

	for (int i = 0; i < Item_count; i++)
	{

		m_ItemArray[i].Render(wx, wy);
	}
}

void CPlayer::RenderDebug(float wx, float wy)
{
	float px = m_PosX - wx;
	float py = m_PosY - wy;

	CGraphicsUtilities::RenderString(10, 70, "プレイヤー位置 X : %.0f , Y : %.0f", m_PosX, m_PosY);

	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 0, 0));

	CRectangle le = GetLEG();
	CGraphicsUtilities::RenderRect(le.Left - wx, le.Top - wy, le.Right - wx, le.Bottom - wy, MOF_XRGB(0, 0, 0));

	CRectangle bo = Getbody();
	CGraphicsUtilities::RenderRect(bo.Left - wx, bo.Top - wy, bo.Right - wx, bo.Bottom - wy, MOF_XRGB(0, 0, 0));

	CRectangle he = Gethed();
	CGraphicsUtilities::RenderRect(he.Left - wx, he.Top - wy, he.Right - wx, he.Bottom - wy, MOF_XRGB(0, 0, 0));
}

void CPlayer::Release(void)
{
	player.Release();
	m_ItemTexture.Release();
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
			//m_Motion.ChangeMotion(m_Power == 0 ? MOTION_JUMPEND : MOTION_SupeerJUMPEND);
			m_Motion.ChangeMotion(m_Power == 0 ? MOTION_WAIT : MOTION_SupeerWAIT);
		}
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;

	}

	if (ox < 0 && m_MoveX >0)
	{
		m_MoveX = 0;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

bool CPlayer::CollisionEnemy(CEnemy& ene)
{

	if (!ene.GetShow())
	{
		return false;
	}

	if (m_HP <= 0)
	{
		return false;
	}


	if (m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}

	CRectangle prec = Getbody();
	CRectangle erec = ene.GetRect();
	if (prec.CollisionRect(erec))
	{
		m_HP -= 1;
		m_DamageWait = 60;
		if (m_Power == 1)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
		return true;
	}
	CRectangle pre = GetLEG();
	CRectangle erebody = ene.Gethed();
	if (pre.CollisionRect(erec))
	{
		m_MoveY = -2;
		ene.Damage(2, m_bReverse);
		return true;
	}
	return false;
}

bool CPlayer::CollisionBlock(CBlock& Block, float ox, float oy)
{
	CRectangle prec = Gethed();
	CRectangle bl = Block.GetRect();
	if (prec.CollisionRect(bl))
	{
		m_MoveX = 0;
		m_MoveY = 0;
		m_PosY += bl.Bottom - prec.Top;

	}
	CRectangle prlg = GetLEG();
	if (prlg.CollisionRect(bl))
	{
		m_PosX += ox;
		m_PosY += oy - 0.5;
		m_MoveY += -50;
		//m_PosY += oy - 0.5;

		if (oy < 40 && m_MoveY>0)
		{
			m_MoveY = 0;

			if (m_bJump)
			{
				m_bJump = false;
				m_Motion.ChangeMotion(MOTION_JUMPEND);
			}
			else if (m_bJump && m_HP == 2)
			{
				m_bJump = false;
				m_Motion.ChangeMotion(MOTION_SupeerJUMPEND);
			}

		}
		else if (oy > 0 && m_MoveY < 0)
		{
			m_MoveY = 0;
		}

		if (ox < 40 && m_MoveX >0)
		{
			m_MoveX = 0;
		}
		else if (ox > 0 && m_MoveX < 0)
		{
			m_MoveX = 0;
		}
	}

	return false;
}
bool CPlayer::CollisionQBlock(CQuestionBlock& QBlock, float ox, float oy)
{
	CRectangle prec = Gethed();
	CRectangle bl = QBlock.GetRect();
	if (prec.CollisionRect(bl))
	{
		m_MoveX = 0;
		m_MoveY = 0;
		m_PosY += bl.Bottom - prec.Top;
	
		if (QBlock.GetItemShow() == false)
		{
			//QBlock.GetItemShow() = true;
			QBlock.Update();
			for (int i = 0; i < Item_count; i++)
			{
				if (m_ItemArray[i].GetShow())
				{
					continue;
				}
				m_ItemArray[i].Fire(QBlock.GetPosx() + m_ItemTexture.GetWidth() * 0.01f, QBlock.GetPosy() - m_ItemTexture.GetHeight());

				break;
			}
		}
	}

	CRectangle prlg = GetLEG();
	if (prlg.CollisionRect(bl))
	{
		m_PosX += ox;
		m_PosY += oy - 0.3;

		if (oy < 40 && m_MoveY>0)
		{
			m_MoveY = 0;

			if (m_bJump && m_Power==0)
			{
				m_bJump = false;
				
				m_Motion.ChangeMotion(MOTION_WAIT);
			}
			else if (m_bJump && m_Power == 1)
			{
				m_bJump = false;
			
				m_Motion.ChangeMotion(MOTION_SupeerWAIT);
			}
		}
		else if (oy > 0 && m_MoveY < 30)
		{
			m_MoveY = 0;
		}

		if (ox < 0 && m_MoveX >40)
		{
			m_MoveX = 0;
		}
		else if (ox > 0 && m_MoveX < 40)
		{
			m_MoveX = 0;
		}
	}
	return false;
}

bool CPlayer::CollisionGoal(CGoal& goal)
{
	CRectangle prec = GetRect();
	CRectangle gol = goal.GetRect();
	if (prec.CollisionRect(gol))
	{
		m_bGoal = true;
	}
	return false;
}

bool CPlayer::CollisionbreakBlock(CbreakBlock& blo, float ox, float oy)
{
	CRectangle prec = Gethed();
	CRectangle bl = blo.GetRect();
	CRectangle bo = Getbody();
	CRectangle prlg = GetLEG();
	if (prec.CollisionRect(bl))
	{
		m_MoveX = 0;
		m_MoveY = 0;
		m_PosY += bl.Bottom - prec.Top;
	}
	else if (prlg.CollisionRect(bl))
	{
		m_PosX += ox;
		m_PosY += oy - 0.3;

		if (oy < 40 && m_MoveY>0)
		{
			m_MoveY = 0;

			if (m_bJump && m_Power==0)
			{
				m_bJump = false;
				
				m_Motion.ChangeMotion(MOTION_WAIT);
			}
			else if (m_bJump && m_Power==1)
			{
				m_bJump = false;
				
				m_Motion.ChangeMotion(MOTION_SupeerWAIT);
			}
		}
		else if (oy > 0 && m_MoveY < 0)
		{
			m_MoveY = 0;

		}
		if (ox < 0 && m_MoveX >0)
		{
			m_MoveX = 0;
		}
		else if (ox > 0 && m_MoveX < 0)
		{
			m_MoveX = 0;
		}
	}
	else if (bo.CollisionRect(bl))
	{
		m_MoveX = 0;
		m_MoveY = 0;
		m_PosX += 0;
		m_PosY += 0;
	}
	return false;
}

bool CPlayer::CollusionItem(CItem& itm)
{
	if (!itm.GetShow())
	{
		return false;
	}
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	if (prec.CollisionRect(irec))
	{
		m_Power = +1;
		m_HP += 1;

		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_SupeerWAIT);
		}
		else if (m_Motion.GetMotionNo() == MOTION_Dash)
		{
			m_Motion.ChangeMotion(MOTION_SupeerDash);
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_SupeerMove);
		}

		if (itm.GetShow() == true)
		{
			itm.showItem();
			m_ItemShow = false;

		}
	}
	return false;
}


CRectangle CPlayer::GetRect(void)
{
	if (m_bJump == true)
	{
		return CRectangle(
			m_PosX + 20, m_PosY + 40, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight()
		);
	}
	else if (m_bDash == true)
	{
		return CRectangle(
			m_PosX + 20, m_PosY + 40, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight()
		);
	}

	else
	{
		return CRectangle(
			m_PosX + 20, m_PosY + 30, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight()
		);
	}
}

CRectangle CPlayer::GetLEG(void)
{
	if (m_bJump == true)
	{
		return CRectangle(
			m_PosX + PLAYER_RECTDECREASE + 10, m_PosY + PLAYER_RECTDECREASE + 50, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight()
		);
	}

	else if (m_bDash == true)
	{
		return CRectangle(
			m_PosX + PLAYER_RECTDECREASE + 10, m_PosY + PLAYER_RECTDECREASE + 60, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight()
		);
	}

	else
	{
		return CRectangle(
			m_PosX + PLAYER_RECTDECREASE + 10, m_PosY + PLAYER_RECTDECREASE + 50, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight()
		);
	}
}

CRectangle CPlayer::Getbody(void)
{


	if (m_bJump == true)
	{
		return CRectangle(
			m_PosX + PLAYER_RECTDECREASE + 10, m_PosY + PLAYER_RECTDECREASE + 50, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight() - 15
		);
	}

	else if (m_bDash == true)
	{
		return CRectangle(
			m_PosX + PLAYER_RECTDECREASE + 10, m_PosY + PLAYER_RECTDECREASE + 50, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight() - 5
		);
	}

	else
	{
		return CRectangle(
			m_PosX + PLAYER_RECTDECREASE + 10, m_PosY + PLAYER_RECTDECREASE + 40, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight() - 5
		);
	}
}

CRectangle CPlayer::Gethed(void)
{
	if (m_bJump == true)
	{
		return CRectangle
		(m_PosX + PLAYER_RECTDECREASE + 10, m_PosY + PLAYER_RECTDECREASE + 10, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight() - 10
		);
	}
	if (m_bDash == true)
	{
		return CRectangle
		(m_PosX + PLAYER_RECTDECREASE + 10, m_PosY + PLAYER_RECTDECREASE + 25, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight() - 20
		);
	}
	else
	{
		return CRectangle
		(m_PosX + PLAYER_RECTDECREASE + 10, m_PosY + PLAYER_RECTDECREASE + 20, m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - 10, m_PosY + m_SrcRect.GetHeight() - 15
		);
	}
}

