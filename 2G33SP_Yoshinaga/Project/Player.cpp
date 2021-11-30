#include "Player.h"   




CPlayer::CPlayer() :
	px(200),
	py(640),
	vx(5),
	JumpSpd	(0.0f),
	MoveFlg(false),
	JumpFlg(false),
    m_bReverse(false),
	LifeCount(3),
	m_DamageWait(0){
}


CPlayer::~CPlayer()
{

}

bool CPlayer::Load(void)
{
	//キャラクタのテクスチャの読み込み
	if (!gTexture.Load("Fox.png")) {
		return	false;
	}

	//ライフゲージのテクスチャの読み込み
if (!HP1.Load("Heart_1.png"))
{
	return false;
}
if (!HP2.Load("Heart_2.png"))
{
	return false;
}
if(!HP3.Load("Heart_3.png"))
{
	return false;
}



	//アニメーションの作成
	SpriteAnimationCreate anim[] = {
		{
			"待機",  
			0,8,
			30,35,
			TRUE,{{10,0,0},{10,1,0},{10,2,0}}
		},
		{
			"移動",
			0,260,
			30,35,
			TRUE,{{10,0,0},{10,1,0},{10,2,0}}
},
		
		{
			"ジャンプ",
			0,50,
			30,35,
			FALSE,{{10,0,0},{10,1,0},{10,2,0}}
},
	
		{
			"ダメージ",
			0,353,
			30,35,
			FALSE,{{5,0,0},{5,1,0},{5,2,0}}
},
	};


	m_Motion.Create(anim, MOTION_COUNT);

	return true;
}

void CPlayer::Initialize(void)
{
	px = 200;
	py=640;
	vx = 5;
	JumpSpd = 0.0f;
	MoveFlg = false;
	JumpFlg = false;
	m_bReverse = false;
	LifeCount = 3;
	m_DamageWait=0;
//	m_Motion.ChangeMotion(MOTION_WAIT);
	
}

void CPlayer::Update(void)
{

	MoveFlg = false;
	//ダメージ中の動作
	if (m_Motion.GetMotionNo()==MOTION_DAMAGE)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}

	}
	else
	{
		//キー入力による動作
		UpdateKey();

	}
	

	UpdateMove();

	px += vx;
	py += JumpSpd;


	//ダメージのインターバルを減らす
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}


//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	
}

void CPlayer::UpdateKey(void)
{
	

	//左キーで移動
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		vx -= PLAYER_SPEED;
		m_bReverse=true;
		MoveFlg = true;
		if (vx<-PLAYER_MAXSPEED)
		{
			vx = -PLAYER_MAXSPEED;
		}

		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}

	}
	//右キーで移動
	else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		vx += PLAYER_SPEED;
		m_bReverse = false;
		MoveFlg =true;
		if (vx>PLAYER_MAXSPEED)
		{
			vx = PLAYER_MAXSPEED;
		}

		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}

	}
	else if(m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(MOTION_WAIT);
	}
	
	//スペースキーでジャンプ
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !JumpFlg)
	{
		//ジャンプ開始
		JumpFlg = true;
		JumpSpd = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMP);
		
	}
	

	if (JumpFlg == false)
	{
		m_Motion.ChangeMotion(MOTION_WAIT);
	}
	
}

void CPlayer::UpdateMove(void)
{

	if (!MoveFlg)
	{
		if (vx > 0)
		{
			vx -= PLAYER_SPEED;
			if (vx <= 0)
			{
				vx = 0;
			}
		}
		else if (vx < 0)
		{
			vx += PLAYER_SPEED;
			if (vx >= 0)
			{
				vx = 0;
			}
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}

     }
	

		//プレイヤーの速度に重力を加える
	JumpSpd += GRAVITY;
	if (JumpSpd >= 20.0f)
	{
		JumpSpd = 20.0f;
	}

}


void CPlayer::CollisionStage(float ox, float oy)
{

	px+= ox;
	py += oy;
	
	if (oy<0 && JumpSpd>0)
	{
		//落下中の下埋まり
		JumpSpd = 0;
		if (JumpFlg)
		{
			JumpFlg = false;
			m_Motion.ChangeMotion(MOTION_JUMP);
		}		
	}
	else if (oy>0 &&JumpSpd<0)
	{
		JumpSpd = 0;
	}


	//左移動中の左埋まり
	if (ox < 0 && vx> 0)
	{
	   vx = 0;		
	}		
	else if (ox > 0 && vx < 0)
	{
	 vx = 0;
	}
	
}

void CPlayer::Render(float wx, float wy)
{

	/*if (CollisionEneHed)
	{
		CGraphicsUtilities::RenderString(100, 100, "当たっている！！", MOF_COLOR_BLACK);
	}*/



	//インターバル2フレームごとに描画をしない
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	//描画矩形
	CRectangle dr = m_SrcRect;


	//反転フラグがONの場合矩形を反転
	if (m_bReverse) {
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//描画位置&テクスチャの描画 
	gTexture.Render(px - wx, py - wy, dr);


	switch (LifeCount) {
	case 1:
	{
		HP1.RenderScale(50, 20,2.0f);
		break;
	}
	case 2:
	{
		HP2.RenderScale(50, 20,2.0f);
		break;
	}
	case 3:
	{
		HP3.RenderScale(50,20,2.0f);
		break;
	}
	default:
		break;
	}

}

void CPlayer::renderDebug(float wx, float wy)
{
	CGraphicsUtilities::RenderString(10, 70, "プレイヤー位置 X : %.0f , Y : %.0f", px, py,MOF_XRGB(255,0,0));

		CRectangle hr = GetRect();
		CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy,
			hr.Right - wx, hr.Bottom - wy, MOF_COLOR_RED);	

		CRectangle lR = GetLegRect();
		CGraphicsUtilities::RenderRect(lR.Left - wx, lR.Top - wy, lR.Right - wx, lR.Bottom - wy, MOF_COLOR_HGREEN);
	
}

void CPlayer::Release(void)
{
	//テクスチャの解放
	gTexture.Release();
	m_Motion.Release();
	HP1.Release();
	HP2.Release();
	HP3.Release();
}






float CPlayer::GetPosY()
{
	return py;
}



//敵との当たり判定
bool CPlayer::CollisionEnemyBody(CEnemy& ene)
{
	if (!ene.GetShow())
	{
		return false;
	}

	//ダメージ中のため当たり判定をおこなわない
	if (m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}
	//敵の矩形と自分の矩形でダメージ
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();
	if (prec.CollisionRect(erec))
	{
		m_DamageWait = 60;
		if (LifeCount > 0)
		{
			LifeCount--;
		}

		if (prec.Left < erec.Left)
		{
			vx = -5.0f;
			m_bReverse = false;
		}
		else
		{
			vx = 5.0f;
			m_bReverse = true;
		}
		
	}
}

void CPlayer::Damage(void)
{
	m_DamageWait = 60;
	if (LifeCount > 0)
	{
		LifeCount--;
	}
	m_Motion.ChangeMotion(MOTION_DAMAGE);
}


bool CPlayer::CollisionEnemyHed(CEnemy& ene)
{

	CRectangle plrec=GetLegRect();
	CRectangle ehrec=ene.GetHedRect();

	if (plrec.CollisionRect(ehrec))
	{
		m_HedCollFlg = true;
	}
	return false;
}

void CPlayer::CollisionJump(void)
{
	m_Motion.ChangeMotion(MOTION_JUMP);

	JumpSpd = -10;
}



