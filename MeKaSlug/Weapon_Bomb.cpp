#include "stdafx.h"
#include "Weapon_Bomb.h"
#include "One_Effect.h"

#include "Collider.h"
#include "Animator.h"
#include "PlayerMgr.h"

#include "ResourceManager.h"


Weapon_Bomb::Weapon_Bomb()
{
	m_v_Jump_Force = 500.0f;
	m_Run_Speed = 300;
}


Weapon_Bomb::~Weapon_Bomb()
{
}

void Weapon_Bomb::DebugUpdate()
{
	WCHAR Str[100] = { 0, };

	swprintf_s(Str, L"Rending Dir: %3.2f %3.2f", m_Rending_Dir.X, m_Rending_Dir.Y);
	TEXT_OUT(300, 200, Str);

	swprintf_s(Str, L"Jump Count: %d", m_i_JumpCount);
	TEXT_OUT(300, 220, Str);
}


void Weapon_Bomb::Init(Positionf _Pos, Dirf _Pos_Dir, Dirf _Power_Pos_Dir)
{
	Name(L"P_Explosion");
	m_Pos = _Pos;
	m_pos_Dir = _Pos_Dir;
	m_Power_pos_Dir = _Power_Pos_Dir;
	m_v_EriPower = 350.0f;


	m_Status_Weapon = Weapon_Type::Explosion;

	if (PlayerMgr::Play_Character::Eri == PlayerMgr::character() &&
		Vector2f::Zero != m_Power_pos_Dir)
	{
		m_Run_Speed += m_v_EriPower;
	}
	else if (Vector2f::Zero != m_Power_pos_Dir)
	{
		m_Run_Speed += PlayerMgr::MainPlayer()->run_speed();
	}

	Init_Collision();
	Init_Render();

	Update_Force(m_v_Jump_Force);
	m_i_JumpCount = 2;
}

void Weapon_Bomb::Init_Render()
{
	// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
	if (1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.X) ||
		1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.Y))
	{
		return;
	}

	p_Render = Create_Renderer<Animator>(10);
	p_Render->Set_Animation(L"WeaponEffect.bmp", L"R_Effect", 0, 29, .01f, true);
	p_Render->Set_Animation(L"WeaponEffect.bmp", L"L_Effect", 29, 0, .01f, true);
	p_Render->Set_TransColor(RGB(0, 248, 0));
	p_Render->Pivot(p_Render->size() * .25f);

	if (.0f < m_pos_Dir.X)
	{
		p_Render->Change_Animation(L"R_Effect");
	}
	if (.0f >= m_pos_Dir.X)
	{
		p_Render->Change_Animation(L"L_Effect");
	}
}

void Weapon_Bomb::Activate()
{
	RESOURCEMANAGER.Play_Sound(L"Bomb_Act.mp3", .5f);
	One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
	Effect->Start(One_Effect::Effect_Type::BOMB, m_Pos + Positionf{ .0f, p_Collider->size().PartY() });

	// 다 튀었으면 빨리 사라져야함
	Death(true);
}







void Weapon_Bomb::Init_Collision()
{
	p_Collider = Create_Collider(L"Weapon", { 30, 30 });
	p_Collider->type(Collider::TYPE::CIRCLE);

	p_Collider->MotherOfTheOne_DE(this);
	p_Collider->Calculate_Figure_Pos();
	p_Collider->Pivot(p_Collider->size() * .5f);
}

/***************** Update *****************/

void Weapon_Bomb::Update()
{
	UpdateCheckLive();
	Update_Fire();
	// Update_Render();

	// 위치 차를 이용한 벡터 출력
	m_PrevPos = m_Pos;
}

void Weapon_Bomb::Update_Fire()
{
	TheOne::Update_Gravity();
	
	// 에리경우
	if (PlayerMgr::Play_Character::Eri == PlayerMgr::character())
	{
		// 누르지 않았을 경우
		if (Vector2f::Zero == m_Power_pos_Dir)
		{
			m_Power_pos_Dir = m_pos_Dir;
		}

		m_Pos.X += (m_Run_Speed) * DELTATIME * m_Power_pos_Dir.X;
		m_Pos.Y += (m_Run_Speed) * DELTATIME * m_Power_pos_Dir.Y;

		p_Collider->Calculate_Figure_Pos();
		return;
	}

	// 에리 아닌 경우
	else if (PlayerMgr::Play_Character::Eri != PlayerMgr::character())
	{
		if(Vector2f::Zero == m_Power_pos_Dir)
		{
			m_Power_pos_Dir = m_pos_Dir;
		}

		m_Pos.X += (m_Run_Speed) * DELTATIME * m_Power_pos_Dir.X;
		m_Pos.Y += (m_Run_Speed) * DELTATIME * m_Power_pos_Dir.Y;

		p_Collider->Calculate_Figure_Pos();
	}
}

void Weapon_Bomb::Update_BottomLine()
{
	if (true == m_b_BottomCheck)
	{
		// 튀는 효과
		if (0 < m_i_JumpCount)
		{
			p_Render->speed(p_Render->speed() * 2.0f);
			m_i_JumpCount--;
			m_b_JumpCheck = false;
			Update_Force(m_v_Jump_Force);
			m_v_Jump_Force *= .75f;
			m_Run_Speed *= .75f;
		}
		else
		{
			Activate();
		}
	}
}