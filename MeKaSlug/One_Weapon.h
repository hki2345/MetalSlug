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

	// �� �ʱ�ȭ �Ѿ��� �ν��Ͻ��� �����̹Ƿ� -������ �̰� �� �ʿ���� ��.��
	// �Ʒ� �ʱ�ȭ ���� ���� ���⿡ ���� ������ �ٸ�����
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

