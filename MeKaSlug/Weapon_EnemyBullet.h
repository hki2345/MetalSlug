#pragma once
#include "One_Weapon.h"

class Animator;
class Weapon_EnemyBullet : public One_Weapon
{
private:
	Animator* p_Render;

public:
	void Init() override {};
	void Start(Positionf _Pos, Dirf _Pos_Dir);
	void Activate();
	void Update() override;

private:
	void Init_Collision() override;
	void Init_Render() override;
	void Update_Fire() override;

public:
	Weapon_EnemyBullet();
	~Weapon_EnemyBullet();
};

