#pragma once

#include "Mof.h"

class COption
{
	
	private:
		bool	m_bEnd;
		int		m_NextScene;
		CTexture  optionTexture;
	public:
		COption();
		~COption();
		bool Load(void);
		void Initialize(void);
		void Update(void);
		void Render(void);
		void Relase(void);
		

};

