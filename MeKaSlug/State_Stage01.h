#pragma once
#include "BaseState.h"
#include "BaseEnemy.h"

class One_Player;
class State_Stage01 : public BaseState
{
public:
	void StateUpdate() override;
	void All_SetUp() override;
	void StateStart() override;
	void Value_DebugRender() override;

public:
	State_Stage01();
	~State_Stage01();
};

