#pragma once
#include "TheOne.h"

class Animator;
class Effect_SaruBead :
	public TheOne
{
private:
	float Speed;
	Animator* p_Render;

public:
	void Start(const Positionf& _Pos);
	void Update() override;
public:
	Effect_SaruBead();
	~Effect_SaruBead();
};

