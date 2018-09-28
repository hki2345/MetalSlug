#pragma once
#include "TheOne.h"

class Animator;
class Effect_Sarubia :public TheOne
{
private:
	Animator* p_Render;

public:
	void Start(const Positionf& _Pos);
	void Update() override;
public:
	Effect_Sarubia();
	~Effect_Sarubia();
};

