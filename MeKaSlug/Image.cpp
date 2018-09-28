#include "stdafx.h"
#include "Image.h"
#include "Core.h"


Image::Image() : 
	m_this_HDC(nullptr), m_HBitMap(nullptr), m_prev_BitMap(nullptr),	
	// 난 따른 것으로 통일해야것지 ㅠ.ㅠ
	m_TransData(RGB(0, 0, 0))
{
}


Image::~Image()
{
	//// 받아논 데이터를 삭제한다. -> HDC에 그려진 거
	//DeleteObject(m_load_BitMap);

	//// HDC에 이전 데이터(초기데이터)를 넣는다.
	//(HBITMAP)SelectObject(m_this_HDC, m_prev_BitMap);

	// HDC를 지운다 -> 이전 데이터와 같이 지움
	DeleteDC(m_this_HDC);
	DeleteObject(m_prev_BitMap);
}

// 윈도우의 크기만큼 찍어내기 위함 - 굳이 윈도우가 아니더라도 되겠징?
HDC& Image::Create_Image(const Size _Size)
{
	KAssert(nullptr == CORE.GetHInstance());

	// HDC를 만든다.
	m_this_HDC = CreateCompatibleDC(CORE.GetHDC());

	// CreateCompatibleBitmap - 해당 사이즈 만큼의 이미지를 만드는 과정
	m_HBitMap = CreateCompatibleBitmap(CORE.GetHDC(), _Size.X, _Size.Y);
	KAssert(nullptr == m_HBitMap);
	KAssert(nullptr == m_this_HDC);

	m_prev_BitMap = (HBITMAP)SelectObject(m_this_HDC, m_HBitMap);

	ImgSize();

	return m_this_HDC;
}

bool Image::Load(const WCHAR* _Path)
{
	// 비트맵 정보를 불러오는 핸들러가 웬걸 HInstance를 원한다. 따라서
	// 코어의 인스턴스를 불러온다.
	KAssert(nullptr == CORE.GetHInstance());

	// 패스에 있는 비트맵이미지에 대해 핸들에 저장하는 과정
	// -> 하지만 이걸로는 윈도우에 찍어낼 수 없다.
	// 핸들을 비트맵 데이터로 필터하는 과정이 필요한다,.
	m_HBitMap = (HBITMAP)LoadImageW(CORE.GetHInstance(), _Path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	

	if (nullptr == m_HBitMap)
	{
		KAssert(true);
		// 실제론 이렇게 되어야 한다.
		return false;
	}

	// 그 과정이 바로 이 이미지가 가진 HDC에 의미를 부여하는 것이다.
	// 바로 코어가 가진 HDC(도화지)에 이미지의 HDC(스티커)를 만들어준다.
	m_this_HDC = CreateCompatibleDC(CORE.GetHDC());

	// SelectObject -> 이제 HDC에 데이터를 보정하여 찍어낼 수 있게 한다.
	// 단 부산물로 이전 초기화된 이미지에 대한 핸들러를 넘겨주는데 이를 prev가 받는다.
	m_prev_BitMap = (HBITMAP)SelectObject(m_this_HDC, m_HBitMap);

	// GetObjectW(m_hOldBitMap, sizeof(BITMAP), &m_ImgInfo);

	KAssert(nullptr == m_this_HDC);
	ImgSize();

	return true;
}

void Image::ImgSize()
{
	// GetObject -> 핸들러에서 제공하는 정보를 세팅해준다.
	GetObjectW(m_HBitMap, sizeof(BITMAP), &m_BitMap);
}
