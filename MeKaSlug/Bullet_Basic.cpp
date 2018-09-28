#include "stdafx.h"
#include "Bullet_Basic.h"

#include "One_Player.h"
#include "Trans_Renderer.h"
#include "ResourceManager.h"
#include "Collider.h"

#include "One_Effect.h"

Bullet_Basic::Bullet_Basic()
{
}


Bullet_Basic::~Bullet_Basic()
{
}

// 랜딩
void Bullet_Basic::Init(Positionf _Pos, Positionf _Pos_Dir)
{
	Name(L"P_Bullet");
	m_pos_Dir = _Pos_Dir;
	m_Pos = _Pos;

	m_Status_Weapon = Weapon_Type::Explosion;
	
	Trans_Renderer* p_Render = Create_Renderer<Trans_Renderer>(30);
	MultiSprite* p_MultiData = RESOURCEMANAGER.Find_Res_MultiSprite(L"Bullet_Basic.bmp");

	p_Render->Set_Sprite(p_MultiData->Get_Sprite(0));


	if (Vector2f::Right == m_pos_Dir || Vector2f::Left == m_pos_Dir)
	{
		p_Render->Set_Sprite(p_MultiData->Get_Sprite(0));
	}
	else if (Vector2f::Up == m_pos_Dir || Vector2f::Down == m_pos_Dir)
	{
		p_Render->Set_Sprite(p_MultiData->Get_Sprite(1));
	}

	p_Render->Set_TransColor(RGB(104, 144, 168));
	p_Render->Pivot({ 5, 5 });

	p_Collider = Create_Collider(L"Weapon", { 10, 10 });
	p_Collider->type(Collider::TYPE::RECT);
	p_Collider->MotherOfTheOne_DE(this);
	p_Collider->Pivot(p_Collider->size() * .5f);
}

void Bullet_Basic::Update()
{
	UpdateCheckLive();
	Update_Fire();
}

void Bullet_Basic::Update_Fire()
{
	m_Pos += m_pos_Dir * m_Run_Speed * TIMEMANAGER.DeltaTime();
	p_Collider->Calculate_Figure_Pos();
}


void Bullet_Basic::Activate()
{
	RESOURCEMANAGER.Play_Sound(L"Bullet_Act.mp3", .3f);
	One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
	Effect->Start(One_Effect::Effect_Type::BULLET, m_Pos + Positionf{ .0f, p_Collider->size().PartY() });

	// 다 튀었으면 빨리 사라져야함
	m_LiveTime = .0f;
}


