#include "Stage.h"



CStage::CStage():
m_ChipTexture(),
m_BackTexture(),
m_ChipSize(0),
m_XCount(0),
m_YCount(0),
m_pChipData(NULL),
m_ScrollX(0),
m_ScrollY(0),
m_EnemyTextureCount(0),
m_pEnemyTexture(NULL),
m_EnemyCount(0),
m_ItemTextureCount(0),
m_pItemTexture(NULL),
m_ItemCount(0){
}

CStage::~CStage(){
}

bool CStage::Load(char* pName){
	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y���������������m�ۂ���
	char* pBuffer = (char*)malloc(fSize + 1);
	//�t�@�C����S�ăo�b�t�@�ɓǂݍ���
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '/0';
	char* pstr;

	//�e�N�X�`���̓ǂݍ���
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

	//�`�b�v�T�C�Y
	m_ChipSize = atof(strtok(NULL, ","));

	//�}�b�v�̃`�b�v��
	m_XCount = atoi(strtok(NULL, ","));
	m_YCount = atoi(strtok(NULL, ","));

	//�}�b�v�`�b�v�p�̃������m��
	m_pChipData = (char*)malloc(m_XCount * m_YCount);

	//�}�b�v�f�[�^�̓ǂݍ���
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pChipData[y * m_XCount + x] = atoi(strtok(NULL, ","));
		}
	}

	//�G�̃e�N�X�`���ǂݍ���
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
	//�z�u�f�[�^�̓ǂݍ���
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
	//�A�C�e���̃e�N�X�`���̓ǂݍ���
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
	//�z�u�f�[�^�̓ǂݍ���
	m_pItemData = (char*)malloc(m_XCount * m_YCount);
	m_ItemCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pItemData[y * m_XCount + x] = atoi(strtok(NULL, ","));
			if (m_pItemData[y * m_XCount + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}
	//���̓ǂݍ���
	if (m_bleakblockSound.Load("se_gareki01.mp3"))
	{
		return false;
	}
	//�t�@�C�������
	fclose(fp);
	free(pBuffer);
	return true;
}

void CStage::Initialize(char* pName, CEnemy* pEnemy, CItem* pItem) {
	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen(pName, "rt");
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y���������������m�ۂ���
	char* pBuffer = (char*)malloc(fSize + 1);
	//�t�@�C����S�ăo�b�t�@�ɓǂݍ���
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '/0';
	char* pstr;

	//�e�N�X�`���̓ǂݍ���
	pstr = strtok(pBuffer, ",");
	m_BackTexture.Load(pstr);

	pstr = strtok(NULL, ",");
	m_ChipTexture.Load(pstr);

	//�`�b�v�T�C�Y
	m_ChipSize = atof(strtok(NULL, ","));

	//�}�b�v�̃`�b�v��
	m_XCount = atoi(strtok(NULL, ","));
	m_YCount = atoi(strtok(NULL, ","));

	//�}�b�v�`�b�v�p�̃������m��
	m_pChipData = (char*)malloc(m_XCount * m_YCount);

	//�}�b�v�f�[�^�̓ǂݍ���
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pChipData[y * m_XCount + x] = atoi(strtok(NULL, ","));
		}
	}

	//�G�̃e�N�X�`���ǂݍ���
	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);
	for (int i = 0; i < m_EnemyTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		m_pEnemyTexture[i].Load(pstr);
	}
	
	//�z�u�f�[�^�̓ǂݍ���
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

	//�A�C�e���̃e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	for (int i = 0; i < m_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		m_pItemTexture[i].Load(pstr);
	}
	//�z�u�f�[�^�̓ǂݍ���
	m_pItemData = (char*)malloc(m_XCount * m_YCount);
	m_ItemCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pItemData[y * m_XCount + x] = atoi(strtok(NULL, ","));
			if (m_pItemData[y * m_XCount + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}
	//�t�@�C�������
	fclose(fp);
	free(pBuffer);

	m_ScrollX = 0;
	m_ScrollY = 0;
	int n = 0;
	//�G
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ�0�͔z�u���Ȃ�
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on]);
			pEnemy[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
	//�A�C�e��
	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ�0�͔z�u���Ȃ�
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
	//�v���C���[�̋�`�擾
	CRectangle prec = pl.GetRect();
	//�X�N���[���̕�
	float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	//�X�e�[�W�S�̂̕�
	float stgw = m_ChipSize * m_XCount;
	//���W����ʒ[�ɂ���Ă���i�E�[����500pixel,���[����400pixel)�ꍇ�X�N���[�����s���ĕ␳����
	if (prec.Right - m_ScrollX > sw - 500)
	{
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - 500);
		if (m_ScrollX >= stgw - sw)
		{
			m_ScrollX = stgw - sw;
		}
	}
	else if (prec.Left - m_ScrollX < 400)
	{
		m_ScrollX -= 400 - (prec.Left - m_ScrollX);
		if (m_ScrollX <= 0)
		{
			m_ScrollX = 0;
		}
	}
	
}

