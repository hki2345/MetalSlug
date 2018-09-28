#pragma once
#include "TheOne.h"
class MS_Select_Normal : public TheOne
{
private:
	float Speed;
	bool Activate;
	
public:
	void Init() override;
	void Update() override;

	bool& activate() { return Activate; }

public:
	MS_Select_Normal();
	~MS_Select_Normal();
};

