#include	"EnemyShot.h"

/**
 * �R���X�g���N�^
 *
 */
CEnemyShot::CEnemyShot() :
m_pTexture(NULL) ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_SpeedX(0.0f),
m_SpeedY(0.0f),
m_bShow(false) {
}

/**
 * �f�X�g���N�^
 *
 */
CEnemyShot::~CEnemyShot(){
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 */
void CEnemyShot::Initialize(void){
	m_PosX = 0;
	m_PosY = 0;
	m_SpeedX = 0;
	m_SpeedY = 0;
	m_bShow = false;
}
/**
 * ����
 * �����̍��W�Ɉʒu��ݒ肵�āA�\���t���O��true�ɕύX����B
 *
 * ����
 * [in]			px				���˂w���W
 * [in]			py				���˂x���W
 * [in]			sx				�ړ��w���x
 * [in]			sy				�ړ��x���x
 * [in]			type			�e�̎��
 */
void CEnemyShot::Fire(float px,float py,float sx,float sy,int type){
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py;
	m_SpeedX = sx;
	m_SpeedY = sy;
	m_EnemyShotType = type;
	m_bShow = true;
	m_ScaleX = 1;
	m_ScaleY = 1;
	m_CenterPosX = px;
}

/**
 * �X�V
 *
 */
void CEnemyShot::Update(){
	//��\��
	if(!m_bShow)
	{
		return;
	}

	if (m_EnemyShotType == 0)
	{
		//���x�𗘗p�����ړ�
		m_PosX += m_SpeedX;
		m_PosY += m_SpeedY;
	}
	if (m_EnemyShotType == 1)
	{
		m_PosX = m_CenterPosX - ((m_pTexture->GetWidth() * m_ScaleX)*0.5f);
		if (m_PosX < 0)
			m_PosX = 0;
		m_PosY += m_SpeedY;
	}

	//��ʊO�ŏ���
	if(m_PosX + m_pTexture->GetWidth() < 0 || m_PosX > g_pGraphics->GetTargetWidth() ||
		m_PosY + m_pTexture->GetHeight() < 0 || m_PosY > g_pGraphics->GetTargetHeight())
	{
		m_bShow = false;
	}
}

/**
 * �`��
 *
 */
void CEnemyShot::Render(float xscal,float yscal,BYTE alp) {
	//��\��
	if (!m_bShow)
	{
		return;
	}

	m_ScaleX = xscal;
	m_ScaleY = yscal;
	//�e�N�X�`���̕`��
	m_pTexture->RenderScale(m_PosX, m_PosY, xscal,yscal,MOF_ARGB(alp,255,255,255));
}

/**
 * �f�o�b�O�`��
 *
 */
void CEnemyShot::RenderDebug(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CGraphicsUtilities::RenderRect(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight(),MOF_XRGB(255,0,0));
}