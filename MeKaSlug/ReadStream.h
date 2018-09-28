#pragma once
#include "BaseStream.h"
class ReadStream : public BaseStream
{
public:
	template<typename T>
	void operator >> (T& _Value)
	{
		// 해당 인자 주소, 해당 버퍼 사이즈, 해당인자 사이즈, 해당인자를 몇 번 읽을 것인지
		fread_s(&_Value, sizeof(_Value), sizeof(_Value), 1, m_pFile);
	}

	template<typename T>
	void Read(void* _pBuf, int _Count)
	{
		fread_s(_pBuf, sizeof(T) * _Count, sizeof(T) * _Count, 1, pFile);
	}

public:
	ReadStream(const WCHAR* _Path);
	~ReadStream();
};

