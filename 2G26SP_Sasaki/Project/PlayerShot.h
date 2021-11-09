#pragma once

#include	"Mof.h"

//移動速度
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

	//初期化処理
	void Initialize(void);

	//弾発射処理
	void Fire(float px,float py);

	//弾移動等の更新処理
	void Update(void);

	//弾描画処理
	void Render(void);

	//弾デバッグ描画処理
	void RenderDebug(void);

	//弾のテクスチャを設定
	void SetTexture(CTexture* pt){ m_pTexture = pt; }

	void SetPlayerShotColor(int pc) { m_pShotColor = pc; }

	//void SetShotColor(int* co) { m_pShotColor; }

	//弾が表示されている場合trueを返す
	bool GetShow(void){ return m_bShow; }

	//弾の表示状態を設定する
	void SetShow(bool bs){ m_bShow = bs; }

	//弾の色を返す
	int GetPlayerColorShow() { return m_pShotColor; }

	//弾の矩形を返す
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight()); }

	
};