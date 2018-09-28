#pragma once
#include <map>
#include <string>

class PathManager // -> 역시 싱글톤으로 만든다.
{
private:
	// 이 폴더가 실행되는 파일경로
	std::wstring m_FilePath;

	// 게임에 쓰일 데이터들을 폴더에 넣을 것인데
	// 그 이름을 저장하는 맵이다.
	std::map<std::wstring, std::wstring> m_map_GamePath;

	void Init();

public:

	void CreateGamePath(const WCHAR* _Name, const WCHAR* _Path);
	void CreateGamePath(const WCHAR* _Name);
	// 이 새로운 경로로 이미지를 바로 이미지를 만들게 한다.
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

