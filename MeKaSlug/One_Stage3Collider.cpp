#include "stdafx.h"
#include "One_Stage3Collider.h"
#include "Bit_Renderer.h"


One_Stage3Collider::One_Stage3Collider()
{
}


One_Stage3Collider::~One_Stage3Collider()
{
}


void One_Stage3Collider::Init()
{
	Bit_Renderer* TR222 = Create_Renderer<Bit_Renderer>(3);
	TR222->Set_Sprite(L"Stage3_Collider.bmp");
	TR222->Pivot({ (float)TR222->size().PartX(), (float)TR222->size().PartY() });
}