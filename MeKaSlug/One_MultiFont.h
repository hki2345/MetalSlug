#pragma once
#include <vector>
#include "TheOne.h"


class Trans_Renderer;
class One_MultiFont : public TheOne
{
private:
	int m_Letter_Space;
	size_t m_String_Size;
	std::wstring m_String;

	std::wstring SpriteName;
	std::vector<Trans_Renderer*> m_vec_AllData;

private:
	void String_SpriteSetting();

public:
	void Set_String(const WCHAR* _CurValue)
	{
		m_String = _CurValue;
		String_SpriteSetting();
	}

	void Set_TransColor(const UINT& _Value);
	void Set_Image(const WCHAR* _pImage);
	void Init_Setting(size_t _Size, const WCHAR* _pImage, 
		Positionf _StartPos, Sizef _RenderSize, const int& _Space = 0);

public:
	One_MultiFont();
	~One_MultiFont();
};

