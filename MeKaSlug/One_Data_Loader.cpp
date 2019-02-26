#include "stdafx.h"

#include "ReadStream.h"
#include "MapData_Creator.h"
#include "Pinset_Renderer.h"

#include "One_Data_Loader.h"


One_Data_Loader::One_Data_Loader()
{
}


One_Data_Loader::~One_Data_Loader()
{
}

void One_Data_Loader::Init()
{
	m_p_Data = m_MotherOfTheOne->StateOfOne_Create<MapData_Creator>();

	m_p_Pinset = Create_Renderer<Pinset_Renderer>(300);
	m_p_Pinset->Set_Pinset(L"Pinset.bmp");
	m_p_Pinset->PinsetSize({ 30, 30 });
	m_p_Pinset->Set_TransColor(VIOLET);
	//m_p_Pinset->IsRender(false);
}

std::vector<Pinset_Renderer::PinsetData> One_Data_Loader::DataLoad(const WCHAR* _Path)
{
	std::wstring m_map_FilePath;
	std::wstring m_pin_FilePath;

	m_map_FilePath = _Path;
	m_map_FilePath += L".MapData";

	m_pin_FilePath = _Path;
	m_pin_FilePath += L".PinData";

	// 읽을 경로 확인
	ReadStream MapStream = ReadStream(FILE_PATH_NOT_L(L"Data", m_map_FilePath.c_str()));
	ReadStream PinStream = ReadStream(FILE_PATH_NOT_L(L"Data", m_pin_FilePath.c_str()));
	
	int map_Size;
	int pin_Size;

	MapStream >> map_Size;
	PinStream >> pin_Size;

	MapData_Creator::EnemyData LoadEnemyData;
	Pinset_Renderer::PinsetData LoadPinData;

	for (int i = 0; i < map_Size; i++)
	{
		MapStream >> LoadEnemyData;

		m_p_Data->Insert_Enemy(LoadEnemyData.m_EPos, (MapData_Creator::Enemy_DataIndex)LoadEnemyData.EnemyIndex);
	}

	for (int i = 0; i < pin_Size; i++)
	{
		PinStream >> LoadPinData;

		m_p_Pinset->Insert_Pinset(LoadPinData.m_EPos, LoadPinData.m_DPos, LoadPinData.m_Condition);
	}

	return m_p_Pinset->GetAllPinsetData();
}