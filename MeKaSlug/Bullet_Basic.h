#pragma once
#include "One_Weapon.h"

class Bullet_Basic : public One_Weapon
{
public:
	void Activate() override;
	void Init() override {};

	// 총의 상태 방향에 따라 랜딩이 다름ㅇㅇ
	void Init(Positionf _Pos, Positionf _Pos_Dir) override;
	void Update() override;
private:
	void Update_Fire() override;

public:
	Bullet_Basic();
	~Bullet_Basic();
};