void CStage::Render(void){
	//���i�̕`��
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

	//�e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	// �}�b�v�`�b�v�̕`��
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ�0�͕`�悵�Ȃ�
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize * (cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//�}�b�v�`�b�v�̕`��
			m_ChipTexture.Render(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize, cr);
		}
	}
}
void CStage::RenderDebug(void){
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10, 100, "�X�N���[�� X : %.0f , Y : %.0f", m_ScrollX, m_ScrollY);
}

void CStage::Release(void){
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
	//�G
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
	//�A�C�e��
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
	m_bleakblockSound.Release();
}

bool CStage::Collision(CRectangle r, CPlayer& pl, float& ox, float& oy,int& popItemNo){
	bool re = false;
	
	//�����蔻��������`�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;
	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	//�����蔻��������`�̍��ォ��E���͈̔͂̂ݓ����蔻����s��
	//����ȊO�̔ԍ��͓����邱�Ƃ��Ȃ��̂Ŕ��肪�K�v�Ȃ�
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ�0�͓����蔻�肵�Ȃ�
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			if (cn == FLAG1)
			{
				continue;
			}
			if (cn == WALL1 || cn == WALL2 || cn == WALL3 || cn == WALL4)
			{
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//�����蔻��p�̃L�����N�^�̋�`
			//��Ŕ͈͂����肵����p�̋�`���쐬
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;		//��̋�`�͉�������Ɠ����l��
			trec.Expansion(-6, 0);			//���͈̔͂��������߂�
			//��Ƃ̓����蔻��
			if (cr.CollisionRect(trec))
			{
				if (cn == GOALPOOL)
				{
					continue;
				}
				if (cn == KINOKOBLOCK)
				{
					m_pChipData[y * m_XCount + x] = 23 + 1;
					popItemNo = 1;
				}
				if (cn == HIDENBLOCK)
				{
					m_pChipData[y * m_XCount + x] = 23 + 1;
					popItemNo = 2;
				}
				if (cn == COINBLOCK)
				{
					pl.BlockCoinGet();
					m_pPoPItemManager->Start(cr.Left, cr.Top - m_ChipSize, POP_COIN);
					m_pChipData[y * m_XCount + x] = 23 + 1;
				}
				if (cn == BLOCK && pl.GetStat() >= 1)
				{
					pl.BreakBlock();
					m_pChipData[y * m_XCount + x] = 0;
					m_bleakblockSound.Play();
				}
				if (cn == CCOINBLOCK)
				{
					if (m_CoinCount < 9)
					{
						m_CoinCount = m_CoinCount + 1;
						pl.BlockCoinGet();
						m_pPoPItemManager->Start(cr.Left, cr.Top - m_ChipSize, POP_COIN);
					}
					else if (m_CoinCount >= 9)
					{
						pl.BlockCoinGet();
						m_pPoPItemManager->Start(cr.Left, cr.Top - m_ChipSize, POP_COIN);
						m_pChipData[y * m_XCount + x] = 23 + 1;
						m_CoinCount = 0;
					}
				}
				re = true;
				//��Ƃ̖��܂�Ȃ̂Ń`�b�v���[�����`�̏�[�̒l���������l�����܂�̒l
				oy += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}
			//�����蔻��p�̃L�����N�^��`
			//���Ŕ͈͂����肵����p�̋�`���쐬
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;		//���̋�`�͏㑤�����Ɠ����l
			brec.Expansion(-6, 0);			//���͈̔͂��������߂�
			//���Ƃ̓����蔻��
			if (cr.CollisionRect(brec))
			{
				if (cn == GOALPOOL)
				{
					continue;
				}
				if (cn == HIDENBLOCK)
				{
					continue;
				}
				re = true;
				//���̖��܂�Ȃ̂Ń`�b�v��[�����`�̉��[�̒l���������l�����܂�̒l
				oy += cr.Top - brec.Bottom;
				r.Top += cr.Top - brec.Bottom;
				r.Bottom += cr.Top - brec.Bottom;
			}
			//�����蔻��p�̃L�����N�^��`
			//���A�E���ꂼ��Ŕ͈͂����肵����p�̋�`���쐬
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;		//���̋�`�͉E�������Ɠ����l��
			lrec.Expansion(0, -6);			//�c�͈̔͂��������߂�
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;		//�E�̋�`�͍������E�Ɠ����l��
			rrec.Expansion(0, -6);			//****
			//���Ɠ����蔻��
			if (cr.CollisionRect(lrec))
			{
				if (cn == HIDENBLOCK)
				{
					continue;
				}
				re = true;
				//���̖��܂�Ȃ̂Ń`�b�v�E�������`�̍��[�̒l���������l�����܂�̒l
				ox += cr.Right - lrec.Left;
				r.Left += cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//�E�Ɠ����蔻��
			else if (cr.CollisionRect(rrec))
			{
				if (cn == HIDENBLOCK)
				{
					continue;
				}
				if (cn == GOALPOOL || cn == FLAG2 || cn == FLAG3)
				{
					pl.IsGoal();
				}
				else if (cn == CASLE)
				{
					pl.Clear();
				}
				else
				{
					re = true;
					//�E�̖��܂�Ȃ̂Ń`�b�v���������`�̉E�[�̒l���������l�����܂�̒l
					ox += cr.Left - rrec.Right;
					r.Left += cr.Left - rrec.Right;
					r.Right += cr.Left - rrec.Right;
				}
			}
		}
	}
	return re;
}

