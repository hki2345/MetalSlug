#include "stdafx.h"
#include "One_BS_Select_Eri.h"
#include "Bit_Renderer.h"


One_BS_Select_Eri::One_BS_Select_Eri()
{
}


One_BS_Select_Eri::~One_BS_Select_Eri()
{
}



void One_BS_Select_Eri::Init()
{
	Bit_Renderer* MSBG = Create_Renderer<Bit_Renderer>(6);
	MSBG->Set_Sprite(L"Select_Character_Eri.bmp");
	
	
	m_Pos = { 258, 280 };
}
