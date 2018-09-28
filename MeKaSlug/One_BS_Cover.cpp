#include "stdafx.h"
#include "One_BS_Cover.h"
#include "Alpha_Renderer.h"

One_BS_Cover::One_BS_Cover() : AlphaTime(.0f), AlphaSpeed(.0f)
{
}


One_BS_Cover::~One_BS_Cover()
{
}

void One_BS_Cover::Init()
{
	BSC = Create_Renderer<Alpha_Renderer>(100);
	BSC->Pivot({ 400, 300 });
	BSC->Set_Sprite(L"Barracks_Cover.bmp");
	BSC->size({800,600});
	BSC->SetAlpha(255);

	AlphaSpeed = .8f;
	AlphaTime = .0f;
	Alpha = 255;

	FadeCheck = false;
	Fade = false;
}

void One_BS_Cover::Init_FadeIn(const bool& _End)
{
	// 마지막 장면에서 쓰임
	if (true == _End)
	{
		m_Pos = m_MotherOfTheOne->CameraIntPos();
	}

	AlphaTime = .0f;
	Alpha = 0;

	FadeCheck = false;
	Fade = true;
}


void One_BS_Cover::Init_FadeOut()
{
	AlphaTime = .0f;
	Alpha = 255;

	FadeCheck = false;
	Fade = false;
}


void One_BS_Cover::Update()
{
	if (false == Fade)
	{
		if (Alpha < 0) { FadeCheck = true; }
		AlphaTime += DELTATIME;

		Alpha -= (int)(AlphaTime * AlphaSpeed);

		BSC->SetAlpha(Alpha);
	}

	else if (true == Fade)
	{
		if (Alpha > 255) { FadeCheck = true; }
		AlphaTime += DELTATIME;

		Alpha += (int)(AlphaTime * AlphaSpeed);

		BSC->SetAlpha(Alpha);
	}
}