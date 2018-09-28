#include "stdafx.h"
#include "Enemy_Bradley.h"

#include "Animator.h"
#include "PlayerMgr.h"
#include "Collider.h"

#include "Weapon_EnemyBradley.h"

#include "One_Effect.h"
#include "Effect_Bradley.h"

#include "ResourceManager.h"


Enemy_Bradley::Enemy_Bradley()
{
}


Enemy_Bradley::~Enemy_Bradley()
{


}


void Enemy_Bradley::Init()
{
	Hp = 50;
	Fire_Count = 8;
	Fire_Time = .2f;

	Name(L"Enemy_Machine");
	m_Pos = { 500, 600 };
	Hp = 25;
	AttRange = 1000.f;
	MoveRange = 300.f;
	Speed = 10.0f;
	OutRange = 500.f;
	IntervalTime = 3.0f;
	m_Time = .0f;

	float Ani_Time = .05f;

	Animator* p_Render = Create_Renderer<Animator>(5);
	p_Render->Set_Animation(L"Bradley_Edit.bmp", L"R_Side_Wrecked", 24, 43, Ani_Time, false);
	p_Render->Set_Animation(L"Bradley_Edit.bmp", L"L_Side_Wrecked", 24, 43, Ani_Time, false);
	p_Render->Set_Animation(L"Bradley_Edit.bmp", L"L_Raise_Wrecked", 0, 19, Ani_Time, false);
	p_Render->Set_Animation(L"Bradley_Edit.bmp", L"R_Raise_Wrecked", 0, 19, Ani_Time, false);

	p_Render->Set_Animation(L"Side_Idle.bmp", L"L_Side_Idle", 0, 1, Ani_Time, true);
	p_Render->Set_Animation(L"Side_Idle.bmp", L"R_Side_Idle", 0, 1, Ani_Time, true);
	p_Render->Set_Animation(L"Raise_Idle.bmp", L"L_Raise_Idle", 0, 1, Ani_Time, true);
	p_Render->Set_Animation(L"Raise_Idle.bmp", L"R_Raise_Idle", 0, 1, Ani_Time, true);

	p_Render->Set_Animation(L"Side_Shoot.bmp", L"L_Side_Attack", 0, 6, Ani_Time, false);
	p_Render->Set_Animation(L"Side_Shoot.bmp", L"R_Side_Attack", 0, 6, Ani_Time, false);
	p_Render->Set_Animation(L"Raise_Shoot.bmp", L"L_Raise_Attack", 0, 6, Ani_Time, false);
	p_Render->Set_Animation(L"Raise_Shoot.bmp", L"R_Raise_Attack", 0, 6, Ani_Time, false);

	p_Render->Set_Animation(L"Side_Idle.bmp", L"L_Side_Interval", 0, 1, Ani_Time, true);
	p_Render->Set_Animation(L"Side_Idle.bmp", L"R_Side_Interval", 0, 1, Ani_Time, true);
	p_Render->Set_Animation(L"Raise_Idle.bmp", L"L_Raise_Interval", 0, 1, Ani_Time, true);
	p_Render->Set_Animation(L"Raise_Idle.bmp", L"R_Raise_Interval", 0, 1, Ani_Time, true);


	p_Render->Set_Animation(L"Middle_To_Raise.bmp", L"L_Side_ToRaise", 0, 9, Ani_Time, false);
	p_Render->Set_Animation(L"Middle_To_Raise.bmp", L"R_Side_ToRaise", 0, 9, Ani_Time, false);
	p_Render->Set_Animation(L"Middle_To_Raise.bmp", L"L_Raise_ToSide", 9, 0, Ani_Time, false);
	p_Render->Set_Animation(L"Middle_To_Raise.bmp", L"R_Raise_ToSide", 9, 0, Ani_Time, false);

	p_Render->Change_Animation(L"R_Raise_Idle");
	p_Render->Pivot({ -5, -10 });
	p_Render->Set_TransColor(ORANGE);

	p_Collider = Create_Collider(L"Enemy", { 120, 120 });
	p_Collider->type(Collider::TYPE::RECT);

	m_Work.SetAniWork(p_Render);

	m_Work.CreateState(L"L_Raise_Idle", L"L_Raise_Idle");
	m_Work.CreateState(L"R_Raise_Idle", L"R_Raise_Idle");
	m_Work.CreateState(L"L_Side_Idle", L"L_Side_Idle");
	m_Work.CreateState(L"R_Side_Idle", L"R_Side_Idle");

	m_Work.CreateState(L"L_Side_Interval", L"L_Side_Interval");
	m_Work.CreateState(L"R_Side_Interval", L"R_Side_Interval");
	m_Work.CreateState(L"L_Raise_Interval", L"L_Raise_Interval");
	m_Work.CreateState(L"R_Raise_Interval", L"R_Raise_Interval");

	m_Work.CreateState(L"L_Side_Attack", L"L_Side_Attack");
	m_Work.CreateState(L"R_Side_Attack", L"R_Side_Attack");
	m_Work.CreateState(L"L_Raise_Attack", L"L_Raise_Attack");
	m_Work.CreateState(L"R_Raise_Attack", L"R_Raise_Attack");

	m_Work.CreateState(L"L_Raise_Wrecked", L"L_Raise_Wrecked");
	m_Work.CreateState(L"R_Raise_Wrecked", L"R_Raise_Wrecked");
	m_Work.CreateState(L"L_Side_Wrecked", L"L_Side_Wrecked");
	m_Work.CreateState(L"R_Side_Wrecked", L"R_Side_Wrecked");


	m_Work.CreateState(L"L_Side_ToRaise", L"L_Side_ToRaise");
	m_Work.CreateState(L"R_Side_ToRaise", L"R_Side_ToRaise");
	m_Work.CreateState(L"L_Raise_ToSide", L"L_Raise_ToSide");
	m_Work.CreateState(L"R_Raise_ToSide", L"R_Raise_ToSide");


	m_s_Acting = L"";
	m_s_Att = L"Attack";
	m_s_Idle = L"Idle";
	m_s_Interval = L"Interval";
	m_s_Damage = L"Damage";
	m_s_Wrecked = L"Wrecked";

	m_s_ToRaise = L"ToRaise";
	m_s_ToSide = L"ToSide";

	m_Work.ChangeState(L"R_Raise_Idle");
	Raise = true;

	m_Index = BaseEnemy::SaruBian;
}

