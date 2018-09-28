#include "stdafx.h"

#include "Bit_Renderer.h"
#include "Trans_Renderer.h"

#include "One_Stage1Collider.h"


One_Stage1Collider::One_Stage1Collider()
{
}


One_Stage1Collider::~One_Stage1Collider()
{
}

void One_Stage1Collider::Init()
{
	Bit_Renderer* TR222 = Create_Renderer<Bit_Renderer>(3);
	TR222->Set_Sprite(L"Stage1_Collider.bmp");
	TR222->Pivot({ (float)TR222->size().PartX(), (float)TR222->size().PartY() });
}
