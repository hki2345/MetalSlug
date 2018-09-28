#pragma once
#include "One_Weapon.h"

class Animator;
class Weapon_MagmaCannon : public One_Weapon
{
private:
	Animator* p_Render;

public:
	void Init() override {};
	void Start(Positionf _Pos);
	void Activate();
	void Update() override;

private:

	void Init_Render() override;
	void Init_Collision() override;

	void Update_Fire() override;

public:
	Weapon_MagmaCannon();
	~Weapon_MagmaCannon();
};

