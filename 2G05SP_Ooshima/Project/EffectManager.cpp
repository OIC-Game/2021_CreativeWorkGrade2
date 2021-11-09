#include	"EffectManager.h"

/**
 * コンストラクタ
 *
 */
CEffectManager::CEffectManager() {
}

/**
 * デストラクタ
 *
 */
CEffectManager::~CEffectManager(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CEffectManager::Load(void){
	//エフェクトの名前
	char* name[] = {
		"effect01.png",
		"effect02.png",
		"effect03.png",
	};
	for ( int i = 0; i < EFC_TYPECOUNT; i++ )
	{
		if (!m_Texture[i].Load(name[i]))
		{
			return false;
		}
	}
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 */
void CEffectManager::Initialize(void){
	//エフェクトの基礎設定
	for(int j = 0;j < EFC_TYPECOUNT;j++)
	{
		for(int i = 0;i < EFFECTCOUNT;i++)
		{
			m_Effect[i][j].SetTexture(&m_Texture[j]);
			m_Effect[i][j].Initialize(j);
		}
	}
}

/**
 * 開始
 * 座標を設定してモーションを開始する。
 *
 * 引数
 * [in]			px					X座標
 * [in]			py					Y座標
 * [in]			type				エフェクトタイプ
 */
CEffect* CEffectManager::Start(float px,float py,int type){
	for ( int i = 0; i < EFFECTCOUNT; i++ )
	{
		//未使用のエフェクトかどうか確認
		if (m_Effect[i][type].GetShow())
		{
			continue;
		}
		//エフェクトのStartを呼び出す
		m_Effect[i][type].Start(px, py);
		//開始したエフェクトのポインタを返す
		return&m_Effect[i][type];
	}
	return NULL;
}

/**
 * 更新
 *
 */
void CEffectManager::Update(void){
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Update();
		}
	}
}

/**
 * 描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CEffectManager::Render(float wx,float wy){
	for(int j = 0;j < EFC_TYPECOUNT;j++)
	{
		for(int i = 0;i < EFFECTCOUNT;i++)
		{
			m_Effect[i][j].Render(wx,wy);
		}
	}
}


/**
 * デバッグ描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CEffectManager::RenderDebug(float wx,float wy){
	for(int j = 0;j < EFC_TYPECOUNT;j++)
	{
		for(int i = 0;i < EFFECTCOUNT;i++)
		{
			m_Effect[i][j].RenderDebug(wx,wy);
		}
	}
}

/**
 * 解放
 *
 */
void CEffectManager::Release(void){
	for(int j = 0;j < EFC_TYPECOUNT;j++)
	{
		for(int i = 0;i < EFFECTCOUNT;i++)
		{
			m_Effect[i][j].Release();
		}
		m_Texture[j].Release();
	}
}
