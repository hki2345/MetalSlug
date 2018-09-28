#pragma once
#include "BaseState.h"

class One_Player;
class State_Debug_S1 :	public BaseState
{
private:
	// 플레이어를 디버그하기 위함
	One_Player* m_p_Player;

public:
	void StateStart() override;
	void StateUpdate() override;
	void All_SetUp() override;
	void Value_DebugRender() override;


public:
	State_Debug_S1();
	~State_Debug_S1();
};

