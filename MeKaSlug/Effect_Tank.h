#pragma once
#include "TheOne.h"

class Animator;
class Effect_Tank : public TheOne
{
private:
	Animator* p_Render;

public:
	void Start(const Positionf& _Pos);
	void Update() override;
public:
	Effect_Tank();
	~Effect_Tank();
};

