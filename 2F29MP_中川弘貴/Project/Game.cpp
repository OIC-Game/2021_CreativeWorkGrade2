#include	"Game.h"

//�ύX����V�[��(�O���Q��)
extern int		gChangeScene;

/*
  �R���X�g���N�^
*/
CGame::CGame() {

}

/*
  �f�X�g���N�^
*/
CGame::~CGame() {

}

/*
  �ǂݍ���
*/
void CGame::Load(void)
{
	pl.Load();
	ai.Load();
}


/*
  ������
*/
void CGame::Initialize(bool vsAiFlg)
{
	pl.Initialize(false);
	if (vsAiFlg)
	{
		ai.Initialize(true);
	}
}

/*
  �X�V
*/
void CGame::Update(bool vsAiFlg)
{
	pl.Update(false);
	if (vsAiFlg)
	{
		ai.Update(true);
	}
}

/*
  �`��
*/
void CGame::Render(bool vsAiFlg)
{
	pl.Render(false);
	if (vsAiFlg)
	{
		ai.Render(true);
	}
}

/*
  ���
*/
void CGame::Release(void)
{
	pl.Release();
	ai.Release();
}