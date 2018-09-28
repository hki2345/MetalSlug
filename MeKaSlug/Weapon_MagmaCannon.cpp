#include "stdafx.h"
#include "Weapon_MagmaCannon.h"
#include "One_Effect.h"

#include "Collider.h"
#include "Animator.h"
#include "PlayerMgr.h"
#include "BossMgr.h"

#include "ResourceManager.h"


Weapon_MagmaCannon::Weapon_MagmaCannon()
{
	m_v_Gravity = 3.0f;
	m_Run_Speed = 80;
}


Weapon_MagmaCannon::~Weapon_MagmaCannon()
{
}


void Weapon_MagmaCannon::Start(Positionf _Pos)
{
	m_LiveTime = 3.0f;
	Name(L"E_Fire");
	m_Pos = _Pos;


	m_Status_Weapon = Weapon_Type::Explosion;
	Init_Collision();
	Init_Render();
}

void Weapon_MagmaCannon::Init_Render()
{
	// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
	if (1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.X) ||
		1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.Y))
	{
		return;
	}

	p_Render = Create_Renderer<Animator>(10);
	p_Render->Set_Animation(L"MagmaCannon.bmp", L"Down", 0, 4, .04f, true);
	p_Render->Change_Animation(L"Down");

	p_Render->Pivot(p_Render->size() * .25f);
	p_Render->Set_TransColor(ORANGE);
}

void Weapon_MagmaCannon::Activate()
{
	One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
	Effect->Start(One_Effect::Effect_Type::MIDDLE, m_Pos + Positionf{ .0f, p_Collider->size().PartY() });

	// 다 튀었으면 빨리 사라져야함
	m_LiveTime = .0f;
}

void Weapon_MagmaCannon::Init_Collision()
{
	p_Collider = Create_Collider(L"Weapon", { 30, 30 });
	p_Collider->type(Collider::TYPE::CIRCLE);

	p_Collider->MotherOfTheOne_DE(this);
	//p_Collider->Calculate_Figure_Pos();
	p_Collider->Pivot(p_Collider->size() * .5f);
}

/***************** Update *****************/

void Weapon_MagmaCannon::Update()
{
	if (true == BossMgr::MainBoss()->BossDie()) { Activate(); }

	TheOne::Update_Gravity();
	UpdateCheckLive();

	if (Obj_Stand == m_Status_Obj)
	{
		Activate();
	}
}

void Weapon_MagmaCannon::Update_Fire()
{
}

