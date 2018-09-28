#include "stdafx.h"
#include "Enemy_Boss.h"


#include "Animator.h"
#include "PlayerMgr.h"
#include "Collider.h"

#include "Weapon_EnemyTankCannon.h"

#include "One_Effect.h"
#include "ResourceManager.h"

#include "Weapon_MagmaCannon.h"
#include "Effect_MagmaCannon.h"

#include "Weapon_FireWave.h"
#include "Effect_FireWater.h"

#include "Weapon_MedicineCannon.h"

#include <stdlib.h>
#include <time.h>

Enemy_Boss::Enemy_Boss()
{
}


Enemy_Boss::~Enemy_Boss()
{
}

void Enemy_Boss::Init()
{
	srand((unsigned int)time(NULL));

	NextStatus = 1;

	Hp = 100;
	Fire_Count = 0;
	Fire_Time = .3f;
	Mode_Time = 5.0f;

	Name(L"Enemy_Boss");

	m_Pos = { m_MotherOfTheOne->CameraPos().X + CORE.GetSize().PartX(), 100 };
	Speed = 1.0f;
	CurSpeed = .0f;
	m_Time = .0f; m_f_Time = .0f;

	float Ani_Time = .05f;

	Animator* p_Render = Create_Renderer<Animator>(8);

	p_Render->Set_Animation(L"Enemy_Boss.bmp", L"Idle", 1, 1, Ani_Time, false);
	p_Render->Set_Animation(L"Enemy_Boss.bmp", L"Wrecked", 0, 0, Ani_Time, false);
	p_Render->Set_Animation(L"Enemy_Boss.bmp", L"MedicineCannon_Open", 2, 11, Ani_Time, false);
	p_Render->Set_Animation(L"Enemy_Boss.bmp", L"MedicineCannon_Close", 11, 2, Ani_Time, false);
	p_Render->Set_Animation(L"Enemy_Boss.bmp", L"MagmaCannon", 12, 17, Ani_Time, true);


	p_Render->Change_Animation(L"Idle");
	p_Render->Pivot({ -5, -10 });
	p_Render->Set_TransColor(ORANGE);

	p_Collider = Create_Collider(L"Enemy", { 400, 400 });
	p_Collider->type(Collider::TYPE::CIRCLE);

	m_Work.SetAniWork(p_Render);

	m_Work.CreateState(L"Idle", L"Idle");
	m_Work.CreateState(L"Wrecked", L"Wrecked");

	m_Work.CreateState(L"MagmaCannon", L"MagmaCannon");
	m_Work.CreateState(L"MedicineCannon_Open", L"MedicineCannon_Open");
	m_Work.CreateState(L"MedicineCannon_Close", L"MedicineCannon_Close");
	m_Work.CreateState(L"WaveAttack", L"Idle");
	m_Work.CreateState(L"RiseAttack", L"Idle");
	m_Work.CreateState(L"Start", L"Idle");

	m_s_Acting = L"";
	
	m_s_Start = L"Start";
	m_s_MagamaCannon = L"MagmaCannon";
	m_s_MedicineCannon_Open = L"MedicineCannon_Open";
	m_s_MedicineCannon_Close = L"MedicineCannon_Close";
	m_s_WaveAttack = L"WaveAttack";
	m_s_RiseAttack = L"RiseAttack";
	m_s_Idle = L"Idle";
	m_s_Wrecked = L"Wrecked";

	m_Work.ChangeState(L"Start");
}


bool Enemy_Boss::StrCheck(const std::wstring _Str)
{
	if (m_Work.CurState()->Name == _Str)
	{
		return true;
	}
	return false;
}

void Enemy_Boss::Update()
{
	m_f_Time += DELTATIME;
	m_Time += DELTATIME;

	// 원래 게임상에선 터뜨려야하지만 에디터에선 플레이어가 없기 때문에 터뜨리지 않는다.
	if (nullptr == PlayerMgr::MainPlayer()) { return; }


	if (Hp <= 0 && false == StrCheck(m_s_Wrecked))
	{
		RESOURCEMANAGER.Play_Sound(L"Boss_Wrecked.mp3");
		m_Pos.Y = 700;
		m_s_Acting = L"";
		m_s_Acting += m_s_Wrecked;
		m_Work.ChangeState(m_s_Acting);
	}


	if (StrCheck(m_s_Idle))
	{
		Idle();
	}
	else if (StrCheck(m_s_Start))
	{
		Start();
	}
	else if (StrCheck(m_s_MagamaCannon))
	{
		MagamaCannon();
	}
	else if (StrCheck(m_s_MedicineCannon_Open))
	{
		MedicineCannon_Open();
	}
	else if (StrCheck(m_s_MedicineCannon_Close))
	{
		MedicineCannon_Close();
	}
	else if (StrCheck(m_s_WaveAttack))
	{
		WaveAttack();
	}
	else if (StrCheck(m_s_RiseAttack))
	{
		RiseAttack();
	}
	else if (StrCheck(m_s_Wrecked))
	{
		Wrecked();
	}
}

