#include "stdafx.h"
#include "Weapon_Sword.h"

#include "Collider.h"


Weapon_Sword::Weapon_Sword()
{
}


Weapon_Sword::~Weapon_Sword()
{
}


void Weapon_Sword::Start(const Positionf& _Pos, const WCHAR* _Name)
{
	Name(_Name);
	m_Pos = _Pos;

	m_Status_Weapon = Weapon_Type::Sword;

	p_Collider = Create_Collider(L"Weapon", { 30, 30 });
	p_Collider->type(Collider::TYPE::RECT);

	p_Collider->MotherOfTheOne_DE(this);
	p_Collider->Calculate_Figure_Pos();
	p_Collider->Pivot(p_Collider->size() * .5f);
	m_LiveTime = .1f;
}

void Weapon_Sword::Update()
{
	UpdateCheckLive();
}

void Weapon_Sword::DebugUpdate()
{
	WCHAR Str[100] = { 0, };

	swprintf_s(Str, L"Pos Dir: %3.2f %3.2f", m_Pos.X, m_Pos.Y);
	TEXT_OUT(300, 200, Str);
}