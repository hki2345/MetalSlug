#pragma once
class BaseStream
{
protected:
	FILE* m_pFile;

private:
	void Open(const WCHAR* _FilePath, const WCHAR* _Mode);

public:
	BaseStream(const WCHAR* _FilePath, const WCHAR* _Mode);
	~BaseStream();
};

