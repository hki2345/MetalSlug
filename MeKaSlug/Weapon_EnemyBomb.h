#pragma once
#include "One_Weapon.h"

class Animator;
class Weapon_EnemyBomb : public One_Weapon
{
private:
	Animator* p_Render;
	float m_v_EriPower;

public:
	void Init() override {};
	void Start(Positionf _Pos, Dirf _Pos_Dir);
	void Activate();
	void DebugUpdate() override;
	void Update() override;

private:
	void Init_Render() override;
	void Init_Collision() override;

	void Update_Fire() override;
	void Update_BottomLine() override;

public:
	Weapon_EnemyBomb();
	~Weapon_EnemyBomb();
};

