#pragma once
#include "One_Weapon.h"

class Bullet_Heavy : public One_Weapon
{
public:
	void Activate() override;
	void Init() override {};
	void Init(Positionf _Pos, Dirf _Pos_Dir) override;
	void Update() override ;
	
private:
	void Init_Render() override;


	void Init_Collision() override;
	
	void Update_Fire() override;

public:
	Bullet_Heavy();
	~Bullet_Heavy();
};

