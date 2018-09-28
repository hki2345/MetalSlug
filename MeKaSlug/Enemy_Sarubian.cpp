#include "stdafx.h"
#include "Enemy_Sarubian.h"
#include "Animator.h"
#include "PlayerMgr.h"
#include "Collider.h"

#include "Weapon_EnemySaruBead.h"

#include "One_Effect.h"
#include "Effect_SaruBead.h"
#include "Effect_Sarubia.h"

#include "ResourceManager.h"


Enemy_Sarubian::Enemy_Sarubian()
{
}


Enemy_Sarubian::~Enemy_Sarubian()
{
}


void Enemy_Sarubian::Init()
{
	Hp = 50;
	Fire_Count = 1;
	Fire_Time = .2f;

	Name(L"Enemy_Machine");
	m_Pos = { 500, 600 };
	Hp = 20;
	AttRange = 400.f;
	MoveRange = 500.f;
	Speed = 10.0f;
	OutRange = 500.f;
	IntervalTime = 3.0f;
	m_Time = .0f;

	float Ani_Time = .05f;

	Animator* p_Render = Create_Renderer<Animator>(5);
	p_Render->Set_Animation(L"Saru_Damage.bmp", L"L_Damage", 0, 6, Ani_Time, false);
	p_Render->Set_Animation(L"Saru_Damage.bmp", L"R_Damage", 0, 6, Ani_Time, false);
	p_Render->Set_Animation(L"Saru_Wrecked.bmp", L"L_Wrecked", 0, 3, Ani_Time, false);
	p_Render->Set_Animation(L"Saru_Wrecked.bmp", L"R_Wrecked", 0, 3, Ani_Time, false);
	p_Render->Set_Animation(L"Saru_Idle.bmp", L"L_Idle", 0, 1, Ani_Time, true);
	p_Render->Set_Animation(L"Saru_Idle.bmp", L"R_Idle", 0, 1, Ani_Time, true);
	p_Render->Set_Animation(L"Saru_Shoot.bmp", L"R_Attack", 0, 11, Ani_Time, false);
	p_Render->Set_Animation(L"Saru_Shoot.bmp", L"L_Attack", 0, 11, Ani_Time, false);
	p_Render->Set_Animation(L"Saru_Move.bmp", L"L_Move", 0, 5, Ani_Time, true);
	p_Render->Set_Animation(L"Saru_Move.bmp", L"R_Move", 0, 5, Ani_Time, true);
	p_Render->Set_Animation(L"Saru_Reload.bmp", L"L_Interval", 0, 5, .1f, false);
	p_Render->Set_Animation(L"Saru_Reload.bmp", L"R_Interval", 0, 5, .1f, false);

	p_Render->Change_Animation(L"L_Idle");
	p_Render->Pivot({ -5, -10 });
	p_Render->Set_TransColor(ORANGE);

	p_Collider = Create_Collider(L"Enemy", { 100, 200 });
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
	m_Work.CreateState(L"L_Damage", L"L_Damage");
	m_Work.CreateState(L"R_Damage", L"R_Damage");
	m_Work.CreateState(L"L_Reload", L"L_Reload");
	m_Work.CreateState(L"R_Reload", L"R_Reload");
	m_Work.CreateState(L"L_Stop", L"L_Stop");
	m_Work.CreateState(L"R_Stop", L"R_Stop");
	m_Work.CreateState(L"L_Wrecked", L"L_Wrecked");
	m_Work.CreateState(L"R_Wrecked", L"R_Wrecked");


	m_s_Acting = L"";
	m_s_Att = L"Attack";
	m_s_Move = L"Move";
	m_s_Idle = L"Idle";
	m_s_Interval = L"Interval";
	m_s_Damage = L"Damage";
	m_s_Reload = L"Reload";
	m_s_Stop = L"Stop";
	m_s_Wrecked = L"Wrecked";

	m_Work.ChangeState(L"R_Idle");

	m_Index = BaseEnemy::SaruBian;
}

void Enemy_Sarubian::DirCheck()
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

bool Enemy_Sarubian::StrCheck(const std::wstring _Str)
{
	if(m_Work.CurState()->Name == L"L_" + _Str || m_Work.CurState()->Name == L"R_" + _Str)
	{
		return true;
	}
	return false;
}

void Enemy_Sarubian::Update()
{
	// ���� ���ӻ󿡼� �Ͷ߷��������� �����Ϳ��� �÷��̾ ���� ������ �Ͷ߸��� �ʴ´�.
	if (nullptr == PlayerMgr::MainPlayer()) { return; }
	if (1500 < MATHMANAGER.Distance(PlayerMgr::MainPlayer()->pos(), m_Pos)) { return; }

	Update_Bottom();
	Update_Gravity();
	
	DirCheck();

	if (Hp <= 0 && false == StrCheck(m_s_Wrecked))
	{
		m_s_Acting += m_s_Wrecked;
		m_Work.ChangeState(m_s_Acting);
	}

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
	else if (StrCheck(m_s_Damage))
	{
		Damage();
	}
	else if (StrCheck(m_s_Reload))
	{
		Reload();
	}
	else if (StrCheck(m_s_Stop))
	{
		Stop();
	}
	else if (StrCheck(m_s_Wrecked))
	{
		Wrecked();
	}
}

