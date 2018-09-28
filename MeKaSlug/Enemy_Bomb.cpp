#include "stdafx.h"
#include "Enemy_Bomb.h"
#include "Animator.h"
#include "PlayerMgr.h"
#include "Collider.h"

#include "ResourceManager.h"

#include "Weapon_EnemyBomb.h"

Enemy_Bomb::Enemy_Bomb()
{
}


Enemy_Bomb::~Enemy_Bomb()
{
}


void Enemy_Bomb::Init()
{
	Die_Time = .3f;
	Name(L"Enemy_Person");

	Fire_Count = 1;
	Fire_Time = .5f;
	m_Pos = { 500, 600 };
	m_pos_Dir = Vector2f::Right;
	Hp = 100;
	AttRange = 200.f;
	MoveRange = 500.f;
	Speed = 150.0f;
	OutRange = 500.f;
	IntervalTime = 3.0f;

	float Ani_Time = .05f;

	p_Render = Create_Renderer<Animator>(5);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"L_Idle", 12, 18, Ani_Time, true);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"R_Idle", 299, 293, Ani_Time, true);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"R_Attack", 24, 37, Ani_Time, true);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"L_Attack", 59, 47, Ani_Time, true);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"L_Move", 0, 11, Ani_Time, true);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"R_Move", 311, 300, Ani_Time, true);

	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"L_SDie", 204, 215, Ani_Time, false);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"R_SDie", 227, 216, Ani_Time, false);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"L_BDie", 228, 238, Ani_Time, false);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"R_BDie", 230, 240, Ani_Time, false);

	p_Render->Change_Animation(L"L_Idle");
	p_Render->Set_TransColor(RGB(255, 105, 0));

	p_Collider = Create_Collider(L"Enemy", { 50,80 });
	p_Collider->type(Collider::TYPE::RECT);


	m_Work.SetAniWork(p_Render);

	m_Work.CreateState(L"L_Idle", L"L_Idle");
	m_Work.CreateState(L"R_Idle", L"R_Idle");
	m_Work.CreateState(L"L_Interval", L"L_Idle");
	m_Work.CreateState(L"R_Interval", L"R_Idle");
	m_Work.CreateState(L"L_Attack", L"L_Attack");
	m_Work.CreateState(L"R_Attack", L"R_Attack");
	m_Work.CreateState(L"L_Move", L"L_Move");
	m_Work.CreateState(L"R_Move", L"R_Move");

	m_Work.CreateState(L"L_SDie", L"L_SDie");
	m_Work.CreateState(L"R_SDie", L"R_SDie");
	m_Work.CreateState(L"L_BDie", L"L_BDie");
	m_Work.CreateState(L"R_BDie", L"R_BDie");


	m_s_Acting = L"";
	m_s_Att = L"Attack";
	m_s_Move = L"Move";
	m_s_Idle = L"Idle";
	m_s_Interval = L"Interval";
	m_s_SDie = L"SDie";
	m_s_BDie = L"BDie";

	m_Work.ChangeState(L"R_Idle");


	m_Index = BaseEnemy::Bomb;
}

void Enemy_Bomb::DirCheck()
{
	m_pos_Dir = MathManager::Inst().PntToPnt_Dir(PlayerMgr::MainPlayer()->pos(), m_Pos);

	if (.0f < m_pos_Dir.X)
	{
		m_s_Acting = L"R_";
	}
	else
	{
		m_s_Acting = L"L_";
	}
}

bool Enemy_Bomb::StrCheck(const std::wstring _Str)
{
	if (m_Work.CurState()->Name == L"L_" + _Str || m_Work.CurState()->Name == L"R_" + _Str)
	{
		return true;
	}
	return false;
}



void Enemy_Bomb::Update()
{
	if (nullptr == PlayerMgr::MainPlayer()) { return; }
	if (1500 < MATHMANAGER.Distance(PlayerMgr::MainPlayer()->pos(), m_Pos)) { return; }

	Update_Bottom();
	Update_Gravity();

	DirCheck();

	if (StrCheck(m_s_Idle))
	{
		Idle();
	}
	else if (StrCheck(m_s_Att))
	{
		Att();
	}
	else if (StrCheck(m_s_Move))
	{
		Move();
	}
	else if (StrCheck(m_s_Interval))
	{
		AttackInterval();
	}

	else if (StrCheck(m_s_SDie) || StrCheck(m_s_BDie))
	{
		Die();
	}
}

