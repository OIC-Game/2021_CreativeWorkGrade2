#pragma once

#include "Mof.h"
#include "GameDefine.h"

class CPipe
{
private:
	bool			m_bRoot;	//TRUE:行き来できる
	int				m_InId;		//入口のステージインデックス
	int				m_InDir;	//入口の方向:0=↑、1=→、2=↓、3=←
	CRectangle		m_In;		//入口の範囲
	int				m_OutId;	//出口のステージインデックス
	int				m_OutDir;	//出口の方向
	CRectangle		m_Out;		//出口の範囲

public:

	class PipeData {
	public:
		bool			Root;	//通行可否
		int				Id;		//ステージインデックス
		int				Dir;	//方向
		CRectangle		Rect;	//範囲

		PipeData() :
			Root(false),
			Id(0),
			Dir(0),
			Rect()
		{};

		~PipeData() {};
	};

	CPipe();
	CPipe(bool _bRoot, int _InId, int _InDir, CRectangle _In, int _OutId, int _OutDir, CRectangle _Out);
	~CPipe();

	CPipe::PipeData CanToPassThrough(CPipe::PipeData in);

	void RenderDebug(int id, float wx, float wy);
};

