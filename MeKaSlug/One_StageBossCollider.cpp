#include "stdafx.h"
#include "One_StageBossCollider.h"
#include "Bit_Renderer.h"


One_StageBossCollider::One_StageBossCollider()
{
}


One_StageBossCollider::~One_StageBossCollider()
{
}

void One_StageBossCollider::Init()
{
	Bit_Renderer* TR222 = Create_Renderer<Bit_Renderer>(3);
	TR222->Set_Sprite(L"StageBoss_Collider.bmp");
	TR222->Pivot({ (float)TR222->size().PartX(), (float)TR222->size().PartY() });
}