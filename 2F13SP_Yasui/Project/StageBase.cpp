#include "StageBase.h"

CStageBase::CStageBase()
{
}

CStageBase::~CStageBase()
{
}

bool CStageBase::Load(char* file)
{
	FILE* fp = fopen(file, "rt");
	if (fp == NULL) {
		return false;
	}
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	//�t�@�C���T�C�Y���������������m�ۂ���
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y�������������m��
	char* buffer = (char*)malloc(fSize + 1);
	//�t�@�C�������ׂăo�b�t�@�ɓǂݍ���
	fSize = fread(buffer, 1, fSize, fp);
	buffer[fSize] = '\0';
	char* pstr;
	m_StageCount = atoi(strtok(NULL, ","));




	m_StageTxt = "Stage_Boss.txt";
	if (!m_Stage.Load(m_StageTxt))
	{
		return false;
	}

	return true;
}

void CStageBase::Initialize()
{
	m_Stage.Initialize();
}

void CStageBase::Update()
{
}

void CStageBase::Render()
{
}

void CStageBase::RenderDebug()
{
}

void CStageBase::Release()
{
}
