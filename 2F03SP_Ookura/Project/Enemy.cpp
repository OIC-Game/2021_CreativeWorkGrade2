#include	"Enemy.h"

/**
 * �R���X�g���N�^
 *
 */
CEnemy::CEnemy() :
	m_pTexture(NULL),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_SpeedX(0.0f),
	m_SpeedY(0.0f),
	m_bShow(false),
	m_HP(0),
	m_ShotArray(),
	m_ShotWait(0),
	m_ShotWaitSet(0),
	m_TargetPosX(0.0f),
	m_TargetPosY(0.0f),
	m_Type(0) {
}

/**
 * �f�X�g���N�^
 *
 */
CEnemy::~CEnemy() {
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * �v���C���[�̈ʒu�ȂǏ�Ԃ��������������Ƃ��Ɏ��s����B
 */
void CEnemy::Initialize(void) {
	m_PosX = 0;
	m_PosY = 0;
	m_SpeedX = 0;
	m_SpeedY = 0;
	m_bShow = false;
	m_HP = 1;
	m_ShotWait = 0;
	m_ShotWaitSet = 40;
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
}
/**
 * �J�n
 * �����̍��W�Ɉʒu��ݒ肵�āA�\���t���O��true�ɕύX����B
 *
 * ����
 * [in]			px				���˂w���W
 * [in]			py				���˂x���W
 */
void CEnemy::Start(float px, float py, int t) {
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py - m_pTexture->GetHeight();
	m_SpeedX = 5;
	m_SpeedY = 1;
	m_Type = t;
	m_bShow = true;
	m_HP = ((m_Type == 1) ? 200 : 1);
	m_ShotWaitSet = ((m_Type == 1) ? 120 : 40);
	m_ShotWait = m_ShotWaitSet;
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
}

/**
 * �X�V
 *
 */
void CEnemy::Update(void) {
	//�e�̍X�V
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}
	//��\��
	if (!m_bShow)
	{
		return;
	}
	switch (m_Type)
	{
	case 0:
		UpdateType0();
		break;
	case 1:
		UpdateType1();
		break;
	}

}
/*Type0�̓G
updaate����switch�ň�v�������̂ݎ��s*/
void CEnemy::UpdateType0(void) {
	/*if (m_PosY < 1000)
	{
		m_PosY += m_SpeedY;
	}
	else
	{
		if (m_ShotWait <= 0)
		{
			int sCnt = 12;
			//kakudo
			float ad = 0.0f;
			for (int cnt = 0; cnt < sCnt; cnt++)
			{
				for (int i = 0; i < ENEMYSHOT_COUNT; i++)
				{
					if (m_ShotArray[i].GetShow())
					{
						continue;
					}
					m_ShotWait = m_ShotWaitSet;
					//hassya ichi
					float stx = m_PosX + m_pTexture->GetWidth() * 0.5f;
					float sty = m_PosY + m_pTexture->GetHeight();
					//tama susumu houkou
					m_ShotArray[i].Fire(stx, sty, cos(MOF_ToRadian(ad)) * 5, sin(MOF_ToRadian(ad)) * 5);
					break;
				}
				//360 / kazu
				ad += 360.0f / sCnt;
			}
		}
		else
		{
			m_ShotWait--;
		}
	}*/
	//��ʉ��Ɍ������Ĉړ�
	m_PosY += m_SpeedY;
	m_PosX += m_SpeedX;

	//��ʊO�ŏ���
	if (m_PosY >= g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
	if (m_SpeedX > 0 && m_PosX + m_pTexture->GetWidth() > g_pGraphics->GetTargetWidth())
	{
		m_SpeedX *= -1;
	}
	else if (m_SpeedX < 0 && m_PosX < 100)
	{
		m_SpeedX *= -1;
	}
	if (m_PosY + m_pTexture->GetHeight() > 500)
	{
		m_SpeedY *= -1;
	}
	//�e�̔���
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			if (m_ShotArray[i].GetShow())
			{
				continue;
			}
			m_ShotWait = m_ShotWaitSet;
			float stx = m_PosX + m_pTexture->GetWidth() * 0.5f;
			float sty = m_PosY + m_pTexture->GetHeight();
			float dx = m_TargetPosX - stx;
			float dy = m_TargetPosY - sty;
			float d = sqrt(dx * dx + dy * dy);
			if (d <= 0)
			{
				break;
			}
			dx /= d;
			dy /= d;
			m_ShotArray[i].Fire(stx, sty, dx * 5, dy * 5);
			//m_ShotArray[i].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f,m_PosY + m_pTexture->GetHeight(),0,5);
			break;
		}
	}
	else
	{
		m_ShotWait--;
	}
}

