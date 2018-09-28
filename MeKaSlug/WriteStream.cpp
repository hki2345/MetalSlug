#include "stdafx.h"
#include "WriteStream.h"


WriteStream::WriteStream(const WCHAR* _Path) : BaseStream(_Path, L"wb")
{
}


WriteStream::~WriteStream()
{
}
