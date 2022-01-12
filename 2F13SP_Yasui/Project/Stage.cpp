#include "Stage.h"
#include "GlobalDefine.h"

extern int stage_number;

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

	if (stage_number == STAGE_LAST)
	{
		char* name[] = {
			"MarioJump.mp3",
			"MarioFire.mp3",
			"MarioDead.mp3",
			"ChangeBigSE.wav"
		};
		for (int i = 0; i < MARIOSOUND_COUNT; i++)
		{
			if (!stage_MarioSE[i].Load(name[i]))
			{
				return false;
			}
		}
	}
	else if (stage_number == STAGE_2_1)
	{
		stage_FishesTexture.Load("Fishes.png");
	}

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
	if (!stage_ExplosionSE.Load("Explosion.mp3"))
	{
		return false;
	}

	return true;

}

void CStage::Initialize(CEnemy* pEnemy, CItem* pItem,int stageState)
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
	stage_State = stageState;

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
				for (int i = 0; i < MARIOSOUND_COUNT; i++)
				{
					pEnemy[n].SetSound(&stage_MarioSE[i],i);
				}
			}
			else
			{
				pEnemy[n].SetTexture(&stage_pEnemyTexture[on],  & stage_EnemyShotTexture);
			}
			pEnemy[n++].Initialize(x * stage_ChipSize, y * stage_ChipSize, on,stage_State);
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
			pItem[n++].Initialize(x * stage_ChipSize, y * stage_ChipSize, on, stage_State);
		}
	}

	//�u���b�N�ړ��̈ʒu�Ƒ��x��������
	for (int y = 0; y < stage_YCount; y++) {
		for (int x = 0; x < stage_XCount; x++) {
			stage_gap[y * stage_XCount + x] = 0;
			stage_gapMove[y * stage_XCount + x] = 0;
		}
	}
	if (stage_number == STAGE_2_1)
	{
		stage_FishesMove = Vector2(-2,0);
		stage_FishesPos = Vector2(g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight() / 2.5f);
	}
}

