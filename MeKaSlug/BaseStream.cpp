#include "stdafx.h"
#include "BaseStream.h"


BaseStream::BaseStream(const WCHAR* _FilePath, const WCHAR* _Mode)
{
	Open(_FilePath, _Mode);
}


BaseStream::~BaseStream()
{
	fclose(m_pFile);
}

void BaseStream::Open(const WCHAR* _FilePath, const WCHAR* _Mode)
{
	// 와이드 바이트 처리
	_wfopen_s(&m_pFile, _FilePath, _Mode);
}