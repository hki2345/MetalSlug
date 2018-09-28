#pragma once
#include "Begin.h"
#include "MatrixInfo.h"

#pragma region �� �ּ�
// HDC�� WINAPI���� �⺻������ �����ϴ� �̹��� ������ �����̴�.
// WINDOW�� HDC �̳༮��
// HDC�ȿ��� �������� ������ �� �ִ�.
// HDC�� ��ȭ���� ������
// WINAPI�� �����ϰ� �̹����� �ε��ϸ�
// �׳༮�� HDCȭ �ȴ�.
// ȭ�� ��ü�� �ȼ�.

// �̹����� �ε��ϰ� �Ǹ�
// �׷��� HDC ���ο� ��� �ִ� �������� ����.
// �ȼ��� ���� ũ��
// �ڽ��� ũ��
// �̹����� HDCȭ �ȴ�.

// ���⼭ �ҷ��� �̹����� ���� HBITMAP�� �ҷ������鼭 ������ ����ִ� �⺻ �����͵���
// ���ԵǴµ� �̸� �����ϴ� �ͱ��� �ؾ� �Ϻ��ϴٰ� �� �� �ְٴ�.
// ���� �̸� �޴� HBITMAP�ڵ鵵 ���� �޸� �� ��� ������ �ξ���Ѵ�. -> �̰ͱ��� ����� ����
#pragma endregion



class Image : public Begin
{
public:
	friend class ResourceManager;

private:
	// �̹����� �׷��� HDC -> ��ƼĿ ����
	HDC		m_this_HDC;

	// �ҷ����� HBITMAP
	HBITMAP m_HBitMap;
	
	// ������ m_load_BitMap�� ��� �ִ� �⺻ �����Ͱ� ���⿡ �Ű��� ����
	// ���� �� �ʿ�
	HBITMAP m_prev_BitMap;

	// ��¥ ��Ʈ�� ������ -> ����ü
	BITMAP	m_BitMap;



	// 255, 255, 255, 255 �����͸� 4����Ʈ�� ȯ���Ͽ� �����Ѵ�.
	// ���� �ڷ��� Int�� ä�õǴ� ���̸�,
	// ��� 4����Ʈ �ڷ��� float, __int32 �� 4����Ʈ�� �� �ȴ�.
	UINT m_TransData;
	
	// �� �̹����� ���İ� �ִ��� üũ -> �׸��� ����
	bool m_Alpha;

	// ������� �ش� ũ�� ��ŭ�� �̹����� ����� -> ȭ�� ũ���� �̹����� �����
	// �ű⿡ ���� ����
	HDC& Create_Image(const Size _Size);
	bool Load(const WCHAR* _Path);
	void ImgSize();


	// �׽�Ʈ�� ���� ���� Ȥ�� �ٸ� �ǹ�-> �� ���� ��
public:
	inline UINT&	Set_TransColor()						{ return m_TransData; }
	inline void		Set_TransColor(const UINT& _Value)		{ m_TransData = _Value; }
	inline int		Width()									{ return m_BitMap.bmWidth; }
	inline int		Height()								{ return m_BitMap.bmHeight; }
	inline Size		size()									{ return {Width(), Height()}; }
	inline HDC&		GetDc()									{ return m_this_HDC;}


	// �ȼ� �浹 -> �ش� �̹��� �ȼ� ��ġ�� �÷����� ������
	COLORREF		Get_PixelColor(Position _Pos)			{ return GetPixel(m_this_HDC, _Pos.X, _Pos.Y); }

public:
	Image();
	~Image();
};

