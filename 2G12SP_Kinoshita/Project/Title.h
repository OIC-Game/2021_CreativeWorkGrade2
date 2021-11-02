#pragma once

#include "Mof.h"


class CTitle
{
private:
	CTexture   m_BackTexture;
	CTexture   m_PlayerTexture;

	float m_PosX;
	float m_PosY;
	float m_MoveX;
	float m_MoveY;

	int   m_Movetime;

	int          m_Select ;

	CRectangle  m_SrcRect;

	CSpriteMotionController  m_Motion;
	enum tag_MOTION
	{
		MOTION_WAIT,
		MOTION_MOVE,

		MOTION_COUNT,

	};
public:
	CTitle();
	~CTitle();
	void Initalize(void);
	bool Load(void);
	void Update(void);
	void Render();
	void RenderDebug(void);
	void Release(void);
	//int GetNextScene(void) { return m_NextScene; }
	//bool IsEnd(void) { return m_bEnd; }
};

