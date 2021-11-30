#pragma once

#include "Mof.h"
#include "GameDefine.h"

class CPipe
{
private:
	bool			m_bRoot;	//TRUE:�s�����ł���
	int				m_InType;	//0 = �y�ǁA1 = �h�A
	int				m_InId;		//�����̃X�e�[�W�C���f�b�N�X
	int				m_InDir;	//�����̕���
	CRectangle		m_In;		//�����͈̔�
	int				m_OutType;	//0 = �y�ǁA1 = �h�A
	int				m_OutId;	//�o���̃X�e�[�W�C���f�b�N�X
	int				m_OutDir;	//�o���̕���
	CRectangle		m_Out;		//�o���͈̔�

public:

	class PipeData {
	public:
		bool			Root;	//�ʍs��
		int				Type;	//0 = �y�ǁA1 = �h�A
		int				Id;		//�X�e�[�W�C���f�b�N�X
		int				Dir;	//����
		CRectangle		Rect;	//�͈�

		PipeData() :
			Root(false),
			Type(0),
			Id(0),
			Dir(0),
			Rect()
		{};

		~PipeData() {};
	};

	CPipe();
	CPipe(bool _bRoot, int _InType, int _InId, int _InDir, CRectangle _In, int _OutType, int _OutId, int _OutDir, CRectangle _Out);
	~CPipe();

	CPipe::PipeData CanToPassThrough(CPipe::PipeData in);

	CPipe::PipeData GetInPipe();

	CPipe::PipeData GetOutPipe();

	void RenderDebug(int id, float wx, float wy);
};

