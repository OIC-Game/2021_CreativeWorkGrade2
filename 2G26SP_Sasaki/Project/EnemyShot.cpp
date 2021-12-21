#include	"EnemyShot.h"

/**
 * �R���X�g���N�^
 *
 */
CEnemyShot::CEnemyShot() :
m_pTexture(NULL) ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_Speed(0.0f) ,
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
	m_Speed = 0;
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
void CEnemyShot::Fire(float px,float py,float spd,int type){
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py;
	m_Speed = spd;
	m_ShotType = type;
	m_bShow = true;
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

	//���x�𗘗p�����ړ�
	if (m_ShotType == 0)
	{
		m_PosX += 0;
		m_PosY += m_Speed;
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