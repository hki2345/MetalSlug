#include "stdafx.h"
#include "PathManager.h"


PathManager::PathManager()
{
	Init();
}


PathManager::~PathManager()
{
}

void PathManager::Init()
{
	// 현재 '이'파일이 구동되는 위치를 Data에 넣어주는 함수
	WCHAR Data[1000];
	GetCurrentDirectoryW(sizeof(WCHAR) * 1000, Data);
	m_FilePath = Data;

	// 프로젝트 혹은 게임이 구동되는 파일 디렉토리 바로 위에서 초기화를 한다.
	m_FilePath.replace(m_FilePath.find_last_of('\\', m_FilePath.size()),
		m_FilePath.size(), L"\\bin\\");
}

void PathManager::CreateGamePath(const WCHAR* _Name, const WCHAR* _Path)
{
	// 방어코드 ->지만 터뜨린다.ㅎㅎ
	if (nullptr != Find_Path(_Name))
	{
		KAssert(true);
	}

	std::wstring NewPath = m_FilePath + _Path + L"\\";
	m_map_GamePath.insert(std::map<std::wstring, std::wstring>::value_type(_Name, NewPath));
}

void PathManager::CreateGamePath(const WCHAR* _Name)
{
	CreateGamePath(_Name, _Name);
}

// 파일과 파일 명을 합쳐 저장하게 해준다.
std::wstring PathManager::CreateFilePath(const WCHAR* _FolderName, const WCHAR* _Name)
{
	std::wstring NewPath = Find_Path(_FolderName);
	return NewPath += _Name;
}

const WCHAR* PathManager::Find_Path(const WCHAR* _Name)
{
	std::map<std::wstring, std::wstring>::iterator findIter = m_map_GamePath.find(_Name);

	if (m_map_GamePath.end() == findIter)
	{
		return nullptr;
	}

	return findIter->second.c_str();
}