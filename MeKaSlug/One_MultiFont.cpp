#include "stdafx.h"
#include "One_MultiFont.h"
#include "Trans_Renderer.h"


One_MultiFont::One_MultiFont() : m_Letter_Space(0)
{
}


One_MultiFont::~One_MultiFont()
{
}

void One_MultiFont::String_SpriteSetting()
{
	size_t NumCount = m_String.size();
	
	for (size_t i = 0; i < m_String_Size; i++)
	{
		size_t NumberSpriteIndex = 0;

		// 숫자
		if (m_String[i] == '0') { NumberSpriteIndex = 0; }
		else  if (m_String[i] == '1') { NumberSpriteIndex = 1; }
		else  if (m_String[i] == '2') { NumberSpriteIndex = 2; }
		else  if (m_String[i] == '3') { NumberSpriteIndex = 3; }
		else  if (m_String[i] == '4') { NumberSpriteIndex = 4; }
		else  if (m_String[i] == '5') { NumberSpriteIndex = 5; }
		else  if (m_String[i] == '6') { NumberSpriteIndex = 6; }
		else  if (m_String[i] == '7') { NumberSpriteIndex = 7; }
		else  if (m_String[i] == '8') { NumberSpriteIndex = 8; }
		else  if (m_String[i] == '9') { NumberSpriteIndex = 9; }

		// 대소문자 복합문자
		else  if (m_String[i] == 'A' || m_String[i] == 'a') { NumberSpriteIndex = 10; }
		else  if (m_String[i] == 'B' || m_String[i] == 'b') { NumberSpriteIndex = 11; }
		else  if (m_String[i] == 'C' || m_String[i] == 'c') { NumberSpriteIndex = 12; }
		else  if (m_String[i] == 'D' || m_String[i] == 'd') { NumberSpriteIndex = 13; }
		else  if (m_String[i] == 'E' || m_String[i] == 'e') { NumberSpriteIndex = 14; }
		else  if (m_String[i] == 'F' || m_String[i] == 'f') { NumberSpriteIndex = 15; }
		else  if (m_String[i] == 'G' || m_String[i] == 'g') { NumberSpriteIndex = 16; }
		else  if (m_String[i] == 'H' || m_String[i] == 'h') { NumberSpriteIndex = 17; }
		else  if (m_String[i] == 'I' || m_String[i] == 'i') { NumberSpriteIndex = 18; }
		else  if (m_String[i] == 'J' || m_String[i] == 'j') { NumberSpriteIndex = 19; }
		else  if (m_String[i] == 'K' || m_String[i] == 'k') { NumberSpriteIndex = 20; }
		else  if (m_String[i] == 'L' || m_String[i] == 'l') { NumberSpriteIndex = 21; }
		else  if (m_String[i] == 'M' || m_String[i] == 'm') { NumberSpriteIndex = 22; }
		else  if (m_String[i] == 'N' || m_String[i] == 'n') { NumberSpriteIndex = 23; }
		else  if (m_String[i] == 'O' || m_String[i] == 'o') { NumberSpriteIndex = 24; }
		else  if (m_String[i] == 'P' || m_String[i] == 'p') { NumberSpriteIndex = 25; }
		else  if (m_String[i] == 'Q' || m_String[i] == 'q') { NumberSpriteIndex = 26; }
		else  if (m_String[i] == 'R' || m_String[i] == 'r') { NumberSpriteIndex = 27; }
		else  if (m_String[i] == 'S' || m_String[i] == 's') { NumberSpriteIndex = 28; }
		else  if (m_String[i] == 'T' || m_String[i] == 't') { NumberSpriteIndex = 29; }
		else  if (m_String[i] == 'U' || m_String[i] == 'u') { NumberSpriteIndex = 30; }
		else  if (m_String[i] == 'V' || m_String[i] == 'v') { NumberSpriteIndex = 31; }
		else  if (m_String[i] == 'W' || m_String[i] == 'w') { NumberSpriteIndex = 32; }
		else  if (m_String[i] == 'X' || m_String[i] == 'x') { NumberSpriteIndex = 33; }
		else  if (m_String[i] == 'Y' || m_String[i] == 'y') { NumberSpriteIndex = 34; }
		else  if (m_String[i] == 'Z' || m_String[i] == 'z') { NumberSpriteIndex = 35; }
		
		
		else  if (m_String[i] == '=') { NumberSpriteIndex = 36; }

		// 특수 문자
		else  if (m_String[i] == '<') { NumberSpriteIndex = 36; }
		else  if (m_String[i] == '>') { NumberSpriteIndex = 37; }
		else  if (m_String[i] == '?') { NumberSpriteIndex = 38; }

		//// 소문자 - 노가다 코드 (두번쓰기 싫어서ㅠㅠ)
		//else  if (m_String[i] == 'a') { NumberSpriteIndex = 36; }
		//else  if (m_String[i] == 'b') { NumberSpriteIndex = 37; }
		//else  if (m_String[i] == 'c') { NumberSpriteIndex = 38; }
		//else  if (m_String[i] == 'd') { NumberSpriteIndex = 39; }
		//else  if (m_String[i] == 'e') { NumberSpriteIndex = 40; }
		//else  if (m_String[i] == 'f') { NumberSpriteIndex = 41; }
		//else  if (m_String[i] == 'g') { NumberSpriteIndex = 42; }
		//else  if (m_String[i] == 'h') { NumberSpriteIndex = 43; }
		//else  if (m_String[i] == 'i') { NumberSpriteIndex = 44; }
		//else  if (m_String[i] == 'j') { NumberSpriteIndex = 45; }
		//else  if (m_String[i] == 'k') { NumberSpriteIndex = 46; }
		//else  if (m_String[i] == 'l') { NumberSpriteIndex = 47; }
		//else  if (m_String[i] == 'm') { NumberSpriteIndex = 48; }
		//else  if (m_String[i] == 'n') { NumberSpriteIndex = 49; }
		//else  if (m_String[i] == 'o') { NumberSpriteIndex = 50; }
		//else  if (m_String[i] == 'p') { NumberSpriteIndex = 51; }
		//else  if (m_String[i] == 'q') { NumberSpriteIndex = 52; }
		//else  if (m_String[i] == 'r') { NumberSpriteIndex = 53; }
		//else  if (m_String[i] == 's') { NumberSpriteIndex = 54; }
		//else  if (m_String[i] == 't') { NumberSpriteIndex = 55; }
		//else  if (m_String[i] == 'u') { NumberSpriteIndex = 56; }
		//else  if (m_String[i] == 'v') { NumberSpriteIndex = 57; }
		//else  if (m_String[i] == 'w') { NumberSpriteIndex = 58; }
		//else  if (m_String[i] == 'x') { NumberSpriteIndex = 59; }
		//else  if (m_String[i] == 'y') { NumberSpriteIndex = 60; }
		//else  if (m_String[i] == 'z') { NumberSpriteIndex = 61; }

		m_vec_AllData[i]->BaseSettingSprite(SpriteName.c_str(), NumberSpriteIndex);
	}
}

