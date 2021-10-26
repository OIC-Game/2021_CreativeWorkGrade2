#include "Stage.h"
#include "GlobalDefine.h"


CStage::CStage() :
	stage_ChipTexture(),
	stage_BackTexture(),
	stage_ChipSize(0),
	stage_XCount(0),
	stage_YCount(0),
	stage_pChipData(NULL),
	stage_Scroll(0.0f, 0.0f),
	stage_EnemyTextureCount(0),
	stage_pEnemyTexture(NULL),
	stage_EnemyCount(0),
	stage_ItemTextureCount(0),
	stage_pItemTexture(NULL),
	stage_ItemCount(0),
	stage_ChipMove(0.0f),
	stage_chipUp(false),
	stage_break(false),
	stage_tmpChipX(0),
	stage_tmpChipY(0),
	stage_BlockAttackSE(),
	stage_NowStage(0),
	stage_BlockDestroy(false),
	stage_BlockDestroyWait(0),
	stage_BlockDestroySE(),
	stage_BlockChange(false),
	stage_FixScroll(false)
{
}

CStage::~CStage()
{
}

bool CStage::Load(char* pName)
{

	FILE* fp = fopen(pName, "rt");
	if (fp == NULL) {
		return false;
	}
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	//�t�@�C���T�C�Y���������������m�ۂ���
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y�������������m��
	char* buffer = (char*)malloc(fSize + 1);
	//�t�@�C�������ׂăo�b�t�@�ɓǂݍ���
	fSize = fread(buffer, 1, fSize, fp);
	buffer[fSize] = '\0';
	char* pstr;

	//�e�N�X�`���̓ǂݍ���
	pstr = strtok(buffer, ",");
	if (!stage_BackTexture.Load(pstr)) {
		return false;
	}
	pstr = strtok(NULL, ",");
	if (!stage_ChipTexture.Load(pstr)) {
		return false;
	}

	//�`�b�v�T�C�Y
	stage_ChipSize = atof(strtok(NULL, ","));
	//�}�b�v�̃`�b�v��
	stage_XCount = atoi(strtok(NULL, ","));
	stage_YCount = atoi(strtok(NULL, ","));

	//�}�b�v�`�b�v�p�̃������m��
	stage_pChipData = (char*)malloc(stage_XCount * stage_YCount);
	stage_gap = new float[stage_XCount * stage_YCount];
	stage_gapMove = new float[stage_XCount * stage_YCount];

	//�`�b�v�f�[�^�̓ǂݍ���
	for (int y = 0; y < stage_YCount; y++) {
		for (int x = 0; x < stage_XCount; x++) {
			stage_pChipData[y * stage_XCount + x] = atoi(strtok(NULL, ","));
		}
	}


	//�G�̃e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	stage_EnemyTextureCount = atoi(pstr);
	stage_pEnemyTexture = new CTexture[stage_EnemyTextureCount];
	for (int i = 0; i < stage_EnemyTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!stage_pEnemyTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//�G�z�u�f�[�^�̓ǂݍ���
	stage_pEnemyData = (char*)malloc(stage_XCount * stage_YCount);
	stage_EnemyCount = 0;
	for (int y = 0; y < stage_YCount; y++)
	{
		for (int x = 0; x < stage_XCount; x++)
		{
			stage_pEnemyData[y * stage_XCount + x] = atoi(strtok(NULL, ","));
			if (stage_pEnemyData[y * stage_XCount + x] > 0)
			{
				stage_EnemyCount++;
			}
		}
	}

	//�A�C�e���̃e�N�X�`���ǂݍ���
	pstr = strtok(NULL, ",");
	stage_ItemTextureCount = atoi(pstr);
	stage_pItemTexture = new CTexture[stage_ItemTextureCount];
	for (int i = 0; i < stage_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!stage_pItemTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//�A�C�e���z�u�f�[�^�̓ǂݍ���
	stage_pItemData = (char*)malloc(stage_XCount * stage_YCount);
	stage_ItemCount = 0;
	for (int y = 0; y < stage_YCount; y++)
	{
		for (int x = 0; x < stage_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			stage_pItemData[y * stage_XCount + x] = atoi(pstr);
			if (stage_pItemData[y * stage_XCount + x] > 0)
			{
				stage_ItemCount++;
			}
		}
	}



	//�t�@�C�������
	fclose(fp);
	free(buffer);



	//SE���[�h
	if (!stage_BlockAttackSE.Load("BlockAttack.mp3"))
	{
		return false;
	}
	if (!stage_BlockDestroySE.Load("BlockDestroy.mp3"))
	{
		return false;
	}
	//�G�e�e�N�X�`�����[�h
	if (!stage_EnemyShotTexture.Load("EnemyShot_Skeleton.png"))
	{
		return false;
	}
	if (!stage_EnemyFireTexture.Load("Mario_Fire.png"))
	{
		return false;
	}

	return true;

}

void CStage::Initialize(CEnemy* pEnemy, CItem* pItem)
{
	stage_Scroll = Vector2(0, 0);
	stage_ChipMove = 0.0f;
	stage_chipUp = false;
	stage_break = false;
	stage_tmpChipX = 0;
	stage_tmpChipY = 0;
	int n = 0;
	stage_BlockDestroy = false;
	stage_BlockDestroyWait = 0;
	stage_BlockChange = false;
	stage_FixScroll = false;

	//�G������
	for (int y = 0; y < stage_YCount; y++)
	{

		for (int x = 0; x < stage_XCount; x++)
		{
			//�z�u�ԍ�
			//0�͔z�u���Ȃ�
			char on = stage_pEnemyData[y * stage_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			if (on == ENEMY_MARIO)
			{
				pEnemy[n].SetTexture(&stage_pEnemyTexture[on], &stage_EnemyFireTexture);
			}
			else
			{
				pEnemy[n].SetTexture(&stage_pEnemyTexture[on],  & stage_EnemyShotTexture);
			}
			pEnemy[n++].Initialize(x * stage_ChipSize, y * stage_ChipSize, on);
		}
	}
	n = 0;
	//�A�C�e��������
	for (int y = 0; y < stage_YCount; y++)
	{
		for (int x = 0; x < stage_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ��O�͔z�u���Ȃ�
			char on = stage_pItemData[y * stage_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pItem[n].SetTexture(&stage_pItemTexture[on]);
			pItem[n++].Initialize(x * stage_ChipSize, y * stage_ChipSize, on);
		}
	}

	//�u���b�N�ړ��̈ʒu�Ƒ��x��������
	for (int y = 0; y < stage_YCount; y++) {
		for (int x = 0; x < stage_XCount; x++) {
			stage_gap[y * stage_XCount + x] = 0;
			stage_gapMove[y * stage_XCount + x] = 0;
		}
	}
}

void CStage::Update(CPlayer& pl)
{

	//�v���C���[�̋�`�擾
	CRectangle prect = pl.GetRectPlayer();
	//�X�N���[���̕�
	float sw = g_pGraphics->GetTargetWidth();
	//�X�e�[�W�S�̂̕�
	float stgw = stage_ChipSize * stage_XCount;

	//���W����ʒ[�ɂ���Ă���(�p�[����200pixel)�ꍇ�X�N���[�����s���ĕ␳����B
	if (pl.Getplayer_PositionX() < 5270 && !pl.GetWarpFlg())
	{
		if (prect.Left - stage_Scroll.x < 400) {
			stage_Scroll.x -= 400 - (prect.Left - stage_Scroll.x);
			if (stage_Scroll.x <= 0) {
				stage_Scroll.x = 0;
			}
		}
		else if (prect.Right - stage_Scroll.x > sw - 400) {
			stage_Scroll.x += (prect.Right - stage_Scroll.x) - (sw - 400);
			if (stage_Scroll.x >= stgw - sw) {
				stage_Scroll.x = stgw - sw;
			}
		}
	}
	else if (pl.GetWarpFlg() && !stage_FixScroll)
	{

		stage_Scroll.x = 6175;//(prect.Right - stage_Scroll.x) - (sw - 400);

			stage_FixScroll = true;
	}

	if (pl.GetMarioDead())
	{
		if (prect.Left - stage_Scroll.x < 400) {
			stage_Scroll.x -= 400 - (prect.Left - stage_Scroll.x);
			if (stage_Scroll.x <= 0) {
				stage_Scroll.x = 0;
			}
		}
		else if (prect.Right - stage_Scroll.x > sw - 400) {
			stage_Scroll.x += (prect.Right - stage_Scroll.x) - (sw - 400);
			if (stage_Scroll.x >= stgw - sw) {
				stage_Scroll.x = stgw - sw;
			}
		}
	}
	


	//�u���b�N��������
	for (int y = 0; y < stage_YCount; y++) {
		for (int x = 0; x < stage_XCount; x++) {
			stage_gap[y * stage_XCount + x] = stage_gapMove[y * stage_XCount + x];

			if (stage_gapMove[y * stage_XCount + x] > 0)
			{
				stage_gapMove[y * stage_XCount + x] -= 0.5;
			}
		}
	}
	if (stage_chipUp && pl.Getplayer_DeadFlg() == false)
	{
		stage_gapMove[stage_tmpChipY * stage_XCount + stage_tmpChipX] = 5;
		stage_BlockAttackSE.Stop();
		stage_BlockAttackSE.Play();
		stage_chipUp = false;
	}

	//�u���b�N�j�󏈗�
	if (stage_BlockDestroy && pl.Getplayer_BigFlg() && pl.Getplayer_DeadFlg() == false)
	{
		if (stage_BlockDestroyWait > 4)
		{
			stage_BlockDestroySE.Play();
		}
		stage_BlockDestroyWait--;
		if (stage_BlockDestroyWait <= 0)
		{
			if (stage_pChipData[stage_tmpChipY * stage_XCount + stage_tmpChipX] == CHIP_BLOCK)
			{
				//��\��
				stage_pChipData[stage_tmpChipY * stage_XCount + stage_tmpChipX] = 0;
				stage_BlockDestroy = false;
			}

		}
	}
	//�u���b�N�ω�����
	if (stage_BlockChange && pl.Getplayer_DeadFlg() == false)
	{
			if (stage_pChipData[stage_tmpChipY * stage_XCount + stage_tmpChipX] == CHIP_QUESTION)
			{

				stage_pChipData[stage_tmpChipY * stage_XCount + stage_tmpChipX] = CHIP_HARDBLOCK;
				stage_BlockChange = false;
			}
	}

	if (pl.GetMarioDead())
	{

		int x = 223;
		for (int y = 12; y < 16; y++)
		{
			stage_pChipData[y * stage_XCount + x] = 0;
		}
	}


}

void CStage::Render(void)
{

	//���i�̕`��
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	float bScale = sch / (float)stage_BackTexture.GetHeight();
	int bw = (int)(stage_BackTexture.GetWidth() * bScale);
	int bh = (int)(stage_BackTexture.GetHeight() * bScale);
	for (float y = ((int)-stage_Scroll.y % bh) - bh; y < sch; y += bh) {
		for (float x = ((int)-stage_Scroll.x / 4 % bw) - bw; x < scw; x += bw) {
			stage_BackTexture.Render(x, y);
		}
	}

	//�e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = stage_ChipTexture.GetWidth() / stage_ChipSize;
	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < stage_YCount; y++)
	{
		//�`�悷��`�b�v�ԍ�
		//�`�b�v�ԍ�0�͕`�悵�Ȃ�
		for (int x = 0; x < stage_XCount; x++)
		{
			char cn = stage_pChipData[y * stage_XCount + x] - 1;
			if (cn < 0) {
				continue;
			}

			//�}�b�v�`�b�v�̋�`
			CRectangle cr(stage_ChipSize * (cn % tcx), stage_ChipSize * (cn / tcx), stage_ChipSize * (cn % tcx + 1), stage_ChipSize * (cn / tcx + 1));
			//�}�b�v�`�b�v�̕`��
			stage_ChipTexture.Render(-stage_Scroll.x + x * stage_ChipSize, -stage_Scroll.y + y * stage_ChipSize - stage_gap[y * stage_XCount + x], cr);
		}
	}


}

void CStage::RenderDebug(void)
{

}

void CStage::Release(void)
{
	//�`�b�v���
	stage_ChipTexture.Release();
	stage_BackTexture.Release();
	if (stage_pChipData) {
		free(stage_pChipData);
		stage_pChipData = NULL;
	}
	//�G���
	if (stage_pEnemyData)
	{
		free(stage_pEnemyData);
		stage_pEnemyData = NULL;
	}
	if (stage_pEnemyTexture)
	{
		delete[] stage_pEnemyTexture;
		stage_pEnemyTexture = NULL;
	}
	//�A�C�e�����
	if (stage_pItemData)
	{
		free(stage_pItemData);
		stage_pItemData = NULL;
	}
	if (stage_pItemTexture)
	{
		delete[] stage_pItemTexture;
		stage_pItemTexture = NULL;
	}
	//�A�C�e�����
	if (stage_gap)
	{
		delete[] stage_gap;
		stage_gap = NULL;
	}
	//�A�C�e�����
	if (stage_gapMove)
	{
		delete[] stage_gapMove;
		stage_gapMove = NULL;
	}


	//SE���
	stage_BlockAttackSE.Release();
	stage_BlockDestroySE.Release();
	
	//�G�e�e�N�X�`�����
	stage_EnemyShotTexture.Release();
	stage_EnemyFireTexture.Release();

}






bool CStage::Collision(CRectangle r, float& ox, float& oy, bool& og, bool& dead, bool& jump, CPlayer& pl,bool& magma)
{
	bool re = false;
	int	 wait = 10;
	//�����蔻�肷���`�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = r.Left / stage_ChipSize;
	int rc = r.Right / stage_ChipSize;
	int tc = r.Top / stage_ChipSize;
	int bc = r.Bottom / stage_ChipSize;

	//�X�e�[�W�͈̔͊O�ɂȂ�Ȃ��悤�ɂ���
	if (lc < 0) lc = 0;
	if (tc < 0) tc = 0;
	if (rc >= stage_XCount) rc = stage_XCount - 1;
	if (bc >= stage_YCount) bc = stage_YCount - 1;
	//�����蔻��������`�̍��ォ��E���͈̔͂̂ݓ����蔻����s��
	//����ȊO�̔ԍ��͓����邱�Ƃ��Ȃ��̂Ŕ���͕K�v�Ȃ�
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			char cn = stage_pChipData[y * stage_XCount + x] - 1;
			//�`�b�v�ԍ�0�͓����蔻�肵�Ȃ�
			if (cn < 0) {
				continue;
			}
			//�S�[���t���b�O�������蔻������Ȃ�
			else if (cn == CHIP_GOALFLAG_L - 1 || cn == CHIP_GOALFLAG_R - 1)
			{
				continue;
			}
			//�N���A�����Ƃ��A�S�[���t���b�O�̋��Ɩ_�̓����蔻������Ȃ�
			if (pl.Getplayer_ClearFlg() && (cn == CHIP_GOALBALL - 1 || cn == CHIP_GOALROD - 1))
			{
				continue;
			}

			//�}�b�v�`�b�v�̋�`
			CRectangle cr(x * stage_ChipSize, y * stage_ChipSize, x * stage_ChipSize + stage_ChipSize, y * stage_ChipSize + stage_ChipSize);

			//�S�[���t���b�O��`
			if (cn == 21 || cn == 5)
			{
				CRectangle temp(x * stage_ChipSize + 12, y * stage_ChipSize, x * stage_ChipSize + stage_ChipSize - 12, y * stage_ChipSize + stage_ChipSize);
				//�}�b�v�`�b�v�̋�`
				cr = temp;
			}
			//�}�O�}��`
			if (cn == 27)
			{
				CRectangle temp(x * stage_ChipSize, y * stage_ChipSize + 10, x * stage_ChipSize + stage_ChipSize, y * stage_ChipSize + stage_ChipSize);
				//�}�b�v�`�b�v�̋�`
				cr = temp;
			}

			CRectangle grec = r;
			grec.Top = grec.Bottom;
			grec.Bottom = grec.Top + 1;
			grec.Expansion(-6, 0);
			if (cr.CollisionRect(grec)) {
				og = true;
			}
			//�����蔻��p�̃L�����N�^��`
			//���Ŕ͈͂����肵����p�̋�`���쐬����
			CRectangle bottomRect = r;
			bottomRect.Top = bottomRect.Bottom - 1;
			bottomRect.Expansion(-6, 0);
			//���Ɠ����蔻��
			if (cr.CollisionRect(bottomRect)) {
				re = true;
				//���̖��܂�Ȃ̂Ń`�b�v��[�����`�̉��[�̒l���������l�����܂�̒l
				oy += cr.Top - bottomRect.Bottom;
				r.Top += cr.Top - bottomRect.Bottom;
				r.Bottom += cr.Top - bottomRect.Bottom;

				//�ڐG���Ă���u���b�N�������Ă���Ƃ��A�G�ƃA�C�e���̃t���O��True
				if (stage_gap[y * stage_XCount + x] != 0)
				{
					dead = true;
					jump = true;
				}
				if (cn == CHIP_GOALROD -1 || cn == CHIP_GOALBALL -1)
				{
					pl.Setplayer_ClearFlg(true);
				}
				if (cn == 35)
				{
					pl.SetWarpFlg(true);
				}
				if (cn == 27)
				{
					magma = true;
				}
			}
			//�����蔻��p�̃L�����N�^��`
			//��Ŕ͈͂����肵����p�̋�`���쐬����
			CRectangle topRect = r;
			topRect.Bottom = topRect.Top + 1;		//��̋�`�͉�������Ɠ����l�ɂ���
			topRect.Expansion(-6, 0);				//���͈̔͂��������߂�
			//��Ɠ����蔻��
			if (cr.CollisionRect(topRect)) {

				re = true;
				//��̖��܂�Ȃ̂Ń`�b�v���[�����`�̏�̒l���������l�����܂�̒l
				oy += cr.Bottom - topRect.Top;
				r.Top += cr.Bottom - topRect.Top;
				r.Bottom += cr.Bottom - topRect.Top;

				//�ڐG�����u���b�N�̓����t���O��True�ɂ���
				if (cn == CHIP_QUESTION - 1 || cn == CHIP_HARDBLOCK - 1 
					|| cn == CHIP_EMOJI - 1 || cn == CHIP_BLOCK - 1 || cn == CHIP_COINBLOCK - 1)
				{

					//X��Y�̒l��ޔ�
					stage_tmpChipX = x;
					stage_tmpChipY = y;
					//�u���b�N�����t���O��True
					stage_chipUp = true;
				}
				//�j��
				if (cn == CHIP_BLOCK - 1 && pl.Getplayer_BigFlg())
				{
					stage_tmpChipX = x;
					stage_tmpChipY = y;
					stage_BlockDestroy = true;
					stage_BlockDestroyWait = 5;
				}
				//�u���b�N�ω�
				if (cn == CHIP_QUESTION - 1 && stage_chipUp)
				{
					stage_tmpChipX = x;
					stage_tmpChipY = y;
					stage_BlockChange = true;
				}

			}
			//�����蔻��p�̃L�����N�^��`
			//���A�E���ꂼ��Ŕ͈͂����肵����p�̋�`���쐬����
			CRectangle leftRect = r;
			leftRect.Right = leftRect.Left + 1;		//���̋�`�͉E�������Ɠ����l�ɂ���
			leftRect.Expansion(0, -6);			//�c�͈̔͂��������߂�
			CRectangle rightRect = r;
			rightRect.Left = rightRect.Right - 1;		//�E�̋�`�͍������E�Ɠ����l�ɂ���
			rightRect.Expansion(0, -6);			//�c�͈̔͂��������߂�
			//���Ɠ����蔻��
			if (cr.CollisionRect(leftRect)) {
				re = true;

				ox += cr.Right - leftRect.Left;
				r.Left += cr.Right - leftRect.Left;
				r.Right += cr.Right - leftRect.Left;
				if (cn == CHIP_GOALROD - 1)
				{
					pl.Setplayer_ClearFlg(true);
				}
				if (cn == CHIP_CLEARTRANSITION - 1)
				{
					pl.Setplayer_ClearTransitionFlg(true);
				}
				if (cn == 35)
				{
					pl.SetWarpFlg(true);
				}
				if (cn == 34)
				{
					pl.SetBossClearTrantionFlg(true);
				}

			}
			//�E�Ɠ����蔻��
			else if (cr.CollisionRect(rightRect)) {
				re = true;

				ox += cr.Left - rightRect.Right;
				r.Left += cr.Left - rightRect.Right;
				r.Right += cr.Left - rightRect.Right;

				if (cn == CHIP_GOALROD - 1)
				{
					pl.Setplayer_ClearFlg(true);
				}
				if (cn == CHIP_CLEARTRANSITION - 1)
				{
					pl.Setplayer_ClearTransitionFlg(true);
				}
				if (cn == 35)
				{
					pl.SetWarpFlg(true);
				}
				if (cn == 34)
				{
					pl.SetBossClearTrantionFlg(true);
				}
			}

		}
	}

	return re;

}