void Enemy_Bradley::DirCheck()
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

	if (true == Raise)
	{
		m_s_Acting += L"Raise_";
	}
	else
	{
		m_s_Acting += L"Side_";
	}
}

bool Enemy_Bradley::StrCheck(const std::wstring _Str)
{
	std::wstring Raise = L"Raise_";
	std::wstring Side = L"Side_";
	if (m_Work.CurState()->Name == L"L_" + Raise + _Str || m_Work.CurState()->Name == L"R_" + Raise + _Str ||
		m_Work.CurState()->Name == L"L_" + Side + _Str || m_Work.CurState()->Name == L"R_" + Side + _Str)
	{
		return true;
	}
	return false;
}

void Enemy_Bradley::Update()
{
	// 원래 게임상에선 터뜨려야하지만 에디터에선 플레이어가 없기 때문에 터뜨리지 않는다.
	if (nullptr == PlayerMgr::MainPlayer()) { return; }
	if (1500 < MATHMANAGER.Distance(PlayerMgr::MainPlayer()->pos(), m_Pos)) { return; }
	
	Update_Bottom();
	Update_Gravity();

	DirCheck();

	if (Hp <= 0 && false == StrCheck(m_s_Wrecked))
	{
		m_s_Acting += m_s_Wrecked;
		m_Work.ChangeState(m_s_Acting);
		m_Work.AniWork()->size({ 200, 200 });
		m_Work.AniWork()->Pivot({ .0, -50 });
	}

	if (StrCheck(m_s_Idle))
	{
		Idle();
	}
	else if (StrCheck(m_s_Att))
	{
		Att();
	}
	else if (StrCheck(m_s_Interval))
	{
		AttackInterval();
	}
	else if (StrCheck(m_s_Damage))
	{
		Damage();
	}
	else if (StrCheck(m_s_ToRaise))
	{
		ToRaise();
	}
	else if (StrCheck(m_s_ToSide))
	{
		ToSide();
	}
	else if (StrCheck(m_s_Wrecked))
	{
		Wrecked();
	}
}

void Enemy_Bradley::DebugUpdate()
{
	WCHAR Str[100] = { 0, };

	swprintf_s(Str, L"EnemyState : %d", Raise);
	TEXT_OUT(500, 100, Str);
}

