#include	"PlayerShot.h"

/**
 * �R���X�g���N�^
 *
 */
CPlayerShot::CPlayerShot() :
m_pTexture(NULL) ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bShow(false) {
}

/**
 * �f�X�g���N�^
 *
 */
CPlayerShot::~CPlayerShot(){
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 */
void CPlayerShot::Initialize(void){
	m_PosX = 0;
	m_PosY = 0;
	m_bShow = false;
}
/**
 * ����
 * �����̍��W�Ɉʒu��ݒ肵�āA�\���t���O��true�ɕύX����B
 *
 * ����
 * [in]			px				���˂w���W
 * [in]			py				���˂x���W
 */
void CPlayerShot::Fire(float px,float py){
	m_PosX = px - m_pTexture->GetWidth() * 0.5f;
	m_PosY = py;
	m_bShow = true;
}

/**
 * �X�V
 *
 */
void CPlayerShot::Update(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//��Ɉړ�
	m_PosY -= PLAYERSHOT_SPEED;
	//��ʏ�iY:0�j����ŏ���
	if(m_PosY + m_pTexture->GetHeight() < 0)
	{
		m_bShow = false;
	}
}

/**
 * �`��
 *
 */
void CPlayerShot::Render(void){
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
void CPlayerShot::RenderDebug(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CGraphicsUtilities::RenderRect(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight(),MOF_XRGB(0,255,0));
}