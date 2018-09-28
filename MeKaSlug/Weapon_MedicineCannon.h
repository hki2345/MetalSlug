#pragma once
#include "One_Weapon.h"

class Animator;
class Weapon_MedicineCannon : public One_Weapon
{
private:
	enum MedicineCannonStatus
	{
		M_CREATE = 0,
		M_ROTATE,
		M_LAUNCH
	};

private:
	MedicineCannonStatus m_this_Status;
	Animator* p_Render;
	Animator* p_Render2;
	Positionf m_TargetPos;

	float m_RotateTime;

	bool Right;

public:
	void Init() override {};
	void Start(const Positionf& _Pos);
	void Activate();
	void Update() override;

private:
	void Update_Create();
	void Update_Rotate();
	void Update_Launch();

	void Init_Render() override;
	void Init_Collision() override;

public:
	Weapon_MedicineCannon();
	~Weapon_MedicineCannon();
};

