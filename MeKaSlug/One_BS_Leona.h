#pragma once
#include "TheOne.h"
class One_BS_Leona :
	public TheOne
{
private:
	TheOne* m_Target;

public:
	void Start(TheOne* _Target);
	void Update();
public:
	One_BS_Leona();
	~One_BS_Leona();
};

