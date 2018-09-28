#include "stdafx.h"
#include "One_EndBG.h"
#include "Bit_Renderer.h"

#include "ResourceManager.h"

One_EndBG::One_EndBG()
{
}


One_EndBG::~One_EndBG()
{
}

void One_EndBG::Init()
{

	Bit_Renderer* TitleArray = Create_Renderer<Bit_Renderer>(6);
	TitleArray->Pivot({ 400, 300 });
	TitleArray->Set_Sprite(L"End.bmp");
}