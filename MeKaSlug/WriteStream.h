#pragma once
#include "BaseStream.h"
class WriteStream : public BaseStream
{
public:
	template<typename T>
	void operator << (const T& _Value)
	{
		// �ش� ���� �ּ�, �ش����� ������, �ش����ڸ� �� �� ���� ������
		fwrite(&_Value, sizeof(_Value), 1, m_pFile);
	}

	template<typename T>
	void Read(void* _pBuf, int _Count)
	{
		fwrite(_pBuf, sizeof(T) * _Count, sizeof(T) * _Count, 1, pFile);
	}

public:
	WriteStream(const WCHAR* _Path);
	~WriteStream();
};