bool CStage::CollisionPlayerFire(CRectangle r){
	bool re = false;

	//�����蔻�肷���`�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;
	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0)
	{
		lc = 0;
	}
	if (tc < 0)
	{
		tc = 0;
	}
	if (rc >= m_XCount)
	{
		rc = m_XCount - 1;
	}
	if (bc >= m_YCount)
	{
		bc = m_YCount - 1;
	}
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ��O�͓����蔻�肵�Ȃ�
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//���Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;	//���̋�`�͏㑤�����Ɠ����l�ɂ���
			brec.Expansion(-1, 0);		//���͈̔͂��������߂�
			//���Ɠ����蔻��
			if (cr.CollisionRect(brec))
			{
				re = true;
			}
			//�����蔻��p�̃L�����N�^��`
			//���A�E���ꂼ��Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;	//���̋�`�͉E�������Ɠ����l�ɂ���
			lrec.Expansion(0, -1);		//�c�͈̔͂��������߂�
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;	//�E�̋�`�͍������E�Ɠ����l�ɂ���
			rrec.Expansion(0, -1);		//�c�͈̔͂��������߂�
			//���Ɠ����蔻��
			if (cr.CollisionRect(lrec))
			{
				re = true;
			}
			//�E�Ɠ����蔻��
			else if (cr.CollisionRect(rrec))
			{
				re = true;
			}
			//�����蔻��p�̃L�����N�^��`
			//��Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;	//��̋�`�͉�������Ɠ����l�ɂ���
			trec.Expansion(-1, 0);		//���͈̔͂��������߂�
			//��Ɠ����蔻��
			if (cr.CollisionRect(trec))
			{
				re = true;
			}
		}
	}
	return re;
}
