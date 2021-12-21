/***********************************

Stage�N���X�֘A�̃\�[�X
�X�e�[�W�N���X�̒�`���L�q
�쐬���F2016/12/8
�쐬�ҁF�a�c

************************************/
#include "Stage.h"
#include "Enemy.h"
//�R���X�g���N�^
CStage::CStage():
m_Texture(),
m_Scroll(0.0f),
m_pEnemyStart(NULL),
m_EnemyCount(0),
m_EnemyTexture(),
m_EnemyShotTexture(),
m_EnemyNo(0)
{
}

//�f�X�g���N�^
CStage::~CStage()
{
}

//���\�[�X�̓ǂݍ���
bool CStage::Load()
{
	//�w�i�e�N�X�`���̓ǂݍ���
	if (!m_Texture.Load("Stage1.png"))
	{
		return false;
	}
	if (!m_EnemyTexture.Load("EnemyBlack.png"))
	{
		return false;
	}
	if (!m_EnemyTextureWhite.Load("EnemyWhite.png"))
	{
		return false;
	}
	if (!m_EnemyTextureBlack.Load("EnemyBlack.png"))
	{
		return false;
	}
	if (!m_EnemyShotTexture.Load("E_missileBlack.png"))
	{
		return false;
	}
	if (!m_EnemyShotTextureBlack.Load("E_missileBlack.png"))
	{
		return false;
	}
	if (!m_EnemyShotTextureWhite.Load("E_missileWhite.png"))
	{
		return false;
	}
	if (!m_BossBlack.Load("BossBlack.png"))
	{
		return false;
	}
	if (!m_BossWhite.Load("BossWhite.png"))
	{
		return false;
	}
	return true;
}

//�p�����^���̏�����
void CStage::Initialize(ENEMYSTART* pst,int cnt)
{
	//�X�N���[���l��������
	m_Scroll = 0.0f;

	m_EnemyNo = 0;
	m_pEnemyStart = pst;
	m_EnemyCount = cnt;
}

//�X�V����
void CStage::Update(CEnemy* ene,int ecnt)
{
	//�X�N���[������
	m_Scroll += SCROLL_SPEED;
	//�G�̏o������
	if (m_EnemyNo < m_EnemyCount && m_Scroll >= m_pEnemyStart[m_EnemyNo].Scroll)
	{//�o�����Ă��Ȃ��G��T��
		for (int i = 0; i < ecnt; i++)
		{//�G���\������Ă���ꍇ�́A�g�p��
			if (ene[i].GetShow()) { continue; }
			//�F���ǂ��炩
			//if(EnemyColor)
			if (m_pEnemyStart[m_EnemyNo].Color == 0)
			{
				//�G�o��
				ene[i].SetTexture(&m_EnemyTextureWhite,&m_EnemyShotTextureWhite);
				ene[i].Start(m_pEnemyStart[m_EnemyNo].PosX, 0, m_pEnemyStart[m_EnemyNo].Color, m_pEnemyStart[m_EnemyNo].Type, m_pEnemyStart[m_EnemyNo].hp);
			}
			if (m_pEnemyStart[m_EnemyNo].Color == 1)
			{
				//�G�o��
				ene[i].SetTexture(&m_EnemyTextureBlack, &m_EnemyShotTextureBlack);
				ene[i].Start(m_pEnemyStart[m_EnemyNo].PosX, 0, m_pEnemyStart[m_EnemyNo].Color, m_pEnemyStart[m_EnemyNo].Type, m_pEnemyStart[m_EnemyNo].hp);
			}
			break;
		}
		//�G�o���������Z
		m_EnemyNo++;
	}
}

//�`�揈��
void CStage::Render()
{
	//�`��
	int h = m_Texture.GetHeight();
	int sch = g_pGraphics->GetTargetHeight();
	for (float y = ((int)m_Scroll % h) - h; y < sch; y += h)
	{
		m_Texture.Render(0.0f,y);
	}
	
}


//���\�[�X���̉������
void CStage::Release()
{
	//�w�i�e�N�X�`�������
	m_Texture.Release();
	m_EnemyTexture.Release();
	m_EnemyTextureBlack.Release();
	m_EnemyTextureWhite.Release();
	m_EnemyShotTexture.Release();
	m_EnemyShotTextureBlack.Release();
	m_EnemyShotTextureWhite.Release();
	m_BossBlack.Release();
	m_BossWhite.Release();
}

//void CStage::RenderDebug(void)
//{
//	CGraphicsUtilities::RenderString(10, 10, MOF_XRGB(0, 0, 0), "�X�N���[��:%.0f", m_Scroll);
//}

void CStage::RenderDebug(void)
{
	CGraphicsUtilities::RenderString(10, 10, MOF_XRGB(0, 0, 0), "�X�N���[��:%.0f,�G�̏o���ԍ�:%d", m_Scroll, m_EnemyNo);
}