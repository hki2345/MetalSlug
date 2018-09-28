#include "stdafx.h"
#include "One_NumberFont.h"
#include "Trans_Renderer.h"


One_NumberFont::One_NumberFont() : m_CurValue(0), m_Size(0)
{
}


One_NumberFont::~One_NumberFont()
{
}

size_t One_NumberFont::NumberCounting(size_t _Value)
{
	size_t Count = 0;

	while (_Value /= 10)
	{
		++Count;
	}
	return Count + 1;
}

void One_NumberFont::NumberSpriteSetting()
{
	size_t NumCount = NumberCounting(m_CurValue);

	if (m_Size < NumCount)
	{
		for (size_t i = 0; i < m_Size; i++)
		{
			AllNumber[i]->Set_Sprite(SpriteName.c_str(), 9);
		}
		return;
	}

	size_t Value = m_CurValue;
	std::list<size_t> ListCount;

	int Count = NumCount - 1;

	size_t ValueCount = 1;

	// 6342345
	while (0 < Count)
	{
		ValueCount *= 10;
		--Count;
	}

	// 10 ÀÚ¸®
	for (size_t i = 0; i < m_Size - NumCount; i++)
	{
		AllNumber[i]->BaseSettingSprite(SpriteName.c_str(), 0);
	}

	for (size_t i = m_Size - NumCount; i < m_Size; i++)
	{
		int NumberSpriteIndex = Value / ValueCount;

		Value -= NumberSpriteIndex * ValueCount;
		ValueCount /= 10;

		AllNumber[i]->BaseSettingSprite(SpriteName.c_str(), NumberSpriteIndex);
	}
}

void One_NumberFont::Set_Image(const WCHAR* _pImage)
{
	SpriteName = _pImage;
}

void One_NumberFont::Init_Setting
(size_t _Size, const WCHAR* _pImage, Positionf _StartPos, Sizef _RenderSize)
{
	SpriteName = _pImage;

	m_Size = _Size;

	m_Pos.X = _StartPos.X + (_RenderSize.X / 2);
	m_Pos.Y = _StartPos.Y + (_RenderSize.Y / 2);

	float NumSize = _RenderSize.X / (float)_Size;

	AllNumber.reserve(_Size);

	for (size_t i = 0; i < m_Size; i++)
	{
		Trans_Renderer* pWork = Create_Renderer<Trans_Renderer>(50);

		pWork->Pivot(Positionf{ i * NumSize - (_RenderSize.X * 0.5f - NumSize * 0.5f) ,0.0f });
		pWork->size(Position{ (int)(NumSize), (int)_RenderSize.Y });
		AllNumber.push_back(pWork);
	}


	for (size_t i = 0; i < m_Size; i++)
	{
		AllNumber[i]->BaseSettingSprite(SpriteName.c_str(), 0);
	}
}


void One_NumberFont::Set_TransColor(const UINT& _Value)
{
	for (size_t i = 0; i < AllNumber.size(); i++)
	{
		AllNumber[i]->Set_TransColor(_Value);
	}
}