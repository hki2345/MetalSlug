#pragma once
#include "TheOne.h"
class One_BS_Pinset : public TheOne
{
public :
	void Init()override;
	void Update(const float& _X);


public:
	One_BS_Pinset();
	~One_BS_Pinset();
};

