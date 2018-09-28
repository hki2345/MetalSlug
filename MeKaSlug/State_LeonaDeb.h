#pragma once
#include "BaseState.h"


class One_Player;
class State_LeonaDeb : public BaseState
{
private:
	// 플레이어를 디버그하기 위함
	One_Player* m_p_Player;

public:
	void StateUpdate() override;
	void All_SetUp() override;
	void Value_DebugRender() override;
	void StateStart() override;

private:
	void Setting_Image() override;
	void Setting_Collider() override;


public:
	State_LeonaDeb();
	~State_LeonaDeb();
};