void Enemy_Bradley::ToSide()
{
	if (false == m_Work.AniWork()->IsActing())
	{
		Raise = false;
		DirCheck();
		m_s_Acting += m_s_Idle;
		m_Work.ChangeState(m_s_Acting);
		m_Time = .0f;
	}
}

void Enemy_Bradley::ToRaise()
{
	if (false == m_Work.AniWork()->IsActing())
	{
		Raise = true;
		DirCheck();
		m_s_Acting += m_s_Idle;
		m_Work.ChangeState(m_s_Acting);
		m_Time = .0f;
	}
}

void Enemy_Bradley::Idle()
{
	float Dis = MATHMANAGER.Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);
	if (AttRange >= Dis)
	{
		m_s_Acting += m_s_Interval;
		m_Work.ChangeState(m_s_Acting);
	}
	else if (MoveRange >= Dis && false == Raise)
	{
		m_s_Acting += m_s_ToRaise;
		m_Work.ChangeState(m_s_Acting);
	}
	else if (MoveRange < Dis && true == Raise)
	{
		m_s_Acting += m_s_ToSide;
		m_Work.ChangeState(m_s_Acting);
	}
}

void Enemy_Bradley::Att()
{
	m_Time += DELTATIME;

	// 미사일 쏘고
	// 공격하고
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);
	m_Work.AniWork()->Pivot({ .0f, .0f });


	if (MoveRange >= Dis && false == Raise)
	{
		m_s_Acting += m_s_ToRaise;
		m_Work.ChangeState(m_s_Acting);
	}
	else if (MoveRange < Dis && true == Raise)
	{
		m_s_Acting += m_s_ToSide;
		m_Work.ChangeState(m_s_Acting);
	}
	else if (AttRange <= Dis)
	{
		m_s_Acting += m_s_Idle;
		m_Work.ChangeState(m_s_Acting);
	}

	else if (Fire_Count > 0 && m_Time > Fire_Time)
	{
		if (true == Raise)
		{
			Weapon_EnemyBradley* NewBomb = m_MotherOfTheOne->StateOfOne_Create<Weapon_EnemyBradley>();
			NewBomb->Start(m_Pos + Positionf{ -50.0f, -50.0f }, Vector2f::Up);

			Effect_Bradley* NewEff = m_MotherOfTheOne->StateOfOne_Create<Effect_Bradley>();
			NewEff->Start(m_Pos + Positionf{ 120.0f, 80.0f }, Raise);
		}
		else
		{
			Weapon_EnemyBradley* NewBomb = m_MotherOfTheOne->StateOfOne_Create<Weapon_EnemyBradley>();
			NewBomb->Start(m_Pos + Positionf{ -100.0f, -20.0f }, Vector2f::Left);

			Effect_Bradley* NewEff = m_MotherOfTheOne->StateOfOne_Create<Effect_Bradley>();
			NewEff->Start(m_Pos + Positionf{ 120.0f, 0.0f }, Raise);
		}

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


void Enemy_Bradley::AttackInterval()
{
	if (m_Time < IntervalTime)
	{
		m_Time += DELTATIME;
	}
	else
	{
		m_s_Acting += m_s_Att;
		m_Work.ChangeState(m_s_Acting);
		Fire_Count = 8;
		m_Time = .0f;
	}
}


void Enemy_Bradley::Damage()
{
	if (false == m_Work.AniWork()->IsActing())
	{
		m_s_Acting += m_s_Idle;
		m_Work.ChangeState(m_s_Acting);
		m_Time = .0f;
	}
}


void Enemy_Bradley::Wrecked()
{
	if (false == m_Work.AniWork()->IsActing())
	{
		RESOURCEMANAGER.Play_Sound(L"MachineWrecked.mp3", .3f);
		One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
		Effect->Start(One_Effect::Effect_Type::BIG, m_Pos_Bottom_Check);
		Name(L"");
		Death(true);
	}
}





void Enemy_Bradley::CollisionEnter(Collider* _Other)
{
	std::wstring Temp = _Other->MotherOfTheOne_DE()->Name();
	if (Temp == L"P_Bullet" && false == StrCheck(m_s_Wrecked))
	{
		_Other->MotherOfTheOne_DE()->Activate();
		Hp--;
	}
	else if ((Temp == L"P_Explosion" || Temp == L"P_Moon") && false == StrCheck(m_s_Wrecked))
	{
		_Other->MotherOfTheOne_DE()->Activate();
		DirCheck();
		Hp -= 5;
	}
}