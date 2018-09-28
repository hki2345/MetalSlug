#pragma once
#include "TheOne.h"


class One_Weapon : public TheOne
{
public:
	enum Weapon_Type {
		Sword = 1,
		Explosion,
		Fire,
	};

protected:
	float m_Run_Speed;
	float m_ActingTime;
	float m_LiveTime;

	Weapon_Type m_Status_Weapon;

public:
	Weapon_Type& Status_Weapon()	{ return m_Status_Weapon; }

	// 위 초기화 총알은 인스턴스식 생성이므로 -오히려 이게 더 필요없음 ㅡ.ㅡ
	// 아래 초기화 총의 상태 방향에 따라 랜딩이 다름ㅇㅇ
	virtual void Init() {};
	virtual void Init(Positionf _Pos, Positionf _Pos_Dir) {};
	virtual void Update() override {};

protected:
	virtual void Update_Fire() {};
	virtual void Activate() {};
	void UpdateCheckLive() override;

public:
	One_Weapon();
	~One_Weapon();
};

