#include "stdafx.h"
#include "One_StageBoss.h"
#include "Bit_Renderer.h"

#include "Alpha_Renderer.h"

One_StageBoss::One_StageBoss()
{
}


One_StageBoss::~One_StageBoss()
{
}

void One_StageBoss::Init()
{
	Bit_Renderer* TR222 = Create_Renderer<Bit_Renderer>(3);
	TR222->Set_Sprite(L"StageBoss_PlayGround.bmp");
	TR222->Pivot({ (float)TR222->size().PartX(), (float)TR222->size().PartY() });

	Alpha_Renderer* p_Render = Create_Renderer<Alpha_Renderer>(50);
	p_Render->Pivot({ 2500, 1200 });
	p_Render->Set_Sprite(L"StageBoss_Front.bmp");
	p_Render->SetAlpha(150);
}