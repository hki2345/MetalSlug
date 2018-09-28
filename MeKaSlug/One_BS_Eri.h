#pragma once
#include "TheOne.h"
class One_BS_Eri : public TheOne
{
private:
	TheOne* m_Target;

public:
	void Start(TheOne* _Target);
	void Update();

public:
	One_BS_Eri();
	~One_BS_Eri();
};

