#include "stdafx.h"
#include "Enemy_MachineGun.h"
#include "Animator.h"
#include "Collider.h"
#include "PlayerMgr.h"
#include "ResourceManager.h"

#include "Weapon_EnemyBullet.h"

Enemy_MachineGun::Enemy_MachineGun()
{
}


Enemy_MachineGun::~Enemy_MachineGun()
{
}



void Enemy_MachineGun::Init()
{
	Fire_Count = 3;
	Fire_Time = 1.0f;
	m_Time = .0f;
	
	Name(L"Enemy_Person");
	m_Pos = { 500, 600 };
	Hp = 100;
	AttRange = 100.f;
	MoveRange = 500.f;
	Speed = 100.0f;
	OutRange = 500.f;
	IntervalTime = 3.0f;
	thisTime = .0f;

	float Ani_Time = .05f;

	p_Render = Create_Renderer<Animator>(5);



	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"L_SDie", 204, 215, Ani_Time, false);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"R_SDie", 227, 216, Ani_Time, false);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"L_BDie", 228, 238, Ani_Time, false);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"R_BDie", 230, 240, Ani_Time, false);

	p_Render->Set_Animation(L"R_Ma_Idle.bmp", L"R_Idle", 0, 7, Ani_Time, true);
	p_Render->Set_Animation(L"R_Ma_Fire.bmp", L"R_Attack", 19, 9, Ani_Time, true);
	p_Render->Set_Animation(L"R_Ma_Move.bmp", L"R_Move", 0, 11, Ani_Time, true);
	p_Render->Set_Animation(L"R_Ma_Reload.bmp", L"R_Interval", 17, 1, .1f, false);

	p_Render->Set_Animation(L"L_Ma_Fire.bmp", L"L_Attack", 0, 10, Ani_Time, true);
	p_Render->Set_Animation(L"L_Ma_Idle.bmp", L"L_Idle", 7, 0, Ani_Time, true);
	p_Render->Set_Animation(L"L_Ma_Move.bmp", L"L_Move", 11, 0, Ani_Time, true);
	p_Render->Set_Animation(L"L_Ma_Reload.bmp", L"L_Interval", 0, 16, .1f, false);


	p_Render->Change_Animation(L"L_Idle");
	p_Render->Pivot({ -5, -10 });
	p_Render->Set_TransColor(RGB(255, 105, 0));

	p_Collider = Create_Collider(L"Enemy", { 50,80 });
	p_Collider->type(Collider::TYPE::RECT);

	m_Work.SetAniWork(p_Render);

	m_Work.CreateState(L"L_Idle", L"L_Idle");
	m_Work.CreateState(L"R_Idle", L"R_Idle");
	m_Work.CreateState(L"L_Interval", L"L_Interval");
	m_Work.CreateState(L"R_Interval", L"R_Interval");
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

	m_Work.ChangeState(L"R_Idle");

	m_Index = BaseEnemy::MachineGun;
}

void Enemy_MachineGun::DirCheck()
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


bool Enemy_MachineGun::StrCheck(const std::wstring _Str)
{
	if (m_Work.CurState()->Name == L"L_" + _Str || m_Work.CurState()->Name == L"R_" + _Str)
	{
		return true;
	}
	return false;
}




void Enemy_MachineGun::Update()
{
	// 원래 게임상에선 터뜨려야하지만 에디터에선 플레이어가 없기 때문에 터뜨리지 않는다.
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
	else if (StrCheck(L"SDie") || StrCheck(L"BDie"))
	{
		Die();
	}
}

void Enemy_MachineGun::DebugUpdate()
{
	WCHAR Str[100] = { 0, };

	swprintf_s(Str, L"EnemyState : %s", m_Work.CurState()->Name.c_str());
	TEXT_OUT(500, 20, Str);
}

void Enemy_MachineGun::Move()
{
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);

	if (AttRange >= Dis)
	{
		m_s_Acting += m_s_Att;
		m_Work.ChangeState(m_s_Acting);
	}
	else if (OutRange <= Dis)
	{
		m_s_Acting += L"Idle";
		m_Work.ChangeState(m_s_Acting);
	}
	else
	{
		if (m_pos_Dir.X < .0f) { m_pos_Dir = Vector2f::Left; }
		else { m_pos_Dir = Vector2f::Right; }

		m_Pos = { m_Pos.X + m_pos_Dir.X * DELTATIME * Speed, m_Pos.Y };
	}
}

void Enemy_MachineGun::Idle()
{
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);

	if (MoveRange >= Dis)
	{
		m_s_Acting += L"Move";
		m_Work.ChangeState(m_s_Acting);
	}
	else if (AttRange >= Dis)
	{
		m_s_Acting += m_s_Att;
		m_Work.ChangeState(m_s_Acting);
	}
}

void Enemy_MachineGun::Att()
{
	m_Time += DELTATIME;
	// 미사일 쏘고
	// 공격하고
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);
	m_Work.AniWork()->Pivot({ .0f, .0f });

	if (AttRange <= Dis)
	{
		m_s_Acting += L"Idle";
		m_Work.ChangeState(m_s_Acting);
	}

	else if (Fire_Count > 0 && m_Time > Fire_Time)
	{
		Weapon_EnemyBullet* NewSword = m_MotherOfTheOne->StateOfOne_Create<Weapon_EnemyBullet>();
		NewSword->Start(m_Pos + Positionf{ m_pos_Dir.X * 20.0f, 0.0f }, m_pos_Dir);
		m_Work.AniWork()->Change_ReAnimation();
		Fire_Count--;
		m_Time = .0f;
	}
	else if (Fire_Count <= 0)
	{
		m_s_Acting += m_s_Interval;
		m_Work.ChangeState(m_s_Acting);
	}
}


void Enemy_MachineGun::AttackInterval()
{
	if (thisTime < IntervalTime)
	{
		thisTime += DELTATIME;
	}
	else
	{
		Fire_Count = 3;
		m_s_Acting += m_s_Att;
		m_Work.ChangeState(m_s_Acting);
		thisTime = .0f;
	}
}

void  Enemy_MachineGun::Die()
{
	m_Time += DELTATIME;
	if (false == m_Work.AniWork()->IsActing() && m_Time > Die_Time)
	{
		Death(true);
	}
}

void Enemy_MachineGun::CollisionEnter(Collider* _Other)
{
	std::wstring Temp = _Other->MotherOfTheOne_DE()->Name();
	if ((Temp == L"P_Sword" || Temp == L"P_Moon" )&& false == StrCheck(L"SDie") && false == StrCheck(L"BDie"))
	{
		RESOURCEMANAGER.Play_Sound(L"Enemy_Die1.mp3", .2f);
		_Other->MotherOfTheOne_DE()->Activate();
		DirCheck();
		m_s_Acting += L"SDie";
		m_Work.ChangeState(m_s_Acting);
		m_Work.AniWork()->size({ 120, 120 });
	}
	else if ((Temp == L"P_Bullet" || Temp == L"P_Explosion") && false == StrCheck(L"SDie") && false == StrCheck(L"BDie"))
	{
		RESOURCEMANAGER.Play_Sound(L"Enemy_Die2.mp3", .2f);
		_Other->MotherOfTheOne_DE()->Activate();
		DirCheck();
		m_s_Acting += L"BDie";
		m_Work.ChangeState(m_s_Acting);
		m_Work.AniWork()->size({ 120, 120 });
	}
}