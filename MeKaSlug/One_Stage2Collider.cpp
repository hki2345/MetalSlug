#include "stdafx.h"
#include "One_Stage2Collider.h"
#include "Bit_Renderer.h"


One_Stage2Collider::One_Stage2Collider()
{
}


One_Stage2Collider::~One_Stage2Collider()
{
}


void One_Stage2Collider::Init()
{
	Bit_Renderer* TR222 = Create_Renderer<Bit_Renderer>(3);
	TR222->Set_Sprite(L"Stage2_Collider.bmp");
	TR222->Pivot({ (float)TR222->size().PartX(), (float)TR222->size().PartY()});
}