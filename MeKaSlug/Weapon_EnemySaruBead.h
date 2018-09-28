#pragma once
#include "One_Weapon.h"

class Animator;
class Weapon_EnemySaruBead : public One_Weapon
{
private:
	Animator* p_Render;
	float m_v_EriPower;
	bool m_Move;

public:
	void Init() override {};
	void Start(Positionf _Pos, Dirf _Pos_Dir);
	void Activate();
	void Update() override;

private:

	void Init_Render() override;
	void Init_Collision() override;

	void Update_Fire() override;

public:
	Weapon_EnemySaruBead();
	~Weapon_EnemySaruBead();
};

