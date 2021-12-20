#include	"Game.h"

//変更するシーン(外部参照)
extern int		gChangeScene;

/*
  コンストラクタ
*/
CGame::CGame() {

}

/*
  デストラクタ
*/
CGame::~CGame() {

}

/*
  読み込み
*/
void CGame::Load(void)
{
	pl.Load();
	ai.Load();
}


/*
  初期化
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
  更新
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
  描画
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
  解放
*/
void CGame::Release(void)
{
	pl.Release();
	ai.Release();
}