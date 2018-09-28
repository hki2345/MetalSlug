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
	// ���̵� ����Ʈ ó��
	_wfopen_s(&m_pFile, _FilePath, _Mode);
}