void Enemy_Boss::DebugUpdate()
{
	WCHAR Str[100] = { 0, };

	swprintf_s(Str, L"EnemyState : %s", m_Work.CurState()->Name.c_str());
	TEXT_OUT(500, 20, Str);


	swprintf_s(Str, L"Boss Position : %3.2f, %3.2f", m_Pos.X, m_Pos.Y);
	TEXT_OUT(500, 40, Str);

	swprintf_s(Str, L"Boss Hp : %d", Hp);
	TEXT_OUT(500, 60, Str);
}

void Enemy_Boss::Start()
{
	if (m_Time > Mode_Time)
	{
		m_s_Acting = m_s_WaveAttack;
		m_Work.ChangeState(m_s_Acting);

		m_Time = .0f;
		m_f_Time = .0f;
	}

	// 우선 위를 맞추고 사이드를 맞춘다.
	if (m_Pos.Y < 500)
	{
		m_Pos.Y += 100 * DELTATIME;
		return;
	}
	else
	{
		m_Pos.Y = 500;
	}
}

void Enemy_Boss::Idle()
{
	if (m_Time > Mode_Time)
	{
		if (1 == NextStatus || 3 < NextStatus)
		{
			NextStatus = 1;
			m_s_Acting = m_s_WaveAttack;
		}
		if (2 == NextStatus)
		{
			m_s_Acting = m_s_MagamaCannon;
		}
		if (3 == NextStatus)
		{
			m_s_Acting = m_s_MedicineCannon_Open;
		}

		m_Work.ChangeState(m_s_Acting);

		m_Time = .0f;
		m_f_Time = .0f;
	}

	Positionf P_Pos = PlayerMgr::MainPlayer()->pos();

	// 우선 위를 맞추고 사이드를 맞춘다.
	if (m_Pos.Y > 500)
	{
		m_Pos.Y -= Speed * m_f_Time;
		return;
	}
	else
	{
		m_Pos.Y = 500;
	}

	// 올라오는 시점
	if (m_Pos.Y <= 1010 && m_Pos.Y >= 990)
	{
		for (size_t i = 0; i < 10; i++)
		{
			int x = i - 5;
			Effect_FireWater* NewEffectWater = m_MotherOfTheOne->StateOfOne_Create<Effect_FireWater>();
			NewEffectWater->Start({ m_Pos.X + x * 40, 950 });
		}
	}

	if (m_Pos.X < P_Pos.X)
	{
		m_Pos.X += MATHMANAGER.Absolute_Num(P_Pos.X - m_Pos.X) * Speed * DELTATIME;
	}
	else if (m_Pos.X > P_Pos.X)
	{
		m_Pos.X -= MATHMANAGER.Absolute_Num(P_Pos.X - m_Pos.X) * Speed * DELTATIME;
	}
	
}

void Enemy_Boss::Wrecked()
{
	m_Pos.Y += 20 * DELTATIME;
	
	if (.5f < m_Time)
	{
		if (7.0f > m_f_Time)
		{
			RESOURCEMANAGER.Play_Sound(L"MachineWrecked.mp3", .3f);
		}
		
		
		One_Effect* NewEffect= m_MotherOfTheOne->StateOfOne_Create<One_Effect>();

		int x = rand() % 100;
		int y = rand() % 200;

		int z = rand() % 2;

		if (0 == z)
		{
			NewEffect->Start(One_Effect::Effect_Type::BIG, m_Pos + Positionf{ (float)x, (float)y});
		}
		if (1 == z)
		{
			NewEffect->Start(One_Effect::Effect_Type::BIG, m_Pos - Positionf{ (float)x,(float)y });
		}

		if (m_Pos.Y > 800)
		{
			for (size_t i = 0; i < 10; i++)
			{
				int x = i - 5;
				Effect_FireWater* NewEffectWater = m_MotherOfTheOne->StateOfOne_Create<Effect_FireWater>();
				NewEffectWater->Start({ m_Pos.X + x * 40, 950 });
			}
		}
		m_Time = .0f;
	}
}

void Enemy_Boss::Init_Idle()
{
	m_s_Acting = m_s_Idle;
	m_Work.ChangeState(m_s_Acting);

	m_Time = .0f;
	m_f_Time = .0f;
	Fire_Count = 0;

	if (4 >= NextStatus)
	{
		NextStatus++;
	}
	else
	{
		NextStatus = 1;
	}
}

