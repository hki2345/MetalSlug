#pragma once
#include "Begin.h"
#include "MatrixInfo.h"

#pragma region 샘 주석
// HDC는 WINAPI에서 기본적으로 지원하는 이미지 데이터 형식이다.
// WINDOW의 HDC 이녀석은
// HDC안에는 여러가지 정보가 들어가 있다.
// HDC는 도화지기 때문에
// WINAPI로 순수하게 이미지를 로드하면
// 그녀석도 HDC화 된다.
// 화면 전체의 픽셀.

// 이미지를 로드하게 되면
// 그래서 HDC 내부에 들고 있는 정보들이 많다.
// 픽셀당 색상 크기
// 자신의 크기
// 이미지가 HDC화 된다.

// 여기서 불러올 이미지에 대한 HBITMAP가 불러와지면서 이전에 들고있던 기본 데이터들이
// 남게되는데 이를 제거하는 것까지 해야 완벽하다고 할 수 있겟다.
// 따라서 이를 받는 HBITMAP핸들도 따로 메모리 내 잠시 저장해 두어야한다. -> 이것까지 지우기 위해
#pragma endregion



class Image : public Begin
{
public:
	friend class ResourceManager;

private:
	// 이미지가 그려질 HDC -> 스티커 개념
	HDC		m_this_HDC;

	// 불러와질 HBITMAP
	HBITMAP m_HBitMap;
	
	// 이전에 m_load_BitMap이 들고 있던 기본 데이터가 여기에 옮겨질 예정
	// 지울 떄 필요
	HBITMAP m_prev_BitMap;

	// 진짜 비트맵 데이터 -> 구조체
	BITMAP	m_BitMap;



	// 255, 255, 255, 255 데이터를 4바이트로 환산하여 저장한다.
	// 따라서 자료형 Int가 채택되는 것이며,
	// 사실 4바이트 자료형 float, __int32 등 4바이트면 다 된다.
	UINT m_TransData;
	
	// 이 이미지에 알파가 있는지 체크 -> 그리지 않음
	bool m_Alpha;

	// 사이즈로 해당 크기 만큼의 이미지를 만든다 -> 화면 크기의 이미지를 만들어
	// 거기에 찍어내기 위함
	HDC& Create_Image(const Size _Size);
	bool Load(const WCHAR* _Path);
	void ImgSize();


	// 테스트를 위한 공개 혹은 다른 의미-> 는 없을 뜻
public:
	inline UINT&	Set_TransColor()						{ return m_TransData; }
	inline void		Set_TransColor(const UINT& _Value)		{ m_TransData = _Value; }
	inline int		Width()									{ return m_BitMap.bmWidth; }
	inline int		Height()								{ return m_BitMap.bmHeight; }
	inline Size		size()									{ return {Width(), Height()}; }
	inline HDC&		GetDc()									{ return m_this_HDC;}


	// 픽셀 충돌 -> 해당 이미지 픽셀 위치에 컬러값을 가져옴
	COLORREF		Get_PixelColor(Position _Pos)			{ return GetPixel(m_this_HDC, _Pos.X, _Pos.Y); }

public:
	Image();
	~Image();
};

