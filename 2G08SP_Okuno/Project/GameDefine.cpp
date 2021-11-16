#include	"GameDefine.h"

CGameDefine* CGameDefine::m_pGameDefine = NULL;

bool CGameDefine::Load_Block(const char* fname) {

	FILE* f = fopen(fname, "rt");
	if (f == NULL) {
		return false;
	}
	fseek(f, 0, SEEK_END);
	long fSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	//ƒƒ‚ƒŠŠm•Û
	char* buffer = (char*)malloc(fSize + 1);
	fSize = fread(buffer, 1, fSize, f);
	buffer[fSize] = '\0';
	//char* pstr;

	m_pGameDefine->m_BlockDefineCount = atoi(strtok(buffer, ","));
	m_pGameDefine->m_BlockDefine = new CBlockDefine[m_pGameDefine->m_BlockDefineCount];

	for (int i = 0; i < m_pGameDefine->m_BlockDefineCount; i++) {
		m_pGameDefine->m_BlockDefine[i].idx = atoi(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].block = atoi(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].damageFlg = atoi(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].damageDirection = atoi(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].move = atoi(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].x_ext1 = atof(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].x_ext2 = atof(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].y_ext1 = atof(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].y_ext2 = atof(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].layer = atoi(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].broken = atoi(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].nextIdx = atoi(strtok(NULL, ","));
		m_pGameDefine->m_BlockDefine[i].nextIdx_Item = atoi(strtok(NULL, ","));
	}

	fclose(f);
	free(buffer);

	return true;
}

bool CGameDefine::Load_Item(const char* fname) {

	FILE* f = fopen(fname, "rt");
	if (f == NULL) {
		return false;
	}
	fseek(f, 0, SEEK_END);
	long fSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	//ƒƒ‚ƒŠŠm•Û
	char* buffer = (char*)malloc(fSize + 1);
	fSize = fread(buffer, 1, fSize, f);
	buffer[fSize] = '\0';
	//char* pstr;

	m_pGameDefine->m_ItemDefineCount = atoi(strtok(buffer, ","));
	m_pGameDefine->m_ItemDefine = new CItemDefine[m_pGameDefine->m_ItemDefineCount];

	for (int i = 0; i < m_pGameDefine->m_ItemDefineCount; i++) {
		m_pGameDefine->m_ItemDefine[i].idx = atoi(strtok(NULL, ","));
		m_pGameDefine->m_ItemDefine[i].move = atof(strtok(NULL, ","));
		m_pGameDefine->m_ItemDefine[i].itemType = atoi(strtok(NULL, ","));
		m_pGameDefine->m_ItemDefine[i].ext1 = atoi(strtok(NULL, ","));
		m_pGameDefine->m_ItemDefine[i].ext2 = atoi(strtok(NULL, ","));
	}

	fclose(f);
	free(buffer);

	return true;
}
bool CGameDefine::Load_Enemy(const char* fname) {

	FILE* f = fopen(fname, "rt");
	if (f == NULL) {
		return false;
	}
	fseek(f, 0, SEEK_END);
	long fSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	//ƒƒ‚ƒŠŠm•Û
	char* buffer = (char*)malloc(fSize + 1);
	fSize = fread(buffer, 1, fSize, f);
	buffer[fSize] = '\0';
	//char* pstr;

	m_pGameDefine->m_EnemyDefineCount = atoi(strtok(buffer, ","));
	m_pGameDefine->m_EnemyDefine = new CEnemyDefine[m_pGameDefine->m_EnemyDefineCount];

	for (int i = 0; i < m_pGameDefine->m_EnemyDefineCount; i++) {
		m_pGameDefine->m_EnemyDefine[i].idx = atoi(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].damageFlg = atoi(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].damageDirection = atoi(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].move = atoi(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].hp = atoi(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].x_ext1 = atof(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].x_ext2 = atof(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].y_ext1 = atof(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].y_ext2 = atof(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].changeFlg = atoi(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].changeIdx = atoi(strtok(NULL, ","));

		m_pGameDefine->m_EnemyDefine[i].animCount = atoi(strtok(NULL, ","));
		m_pGameDefine->m_EnemyDefine[i].anim = new SpriteAnimationCreate[m_pGameDefine->m_EnemyDefine[i].animCount];
		for (int j = 0; j < m_pGameDefine->m_EnemyDefine[i].animCount; j++) {
			m_pGameDefine->m_EnemyDefine[i].anim[j].Name = strtok(NULL, ",");
			m_pGameDefine->m_EnemyDefine[i].anim[j].OffsetX = atoi(strtok(NULL, ","));
			m_pGameDefine->m_EnemyDefine[i].anim[j].OffsetY = atoi(strtok(NULL, ","));
			m_pGameDefine->m_EnemyDefine[i].anim[j].Width = atoi(strtok(NULL, ","));
			m_pGameDefine->m_EnemyDefine[i].anim[j].Height = atoi(strtok(NULL, ","));
			m_pGameDefine->m_EnemyDefine[i].anim[j].bLoop = atoi(strtok(NULL, ","));
			int frameCount = atoi(strtok(NULL, ","));
			for (int t = 0; t < frameCount; t++) {
				m_pGameDefine->m_EnemyDefine[i].anim[j].Pattern[t].Wait = atoi(strtok(NULL, ","));
				m_pGameDefine->m_EnemyDefine[i].anim[j].Pattern[t].No = atoi(strtok(NULL, ","));
				m_pGameDefine->m_EnemyDefine[i].anim[j].Pattern[t].Step = atoi(strtok(NULL, ","));
			}
		}
	}

	fclose(f);
	free(buffer);

	return true;
}