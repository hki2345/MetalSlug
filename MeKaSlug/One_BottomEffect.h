#pragma once
#include "TheOne.h"
#include "Animator.h"

class One_BottomEffect :public TheOne
{
private:
	Animator* p_Render;

public:
	void Start(const Positionf& _Pos);

public:
	One_BottomEffect();
	~One_BottomEffect();
};

