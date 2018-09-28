#include "stdafx.h"
#include "Bullet_Heavy.h"


#include "One_Player.h"
#include "MultiSprite.h"
#include "Sprite.h"
#include "Trans_Renderer.h"

#include "Collider.h"

#include "ResourceManager.h"
#include "MathManager.h"



#include "One_Effect.h"


Bullet_Heavy::Bullet_Heavy()
{
	m_Run_Speed = 1000;
}


Bullet_Heavy::~Bullet_Heavy()
{
}

void Bullet_Heavy::Init(Positionf _Pos, Dirf _Pos_Dir)
{
	Name(L"P_Bullet");
	m_Pos = _Pos;
	m_pos_Dir = _Pos_Dir;
	m_Status_Weapon = Weapon_Type::Explosion;

	Init_Collision();
	Init_Render();
}

void Bullet_Heavy::Init_Render()
{
	// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
	if (1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.X) ||
		1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.Y))
	{
		return;
	}

	Trans_Renderer* p_Render = Create_Renderer<Trans_Renderer>(10);
	MultiSprite* p_MultiData = RESOURCEMANAGER.Find_Res_MultiSprite(L"HeavyMachine.bmp");


	if (Vector2f::Right == m_pos_Dir)
	{
		p_Render->Set_Sprite(p_MultiData->Get_Sprite(0));
	}
	else if (Vector2f::Left == m_pos_Dir)
	{
		p_Render->Set_Sprite(p_MultiData->Get_Sprite(16));
	}
	else if (Vector2f::Up == m_pos_Dir)
	{
		p_Render->Set_Sprite(p_MultiData->Get_Sprite(48));
	}
	else if (Vector2f::Down == m_pos_Dir)
	{
		p_Render->Set_Sprite(p_MultiData->Get_Sprite(32));
	}

	// 1사 분면 - 랜딩을 다 다르게 해야하기 때문에 일일이 나누어야한다. ㅇ으.ㅡ;ㅓㅣ;ㅁㄴㅇㄹ
	// 1사 분면
	else if (0.0f < m_pos_Dir.X && 0.0f > m_pos_Dir.Y)
	{
		for (size_t i = 0; i < 15; i++)
		{
			if (Render_pos_Dir_Check(Vector2f::Right, Vector2f::Up, 15, i))
			{
				p_Render->Set_Sprite(p_MultiData->Get_Sprite(17 + i));
				break;
			}
		}

		// 안전 코드 - 영역 안에 없을 경우 - 직선
		if (nullptr == p_Render->Get_Sprte())
		{
			p_Render->Set_Sprite(p_MultiData->Get_Sprite(16));
		}
	}
	// 2사 분면
	else if (0.0f > m_pos_Dir.X && 0.0f > m_pos_Dir.Y)
	{
		for (size_t i = 0; i < 15; i++)
		{
			if (Render_pos_Dir_Check(Vector2f::Left, Vector2f::Up, 15, i))
			{
				// 리소스 역순 저장됌
				p_Render->Set_Sprite(p_MultiData->Get_Sprite(48 + (15 - i)));
				break;
			}
		}
		// 안전 코드 - 영역 안에 없을 경우 - 직선
		if (nullptr == p_Render->Get_Sprte())
		{
			p_Render->Set_Sprite(p_MultiData->Get_Sprite(48));
		}
	}
	// 3사 분면
	else if (0.0f > m_pos_Dir.X && 0.0f < m_pos_Dir.Y)
	{
		for (size_t i = 0; i < 15; i++)
		{
			if (Render_pos_Dir_Check(Vector2f::Left, Vector2f::Down, 15, i))
			{
				// 리소스 역순 저장됌
				p_Render->Set_Sprite(p_MultiData->Get_Sprite(32 + (15 - i)));
				break;
			}
		}
		// 안전 코드 - 영역 안에 없을 경우 - 직선
		if (nullptr == p_Render->Get_Sprte())
		{
			p_Render->Set_Sprite(p_MultiData->Get_Sprite(32));
		}
	}
	// 4사 분면
	else if (0.0f < m_pos_Dir.X && 0.0f < m_pos_Dir.Y)
	{
		for (size_t i = 0; i < 15; i++)
		{
			if (Render_pos_Dir_Check(Vector2f::Right, Vector2f::Down, 15, i))
			{
				// 리소스 역순 저장됌
				p_Render->Set_Sprite(p_MultiData->Get_Sprite(1 + i));
				break;
			}
		}
		// 안전 코드 - 영역 안에 없을 경우 - 직선
		if (nullptr == p_Render->Get_Sprte())
		{
			p_Render->Set_Sprite(p_MultiData->Get_Sprite(0));
		}
	}

	p_Render->Set_TransColor(RGB(0, 248, 0));
	p_Render->Pivot({ 40, 0 });
}








void Bullet_Heavy::Init_Collision()
{
	p_Collider = Create_Collider(L"Weapon", { 10, 10 });
	p_Collider->type(Collider::TYPE::CIRCLE);
	p_Collider->MotherOfTheOne_DE(this);
	p_Collider->Pivot({ 40, 0 });
}

/***************** Update *****************/

void Bullet_Heavy::Update()
{
	UpdateCheckLive();
	Update_Fire();
}

void Bullet_Heavy::Update_Fire()
{
	// window 좌표 기준 Y축 반전 있어야함 -> 반전을 벡터에서 시켜버림
	m_Pos.X += (m_pos_Dir.X * m_Run_Speed * DELTATIME);
	m_Pos.Y += (m_pos_Dir.Y * m_Run_Speed * DELTATIME);
	p_Collider->Calculate_Figure_Pos();
}

void Bullet_Heavy::Activate()
{
	RESOURCEMANAGER.Play_Sound(L"Bullet_Act.mp3", .3f);
	One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
	Effect->Start(One_Effect::Effect_Type::BULLET, m_Pos + Positionf{ .0f, p_Collider->size().PartY() });

	// 다 튀었으면 빨리 사라져야함
	m_LiveTime = .0f;
}
