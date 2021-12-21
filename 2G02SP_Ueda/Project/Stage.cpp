#include	"Stage.h"
#include	<sys/stat.h>

/**
 * コンストラクタ
 *
 */
CStage::CStage() :
m_ChipTexture() ,
m_BackTexture() ,
m_InfoTexture() ,
m_NumberTexture() ,
m_ChipSize(0) ,
m_XCount(0) ,
m_YCount(0) ,
m_pChipData(NULL) ,
m_ScrollX(0) ,
m_ScrollY(0),
m_EnemyTextureCount(0),
m_pEnemyTexture(NULL),
m_pEnemyData(NULL),
m_EnemyCount(0),
m_bGoalBottom(0),
m_bGoalTop(0),
m_bGoalX(0),
m_bCastle(0),
m_bGoal(false),
m_ItemTextureCount(0),
m_pItemTexture(NULL),
m_ItemCount(0),
m_tPipe(),
m_bPipe(),
m_rPipe(),
m_lPipe(),
m_uPipe(),
m_bCoinCount(0),
m_bTimeCount(0),
m_bcten(0),
m_bcone(0),
m_bthun(0),
m_btten(0),
m_btone(0),
m_bUnder(false),
m_bOn(false),
m_Player(),
m_pItemData(),
timecount(0)
{
}

/**
 * デストラクタ
 *
 */
CStage::~CStage(){
}

/**
 * 読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			pName				ステージファイルの名前
 */
bool CStage::Load(char* pName,char* gpName){
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* pBuffer = (char*)malloc(fSize + 1);
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr))
	{
		return false;
	}

	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr))
	{
		return false;
	}

	pstr = strtok(NULL, ",");
	if (!m_InfoTexture.Load(pstr))
	{
		return false;
	}

	pstr = strtok(NULL, ",");
	if (!m_NumberTexture.Load(pstr))
	{
		return false;
	}

	m_ChipSize = atof(strtok(NULL, ","));
	m_XCount = atoi(strtok(NULL, ","));
	m_YCount = atoi(strtok(NULL, ","));

	m_pChipData = (char*)malloc(m_XCount * m_YCount);

	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pChipData[y * m_XCount + x] = atoi(strtok(NULL, ","));
		}
	}
	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);
	m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
	for (int i = 0; i < m_EnemyTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pEnemyTexture[i].Load(pstr))
		{
			return false;
		}
	}

	m_pEnemyData = (char*)malloc(m_XCount * m_YCount);
	m_EnemyCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pEnemyData[y * m_XCount + x] = atoi(strtok(NULL, ","));
			if (m_pEnemyData[y * m_XCount + x] > 0)
			{
				m_EnemyCount++;
			}
		}
	}

	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for (int i = 0; i < m_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pItemTexture[i].Load(pstr))
		{
			return false;
		}
	}

	m_pItemData = (char*)malloc(m_XCount * m_YCount);
	m_ItemCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			m_pItemData[y * m_XCount + x] = atoi(pstr);
			if (m_pItemData[y * m_XCount + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}


	fp = fopen(gpName, "rt");
	if (fp == NULL) {
		return false;
	}
	fseek(fp, 0, SEEK_END);
	fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	pBuffer = (char*)malloc(fSize + 1);
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';

	m_bGoalX = atoi(strtok(pBuffer, ","));
	m_bGoalTop = atoi(strtok(NULL, ","));
	m_bGoalBottom = atoi(strtok(NULL, ","));
	m_bCastle = atoi(strtok(NULL, ","));

	fclose(fp);
	free(pBuffer);
	return true;
}

bool CStage::LoadStage(char* pName)
{
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* pBuffer = (char*)malloc(fSize + 1);
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	pstr = strtok(pBuffer, ",");
	pstr = strtok(NULL, ",");
	pstr = strtok(NULL, ",");
	pstr = strtok(NULL, ",");

	m_ChipSize = atof(strtok(NULL, ","));
	m_XCount = atoi(strtok(NULL, ","));
	m_YCount = atoi(strtok(NULL, ","));

	m_pChipData = (char*)malloc(m_XCount * m_YCount);

	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pChipData[y * m_XCount + x] = atoi(strtok(NULL, ","));
		}
	}
	return true;
}

