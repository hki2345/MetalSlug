#include "stdafx.h"
#include "Image.h"
#include "Core.h"


Image::Image() : 
	m_this_HDC(nullptr), m_HBitMap(nullptr), m_prev_BitMap(nullptr),	
	// �� ���� ������ �����ؾ߰��� ��.��
	m_TransData(RGB(0, 0, 0))
{
}


Image::~Image()
{
	//// �޾Ƴ� �����͸� �����Ѵ�. -> HDC�� �׷��� ��
	//DeleteObject(m_load_BitMap);

	//// HDC�� ���� ������(�ʱⵥ����)�� �ִ´�.
	//(HBITMAP)SelectObject(m_this_HDC, m_prev_BitMap);

	// HDC�� ����� -> ���� �����Ϳ� ���� ����
	DeleteDC(m_this_HDC);
	DeleteObject(m_prev_BitMap);
}

// �������� ũ�⸸ŭ ���� ���� - ���� �����찡 �ƴϴ��� �ǰ�¡?
HDC& Image::Create_Image(const Size _Size)
{
	KAssert(nullptr == CORE.GetHInstance());

	// HDC�� �����.
	m_this_HDC = CreateCompatibleDC(CORE.GetHDC());

	// CreateCompatibleBitmap - �ش� ������ ��ŭ�� �̹����� ����� ����
	m_HBitMap = CreateCompatibleBitmap(CORE.GetHDC(), _Size.X, _Size.Y);
	KAssert(nullptr == m_HBitMap);
	KAssert(nullptr == m_this_HDC);

	m_prev_BitMap = (HBITMAP)SelectObject(m_this_HDC, m_HBitMap);

	ImgSize();

	return m_this_HDC;
}

bool Image::Load(const WCHAR* _Path)
{
	// ��Ʈ�� ������ �ҷ����� �ڵ鷯�� ���� HInstance�� ���Ѵ�. ����
	// �ھ��� �ν��Ͻ��� �ҷ��´�.
	KAssert(nullptr == CORE.GetHInstance());

	// �н��� �ִ� ��Ʈ���̹����� ���� �ڵ鿡 �����ϴ� ����
	// -> ������ �̰ɷδ� �����쿡 �� �� ����.
	// �ڵ��� ��Ʈ�� �����ͷ� �����ϴ� ������ �ʿ��Ѵ�,.
	m_HBitMap = (HBITMAP)LoadImageW(CORE.GetHInstance(), _Path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	

	if (nullptr == m_HBitMap)
	{
		KAssert(true);
		// ������ �̷��� �Ǿ�� �Ѵ�.
		return false;
	}

	// �� ������ �ٷ� �� �̹����� ���� HDC�� �ǹ̸� �ο��ϴ� ���̴�.
	// �ٷ� �ھ ���� HDC(��ȭ��)�� �̹����� HDC(��ƼĿ)�� ������ش�.
	m_this_HDC = CreateCompatibleDC(CORE.GetHDC());

	// SelectObject -> ���� HDC�� �����͸� �����Ͽ� �� �� �ְ� �Ѵ�.
	// �� �λ깰�� ���� �ʱ�ȭ�� �̹����� ���� �ڵ鷯�� �Ѱ��ִµ� �̸� prev�� �޴´�.
	m_prev_BitMap = (HBITMAP)SelectObject(m_this_HDC, m_HBitMap);

	// GetObjectW(m_hOldBitMap, sizeof(BITMAP), &m_ImgInfo);

	KAssert(nullptr == m_this_HDC);
	ImgSize();

	return true;
}

void Image::ImgSize()
{
	// GetObject -> �ڵ鷯���� �����ϴ� ������ �������ش�.
	GetObjectW(m_HBitMap, sizeof(BITMAP), &m_BitMap);
}
