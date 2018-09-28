#pragma once
#include <map>
#include <string>

class PathManager // -> ���� �̱������� �����.
{
private:
	// �� ������ ����Ǵ� ���ϰ��
	std::wstring m_FilePath;

	// ���ӿ� ���� �����͵��� ������ ���� ���ε�
	// �� �̸��� �����ϴ� ���̴�.
	std::map<std::wstring, std::wstring> m_map_GamePath;

	void Init();

public:

	void CreateGamePath(const WCHAR* _Name, const WCHAR* _Path);
	void CreateGamePath(const WCHAR* _Name);
	// �� ���ο� ��η� �̹����� �ٷ� �̹����� ����� �Ѵ�.
	std::wstring CreateFilePath(const WCHAR* _FolderName, const WCHAR* _Name);
	const WCHAR* Find_Path(const WCHAR* _Name);

	const WCHAR* Get_FilePath()
	{
		return m_FilePath.c_str();
	}

	static PathManager& Inst()
	{
		static PathManager NewPathMgr = PathManager();
		return NewPathMgr;
	}

private:
	PathManager();
	~PathManager();
};

