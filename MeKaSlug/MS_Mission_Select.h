#pragma once
#include "TheOne.h"
class MS_Mission_Select : public TheOne
{
private:
	float Speed;
	bool Activate;

public:
	void Init() override;
	void Update() override;

	bool& activate() { return Activate; }


public:
	MS_Mission_Select();
	~MS_Mission_Select();
};

