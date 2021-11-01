#include "Stage.h"

CStage::CStage() :
	m_BgTexture(),
	m_ChipTexture(),
	//m_ChipSize(0),
	m_XSize(0),
	m_YSize(0),
	m_ChipData(),
	m_StartX(0),
	m_StartY(0),
	m_ScrollX(0),
	m_ScrollY(0),
	m_pEnemyData(),
	m_EnemyTextureCount(0),
	m_pEnemyTexture(NULL),
	m_EnemyCount(0),
	m_EnemyArray(),
	m_pItemData(),
	m_ItemTextureCount(0),
	m_pItemTexture(NULL),
	m_ItemCount(0),
	m_ItemArray(),
	m_BlockArray(),
	m_BlockCount(0)
{
}

CStage::~CStage()
{
}

bool CStage::Load(char* fname, int sx, int sy)
{
	FILE* f = fopen(fname, "rt");
	if (f == NULL) {
		return false;
	}
	fseek(f, 0, SEEK_END);
	long fSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	//メモリ確保
	char* buffer = (char*)malloc(fSize + 1);
	fSize = fread(buffer, 1, fSize, f);
	buffer[fSize] = '\0';
	char* pstr;

	pstr = strtok(buffer, ",");
	if (!m_BgTexture.Load(pstr)) {
		return false;
	}

	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr)) {
		return false;
	}

	float _ChipSize = atof(strtok(NULL, ","));
	m_XSize = atoi(strtok(NULL, ","));
	m_YSize = atoi(strtok(NULL, ","));
	m_ChipData = new int[m_XSize * m_YSize];
	m_BlockCount = 0;

	for (int y = 0; y < m_YSize; y++) {
		for (int x = 0; x < m_XSize; x++) {
			int c = atoi(strtok(NULL, ","));
			m_ChipData[y * m_XSize + x] = c;
			if (c > 0) {
				m_BlockCount++;
			}
		}
	}

	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);
	m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
	for (int i = 0; i < m_EnemyTextureCount; i++) {
		pstr = strtok(NULL, ",");
		if (!m_pEnemyTexture[i].Load(pstr)) {
			return false;
		}
	}

	m_pEnemyData = (char*)malloc(m_XSize * m_YSize);
	m_EnemyCount = 0;
	for (int y = 0; y < m_YSize; y++) {
		for (int x = 0; x < m_XSize; x++) {
			m_pEnemyData[y * m_XSize + x] = atoi(strtok(NULL, ","));
			if (m_pEnemyData[y * m_XSize + x] > 0) {
				m_EnemyCount++;
			}
		}
	}

	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for (int i = 0; i < m_ItemTextureCount; i++) {
		pstr = strtok(NULL, ",");
		if (!m_pItemTexture[i].Load(pstr)) {
			return false;
		}
	}

	m_pItemData = (char*)malloc(m_XSize * m_YSize);
	m_ItemCount = 0;
	for (int y = 0; y < m_YSize; y++) {
		for (int x = 0; x < m_XSize; x++) {
			m_pItemData[y * m_XSize + x] = atoi(strtok(NULL, ","));
			if (m_pItemData[y * m_XSize + x] > 0) {
				m_ItemCount++;
			}
		}
	}

	m_StartX = sx;
	m_StartY = sy;

	fclose(f);
	free(buffer);

	return true;
}

