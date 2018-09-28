#pragma once
#include "One_Weapon.h"


class MultiSprite;
class Trans_Renderer;
class Weapon_EnemyBradley : public One_Weapon
{
private:
	MultiSprite* p_Render;
	Trans_Renderer* p_Trans_Render;

public:
	void Init() override {};
	void Start(Positionf _Pos, Dirf _Pos_Dir);
	void Activate();
	void Update() override;

private:
	void Init_Render() override;
	void Init_Collision() override;

	void Update_Fire() override;
	void Update_BottomLine() override;
	void Update_Render();

public:
	Weapon_EnemyBradley();
	~Weapon_EnemyBradley();
};

