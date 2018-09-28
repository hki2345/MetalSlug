#pragma once
#include "BaseState.h"

class State_End : public BaseState
{
	float m_Time;
	float GameTime;

private:
	void StateUpdate() override;
	void All_SetUp() override;

	void Value_DebugRender() override;
	void StateStart() override;
public:
	State_End();
	~State_End();
};

