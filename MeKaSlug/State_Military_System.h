#pragma once
#include "BaseState.h"

class MS_Select_Normal;
class MS_Arrow_Side;
class MS_Mission_Select;
class One_MS_BackGround;
class One_BS_Cover;
class State_Military_System :public BaseState
{
private:
	// 수행 단계를 지정
	size_t State_Count;

	MS_Arrow_Side* Arrow;
	MS_Select_Normal* Select_Normal;
	MS_Mission_Select* Select_Mission;
	One_MS_BackGround* MS_Back;
	One_BS_Cover*		BS_Cover;


private:
	void StateUpdate() override;
	void All_SetUp() override;

	void Value_DebugRender() override;
	void StateStart() override;
	void Setting_Image() override;
public:
	State_Military_System();
	~State_Military_System();
};

