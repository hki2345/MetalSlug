#pragma once
#include "BaseState.h"

class State_Title :	public BaseState
{
private:
	void StateUpdate() override;
	void All_SetUp() override;
	void StateStart() override;

	void Value_DebugRender() override;

	void Setting_Key() override;
	void Setting_Image() override;

public:
	State_Title();
	~State_Title();
};

