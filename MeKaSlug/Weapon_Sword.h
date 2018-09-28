#pragma once
#include "One_Weapon.h"
class Weapon_Sword : public One_Weapon
{
public:
	void Init() override {};
	void Start(const Positionf& _Pos, const WCHAR* _Name);
	void Update() override;
	void DebugUpdate() override;
	void Update_Fire() {};

public:
	Weapon_Sword();
	~Weapon_Sword();
};

