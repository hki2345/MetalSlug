#pragma once
#include "TheOne.h"
class Animator;
class Effect_Bradley : public TheOne
{
private:
	Animator* p_Render;

public:
	void Start(const Positionf& _Pos, const bool& _Raise);
	void Update() override;
public:
	Effect_Bradley();
	~Effect_Bradley();
};

