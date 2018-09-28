#include "stdafx.h"
#include "Enemy_Bomb.h"
#include "Animator.h"
#include "PlayerMgr.h"
#include "Collider.h"

// 카메라 이동 지금 캐릭터로도

// 맵에디터씬 만들고
// 백그라운드 변경할수 있게 해놔라
// 백그라운드 랜더 안되게 하는 기능 만들어 놔라.
// BackPixelName 픽셀

class MonsterData 
{
	//IPOS m_Pos;
	int Type;
};

class StageData {
	wchar_t BackGroundName[256];
	wchar_t BackPixelName[256];
	MonsterData* pMonsterData = new MonsterData[1000];
};

class EditStageData {
	std::wstring BackGroundName[256];
	std::wstring BackPixelName[256];
	std::vector<MonsterData> MonData;
};


Enemy_Bomb::Enemy_Bomb()
{
}


Enemy_Bomb::~Enemy_Bomb()
{
}


void Enemy_Bomb::Init()
{
	m_Pos = { 500, 600 };
	Hp = 100;
	AttRange = 100.f;
	MoveRange = 500.f;
	Speed = 100.0f;
	OutRange = 500.f;
	IntervalTime = 3.0f;
	thisTime = .0f;

	float Ani_Time = .05f;

	Animator* p_Render = Create_Renderer<Animator>(5);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"L_Idle", 12, 18, Ani_Time, true);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"R_Idle", 299, 293, Ani_Time, true);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"R_Attack", 24, 37, Ani_Time, true);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"L_Attack", 59, 47, Ani_Time, true);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"L_Move", 0, 11, Ani_Time, true);
	p_Render->Set_Animation(L"Enemy_Edit.bmp", L"R_Move", 311, 300, Ani_Time, true);

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


	m_s_Acting = L"";
	m_s_Att = L"Attack";
	m_s_Move = L"Move";
	m_s_Idle = L"Idle";
	m_s_Interval = L"Interval";

	m_Work.ChangeState(L"R_Idle");
}

void Enemy_Bomb::DirCheck()
{
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
		m_pos_Dir = MATHMANAGER.PntToPnt_Dir(PlayerMgr::MainPlayer()->pos(), m_Pos);

		if(m_pos_Dir.X < .0f) { m_pos_Dir = Vector2f::Left; }
		else { m_pos_Dir = Vector2f::Right; }

		m_Pos = { m_Pos.X + m_pos_Dir.X * DELTATIME * Speed, m_Pos.Y };
	}
	Update_Bottom();
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
	// 미사일 쏘고
	// 공격하고
	float Dis = MathManager::Inst().Distance(PlayerMgr::MainPlayer()->pos(), m_Pos);
	m_Work.AniWork()->Pivot({ .0f, .0f });

	if (AttRange <= Dis)
	{
		m_s_Acting += m_s_Idle;
		m_Work.ChangeState(m_s_Acting);
	}
	else if (false == m_Work.AniWork()->IsActing())
	{
		m_s_Acting += m_s_Interval;
		m_Work.ChangeState(m_s_Acting);
	}
}

void Enemy_Bomb::AttackInterval()
{
	if (thisTime < IntervalTime)
	{
		thisTime += DELTATIME;
	}
	else
	{
		m_s_Acting += m_s_Att;
		m_Work.ChangeState(m_s_Acting);
		thisTime = .0f;
	}
}

void Enemy_Bomb::Run()
{


}

