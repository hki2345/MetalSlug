#pragma once
// 이미지와 스프라이트는 통합하여 관리
// 이미지나 그 이미지를 어느 부분만 보겠다는 것 자체가 같은 맥락
// 따라서 트렌스나 그냥 찍어내는 거나 같기 떄문에 따로 클래스를 만들지 않고
// 기존 클래스를 스프라이트로 대체하면서 찍는 식으로 간다.
#include "Image.h"

class Sprite : public Begin
{
private:
	// 무슨 이미지를
	// 얼마만큼 자를 것인가.
	Image*	m_p_Image;
	Rect	m_Rect;

public:
	Rect&	rect()				{ return m_Rect; }
	void	rect(Rect _Rect)	{ m_Rect = _Rect; }

	HDC&	GetDc()			{ return m_p_Image->GetDc(); }
	Image*	Get_Img()		{ return m_p_Image; }
	Sizef	size()			{ return m_Rect.Size; }
	int		Width()			{ return m_Rect.Size.X; }
	int		Height()		{ return m_Rect.Size.Y;}
	void	Width(int _X)	{ m_Rect.Size.X = _X; }
	void	Height(int _Y)	{ m_Rect.Size.Y = _Y; }

	inline UINT&	Set_TransColor()						{ return m_p_Image->Set_TransColor(); }
	inline void		Set_TransColor(const UINT& _Value)		{ m_p_Image->Set_TransColor(_Value); }

public:
	Sprite(Image* _Img, Rect _Rect);
	~Sprite();
};