/*Type1�̓G
switch�ň�v�������̂ݎ��s*/
void CEnemy::UpdateType1(void) {

	/*m_PosY += m_SpeedY;
	m_PosX += m_SpeedX;

	//��ʊO�ŏ���
	if (m_PosY >= g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
	if (m_SpeedX > 0 && m_PosX + m_pTexture->GetWidth() > g_pGraphics->GetTargetWidth())
	{
		m_SpeedX *= -1;
	}
	else if (m_SpeedX < 0 && m_PosX < 100)
	{
		m_SpeedX *= -1;
	}
	if (m_PosY + m_pTexture->GetHeight() > 500)
	{
		m_SpeedY *= -1;
	}
	//�e�̔���
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			if (m_ShotArray[i].GetShow())
			{
				continue;
			}
			m_ShotWait = m_ShotWaitSet;
			float stx = m_PosX + m_pTexture->GetWidth() * 0.5f;
			float sty = m_PosY + m_pTexture->GetHeight();
			float dx = m_TargetPosX - stx;
			float dy = m_TargetPosY - sty;
			float d = sqrt(dx * dx + dy * dy);
			if (d <= 0)
			{
				break;
			}
			dx /= d;
			dy /= d;
			m_ShotArray[i].Fire(stx, sty, dx * 5, dy * 5);
			//m_ShotArray[i].Fire(m_PosX + m_pTexture->GetWidth() * 0.5f,m_PosY + m_pTexture->GetHeight(),0,5);
			break;
		}
	}
	else
	{
		m_ShotWait--;*
	}*/
	if (m_PosY < 100)
	{
		m_PosY += m_SpeedY;
	}
	else
	{
		if (m_ShotWait <= 0)
		{
			int sCnt = 12;
			//kakudo
			float ad = 0.0f;
			for (int cnt = 0; cnt < sCnt; cnt++)
			{
				for (int i = 0; i < ENEMYSHOT_COUNT; i++)
				{
					if (m_ShotArray[i].GetShow())
					{
						continue;
					}
					m_ShotWait = m_ShotWaitSet;
					//hassya ichi
					float stx = m_PosX + m_pTexture->GetWidth() * 0.5f;
					float sty = m_PosY + m_pTexture->GetHeight();
					//tama susumu houkou
					m_ShotArray[i].Fire(stx, sty, cos(MOF_ToRadian(ad)) * 5, sin(MOF_ToRadian(ad)) * 5);
					break;
				}
				//360 / kazu
				ad += 360.0f / sCnt;
			}
		}
		else
		{
			m_ShotWait--;
		}
	}
}


/**
 * �_���[�W����
 * �������̂g�o�����炵�g�o���O�ȉ��ɂȂ�ΓG����������
 *
 * ����
 * [in]			dmg				�_���[�W
 *
 */
void CEnemy::Damage(int dmg) {
	m_HP -= dmg;
	if (m_HP <= 0)
	{
		m_bShow = false;
	}
}

/**
 * �`��
 *
 */
void CEnemy::Render(void) {
	//�e�̕`��
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render();
	}
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX, m_PosY);
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			i				�G�̔z����ԍ�
 */
void CEnemy::RenderDebug(int i) {
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10, 70 + i * 24, MOF_XRGB(0, 0, 0), "�G[%d] %s , �ʒu X : %.0f , Y : %.0f", i + 1, ((m_bShow) ? "�\��" : "��\��"), m_PosX, m_PosY, m_HP);

	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CGraphicsUtilities::RenderRect(m_PosX, m_PosY, m_PosX + m_pTexture->GetWidth(), m_PosY + m_pTexture->GetHeight(), MOF_XRGB(255, 0, 0));
	//�e�̕`��
	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		m_ShotArray[i].RenderDebug();
	}
}