#pragma once

#include	"Mof.h"

//�ړ����x
#define		PLAYERSHOT_SPEED		6

class CPlayerShot {
private:
	CTexture*				m_pTexture;
	float					m_PosX;
	float					m_PosY;
	bool					m_bShow;
	int						m_pShotColor;
public:
	CPlayerShot();
	~CPlayerShot();

	//����������
	void Initialize(void);

	//�e���ˏ���
	void Fire(float px,float py);

	//�e�ړ����̍X�V����
	void Update(void);

	//�e�`�揈��
	void Render(void);

	//�e�f�o�b�O�`�揈��
	void RenderDebug(void);

	//�e�̃e�N�X�`����ݒ�
	void SetTexture(CTexture* pt){ m_pTexture = pt; }

	void SetShotColor(int* co) { m_pShotColor; }

	//�e���\������Ă���ꍇtrue��Ԃ�
	bool GetShow(void){ return m_bShow; }

	//Chapter7-8�Œǉ�
	//�e�̕\����Ԃ�ݒ肷��
	void SetShow(bool bs){ m_bShow = bs; }

	//�e�̋�`��Ԃ�
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight()); }

	
};