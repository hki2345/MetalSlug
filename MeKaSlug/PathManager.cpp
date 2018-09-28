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
	// ���� '��'������ �����Ǵ� ��ġ�� Data�� �־��ִ� �Լ�
	WCHAR Data[1000];
	GetCurrentDirectoryW(sizeof(WCHAR) * 1000, Data);
	m_FilePath = Data;

	// ������Ʈ Ȥ�� ������ �����Ǵ� ���� ���丮 �ٷ� ������ �ʱ�ȭ�� �Ѵ�.
	m_FilePath.replace(m_FilePath.find_last_of('\\', m_FilePath.size()),
		m_FilePath.size(), L"\\bin\\");
}

void PathManager::CreateGamePath(const WCHAR* _Name, const WCHAR* _Path)
{
	// ����ڵ� ->���� �Ͷ߸���.����
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

// ���ϰ� ���� ���� ���� �����ϰ� ���ش�.
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