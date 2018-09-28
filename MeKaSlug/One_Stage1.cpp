#include "stdafx.h"

#include "Bit_Renderer.h"
#include "Trans_Renderer.h"

#include "One_Stage1.h"


One_Stage1::One_Stage1()
{
}


One_Stage1::~One_Stage1()
{
}

void One_Stage1::Init()
{
	Bit_Renderer* TR222 = Create_Renderer<Bit_Renderer>(3);
	TR222->Set_Sprite(L"Stage1_PlayGround.bmp");
	TR222->Pivot({ (float)TR222->size().PartX(), (float)TR222->size().PartY() });

	// Àå½Ä
	Trans_Renderer* TR2 = Create_Renderer<Trans_Renderer>(20);
	TR2->Set_Sprite(L"Stage1_Front.bmp");
	TR2->Pivot({ (float)TR2->size().PartX(), 740 });
	TR2->Set_TransColor(VIOLET);
}