void Enemy_Sarubian::DebugUpdate()
{
	WCHAR Str[100] = { 0, };

	swprintf_s(Str, L"EnemyState : %s", m_Work.CurState()->Name.c_str());
	TEXT_OUT(500, 20, Str);
}

void Enemy_Sarubian::Move()
{
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);

	if (AttRange >= Dis)
	{
		m_s_Acting += m_s_Interval;
		m_Work.ChangeState(m_s_Acting);
	}
	else if (OutRange <= Dis)
	{
		m_s_Acting += m_s_Idle;
		m_Work.ChangeState(m_s_Acting);
	}
	else
	{
		if (m_pos_Dir.X < .0f) { m_pos_Dir = Vector2f::Left; }
		else { m_pos_Dir = Vector2f::Right; }

		m_Pos = { m_Pos.X + m_pos_Dir.X * DELTATIME * Speed, m_Pos.Y };
	}
}

void Enemy_Sarubian::Idle()
{
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);

	if (MoveRange >= Dis)
	{
		m_s_Acting += L"Move";
		m_Work.ChangeState(m_s_Acting);
	}
	else if (AttRange >= Dis)
	{
		m_s_Acting += m_s_Interval;
		m_Work.ChangeState(m_s_Acting);
	}
}

void Enemy_Sarubian::Att()
{
	m_Time += DELTATIME;
	// �̻��� ���
	// �����ϰ�
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);
	m_Work.AniWork()->Pivot({ .0f, .0f });

	if (AttRange <= Dis)
	{
		m_s_Acting += m_s_Idle;
		m_Work.ChangeState(m_s_Acting);
	}

	else if (Fire_Count > 0 && m_Time > Fire_Time)
	{
		Weapon_EnemySaruBead* NewBomb = m_MotherOfTheOne->StateOfOne_Create<Weapon_EnemySaruBead>();
		NewBomb->Start(m_Pos + Positionf{ -100.0f, -50.0f }, m_pos_Dir);

		Effect_SaruBead* NewBeadEff = m_MotherOfTheOne->StateOfOne_Create<Effect_SaruBead>();
		NewBeadEff->Start(m_Pos + Positionf{ 100.0f, -50.0f });

		Effect_Sarubia* NewEff = m_MotherOfTheOne->StateOfOne_Create<Effect_Sarubia>();
		NewEff->Start(m_Pos + Positionf{ -100.0f, -50.0f });

		Fire_Count--;
		m_Time = .0f;

		m_s_Acting += m_s_Interval;
		m_Work.ChangeState(m_s_Acting);
	}
}


void Enemy_Sarubian::AttackInterval()
{
	if (m_Time < IntervalTime)
	{
		m_Time += DELTATIME;
	}
	else
	{
		m_s_Acting += m_s_Att;
		m_Work.ChangeState(m_s_Acting);
		Fire_Count = 1;
		m_Time = .0f;
	}
}


void Enemy_Sarubian::Damage()
{
	if (false == m_Work.AniWork()->IsActing())
	{
		m_s_Acting += m_s_Idle;
		m_Work.ChangeState(m_s_Acting);

		m_Time = .0f;
	}
}
void Enemy_Sarubian::Reload()
{

}
void Enemy_Sarubian::Stop()
{

}
void Enemy_Sarubian::Wrecked()
{
	if (false == m_Work.AniWork()->IsActing())
	{
		m_Time += DELTATIME;

		if (m_Time > 2.0f)
		{
			RESOURCEMANAGER.Play_Sound(L"MachineWrecked.mp3", .3f);
			PlayerMgr::DestroyEnemyCnt();
			One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
			Effect->Start(One_Effect::Effect_Type::HUGE, m_Pos_Bottom_Check);
			Name(L"");
			Death(true);
		}
	}
}





void Enemy_Sarubian::CollisionEnter(Collider* _Other)
{
	std::wstring Temp = _Other->MotherOfTheOne_DE()->Name();
	if (Temp == L"P_Bullet" && false == StrCheck(m_s_Wrecked))
	{
		_Other->MotherOfTheOne_DE()->Activate();
		Hp--;
	}
	else if((Temp == L"P_Explosion" || Temp == L"P_Moon") && false == StrCheck(m_s_Wrecked))
	{
		_Other->MotherOfTheOne_DE()->Activate();
		DirCheck();
		m_s_Acting += m_s_Damage;
		Hp -= 5;
		m_Work.ChangeState(m_s_Acting);
	}
}