void CStage::Initialize(CPlayer* pPlayer, CEnemy* pEnemy,CItem* pItem){
	m_Player = pPlayer;
	m_bGoal = false;
	m_bUnder = false;
	m_bOn = false;
	m_ScrollX = 0;
	m_ScrollY = 0;
	m_bCoinCount = 0;
	m_bTimeCount = 400;
	timecount = 0;
	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on]);
			pEnemy[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			char on = m_pItemData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pItem[n].SetTexture(&m_pItemTexture[on]);
			pItem[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
}

void CStage::Update(CPlayer& pl){
	CRectangle tp(57 * m_ChipSize + 24, 7 * m_ChipSize + m_ChipSize / 2, 58 * m_ChipSize + 8, 8 * m_ChipSize);
	CRectangle bp(57 * m_ChipSize, 10 * m_ChipSize, 59 * m_ChipSize, 11 * m_ChipSize);
	CRectangle lp(61 * m_ChipSize - 1, 26 * m_ChipSize, 62 * m_ChipSize, 27 * m_ChipSize);
	CRectangle rp(63 * m_ChipSize - m_ChipSize / 8, 25 * m_ChipSize, 64 * m_ChipSize, 27 * m_ChipSize);
	CRectangle up(163 * m_ChipSize, 7 * m_ChipSize, 165 * m_ChipSize, 8 * m_ChipSize);
	m_tPipe = tp;
	m_bPipe = bp;
	m_lPipe = lp;
	m_rPipe = rp;
	m_uPipe = up;
	CRectangle prec = pl.GetRect();
	float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	float stgw = m_ChipSize * m_XCount;
	if (!pl.GetUnder())
	{
		if (m_bGoal)
		{
			if (prec.Right - m_ScrollX > sw - g_pGraphics->GetTargetWidth() / 2 + 32)
			{
				m_ScrollX += (prec.Right - m_ScrollX) - (sw - g_pGraphics->GetTargetWidth() / 2 + 32);
				if (m_ScrollX >= stgw - sw)
				{
					m_ScrollX = stgw - sw;
				}
			}
		}
		else
		{
			if (prec.Right - m_ScrollX > sw - g_pGraphics->GetTargetWidth() / 2)
			{
				m_ScrollX += (prec.Right - m_ScrollX) - (sw - g_pGraphics->GetTargetWidth() / 2);
				if (m_ScrollX >= stgw - sw)
				{
					m_ScrollX = stgw - sw;
				}
			}
		}
	}
	if (!pl.GetDead())
	{
		if (timecount <= 0 && !m_bGoal)
		{
			if (m_bTimeCount > 0)
			{
				m_bTimeCount--;
				timecount = 24;
			}
		}
		else
		{
			timecount--;
		}
	}
	m_bCoinCount = pl.GetCoinCount();
	m_bcten = m_bCoinCount / 10;
	m_bcone = m_bCoinCount % 10;
	m_bthun = m_bTimeCount / 100;
	m_btten = (m_bTimeCount % 100) / 10;
	m_btone = m_bTimeCount % 10;
	if (m_bTimeCount <= 0)
	{
		pl.DeadEnd();
	}
}

void CStage::Render(void){
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-m_ScrollY % hn) - hn; y < sch; y += hn)
	{
		for (float x = ((int)-m_ScrollX % wn) - wn; x < scw; x += wn)
		{
			m_BackTexture.Render(x, y);
		}
	}

	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize * (cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			m_ChipTexture.Render(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize, cr);
		}
	}
	m_InfoTexture.Render(0, 0);
	int ntcx = m_NumberTexture.GetWidth() / NCHIPSIZE;
	CRectangle ctr(NCHIPSIZE * (m_bcten % ntcx), NCHIPSIZE * (m_bcten / ntcx), NCHIPSIZE * (m_bcten % ntcx + 1), NCHIPSIZE * (m_bcten / ntcx + 1));
	CRectangle cor (NCHIPSIZE * (m_bcone % ntcx), NCHIPSIZE * (m_bcone / ntcx), NCHIPSIZE * (m_bcone % ntcx + 1), NCHIPSIZE * (m_bcone / ntcx + 1));
	CRectangle thr(NCHIPSIZE * (m_bthun % ntcx), NCHIPSIZE * (m_bthun / ntcx), NCHIPSIZE * (m_bthun % ntcx + 1), NCHIPSIZE * (m_bthun / ntcx + 1));
	CRectangle ttr (NCHIPSIZE * (m_btten % ntcx), NCHIPSIZE * (m_btten / ntcx), NCHIPSIZE * (m_btten % ntcx + 1), NCHIPSIZE * (m_btten / ntcx + 1));
	CRectangle tor (NCHIPSIZE * (m_btone % ntcx), NCHIPSIZE * (m_btone / ntcx), NCHIPSIZE * (m_btone % ntcx + 1), NCHIPSIZE * (m_btone / ntcx + 1));
	m_NumberTexture.Render(208, 32, ctr);
	m_NumberTexture.Render(224, 32, cor);
	m_NumberTexture.Render(416, 32, thr);
	m_NumberTexture.Render(432, 32, ttr);
	m_NumberTexture.Render(448, 32, tor);
	//CGraphicsUtilities::RenderRect(m_uPipe.Left - m_ScrollX, m_uPipe.Top - m_ScrollY, m_uPipe.Right - m_ScrollX, m_uPipe.Bottom - m_ScrollY, MOF_XRGB(0, 255, 0));
	//CGraphicsUtilities::RenderRect(m_rPipe.Left - m_ScrollX, m_rPipe.Top - m_ScrollY, m_rPipe.Right - m_ScrollX, m_rPipe.Bottom - m_ScrollY, MOF_XRGB(0, 255, 0));
}

