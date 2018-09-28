#include "stdafx.h"
#include "Core.h"
#include "One_BackGround.h"
#include "Bit_Renderer.h"


One_BackGround::One_BackGround() :TitleTime(.0f), PlayTime(.0f)
{
	TitleTime = .05f;
}


One_BackGround::~One_BackGround()
{
}

void One_BackGround::Init()
{
	TitleArray = Create_Renderer<Bit_Renderer>(6);
	TitleArray->Pivot({400, 300});
	TitleArray->Set_Sprite(L"1.bmp");
}

void One_BackGround::Update()
{
	PlayTime += DELTATIME;
	if (PlayTime > TitleTime)
	{
		PlayTime = .0f;
	}
	else 
	{
		return;
	}
	if (TitleCnt >= 57)
	{
		TitleCnt = 0;
	}

	WCHAR Num_Char[10];

	_itow_s(TitleCnt, Num_Char, 10);
	std::wstring Num_str = Num_Char;

	Num_str += L".bmp";
	TitleArray->Set_Sprite(Num_str.c_str());
	TitleCnt++;

}