#include "Stage.h"

CStage::CStage():

m_ScrollX(0),
m_ScrollY(0),
m_EnemyCount(0),
m_ItemTextureCount(0),
m_pItemTexture(NULL),
m_ItemCount(0)
{}

CStage::~CStage()
{
}

bool CStage::Load(char* pName)
{
	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	if (fp==NULL)
	{
		return false;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
		//ファイルを全てバッファに読み込む
	fSize =fread(pBuffer,1,fSize,fp);
	pBuffer[fSize]='\0';
	char* pstr;

	//テクスチャの読み込み
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr))
	{
		return false;
	}

	pstr = strtok(NULL,",");
	if (!m_ChipTexture.Load(pstr))
	{
		return false;
	}
	//チップサイズ
	m_ChipSize = atof(strtok(NULL, ","));

	//マップのチップ数
	m_XCount = atoi(strtok(NULL, ","));
	m_YCount = atoi(strtok(NULL, ","));

	//マップチップ用のメモリ確保
	m_pChipData = (char*)malloc(m_XCount * m_YCount);

	//マップチップデータの読み込み
	for  (int y = 0;y<m_YCount;y++)
	{
		for (int x = 0;x< m_XCount;x++)
		{
			m_pChipData[y*m_XCount + x] = atoi(strtok(NULL,","));
		}
	}

 	//敵のテクスチャ読み込み
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

	//配置データの読み込み
	m_pEnemyData = (char*)malloc(m_XCount * m_YCount);
	m_EnemyCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			m_pEnemyData[y * m_XCount + x] = atoi(pstr);
			if (m_pEnemyData[y * m_XCount + x] > 0)
			{
				m_EnemyCount++;
			}
		}
	}

	//アイテムのテクスチャ読み込み
	pstr = strtok(NULL,",");
	m_ItemTextureCount = atoi(pstr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for(int i = 0;i < m_ItemTextureCount;i++)
	{
		pstr = strtok(NULL,",");
		if(!m_pItemTexture[i].Load(pstr))
		{
			return false;
		}
	}
	
	//配置データの読み込み
	m_pItemData = (char*)malloc(m_XCount * m_YCount);
	m_ItemCount = 0;
	for(int y = 0;y < m_YCount;y++)
	{
		for(int x = 0;x < m_XCount;x++)
		{
			pstr = strtok(NULL,",");
			m_pItemData[y * m_XCount + x] = atoi(pstr);
			if(m_pItemData[y * m_XCount + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}


	//ファイルを閉じる
	fclose(fp);
	free(pBuffer);
	return true;
}

void CStage::Initialize(CEnemy* pEnemy, CItem* pItem)
{
	m_ScrollX = 0;
	m_ScrollY = 0;
	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号０は配置しない
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
			//配置番号
			//番号０は配置しない
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

void CStage::Update(CPlayer& pl)
{

	CRectangle prec = pl.GetRect();

		float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();

		float stgw = m_ChipSize * m_XCount;

	if (prec.Left - m_ScrollX < 200)
	{
		m_ScrollX -=200 - (prec.Left - m_ScrollX);
			if (m_ScrollX<=0)
			{
				m_ScrollX = 0;
			}		
	}
	else if (prec.Right-m_ScrollX>sw-300)
	{
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - 300);
		if (m_ScrollX>=stgw-sw)
		{
			m_ScrollX = stgw - sw;
		}
	}
}

bool CStage::Collision(CRectangle r, float& ox, float& oy)
{	
		bool re = false;

		//当たり判定する矩形の左上と右下のチップ位置を求める
		int lc = r.Left / m_ChipSize;
		int rc = r.Right / m_ChipSize;
		int tc = r.Top / m_ChipSize;
		int bc = r.Bottom / m_ChipSize;
		//ステージの範囲外にならないようにする
		if (lc < 0) lc = 0;
		if (tc < 0) tc = 0;
		if (rc >= m_XCount) rc = m_XCount - 1;
		if (bc >= m_YCount) bc = m_YCount - 1; 
		
		for (int y = tc; y <= bc; y++)
		{
			for (int x = lc; x <= rc; x++)
			{
				//描画するチップ番号
				char cn = m_pChipData[y * m_XCount + x] - 1;
				if (cn < 0)
				{
					continue;
				}
			
				CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);

				CRectangle grec = r;
				grec.Top = grec.Bottom - 1;	//下の矩形は上側を下と同じ値にする
				grec.Expansion(-6, 0);		//横の範囲を少し狭める

				if (cr.CollisionRect(grec))
				{
					re = true;
				}

				CRectangle brec = r;
				brec.Top = brec.Bottom - 1;
				brec.Expansion(-6, 0);

				//下との当たり判定
				if (cr.CollisionRect(brec)) {
					re = true;

					oy += cr.Top - brec.Bottom;
					r.Top += cr.Top - brec.Bottom;
					r.Bottom += cr.Top - brec.Bottom;
				}
		
				CRectangle trec = r;
				trec.Bottom = trec.Top + 1;
				trec.Expansion(-6, 0);


				//上との当たり判定
				if (cr.CollisionRect(trec)) {
					re = true;

					//
					oy += cr.Bottom - trec.Top;
					r.Top += cr.Bottom - trec.Top;
					r.Bottom += cr.Bottom - trec.Top;
				}

				CRectangle lrec = r;
				lrec.Right = lrec.Left + 1;
				lrec.Expansion(0, -6);
				CRectangle rrec = r;
				rrec.Left = rrec.Right - 1;
				rrec.Expansion(0, -6);


				//左との当たり判定
				if (cr.CollisionRect(lrec))
				{
					re = true;

					ox += cr.Right - lrec.Left;
					r.Left += cr.Right - lrec.Left;
					r.Right += cr.Right - lrec.Left;
				}
				

				//右との当たり判定
				else if (cr.CollisionRect(rrec))
				{
					re = true;
					
					ox += cr.Left - rrec.Right;
					r.Left += cr.Left - rrec.Right;
					r.Right += cr.Left - rrec.Right;
				}
			}
			

		}

	return re;
}


void CStage::Render(void)
{
	//遠景の描画
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

	//テクスチャの横幅からからマップチップの縦オフセットを求める
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	//マップチップの描画
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//描画するチップ番号
			//チップ番号0は描画しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0) 
			{
				continue;
			}
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize * (cn / tcx),
				m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//マップチップの描画
			m_ChipTexture.Render(-m_ScrollX + x * m_ChipSize,
				-m_ScrollY + y * m_ChipSize, cr);

		}

	}

}

void CStage::RenderDebug(void) {
	//位置の描画
	CGraphicsUtilities::RenderString(10, 100, "スクロール X : %.0f , Y : %.0f", m_ScrollX, m_ScrollY);
}


void CStage::Release(void)
{
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData);
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

