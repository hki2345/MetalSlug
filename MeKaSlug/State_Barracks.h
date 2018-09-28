#pragma once
#include "BaseState.h"
#include "PlayerMgr.h"


class One_BS_BackGround;
class One_BS_Cover;
class One_BS_Front;
class One_BS_Select_Cover;
class One_BS_Select_Eri;
class One_BS_Select_Leona;
class One_BS_Pinset;
class State_Barracks : public BaseState
{
private:
	One_BS_BackGround* BS_Back;
	One_BS_Cover* BS_Cover;
	One_BS_Front* BS_Front;
	One_BS_Select_Cover* BS_Select_Cover;
	One_BS_Select_Eri* BS_Select_Eri;
	One_BS_Select_Leona* BS_Select_Leona;
	One_BS_Pinset* BS_Pinset;

	float m_Time;
	float GameTime;

	// 수행 단계를 지정
	PlayerMgr::Play_Character m_Player_Select;

private:
	void StateUpdate() override;
	void All_SetUp() override;

	void Value_DebugRender() override;
	void StateStart() override;
	void Setting_Image() override;

	void Update_Init();
	void Update_Select_Eri();
	void Update_Select_Leona();

public:
	State_Barracks();
	~State_Barracks();
};

