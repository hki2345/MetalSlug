#pragma once
#include "TheOne.h"
class One_Item : public TheOne
{
protected:

protected:

	float m_Run_Speed;

public:

	// 초기화 문 필요
	void Init() override {};
	void Update() override {};

public:
	One_Item();
	~One_Item();
};

