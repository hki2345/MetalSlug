#include "stdafx.h"
#include "One_MS_BackGround.h"
#include "Bit_Renderer.h"


One_MS_BackGround::One_MS_BackGround()
{
}


One_MS_BackGround::~One_MS_BackGround()
{
}



void One_MS_BackGround::Init()
{
	Bit_Renderer* MSBG = Create_Renderer<Bit_Renderer>(6);
	MSBG->Pivot({ 400, 300 });
	MSBG->Set_Sprite(L"Military_System_BackGround.bmp");
}
