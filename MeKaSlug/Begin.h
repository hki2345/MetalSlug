#pragma once
#include <string>

// 모든 것(물체, 스테이트, 등의 모든 것)의 시작점 -> 이름과 생명이 있다.
class Begin
{
private:
	std::wstring	NameData;

public:
	// 이름데이터를 주고 받음
	const WCHAR*	Name() const				{ return NameData.c_str(); }
	void			Name(const WCHAR* _Value)	{ NameData = _Value; }

protected:
	Begin() {};
	virtual ~Begin() = 0 {};
};