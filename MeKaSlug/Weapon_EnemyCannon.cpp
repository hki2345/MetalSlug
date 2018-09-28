#include "stdafx.h"
#include "Weapon_EnemyCannon.h"
#include "One_Effect.h"

#include "Collider.h"
#include "MultiSprite.h"
#include "Trans_Renderer.h"
#include "PlayerMgr.h"

#include "ResourceManager.h"


Weapon_EnemyCannon::Weapon_EnemyCannon()
{
	m_v_Gravity = 5.0f;
	m_v_Jump_Force = 600.0f;
	m_Run_Speed = 200;
}


Weapon_EnemyCannon::~Weapon_EnemyCannon()
{
}

void Weapon_EnemyCannon::DebugUpdate()
{
	WCHAR Str[100] = { 0, };

	swprintf_s(Str, L"Rending Dir: %3.2f %3.2f", m_pos_Dir.X, m_pos_Dir.Y);
	TEXT_OUT(300, 200, Str);
}


void Weapon_EnemyCannon::Start(Positionf _Pos, Dirf _Pos_Dir)
{
	Name(L"E_Explosion");
	m_Pos = _Pos;
	m_pos_Dir = _Pos_Dir;
	m_pos_PrevDir = _Pos_Dir;


	m_Status_Weapon = Weapon_Type::Explosion;
	Init_Collision();
	Init_Render();

	Update_Force(m_v_Jump_Force);
}

void Weapon_EnemyCannon::Init_Render()
{
	// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
	if (1.0f < MATHMANAGER.Absolute_Num(m_pos_PrevDir.X) ||
		1.0f < MATHMANAGER.Absolute_Num(m_pos_PrevDir.Y))
	{
		return;
	}

	p_Trans_Render = Create_Renderer<Trans_Renderer>(10);
	p_Render = RESOURCEMANAGER.Find_Res_MultiSprite(L"Bomb_Cannon_Bullet.bmp");
	p_Render->Set_TransColor(RGB(255, 105, 0));
	
	p_Trans_Render->Set_Sprite(p_Render->Get_Sprite(30));
	p_Trans_Render->Set_TransColor(RGB(255, 105, 0));
}

void Weapon_EnemyCannon::Activate()
{
	One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
	Effect->Start(One_Effect::Effect_Type::MIDDLE, m_Pos + Positionf{ .0f, p_Collider->size().PartY() });

	// 다 튀었으면 빨리 사라져야함
	m_LiveTime = .0f;
}

void Weapon_EnemyCannon::Init_Collision()
{
	p_Collider = Create_Collider(L"Weapon", { 30, 30 });
	p_Collider->type(Collider::TYPE::CIRCLE);

	p_Collider->MotherOfTheOne_DE(this);
	p_Collider->Calculate_Figure_Pos();
	p_Collider->Pivot(p_Collider->size() * .5f);
}

/***************** Update *****************/

void Weapon_EnemyCannon::Update()
{
	UpdateCheckLive();
	Update_Fire();
	Update_Render();

	// 위치 차를 이용한 벡터 출력
	m_PrevPos = m_Pos;
}

void Weapon_EnemyCannon::Update_Fire()
{
	TheOne::Update_Gravity();
	m_Pos.X += (m_Run_Speed)* DELTATIME * m_pos_PrevDir.X;
}

void Weapon_EnemyCannon::Update_BottomLine()
{
	if (true == m_b_BottomCheck)
	{
		Activate();
	}
}

void Weapon_EnemyCannon::Update_Render()
{
	size_t DivideSprite = 5;

	m_pos_Dir = MATHMANAGER.PntToPnt_Dir(m_Pos, m_PrevPos);
	if (Vector2f::Right == m_pos_Dir)
	{
		p_Trans_Render->Set_Sprite(p_Render->Get_Sprite(30));
	}
	else if (Vector2f::Left == m_pos_Dir)
	{
		p_Trans_Render->Set_Sprite(p_Render->Get_Sprite(24));
	}
	else if (Vector2f::Up == m_pos_Dir)
	{
		p_Trans_Render->Set_Sprite(p_Render->Get_Sprite(20));
	}
	else if (Vector2f::Down == m_pos_Dir)
	{
		p_Trans_Render->Set_Sprite(p_Render->Get_Sprite(25));
	}

	// 1사 분면 - 랜딩을 다 다르게 해야하기 때문에 일일이 나누어야한다. ㅇ으.ㅡ;ㅓㅣ;ㅁㄴㅇㄹ
	// 1사 분면
	else if (0.0f < m_pos_Dir.X && 0.0f > m_pos_Dir.Y)
	{
		for (size_t i = 0; i < DivideSprite; i++)
		{
			if (Render_pos_Dir_Check(Vector2f::Right, Vector2f::Up, DivideSprite, i))
			{
				p_Trans_Render->Set_Sprite(p_Render->Get_Sprite(30 + i));
				break;
			}
		}
	}
	// 2사 분면
	else if (0.0f > m_pos_Dir.X && 0.0f > m_pos_Dir.Y)
	{
		for (size_t i = 0; i < DivideSprite; i++)
		{
			if (Render_pos_Dir_Check(Vector2f::Left, Vector2f::Up, DivideSprite, i))
			{
				// 리소스 역순 저장됌
				p_Trans_Render->Set_Sprite(p_Render->Get_Sprite(20 + (DivideSprite - 1 - i)));
				break;
			}
		}
	}
	// 3사 분면
	else if (0.0f > m_pos_Dir.X && 0.0f < m_pos_Dir.Y)
	{
		for (size_t i = 0; i < DivideSprite; i++)
		{
			if (Render_pos_Dir_Check(Vector2f::Left, Vector2f::Down, DivideSprite, i))
			{
				// 리소스 역순 저장됌
				p_Trans_Render->Set_Sprite(p_Render->Get_Sprite(25 + (DivideSprite - 1 - i)));
				break;
			}
		}
	}
	// 4사 분면
	else if (0.0f < m_pos_Dir.X && 0.0f < m_pos_Dir.Y)
	{
		for (size_t i = 0; i < DivideSprite; i++)
		{
			if (Render_pos_Dir_Check(Vector2f::Right, Vector2f::Down, DivideSprite, i))
			{
				// 리소스 역순 저장됌
				p_Trans_Render->Set_Sprite(p_Render->Get_Sprite(35 + i));
				break;
			}
		}
	}
}