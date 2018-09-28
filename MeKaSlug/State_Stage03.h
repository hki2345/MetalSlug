#pragma once
#include "BaseState.h"

class One_Player;
class State_Stage03 : public BaseState
{
public:
	void StateStart() override;
	void StateUpdate() override;
	void All_SetUp() override;
	void Value_DebugRender() override;


public:
	State_Stage03();
	~State_Stage03();
};

