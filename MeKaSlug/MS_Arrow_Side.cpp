#include "stdafx.h"
#include "MS_Arrow_Side.h"
#include "Trans_Renderer.h"

MS_Arrow_Side::MS_Arrow_Side() : TargetUI(nullptr), Speed(200.0f), In(false)
{
}


MS_Arrow_Side::~MS_Arrow_Side()
{
}

void MS_Arrow_Side::Init()
{
	ArrowRIght = Create_Renderer<Trans_Renderer>(6);
	ArrowRIght->Set_Sprite(L"Arrow_Right_Side.bmp");
	ArrowRIght->Set_TransColor(VIOLET);
	ArrowRIght->size({ 64, 39 });
	ArrowRIght->Pivot({ 300, 0  });

	ArrowLeft = Create_Renderer<Trans_Renderer>(6);
	ArrowLeft->Set_Sprite(L"Arrow_Left_Side.bmp");
	ArrowLeft->Set_TransColor(VIOLET);
	ArrowLeft->size({ 64, 39 });
	ArrowLeft->Pivot({-300, 0});

	m_Pos = {-100, -100};
}

void MS_Arrow_Side::Update()
{
	if (nullptr != TargetUI)
	{
		if (350 < ArrowRIght->Pivot().X)
		{
			In = true;
		}
		else if (300 > ArrowRIght->Pivot().X)
		{
			In = false;
		}

		if (true == In)
		{
			ArrowRIght->Pivot({ ArrowRIght->Pivot().X - Speed * DELTATIME, 0 });
			ArrowLeft->Pivot({ ArrowLeft->Pivot().X + Speed * DELTATIME, 0 });
		}
		else
		{
			ArrowRIght->Pivot({ ArrowRIght->Pivot().X + Speed * DELTATIME, 0 });
			ArrowLeft->Pivot({ ArrowLeft->Pivot().X - Speed * DELTATIME, 0 });
		}
	}
}