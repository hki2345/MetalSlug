#pragma once
#include "BaseState.h"

class Enemy_Boss;
class State_Debug_SB :	public BaseState
{
private:
	Enemy_Boss* p_Boss;

public:
	void StateStart() override;
	void StateUpdate() override;
	void All_SetUp() override;
	void Value_DebugRender() override;


public:
	State_Debug_SB();
	~State_Debug_SB();
};

