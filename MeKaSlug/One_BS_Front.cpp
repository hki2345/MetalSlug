#include "stdafx.h"
#include "One_BS_Front.h"
#include "Bit_Renderer.h"

One_BS_Front::One_BS_Front()
{
}


One_BS_Front::~One_BS_Front()
{
}


void One_BS_Front::Init()
{
	Bit_Renderer* MSBG = Create_Renderer<Bit_Renderer>(10);
	MSBG->Pivot({ 400, 50 });
	MSBG->Set_Sprite(L"Barracks_Front.bmp");
}