void CStage::Update(CPlayer& pl)
{

	//�v���C���[�̋�`�擾
	CRectangle prect = pl.GetRectPlayer();
	//�X�N���[���̕�
	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	//�X�e�[�W�S�̂̕�
	float stgw = stage_ChipSize * stage_XCount;
	float stgh = stage_ChipSize * stage_YCount;

	//���W����ʒ[�ɂ���Ă���(�p�[����200pixel)�ꍇ�X�N���[�����s���ĕ␳����B
	if (stage_number == STAGE_LAST)
	{
		if (stage_Scroll.x < 10572 && !pl.GetWarpFlg() && pl.Getplayer_PositionY() <= 1000)
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

			stage_Scroll.x = 12064;

			stage_FixScroll = true;
		}
	}
	else if (stage_number == STAGE_3_1)
	{
		if (prect.Left - stage_Scroll.x < 200) {
			stage_Scroll.x -= 200 - (prect.Left - stage_Scroll.x);
			if (stage_Scroll.x <= 0) {
				stage_Scroll.x = 0;
			}
		}
		else if (prect.Right - stage_Scroll.x > sw - 700) {
			stage_Scroll.x += (prect.Right - stage_Scroll.x) - (sw - 700);
			if (stage_Scroll.x >= stgw - sw) {
				stage_Scroll.x = stgw - sw;
			}
		}
	}
	else
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
		if (stage_number == STAGE_1_1)
		{
			stage_Scroll.y = 32;
		}
		else if (stage_number == STAGE_2_1)
		{
			if (!pl.GetPlayerMaguroFly())
			{
				if (prect.Top - stage_Scroll.y < 200) {
					stage_Scroll.y -= 200 - (prect.Top - stage_Scroll.y);
					if (stage_Scroll.y <= 0) {
						stage_Scroll.y = 0;
					}
				}
				else if (prect.Bottom - stage_Scroll.y > sh - 200) {
					stage_Scroll.y += (prect.Bottom - stage_Scroll.y) - (sh - 200);
					if (stage_Scroll.y >= stgh - sh) {
						stage_Scroll.y = stgh - sh;
					}
				}
			}
			else
			{
				if (stage_Scroll.y > 0)
				{
					stage_Scroll.y -= 2.5f;
				}
			}
		}

		

	}
	if (stage_number == STAGE_1_1)
	{
		if (pl.Getplayer_PositionY() > 1000 && pl.GetDokanWarpFlg())
		{
			
			if (prect.Left - stage_Scroll.x < 400) {
				stage_Scroll.x -= 400 - (prect.Left - stage_Scroll.x);
				if (stage_Scroll.x <= 0) {
					stage_Scroll.x = 0;
				}
			}
			else if (prect.Right - stage_Scroll.x > sw - 400 && pl.Getplayer_PositionX() < 900) {
				stage_Scroll.x += (prect.Right - stage_Scroll.x) - (sw - 400);
				if (stage_Scroll.x >= stgw - sw) {
					stage_Scroll.x = stgw - sw;
				}
			}
			stage_Scroll.y = 932;

		}
	}
	if (stage_number == STAGE_2_1)
	{
		
		

		stage_FishesPos.x += stage_FishesMove.x;


		if (-stage_Scroll.x + stage_FishesPos.x + stage_FishesTexture.GetWidth() < 64)
		{
			stage_FishesPos.x = g_pGraphics->GetTargetWidth() + stage_Scroll.x;
			stage_FishesPos.y = CUtilities::Random(0, g_pGraphics->GetTargetHeight() - stage_Scroll.y);
			stage_FishesMove.x = -(int)CUtilities::Random(1, 7);
		}

	}

	if (pl.GetMarioDead())
	{
		/*if (prect.Left - stage_Scroll.x < 200)
		{
			stage_Scroll.x -= 200 - (prect.Left - stage_Scroll.x);
			if (stage_Scroll.x <= 0) {
				stage_Scroll.x = 0;
			}
		}*/
		if (prect.Right - stage_Scroll.x > sw - 50)
		{
			stage_Scroll.x += (prect.Right - stage_Scroll.x) - (sw - 50);
			if (stage_Scroll.x >= stgw - sw)
			{
				stage_Scroll.x = stgw - sw;
			}
		}
		if (pl.GetBossClearFlg())
		{
			if (stage_Scroll.x < 13332)
				stage_Scroll.x += 5;
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
			if (stage_pChipData[stage_tmpChipY * stage_XCount + stage_tmpChipX] == CHIP_BLOCK || 
				stage_pChipData[stage_tmpChipY * stage_XCount + stage_tmpChipX] == CHIP_BLUEBLOCK)
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

		int x = 407;
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
	//float bScale = sch / (float)stage_BackTexture.GetHeight();
	int bw = (int)(stage_BackTexture.GetWidth());
	int bh = (int)(stage_BackTexture.GetHeight());
	for (float y = ((int)-stage_Scroll.y % bh); y < sch; y += bh) {
		for (float x = ((int)-stage_Scroll.x / 4 % bw) - bw; x < scw; x += bw) {
			stage_BackTexture.Render(x, y);
		}
	}
	if (stage_number == STAGE_2_1)
	{
		Vector2 scroll(-stage_Scroll.x + stage_FishesPos.x, -stage_Scroll.y + stage_FishesPos.y);
		stage_FishesTexture.Render(scroll.x, scroll.y, TEXALIGN_CENTERLEFT);
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
			if (-stage_Scroll.x + x * stage_ChipSize < -64 || -stage_Scroll.x + x * stage_ChipSize > g_pGraphics->GetTargetWidth() + 64)
			{
				continue;
			}
			if (-stage_Scroll.y + y * stage_ChipSize < -128 || -stage_Scroll.y + y * stage_ChipSize > g_pGraphics->GetTargetHeight() + 64)
			{
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
	CGraphicsUtilities::RenderString(600, 20, "�X�N���[��:X%fY%f", stage_Scroll.x, stage_Scroll.y);
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
	stage_FishesTexture.Release();

	//SE���
	stage_BlockAttackSE.Release();
	stage_BlockDestroySE.Release();
	
	//�G�e�e�N�X�`�����
	stage_EnemyShotTexture.Release();
	stage_EnemyFireTexture.Release();
	for (int i = 0; i < MARIOSOUND_COUNT; i++)
	{
		stage_MarioSE[i].Release();
	}
	stage_ExplosionSE.Release();

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
			else if (cn == CHIP_GOALFLAG_L - 1 || cn == CHIP_GOALFLAG_R - 1 || cn == 4)
			{
				continue;
			}
			//�N���A�����Ƃ��A�S�[���t���b�O�̋��Ɩ_�̓����蔻������Ȃ�
			if (pl.Getplayer_ClearFlg() && (cn == CHIP_GOALBALL - 1 || cn == CHIP_GOALROD - 1))
			{
				continue;
			}
			//���̓����蔻������Ȃ�
			if (cn == 49 || cn == 50 || cn == 51)
			{
				continue;
			}
			if (cn == 56 || cn == 57)
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

				if (cn == 42 || cn == 43)
				{
					if (g_pInput->IsKeyHold(MOFKEY_DOWN))
					{
						pl.SetDokanWarpFlg(true);
						pl.SetPlayerPos(Vector2(200, 1200));
					}
				}
				if (cn == CHIP_CLEARTRANSITION - 1)
				{
					pl.Setplayer_ClearTransitionFlg(true);
				}
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
					|| cn == CHIP_EMOJI - 1 || cn == CHIP_BLOCK - 1 || cn == CHIP_COINBLOCK - 1
					|| cn == CHIP_BLUEBLOCK -1 || cn == CHIP_BLUEHARDBLOCK - 1)
				{

					//X��Y�̒l��ޔ�
					stage_tmpChipX = x;
					stage_tmpChipY = y;
					//�u���b�N�����t���O��True
					stage_chipUp = true;
				}
				//�j��
				if ((cn == CHIP_BLOCK - 1 || cn == CHIP_BLUEBLOCK - 1) && pl.Getplayer_BigFlg())
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
				
				if (cn == 35)
				{
					pl.SetWarpFlg(true);
				}
				if (cn == 34)
				{
					pl.SetBossClearTrantionFlg(true);
				}
				if (cn == 63)
				{
					pl.SetPlayerMaguroFly(true);
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
				if (cn == CHIP_CLEARTRANSITION - 1 || cn == 58)
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
				if (cn == 44 || cn == 52)
				{
					if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
					{
						pl.SetDokanWarpFlg(false);
						pl.SetPlayerPos(Vector2(3600, 458));
					}
				}
				if (cn == 63)
				{
					pl.SetPlayerMaguroFly(true);
				}
			}

		}
	}

	return re;

}

void CStage::ExplotionCastle()
{
	for (int y = 1; y < 7; y++)
	{
		for (int x = 294; x < 300; x++)
		{
			if (stage_pChipData[y * stage_XCount + x] == 58)
			{
				continue;
			}
			stage_pChipData[y * stage_XCount + x] = 58;
		}
	}
	if (!stage_ExplosionSE.IsPlay())
	{
		stage_ExplosionSE.Play();
	}
	

}

void CStage::EndString()
{
	for (int y = 18; y < 23; y++)
	{
		for (int x = 423; x < 442; x++)
		{
			if (stage_pChipData[y * stage_XCount + x] == 57)
			{
				continue;
			}
			if (stage_pChipData[y * stage_XCount + x] == 0)
			{
				continue;
			}
			stage_pChipData[y * stage_XCount + x] = 0;
		}
	}
}


