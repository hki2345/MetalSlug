#pragma once
#include "TheOne.h"

class Animator;
class Effect_FireWater : public TheOne
{
private:
	Animator* p_Render;


public:
	void Start(const Positionf& _Pos);
	void Update() override;

public:
	Effect_FireWater();
	~Effect_FireWater();
};

