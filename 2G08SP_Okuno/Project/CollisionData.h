#pragma once

class CCollisionData {
public:
	bool		damage; //�_���[�W���󂯂邩�ǂ���
	float		ox; //�������̖��܂�
	float		oy; //�c�����̖��܂�
	bool		og; //�ڒn��Ԃ��ǂ���
	bool		unfallleftflg; //�񗎉��ړ��p�t���O
	bool		unfallrightflg; //�񗎉��ړ��p�t���O

	CCollisionData() :
		damage(false),
		ox(0),
		oy(0),
		og(false),
		unfallleftflg(false),
		unfallrightflg(false)
	{
	}

	~CCollisionData() {
	}
};