void Enemy_Boss::MagamaCannon()
{
	if (m_Time > Mode_Time)
	{
		Init_Idle();
	}

	if (m_f_Time > Fire_Time)
	{
		RESOURCEMANAGER.Play_Sound(L"Boss_Medicine.mp3", .5f);
		Weapon_MagmaCannon* NewMagma =m_MotherOfTheOne->StateOfOne_Create<Weapon_MagmaCannon>();
		NewMagma->Start({ m_Pos.X, m_Pos.Y + 200 });


		Effect_MagmaCannon* NewEffectMagma = m_MotherOfTheOne->StateOfOne_Create<Effect_MagmaCannon>();
		NewEffectMagma->Start(this);
		m_f_Time = .0f;
	}

	Positionf P_Pos = PlayerMgr::MainPlayer()->pos();

	if (m_Pos.X < P_Pos.X)
	{
		m_Pos.X += MATHMANAGER.Absolute_Num(P_Pos.X - m_Pos.X) * Speed * DELTATIME;
	}
	else if (m_Pos.X > P_Pos.X)
	{
		m_Pos.X -= MATHMANAGER.Absolute_Num(P_Pos.X - m_Pos.X) * Speed * DELTATIME;
	}

	m_Pos.Y = 500;
}

void Enemy_Boss::MedicineCannon_Open()
{
	if (m_Time > Mode_Time)
	{
		m_s_Acting = m_s_MedicineCannon_Close;
		m_Work.ChangeState(m_s_Acting);

		m_Time = .0f;
		m_f_Time = .0f;
		Fire_Count = 0;
	}
	
	if (m_f_Time > Fire_Time * 2.5f)
	{
		RESOURCEMANAGER.Play_Sound(L"Boss_Medicine.mp3", .5f);
		Weapon_MedicineCannon* NewMagma = m_MotherOfTheOne->StateOfOne_Create<Weapon_MedicineCannon>();
		NewMagma->Start(m_Pos);
		m_f_Time = .0f;
	}

	m_Pos.Y = 500;
}
void Enemy_Boss::MedicineCannon_Close()
{
	if (false == m_Work.AniWork()->IsActing())
	{
		Init_Idle();
	}
}

void Enemy_Boss::WaveAttack()
{	
	int TargetPos = 1800;

	if (0 < Fire_Count)
	{		
		/*if (NextStatus == 0)
		{
			Init_Idle();
		}
		else*/
		{
			m_s_Acting = m_s_RiseAttack;
			m_Work.ChangeState(m_s_Acting);

			m_Time = .0f;
			m_f_Time = .0f;
			Fire_Count = 0;
		}

		return;
	}

	if ((int)m_Pos.X == TargetPos)
	{
		if (m_Pos.Y < 1000)
		{
			m_Pos.Y += Speed * m_f_Time;
		}
		else if (m_Pos.Y > 1000)
		{
			RESOURCEMANAGER.Play_Sound(L"Boss_Wave.mp3", .5f);
			Weapon_FireWave* NewEffectMagma = m_MotherOfTheOne->StateOfOne_Create<Weapon_FireWave>();
			NewEffectMagma->Start(m_Pos);
			
			for (size_t i = 0; i < 10; i++)
			{
				int x = i - 5;
				Effect_FireWater* NewEffectWater = m_MotherOfTheOne->StateOfOne_Create<Effect_FireWater>();
				NewEffectWater->Start({ m_Pos.X + x * 40, 950 });
			}

			m_f_Time = .0f;
			Fire_Count++;
		}
		return;
	}

	// 목표지점으로 이동
	if (m_Pos.X < TargetPos)
	{
		m_Pos.X += MATHMANAGER.Absolute_Num(TargetPos + 20 - m_Pos.X) * Speed * DELTATIME;
	}
	else if (m_Pos.X > TargetPos)
	{
		m_Pos.X -= MATHMANAGER.Absolute_Num(TargetPos - 20 - m_Pos.X) * Speed * DELTATIME;
	}

	// 낙하 보정
	m_f_Time = .0f;
}
void Enemy_Boss::RiseAttack()
{
	int TargetPos = (int)PlayerMgr::MainPlayer()->pos().X;

	if (m_Pos.Y < 1400)
	{
		m_Pos.Y += Speed * m_f_Time;
	}
	else if (m_Pos.Y > 1400)
	{
		// 목표지점으로 이동
		if (m_Pos.X < TargetPos - 20)
		{
			m_Pos.X += MATHMANAGER.Absolute_Num(TargetPos + 20 - m_Pos.X) * Speed * DELTATIME;
		}
		else if (m_Pos.X > TargetPos + 20)
		{
			m_Pos.X -= MATHMANAGER.Absolute_Num(TargetPos - 20 - m_Pos.X) * Speed * DELTATIME;
		}
		else
		{
			Init_Idle();
		}
	}
}



void Enemy_Boss::CollisionEnter(Collider* _Other)
{
	std::wstring Temp = _Other->MotherOfTheOne_DE()->Name();
	if (Temp == L"P_Bullet" && false == StrCheck(m_s_Wrecked))
	{
		_Other->MotherOfTheOne_DE()->Activate();
		Hp--;
	}
	else if (Temp == L"P_Explosion" && false == StrCheck(m_s_Wrecked))
	{
		_Other->MotherOfTheOne_DE()->Activate();
		Hp -= 5;
	}
}