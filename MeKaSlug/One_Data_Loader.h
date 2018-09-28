#pragma once
#include "TheOne.h"
#include "Pinset_Renderer.h"

class MapData_Creator;
class One_Data_Loader : public TheOne
{
private:
	Pinset_Renderer* m_p_Pinset;
	MapData_Creator* m_p_Data;

public:
	void Init() override;
	std::vector<Pinset_Renderer::PinsetData> DataLoad(const WCHAR* _Path);

public:
	One_Data_Loader();
	~One_Data_Loader();
};

