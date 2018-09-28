#pragma once
#include "BaseState.h"

class One_Player;
class One_Stage_SCover;
class One_Stage_CCover;
class State_Stage02 : public BaseState
{
private:
	One_Stage_SCover*	m_SCover;
	One_Stage_CCover*	m_CCover;

public:
	void StateStart() override;
	void StateUpdate() override;
	void All_SetUp() override;
	void Value_DebugRender() override;


public:
	State_Stage02();
	~State_Stage02();
};