void CStage::Initialize(bool bGoal, int gType, int gx, int gy)
{
	m_ScrollX = 0;
	m_ScrollY = 0;

	if (m_EnemyArray) {
		for (int i = 0; i < m_EnemyCount; i++) {
			m_EnemyArray[i].Release();
		}
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	m_EnemyArray = new CEnemy[m_EnemyCount];
	int n = 0;
	for (int y = 0; y < m_YSize; y++) {
		for (int x = 0; x < m_XSize; x++) {
			char on = m_pEnemyData[y * m_XSize + x] - 1;
			if (on < 0) {
				continue;
			}
			m_EnemyArray[n].Load(m_pEnemyTexture, CGameDefine::GetGameDefine()->GetEnemyByIdx(on + 1));
			m_EnemyArray[n++].Initialize(Vector2(x * CHIPSIZE, y * CHIPSIZE), (bGoal && (gType == 1) && (x == gx) && (y == gy)), GetStageHeight());
		}
	}

	int tcx = m_ChipTexture.GetWidth() / CHIPSIZE;

	if (m_ItemArray) {
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	if (m_BlockArray) {
		delete[] m_BlockArray;
		m_BlockArray = NULL;
	}
	m_ItemArray = new CItem[m_ItemCount];
	m_BlockArray = new CBlock[m_BlockCount];
	n = 0;
	int ci = 0;
	for (int y = 0; y < m_YSize; y++) {
		for (int x = 0; x < m_XSize; x++) {
			char on = m_pItemData[y * m_XSize + x] - 1;
			int cn = m_ChipData[y * m_XSize + x] - 1;
			if (on >= 0) {
				CItemDefine* bd = CGameDefine::GetGameDefine()->GetItemByIdx(on + 1);
				m_ItemArray[n].Load(&m_pItemTexture[on], CRectangle(0, 0, CHIPSIZE, CHIPSIZE));
				m_ItemArray[n++].Initialize(CVector2(x * CHIPSIZE, y * CHIPSIZE), CVector2(0, 0), bd, on, x, y, (cn < 0), GetStageHeight());
			}
			if (cn >= 0) {
				CRectangle cr = CRectangle(cn % tcx, cn / tcx, cn % tcx + 1, cn / tcx + 1) * CHIPSIZE;
				CItem* item = NULL;
				if (on >= 0) {
					item = &m_ItemArray[n - 1];
				}

				CBlockDefine* bd = CGameDefine::GetGameDefine()->GetBlockByIdx(cn + 1);
				m_BlockArray[ci++].Load(&m_ChipTexture, CVector2(x, y) * CHIPSIZE, cr, item, cn, bd->broken, bd);
			}
		}
	}
}

void CStage::Update(CPlayer& pl)
{
	CRectangle prec = pl.GetRect(false);
	float sw = g_pGraphics->GetTargetWidth();
	float hsw = sw * 0.4f;
	float stgw = CHIPSIZE * m_XSize;
	if (sw < stgw) {
		if (m_ScrollX > stgw - sw) {
			m_ScrollX = stgw - sw;
		}

		if (prec.Left - m_ScrollX < hsw) {
			m_ScrollX -= hsw - (prec.Left - m_ScrollX);
			if (m_ScrollX <= 0) {
				m_ScrollX = 0;
			}
		}
		else if (prec.Right - m_ScrollX > sw - hsw) {
			m_ScrollX += (prec.Right - m_ScrollX) - (sw - hsw);
			if (m_ScrollX >= stgw - sw) {
				m_ScrollX = stgw - sw;
			}
		}
	}
	else {
		m_ScrollX = (stgw - sw) / 2;
	}
	float sh = g_pGraphics->GetTargetHeight();
	float hsh = 100;
	float stgh = CHIPSIZE * m_YSize;
	if (sh < stgh) {
		if (m_ScrollY > stgh - sh) {
			m_ScrollY = stgh - sh;
		}
		if (prec.Top - m_ScrollY < hsh) {
			m_ScrollY -= hsh - (prec.Top - m_ScrollY);
			if (m_ScrollY <= 0) {
				m_ScrollY = 0;
			}
		}
		else if (prec.Bottom - m_ScrollY > sh - hsh) {
			m_ScrollY += (prec.Bottom - m_ScrollY) - (sh - hsh);
			if (m_ScrollY >= stgh - sh) {
				m_ScrollY = stgh - sh;
			}
		}
	}
	else {
		m_ScrollY = (stgh - sh) / 2;
	}

	for (int i = 0; i < GetBlockCount(); i++) {
		m_BlockArray[i].Update();
	}

	for (int i = 0; i < 2; i++) {
		if (!pl.GetSkillObj()[i].GetShowNow()) continue;
		pl.GetSkillObj()[i].CollisionStage(Collision(NULL, NULL, pl.GetSkillObj()[i].GetBRect(), pl.GetSkillObj()[i].GetRect(), pl.GetSkillObj()[i].GetMove()));
	}

	for (int i = 0; i < GetEnemyCount(); i++) {
		if (!m_EnemyArray[i].GetShow()) {
			continue;
		}
		CRectangle erec_b = m_EnemyArray[i].GetRect();
		m_EnemyArray[i].Update(GetScrollX(), GetScrollY(), pl.GetRect(true));
		if (!m_EnemyArray[i].GetDisplay()) {
			continue;
		}
		pl.CollisionEnemy(m_EnemyArray[i]);
		CRectangle erec_a = m_EnemyArray[i].GetRect();

		m_EnemyArray[i].CollisionStage(Collision(NULL, &m_EnemyArray[i], erec_b, erec_a, m_EnemyArray[i].GetMove()));
	}


	for (int i = 0; i < GetItemCount(); i++) {
		if (!m_ItemArray[i].GetShow()) {
			continue;
		}
		CRectangle irec_b = m_ItemArray[i].GetRect();
		m_ItemArray[i].Update(GetScrollX(), GetScrollY());
		if (!m_ItemArray[i].GetDisplay()) {
			continue;
		}
		pl.CollisionItem(m_ItemArray[i]);
		CRectangle irec_a = m_ItemArray[i].GetRect();

		m_ItemArray[i].CollisionStage(Collision(NULL, NULL, irec_b, irec_a, m_ItemArray[i].GetMove()));
	}

	for (int i = 0; i < GetEnemyCount(); i++) {
		if (!m_EnemyArray[i].GetDisplay()) continue;

		for (int j = 0; j < GetEnemyCount(); j++) {
			if (i == j || !m_EnemyArray[j].GetDisplay()) {
				continue;
			}
			m_EnemyArray[i].CollisionEnemy(m_EnemyArray[j]);
		}
		for (int k = 0; k < 2; k++) {
			CSkillObj* sObj = &pl.GetSkillObj()[k];
			if (!sObj->GetShowNow()) {
				continue;
			}
			m_EnemyArray[i].CollisionSkill(*sObj);
		}
	}
}

void CStage::Render()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	float s = 1.0f;
	int bw = m_BgTexture.GetWidth();
	int bh = m_BgTexture.GetHeight();
	float stgh = CHIPSIZE * m_YSize;
	if (bh < MOF_MAX(stgh, sch)) {
		s = (float)MOF_MAX(stgh, sch) / bh;
		bw = bw * s;
		bh = bh * s;
	}
	//for (float y = ((int)-m_ScrollY % bh) - bh; y < sch; y += bh) {
	int y = -m_ScrollY;
	if (y > 0) y = 0;
	for (float x = ((int)-m_ScrollX % bw) - bw; x < scw; x += bw) {
		m_BgTexture.RenderScale(x, y, s);
	}
	//}

	/*
	int tcx = m_ChipTexture.GetWidth() / CHIPSIZE;

	for (int y = 0; y < m_YSize; y++) {
		for (int x = 0; x < m_XSize; x++) {
			char cn = m_ChipData[y * m_XSize + x] - 1;
			if (cn < 0) {
				continue;
			}
			CRectangle cr(CHIPSIZE * (cn % tcx), CHIPSIZE * (cn / tcx), CHIPSIZE * (cn % tcx + 1), CHIPSIZE * (cn / tcx + 1));
			m_ChipTexture.Render(-m_ScrollX + x * CHIPSIZE, -m_ScrollY + y * CHIPSIZE, cr);
		}
	}*/

	for (int i = 0; i < GetBlockCount(); i++) {
		m_BlockArray[i].Render(GetScrollX(), GetScrollY());
	}

	for (int i = 0; i < GetEnemyCount(); i++) {
		m_EnemyArray[i].Render(GetScrollX(), GetScrollY());
	}

	for (int i = 0; i < GetItemCount(); i++) {
		m_ItemArray[i].Render(GetScrollX(), GetScrollY());
	}
}

void CStage::RenderDebug_Enemy()
{
	for (int i = 0; i < GetEnemyCount(); i++) {
		CGraphicsUtilities::RenderString(0, 30 * i, "pos x:%.2f pos y:%.2f", m_EnemyArray[i].GetRect().Left, m_EnemyArray[i].GetRect().Top);
	}
}

void CStage::Release()
{
	m_ChipTexture.Release();
	m_BgTexture.Release();
	if (m_ChipData) {
		delete[] m_ChipData;
		m_ChipData = NULL;
	}
	if (m_pEnemyData) {
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pEnemyTexture) {
		for (int i = 0; i < m_EnemyTextureCount; i++) {
			m_pEnemyTexture[i].Release();
		}
		delete[] m_pEnemyTexture;
		m_pEnemyTexture = NULL;
	}
	if (m_EnemyArray) {
		for (int i = 0; i < m_EnemyCount; i++) {
			m_EnemyArray[i].Release();
		}
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	if (m_pItemData) {
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pItemTexture) {
		for (int i = 0; i < m_ItemTextureCount; i++) {
			m_pItemTexture[i].Release();
		}
		delete[] m_pItemTexture;
		m_pItemTexture = NULL;
	}
	if (m_ItemArray) {
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	if (m_BlockArray) {
		delete[] m_BlockArray;
		m_BlockArray = NULL;
	}
}

CCollisionData CStage::Collision(CPlayer* pl, CEnemy* ene, CRectangle rb, CRectangle ra, CVector2 move)
{
	CCollisionData coll = CCollisionData();

	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	for (int i = 0; i < m_BlockCount; i++) {
		if (m_BlockArray[i].GetType() < 0) continue;
		CRectangle cr = m_BlockArray[i].GetRect();
		if (cr.Right - m_ScrollX < -CHIPSIZE || cr.Left - m_ScrollX > sw + CHIPSIZE ||
			cr.Bottom - m_ScrollY < -CHIPSIZE || cr.Top - m_ScrollY > sh + CHIPSIZE) continue;

		if (move.y >= 0) {
			CRectangle b_trec = cr;
			//接地判定
			CRectangle brec = CRectangle(MOF_MIN(rb.Left, ra.Left), MOF_MIN(rb.Bottom, ra.Bottom), MOF_MAX(rb.Right, ra.Right), MOF_MAX(rb.Bottom, ra.Bottom));
			//brec.Bottom += 1;
			brec.Expansion(-6, 0);

			if (!m_BlockArray[i].CheckDirection(BlockAll) || (cr.Right <= rb.Left && cr.Right >= ra.Left) || (cr.Left >= rb.Right && cr.Left <= ra.Right)) {
				b_trec.Bottom = b_trec.Top + 6;
			}

			if (b_trec.CollisionRect(brec)) {
				if (m_BlockArray[i].CheckDirection(BlockDown) && !m_BlockArray[i].CheckDamageDirection(BlockDown)) {
					coll.og = true;

					if (pl != NULL) {
						pl->SlideMove(m_BlockArray[i].GetMove());
					}

					if (ene != NULL) {
						if (m_BlockArray[i].IsAttacked()) { //ブロックが壊された状態
							ene->PushedUp();
						}
						ene->SlideMove(m_BlockArray[i].GetMove());
					}
				}
			}

			//下方向判定
			brec -= CVector2(0, 1);

			if (b_trec.CollisionRect(brec)) {
				brec += CVector2(0, 1);
				/*if (0 < coll.oy) {
					coll.crush = true;
					break;
				}*/
				if (m_BlockArray[i].CheckDirection(BlockDown)) {
					coll.oy += b_trec.Top - brec.Bottom;
					ra.Top += b_trec.Top - brec.Bottom;
					ra.Bottom += b_trec.Top - brec.Bottom;

					if (rb.Top > ra.Top) {
						rb.Top = ra.Top;
						rb.Bottom = ra.Bottom;
					}
				}

				if (pl != NULL) {
					if (m_BlockArray[i].CheckDamageFlg(DAMAGE_ONLY_PLAYER) && m_BlockArray[i].CheckDamageDirection(BlockDown)) {
						coll.damage = true;
					}
				}
			}
		}
		if (m_BlockArray[i].GetType() < 0) {
			continue;
		}

		if (move.y <= 0) {

			CRectangle b_brec = cr;
			//上方向判定
			CRectangle trec = CRectangle(MOF_MIN(rb.Left, ra.Left), MOF_MIN(rb.Top, ra.Top), MOF_MAX(rb.Right, ra.Right), MOF_MAX(rb.Top, ra.Top));
			trec.Expansion(-6, 0);
			trec += CVector2(0, 1);

			if (!m_BlockArray[i].CheckDirection(BlockAll) || (cr.Right <= rb.Left && cr.Right >= ra.Left) || (cr.Left >= rb.Right && cr.Left <= ra.Right)) {
				b_brec.Top = b_brec.Bottom - 6;
			}

			if (b_brec.CollisionRect(trec)) {
				trec -= CVector2(0, 1);
				/*if (0 > coll.oy) {
					coll.crush = true;
					break;
				}*/
				if (m_BlockArray[i].CheckDirection(BlockUp)) {
					coll.oy += b_brec.Bottom - trec.Top;
					ra.Top += b_brec.Bottom - trec.Top;
					ra.Bottom += b_brec.Bottom - trec.Top;

					if (rb.Top < ra.Top) {
						rb.Top = ra.Top;
						rb.Bottom = ra.Bottom;
					}
				}

				if (pl != NULL) {
					m_BlockArray[i].AttackBlock(pl, m_pItemTexture);
					if (m_BlockArray[i].CheckDamageFlg(DAMAGE_ONLY_PLAYER) && m_BlockArray[i].CheckDamageDirection(BlockUp)) {
						coll.damage = true;
					}
				}
			}
		}

		if (move.x >= 0) {

			CRectangle b_lrec = cr;
			//右方向判定
			CRectangle rrec = CRectangle(MOF_MIN(rb.Right, ra.Right), MOF_MIN(rb.Top, ra.Top), MOF_MAX(rb.Right, ra.Right), MOF_MAX(rb.Bottom, ra.Bottom));
			rrec.Expansion(0, -6);
			rrec -= CVector2(1, 0);

			if (!m_BlockArray[i].CheckDirection(BlockAll)) {
				b_lrec.Right = b_lrec.Left + 6;
			}

			if (b_lrec.CollisionRect(rrec)) {
				rrec += CVector2(1, 0);
				/*if (0 < coll.ox) {
					coll.crush = true;
					break;
				}*/
				if (m_BlockArray[i].CheckDirection(BlockRight)) {
					coll.ox += b_lrec.Left - rrec.Right;
					ra.Left += b_lrec.Left - rrec.Right;
					ra.Right += b_lrec.Left - rrec.Right;

					if (rb.Left > ra.Left) {
						rb.Left = ra.Left;
						rb.Right = ra.Right;
					}
				}

				if (pl != NULL) {
					if (m_BlockArray[i].CheckDamageFlg(DAMAGE_ONLY_PLAYER) && m_BlockArray[i].CheckDamageDirection(BlockRight)) {
						coll.damage = true;
					}
				}
			}
		}

		if (move.x <= 0) {

			CRectangle b_rrec = cr;
			//左方向判定
			CRectangle lrec = CRectangle(MOF_MIN(rb.Left, ra.Left), MOF_MIN(rb.Top, ra.Top), MOF_MAX(rb.Left, ra.Left), MOF_MAX(rb.Bottom, ra.Bottom));
			lrec.Expansion(0, -6);
			lrec -= CVector2(1, 0);

			if (!m_BlockArray[i].CheckDirection(BlockAll)) {
				b_rrec.Left = b_rrec.Right - 6;
			}

			if (b_rrec.CollisionRect(lrec)) {
				lrec += CVector2(1, 0);
				/*if (0 > coll.ox) {
					coll.crush = true;
					break;
				}*/
				if (m_BlockArray[i].CheckDirection(BlockLeft)) {
					coll.ox += b_rrec.Right - lrec.Left;
					ra.Left += b_rrec.Right - lrec.Left;
					ra.Right += b_rrec.Right - lrec.Left;

					if (rb.Left < ra.Left) {
						rb.Left = ra.Left;
						rb.Right = ra.Right;
					}
				}

				if (pl != NULL) {
					if (m_BlockArray[i].CheckDamageFlg(DAMAGE_ONLY_PLAYER) && m_BlockArray[i].CheckDamageDirection(BlockLeft)) {
						coll.damage = true;
					}
				}
			}
		}
	}

	return coll;
}
