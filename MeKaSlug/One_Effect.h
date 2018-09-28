#pragma once
#include "TheOne.h"

class Animator;
class One_Effect : public TheOne
{
public:
	enum Effect_Type 
	{
		SMALL,
		MIDDLE,
		BIG,
		HUGE,
		BOMB,
		BULLET,
	};

private:
	Animator* p_Render;
	Effect_Type this_Type;

public:
	virtual void DebugUpdate() override;
	void Start(const Effect_Type& _Value, const Positionf& _Pos);
	void Update() override;

public:
	One_Effect();
	~One_Effect();
};

