#pragma once
#include "One_Weapon.h"

class Animator;
class Weapon_FireWave : public One_Weapon
{
private:
	Animator* p_Render;

public:
	void Init() override {};
	void Start(const Positionf& _Pos);
	void Activate();
	void Update() override;

private:

	void Init_Render() override;
	void Init_Collision() override;

	void Update_Fire() override {};
public:
	Weapon_FireWave();
	~Weapon_FireWave();
};

