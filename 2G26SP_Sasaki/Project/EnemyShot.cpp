#include	"EnemyShot.h"

/**
 * �R���X�g���N�^
 *
 */
CEnemyShot::CEnemyShot() :
m_pTexture(NULL) ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_SpdX(0.0f) ,
m_SpdY(0.0f) ,
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
	m_SpdX = 0;
	m_SpdY = 0;
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
 */
void CEnemyShot::Fire(float px,float py,float sx,float sy){
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py;
	m_SpdX = sx;
	m_SpdY = sy;
	m_bShow = true;
}

/**
 * �X�V
 *
 */
void CEnemyShot::Update(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//���x�𗘗p�����ړ�
	m_PosX += m_SpdX;
	m_PosY += m_SpdY;
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
void CEnemyShot::Render(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX,m_PosY);
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