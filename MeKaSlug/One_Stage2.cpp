#include "stdafx.h"
#include "One_Stage2.h"
#include "Bit_Renderer.h"


One_Stage2::One_Stage2()
{
}


One_Stage2::~One_Stage2()
{
}


void One_Stage2::Init()
{
	Bit_Renderer* TR222 = Create_Renderer<Bit_Renderer>(3);
	TR222->Set_Sprite(L"Stage2_PlayGround.bmp");
	TR222->Pivot({ (float)TR222->size().PartX(), (float)TR222->size().PartY()});
}