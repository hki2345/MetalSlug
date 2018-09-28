#include "stdafx.h"
#include "Weapon_Moon.h"

#include "Collider.h"



Weapon_Moon::Weapon_Moon()
{
}


Weapon_Moon::~Weapon_Moon()
{
}

void Weapon_Moon::Start(const Positionf& _Pos, const WCHAR* _Name)
{
	Name(_Name);
	m_Pos = _Pos;

	m_Status_Weapon = Weapon_Type::Sword;

	p_Collider = Create_Collider(L"Weapon", { 150, 150 });
	p_Collider->type(Collider::TYPE::CIRCLE);

	p_Collider->MotherOfTheOne_DE(this);
	p_Collider->Calculate_Figure_Pos();
	m_LiveTime = .1f;
}

void Weapon_Moon::Update()
{
	UpdateCheckLive();
}

void Weapon_Moon::DebugUpdate()
{
	WCHAR Str[100] = { 0, };

	swprintf_s(Str, L"Pos Dir: %3.2f %3.2f", m_Pos.X, m_Pos.Y);
	TEXT_OUT(300, 200, Str);
}