#pragma once
#include <vector>
#include "TheOne.h"

class Trans_Renderer;
class One_NumberFont : public TheOne
{
	private:
		size_t m_Size;
		size_t m_CurValue;

		std::wstring SpriteName;
		std::vector<Trans_Renderer*> AllNumber;

	private:
		size_t NumberCounting(size_t _Value);
		void NumberSpriteSetting();

	public:
		void Set_Number(size_t _CurValue) {
			m_CurValue = _CurValue;
			NumberSpriteSetting();
		}
		void Set_TransColor(const UINT& _Value);

	public:
		void Set_Image(const WCHAR* _pImage);
		void Init_Setting(size_t _Size, const WCHAR* _pImage, Positionf _StartPos, Sizef _RenderSize);

public:
	One_NumberFont();
	~One_NumberFont();
};

