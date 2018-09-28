#include "stdafx.h"
#include "One_BS_Select_Leona.h"
#include "Bit_Renderer.h"

One_BS_Select_Leona::One_BS_Select_Leona()
{
}


One_BS_Select_Leona::~One_BS_Select_Leona()
{
}

void One_BS_Select_Leona::Init()
{
	Bit_Renderer* MSBG = Create_Renderer<Bit_Renderer>(6);
	MSBG->Set_Sprite(L"Select_Character_Leona.bmp");
	m_Pos = { 552, 289 };
}