void Enemy_Bomb::DebugUpdate()
{
	WCHAR Str[100] = { 0, };

	swprintf_s(Str, L"EnemyState : %s", m_Work.CurState()->Name.c_str());
	TEXT_OUT(500, 20, Str);

	swprintf_s(Str, L"Bottom Pos : %d", m_Pos_Bottom_Check.Y);
	TEXT_OUT(500, 40, Str);

	swprintf_s(Str, L"Pos : %f", m_Pos.Y);
	TEXT_OUT(500, 60, Str);

	swprintf_s(Str, L"Bottom Pos : %f", PartYSize);
	TEXT_OUT(500, 80, Str);
	
	swprintf_s(Str, L"Dir Pos : %f", m_pos_Dir.X);
	TEXT_OUT(500, 100, Str);
}


void Enemy_Bomb::Move()
{
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);

	if (AttRange >= Dis)
	{
		m_s_Acting += m_s_Att;
		m_Work.ChangeState(m_s_Acting);
	}
	else if (OutRange <= Dis)
	{
		m_s_Acting += m_s_Idle;
		m_Work.ChangeState(m_s_Acting);
	}
	else
	{
		if(m_pos_Dir.X < .0f) { m_pos_Dir = Vector2f::Left; }
		else { m_pos_Dir = Vector2f::Right; }

		m_Pos = { m_Pos.X + m_pos_Dir.X * DELTATIME * Speed, m_Pos.Y };
	}
}

void Enemy_Bomb::Idle()
{
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);

	if (MoveRange >= Dis)
	{
		m_s_Acting += m_s_Move;
		m_Work.ChangeState(m_s_Acting);
	}
	else if (AttRange >= Dis)
	{
		m_s_Acting += m_s_Att;
		m_Work.ChangeState(m_s_Acting);
	}
}

void Enemy_Bomb::Att()
{
	m_Time += DELTATIME;

	// 미사일 쏘고
	// 공격하고
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);
	m_Work.AniWork()->Pivot({ .0f, .0f });

	if (AttRange <= Dis)
	{
		m_s_Acting += m_s_Idle;
		m_Work.ChangeState(m_s_Acting);
		m_Time = .0f;
	}
	else if (false == m_Work.AniWork()->IsActing())
	{
		m_s_Acting += m_s_Interval;
		m_Work.ChangeState(m_s_Acting);
		m_Time = .0f;
	}

	else if (Fire_Count > 0 && m_Time < Fire_Time)
	{
		Weapon_EnemyBomb* NewBomb = m_MotherOfTheOne->StateOfOne_Create<Weapon_EnemyBomb>();
		NewBomb->Start(m_Pos, m_pos_Dir);
		Fire_Count--;
	}
}

void Enemy_Bomb::AttackInterval()
{
	if (m_Time < IntervalTime)
	{
		m_Time += DELTATIME;
	}
	else
	{
		Fire_Count = 1;
		m_s_Acting += m_s_Att;
		m_Work.ChangeState(m_s_Acting);
		m_Time = .0f;
	}
}

void Enemy_Bomb::Run()
{


}


void Enemy_Bomb::Die()
{
	m_Time += DELTATIME;
	if (false == m_Work.AniWork()->IsActing() && m_Time > Die_Time)
	{
		Death(true);
	}
}

void Enemy_Bomb::CollisionEnter(Collider* _Other)
{
	std::wstring Temp = _Other->MotherOfTheOne_DE()->Name();
	if ((Temp == L"P_Sword" || Temp == L"P_Moon") && false == StrCheck(m_s_SDie) && false == StrCheck(m_s_BDie))
	{
		RESOURCEMANAGER.Play_Sound(L"Enemy_Die4.mp3", .2f);
		_Other->MotherOfTheOne_DE()->Activate();
		DirCheck();
		m_s_Acting += m_s_SDie;
		m_Work.ChangeState(m_s_Acting);
	}
	else if ((Temp == L"P_Bullet" || Temp == L"P_Explosion") && false == StrCheck(m_s_SDie) && false == StrCheck(m_s_BDie))
	{
		RESOURCEMANAGER.Play_Sound(L"Enemy_Die6.mp3", .2f);
		_Other->MotherOfTheOne_DE()->Activate();
		DirCheck();
		m_s_Acting += m_s_BDie;
		m_Work.ChangeState(m_s_Acting);
	}
}