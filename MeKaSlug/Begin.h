#pragma once
#include <string>

// ��� ��(��ü, ������Ʈ, ���� ��� ��)�� ������ -> �̸��� ������ �ִ�.
class Begin
{
private:
	std::wstring	NameData;

public:
	// �̸������͸� �ְ� ����
	const WCHAR*	Name() const				{ return NameData.c_str(); }
	void			Name(const WCHAR* _Value)	{ NameData = _Value; }

protected:
	Begin() {};
	virtual ~Begin() = 0 {};
};