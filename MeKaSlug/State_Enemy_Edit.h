#pragma once
#include "BaseState.h"

class One_Edit_Enemy;
class State_Enemy_Edit : public BaseState
{
private:
	One_Edit_Enemy* m_Editor;
	TheOne* m_EditStage;
	int m_v_EditStage;

	bool m_On_Collider;
	void UpdateStageCollider();

private:
	void Init_Data();
	void UpdateStage1();
	void UpdateStage2();
	void UpdateStage3();
	void UpdateStageBoss();


public:
	void StateUpdate() override;
	void All_SetUp() override;
	void Value_DebugRender() override;

public:
	State_Enemy_Edit();
	~State_Enemy_Edit();
};

