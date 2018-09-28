#pragma once
#include "TheOne.h"

class Animator;
class Effect_MagmaCannon :public TheOne
{
private:
	Animator* p_Render;
	TheOne* p_Target;


public:
	void Start(TheOne* _Pos);
	void Update() override;

public:
	Effect_MagmaCannon();
	~Effect_MagmaCannon();
};