void One_MultiFont::Set_Image(const WCHAR* _pImage)
{
	SpriteName = _pImage;
}

void One_MultiFont::Init_Setting
(size_t _Size, const WCHAR* _pImage, 
	Positionf _StartPos, Sizef _RenderSize, const int& _Space/* = 0*/)
{
	SpriteName = _pImage;

	m_String_Size = _Size;
	m_Letter_Space = _Space;

	m_Pos.X = _StartPos.X + (_RenderSize.X / 2);
	m_Pos.Y = _StartPos.Y + (_RenderSize.Y / 2);

	float NumSize = _RenderSize.X / (float)_Size;

	m_vec_AllData.reserve(_Size);

	for (size_t i = 0; i < m_String_Size; i++)
	{
		Trans_Renderer* pWork = Create_Renderer<Trans_Renderer>(50);

		pWork->Pivot(Positionf{ i * NumSize - (_RenderSize.X * 0.5f - NumSize * 0.5f) ,0.0f });
		pWork->size(Position{ (int)(NumSize) + m_Letter_Space, (int)_RenderSize.Y + m_Letter_Space });
		m_vec_AllData.push_back(pWork);
	}

	// 일단 0으로 초기화
	for (size_t i = 0; i < m_String_Size; i++)
	{
		m_vec_AllData[i]->BaseSettingSprite(SpriteName.c_str(), 0);
	}
}

void One_MultiFont::Set_TransColor(const UINT& _Value)
{
	for (size_t i = 0; i < m_vec_AllData.size(); i++)
	{
		m_vec_AllData[i]->Set_TransColor(_Value);
	}
}