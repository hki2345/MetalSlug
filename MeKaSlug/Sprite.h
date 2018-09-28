#pragma once
// �̹����� ��������Ʈ�� �����Ͽ� ����
// �̹����� �� �̹����� ��� �κи� ���ڴٴ� �� ��ü�� ���� �ƶ�
// ���� Ʈ������ �׳� ���� �ų� ���� ������ ���� Ŭ������ ������ �ʰ�
// ���� Ŭ������ ��������Ʈ�� ��ü�ϸ鼭 ��� ������ ����.
#include "Image.h"

class Sprite : public Begin
{
private:
	// ���� �̹�����
	// �󸶸�ŭ �ڸ� ���ΰ�.
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

