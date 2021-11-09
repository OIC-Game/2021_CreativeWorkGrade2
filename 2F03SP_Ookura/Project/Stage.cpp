#include	"Stage.h"

CStage::CStage() :
m_Texture() ,
m_Scroll(0.0f) ,
m_pEnemyStart(NULL) ,
m_EnemyTexture() ,
m_EnemyCount(0),
m_EnemyShotTexture() ,
m_EnemyNo(0) {
}


CStage::~CStage(){
}


bool CStage::Load(void) {
	//�e�N�X�`���̓ǂݍ���
	if (!m_Texture.Load("Stage1.png"))
	{
		return false;
	}
	

	
	if(!m_EnemyTexture.Load("Enemy1.png"))
	{
		return false;
	}
	if(!m_EnemyShotTexture.Load("E_missile.png"))
	{
		return false;
	}
	return true;
}

/**
 * ������
 */
void CStage::Initialize(ENEMYSTART* pSt, int cnt){
	m_Scroll = 0;
	m_EnemyNo = 0;
	m_pEnemyStart = pSt;
	m_EnemyCount = cnt;
	
}

/**
 * �X�V

 */
void CStage::Update(CEnemy* ene,int ecnt){
	m_Scroll += SCROLL_SPEED;
	//�X�N���[���ʒu���G�̏o���ʒu���傫���Ȃ�����G���o��������
	if(m_EnemyNo < m_pEnemyStart->Count && m_Scroll >= m_pEnemyStart->Scroll[m_EnemyNo])
	{
		for(int i = 0;i < ecnt;i++)
		{
			if(ene[i].GetShow())
			{
				continue;
			}
			ene[i].SetTexture(&m_EnemyTexture,&m_EnemyShotTexture);
			ene[i].Start(m_pEnemyStart->PosX[m_EnemyNo],0,m_pEnemyStart->Type[m_EnemyNo]);
			break;
		}
		m_EnemyNo++;
	}
}

/**
 * �`��
 *
 */
void CStage::Render(void){
	//�e�N�X�`���̕`��
	//�����e�N�X�`�����J��Ԃ��ŉ�ʒ[�𒴂���܂ŕ`����s��
	int h = m_Texture.GetHeight();
	int sch = g_pGraphics->GetTargetHeight();
	for(float y = ((int)m_Scroll % h) - h;y < sch;y += h) 
	{
		m_Texture.Render(0.0f , y);
	}
}

/**
 * �f�o�b�O�`��
 *
 */
void CStage::RenderDebug(void){
	//�X�N���[���l�̕`��
	CGraphicsUtilities::RenderString(10,10,MOF_XRGB(0,0,0),"�X�N���[�� : %.0f , �G�̏o���ԍ� : %d",m_Scroll,m_EnemyNo);
}

/**
 * ���
 *
 */
void CStage::Release(void){
	m_Texture.Release();
	m_EnemyTexture.Release();
	m_EnemyShotTexture.Release();
}