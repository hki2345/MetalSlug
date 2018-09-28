#pragma once
#include "BaseState.h"

class Enemy_Boss;
class State_Boss :	public BaseState
{
private:
	Enemy_Boss* p_Boss;
	bool m_GameOver;

public:
	void StateStart() override;
	void StateUpdate() override;
	void All_SetUp() override;
	void Value_DebugRender() override;

public:
	State_Boss();
	~State_Boss();
};

