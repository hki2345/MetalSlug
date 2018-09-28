#include "stdafx.h"
#include "One_BS_BackGround.h"
#include "Bit_Renderer.h"


One_BS_BackGround::One_BS_BackGround()
{
}


One_BS_BackGround::~One_BS_BackGround()
{
}



void One_BS_BackGround::Init()
{
	Bit_Renderer* MSBG = Create_Renderer<Bit_Renderer>(6);
	MSBG->Pivot({ 400, 300 });
	MSBG->Set_Sprite(L"Barracks_BackGround.bmp");
}
