#pragma once
#include "BaseState.h"

class One_Player;
class State_Game : public BaseState
{
public:
	void StateUpdate() override;
	void All_SetUp() override;
	void Value_DebugRender() override;
	
private:
	void Setting_Key() override;
	void Setting_Image() override;
	void Setting_Collider() override;


public:
	State_Game();
	~State_Game();
};

