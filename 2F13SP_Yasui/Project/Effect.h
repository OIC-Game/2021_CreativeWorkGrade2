#pragma once
#include "Mof.h"

enum tag_EFFECTTYPE
{
	EFFECT_EXPLOSITON,

	EFFECT_TYPECOUNT,
};

class CEffect
{
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	CRectangle				m_SrcRect;
	CVector2				m_Position;
	bool					m_ShowFlg;
	float					m_Scale;
public:
	CEffect();
	~CEffect();
	void Initialize(int type);
	void Start(CVector2 pos,float scale);
	void Update(void);
	void Render(Vector2 scroll);
	void RenderDebug();
	void Release(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow() { return m_ShowFlg; }
};

