#pragma once
#include "One_Weapon.h"

class Animator;
class Weapon_Bomb : public One_Weapon
{
private:
	Animator* p_Render;

	Dirf m_Power_pos_Dir;
	Dirf m_Rending_Dir;
	int m_i_JumpCount;

	float m_v_EriPower;

public:
	void Init() override {};
	void Init(Positionf _Pos, Dirf _Pos_Dir, Dirf _Power_Pos_Dir);
	void Activate();
	void DebugUpdate() override;
	void Update() override ;

private:
	void Init_Render() override;
	void Init_Collision() override;

	void Update_Fire() override ;
	void Update_Render(); 
	void Update_BottomLine() override;

public:
	Weapon_Bomb();
	~Weapon_Bomb();
};