void CStage::RenderDebug(void){
	CGraphicsUtilities::RenderString(10,100,"スクロール X : %.0f , Y : %.0f",m_ScrollX,m_ScrollY);
}

void CStage::Release(void){
	m_ChipTexture.Release();
	m_BackTexture.Release();
	m_InfoTexture.Release();
	m_NumberTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
	if (m_pEnemyData)
	{
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pEnemyTexture)
	{
		delete[] m_pEnemyTexture;
		m_pEnemyTexture = NULL;
	}
	if (m_pItemData)
	{
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pItemTexture)
	{
		delete[] m_pItemTexture;
		m_pItemTexture = NULL;
	}
}

bool CStage::Collision(CRectangle r, float& ox, float& oy)
{
	bool re = false;
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			int temp = y * m_XCount + x;
			if (temp < 0)
			{
				continue;
			}
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0 || cn == FLAG || cn == FLAGTOP || cn == GOALBAR || cn == GOALPOINT || cn == CASTLEWALL || cn == CASTLEGATE || cn == CASTLEDARK || cn == CASTLEFENCE || cn == CASTLEWALLFENCE || cn == CASTLELWINDOW || cn == CASTLERWINDOW)
			{
				continue;
			}
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;
				brec.Expansion(-6, 0);
            if (cr.CollisionRect(brec))
			{
				re = true;
				oy += cr.Top - brec.Bottom;
				r.Top += cr.Top - brec.Bottom;
				r.Bottom += cr.Top - brec.Bottom;
			}
			CRectangle lrec = r;
			CRectangle rrec = r;
				lrec.Right = lrec.Left + 1;
				lrec.Expansion(0, -6);

				rrec.Left = rrec.Right - 1;
				rrec.Expansion(0, -6);
				if (cr.CollisionRect(lrec))
				{
					re = true;
					ox += cr.Right - lrec.Left;
					r.Left += cr.Right - lrec.Left;
					r.Right += cr.Right - lrec.Left;
				}
				else if (cr.CollisionRect(rrec))
				{
					re = true;
					ox += cr.Left - rrec.Right;
					r.Left += cr.Left - rrec.Right;
					r.Right += cr.Left - rrec.Right;
				}
			CRectangle trec = r;
			CRectangle tirec = r;
			trec.Bottom = trec.Top + 1;
				trec.Expansion(-6, 0);
				tirec.Bottom = tirec.Top + 1;
				tirec.Expansion(-6, 0);
			if (cr.CollisionRect(trec))
			{
				re = true;
				oy += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}
			if (cr.CollisionRect(tirec))
			{
				if (cn == ITEMBOX)
				{
					m_pChipData[y * m_XCount + x] = 5;
				}
				else if (m_Player->GetbGiant() && cn != ITEMBOXAFTER)
				{
					m_pChipData[y * m_XCount + x] = 0;
				}
			}
		}
	}
	return re;
}

bool CStage::GetGoal(CPlayer& pl, float& ox)
{
	
	if (pl.GetGoal()) 
	{
		return true;
	}

	CRectangle prec = pl.GetRect();
	ox = prec.Right - (m_bGoalX * m_ChipSize + m_ChipSize * 0.5f);
	if (ox < 0)
	{
		return false;
	}
	m_bGoal = true;
	return true;
}

void CStage::PipeRender(void)
{
	CRectangle pl(m_ChipSize * 0, m_ChipSize * 1, m_ChipSize * 1, m_ChipSize * 3);
	CRectangle pr(m_ChipSize * 1, m_ChipSize * 1, m_ChipSize * 2, m_ChipSize * 3);
	CRectangle pt(m_ChipSize * 0, m_ChipSize * 3, m_ChipSize * 2, m_ChipSize * 4);
	CRectangle pb(m_ChipSize * 0, m_ChipSize * 4, m_ChipSize * 2, m_ChipSize * 5);
	m_ChipTexture.Render(m_ChipSize * 57 - m_ScrollX, m_ChipSize * 8 - m_ScrollY, pl);
	m_ChipTexture.Render(m_ChipSize * 58 - m_ScrollX, m_ChipSize * 8 - m_ScrollY, pr);
	m_ChipTexture.Render(m_ChipSize * 163 - m_ScrollX, m_ChipSize * 10 - m_ScrollY, pl);
	m_ChipTexture.Render(m_ChipSize * 164 - m_ScrollX, m_ChipSize * 10 - m_ScrollY, pr);
	m_ChipTexture.Render(m_ChipSize * 61 - m_ScrollX, m_ChipSize * 25 - m_ScrollY, pt);
	m_ChipTexture.Render(m_ChipSize * 61 - m_ScrollX, m_ChipSize * 26 - m_ScrollY, pb);
}
