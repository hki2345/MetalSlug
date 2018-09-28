#include "stdafx.h"
#include "One_BS_Pinset.h"
#include "Trans_Renderer.h"


One_BS_Pinset::One_BS_Pinset()
{
}


One_BS_Pinset::~One_BS_Pinset()
{
}



void One_BS_Pinset::Init()
{
	Trans_Renderer* MSBG = Create_Renderer<Trans_Renderer>(8);
	m_Pos = { 550, 70 };
	MSBG->Set_Sprite(L"BS_Pinset.bmp");
	MSBG->Set_TransColor(VIOLET);
	MSBG->size({50, 50});
}
void One_BS_Pinset::Update(const float& _X)
{
	m_Pos = { _X, m_Pos.Y };
}