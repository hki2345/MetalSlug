#pragma once
#include "TheOne.h"

class Bit_Renderer;
class One_BackGround : public TheOne
{
private:
	Bit_Renderer* TitleArray;
	size_t	TitleCnt;
	float	TitleTime;
	float	PlayTime;

public: 
	void Init() override;
	void Update() override;

public:
	One_BackGround();
	~One_BackGround();
};

