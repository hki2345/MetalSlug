#include "stdafx.h"
#include "ReadStream.h"


ReadStream::ReadStream(const WCHAR* _Path) : BaseStream(_Path, L"rb")
{
}


ReadStream::~ReadStream()
{
}
