#include "stdafx.h"
#include "Player_Eri.h"

#include "Weapon_Bomb.h"
#include "BossMgr.h"

#include "Animator.h"

Player_Eri::Player_Eri()
{
}


Player_Eri::~Player_Eri()
{
}



void Player_Eri::Init()
{
	One_Player::Init();
	One_Player::Init_Collision();
	Init_Render();
}

void Player_Eri::Update()
{
	One_Player::Update_Fever();
	TheOne::Update_Gravity();
	if (nullptr != BossMgr::MainBoss() && BossMgr::MainBoss()->BossDie())
	{
		m_Time += DELTATIME;
		if (m_Ceremony_Time < m_Time)
		{
			m_Status_Body = Body_Ceremony;
			m_Status_Leg = Leg_BodyAcition;
			Update_Set_AniRender();
			return;
		}

		m_Status_Body = Body_Idle;
		m_Status_Leg = Leg_Idle;

		Update_Set_AniRender();
		return;
	}

	switch (m_Status_Die)
	{
	case One_Player::Die_None:
		One_Player::Update_Jump();

		if (false == m_Auto_Move)
		{
			Update_Key();
			One_Player::Update_Key_Render();
		}
		else if (true == m_Auto_Move)
		{
			One_Player::Update_AutoMove();
		}
		break;
	case One_Player::Die_Respawn:
	case One_Player::Die_Sword:
	case One_Player::Die_Shut:
	case One_Player::Die_Air:
	case One_Player::Die_Fire:
	case One_Player::Die_Laser:
		One_Player::Update_Die();
		break;
	default:
		break;
	}
	Update_Set_AniRender();
}



void Player_Eri::Init_Render()
{
	float Ani_Time = .08f;
	float Jump_Ani_Time = .01f;

	// 생성자 값은 레이어층
	p_RenderBody = Create_Renderer<Animator>(10);

	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_Idle", 0, 3, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_Idle", 3, 0, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_Look_Up_Idle", 6, 9, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_Look_Up_Idle", 7, 4, Ani_Time, true);

	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_RunStop", 12, 14, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_RunStop", 15, 13, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_Run", 36, 47, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_Run", 47, 36, Ani_Time, true);

	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_Jump", 24, 29, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_Jump", 31, 26, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_RunJump", 32, 34, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_RunJump", 35, 33, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_JumpLookUp", 36, 47, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_JumpLookUp", 47, 36, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_JumpLookDown", 74, 74, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_JumpLookDown", 73, 73, Ani_Time, true);

	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_Shot_Side", 48, 55, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_Shot_Side", 55, 48, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_Shot_Up", 56, 65, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_Shot_Up", 67, 58, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_Shot_Down", 68, 71, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_Shot_Down", 71, 68, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_Sword1", 76, 81, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_Sword1", 83, 78, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_Sword2", 84, 92, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_Sword2", 95, 86, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Right.bmp", L"Right_Eri_NoGun_Body_Bomb", 96, 101, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_NoGun_Body_Left.bmp", L"Left_Eri_NoGun_Body_Bomb", 103, 98, Ani_Time, false);




	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Idle", 8, 11, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Idle", 11, 8, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Look_Up_Idle", 12, 15, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Look_Up_Idle", 15, 12, Ani_Time, true);

	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_RunStop", 8, 11, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_RunStop", 11, 8, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Run", 28, 39, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Run", 39, 28, Ani_Time, true);

	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_JumpLookUp", 12, 15, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_JumpLookUp", 15, 12, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_JumpLookDown", 52, 54, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_JumpLookDown", 55, 53, Ani_Time, true);

	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Jump", 20, 23, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Jump", 23, 20, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_RunJump", 24, 31, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_RunJump", 31, 24, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Shot_Side", 0, 3, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Shot_Side", 3, 0, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Shot_Up", 4, 7, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Shot_Up", 7, 4, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Shot_Down", 44, 47, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Shot_Down", 47, 44, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Shot_AngleUp", 40, 41, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Shot_AngleUp", 43, 42, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Shot_AngleDown", 47, 48, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Shot_AngleDown", 48, 47, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Sword1", 56, 61, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Sword1", 63, 58, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Sword2", 64, 72, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Sword2", 75, 66, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Right.bmp", L"Right_Eri_Gun_Body_Bomb", 76, 81, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_Gun_Body_Left.bmp", L"Left_Eri_Gun_Body_Bomb", 83, 78, Ani_Time, false);



	p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Idle");
	p_RenderBody->Pivot({ 5, -10 });



	p_RenderLeg = Create_Renderer<Animator>(9);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Right.bmp", L"Right_Eri_Leg_Idle", 0, 0, Ani_Time, true);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Left.bmp", L"Left_Eri_Leg_Idle", 3, 3, Ani_Time, true);

	p_RenderLeg->Set_Animation(L"Eri_Leg_Right.bmp", L"Right_Eri_Leg_RunStop", 7, 4, Ani_Time, false);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Left.bmp", L"Left_Eri_Leg_RunStop", 4, 7, Ani_Time, false);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Right.bmp", L"Right_Eri_Leg_Run", 24, 35, Ani_Time, true);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Left.bmp", L"Left_Eri_Leg_Run", 35, 24, Ani_Time, true);



	p_RenderLeg->Set_Animation(L"Eri_Leg_Right.bmp", L"Right_Eri_Leg_JumpUp", 8, 13, Ani_Time, false);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Left.bmp", L"Eri_Leg_Left_JumpUp", 11, 8, Ani_Time, false);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Right.bmp", L"Right_Eri_Leg_JumpDown", 13, 13, Ani_Time, false);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Left.bmp", L"Left_Eri_Leg_JumpDown", 15, 14, Ani_Time, false);

	p_RenderLeg->Set_Animation(L"Eri_Leg_Right.bmp", L"Right_Eri_Leg_Run_JumpUp", 16, 18, Ani_Time, false);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Left.bmp", L"Left_Eri_Leg_Run_JumpUp", 19, 17, Ani_Time, false);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Right.bmp", L"Right_Eri_Leg_Run_JumpDown", 20, 21, Ani_Time, false);
	p_RenderLeg->Set_Animation(L"Eri_Leg_Left.bmp", L"Left_Eri_Leg_Run_JumpDown", 23, 22, Ani_Time, false);



	p_RenderLeg->Set_Animation(L"Eri_Leg_Left.bmp", L"Eri_Leg_None", 0, 0, Ani_Time, false);


	p_RenderLeg->Change_Animation(L"Left_Eri_Leg_Idle");
	p_RenderLeg->Pivot({ -5, -10 });




	p_RenderBody->Set_Animation(L"Eri_Respawn.bmp", L"Eri_Respawn", 0, 6, .04f, false);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_NoGun_Body_Sit_Walk", 0, 10, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_Gun_Body_Sit_Walk", 12, 22, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_NoGun_Body_Sit_Walk", 11, 1, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_Gun_Body_Sit_Walk", 23, 13, Ani_Time, true);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_NoGun_Body_Sit", 27, 30, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_Gun_Body_Sit", 35, 38, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_NoGun_Body_Sit", 28, 25, Ani_Time, true);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_Gun_Body_Sit", 36, 33, Ani_Time, true);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_NoGun_Body_Sitting", 24, 30, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_Gun_Body_Sitting", 32, 38, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_NoGun_Body_Sitting", 31, 25, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_Gun_Body_Sitting", 39, 33, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_NoGun_Body_Bomb", 40, 45, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_Gun_Body_Bomb", 48, 53, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_NoGun_Body_Bomb", 47, 42, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_Gun_Body_Bomb", 55, 50, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_NoGun_Body_Sword", 56, 64, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_Gun_Body_Sword", 68, 76, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_NoGun_Body_Sword", 67, 59, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_Gun_Body_Sword", 79, 72, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_NoGun_Body_Shut", 80, 93, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Right.bmp", L"Right_Eri_All_Gun_Body_Shut", 96, 103, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_NoGun_Body_Shut", 95, 83, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Left.bmp", L"Left_Eri_All_Gun_Body_Shut", 103, 96, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Right.bmp", L"Right_Eri_All_NoGun_Body_SitKick", 16, 19, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Right.bmp", L"Right_Eri_All_Gun_Body_SitKick", 16, 19, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Left.bmp", L"Left_Eri_All_NoGun_Body_SitKick", 19, 16, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Left.bmp", L"Left_Eri_All_Gun_Body_SitKick", 23, 20, Ani_Time, false);


	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Right.bmp", L"Right_Eri_All_NoGun_Body_Kick", 0, 5, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Right.bmp", L"Right_Eri_All_Gun_Body_Kick", 8, 13, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Left.bmp", L"Left_Eri_All_NoGun_Body_Kick", 7, 2, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Left.bmp", L"Left_Eri_All_Gun_Body_Kick", 15, 10, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Right.bmp", L"Right_Eri_All_Body_MoonSlasher", 80, 94, .04f, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Left.bmp", L"Left_Eri_All_Body_MoonSlasher", 95, 81, .04f, false);


	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Right.bmp", L"Right_Eri_All_Body_Die_Sword", 24, 43, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Left.bmp", L"Left_Eri_All_Body_Die_Sword", 43, 24, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Right.bmp", L"Right_Eri_All_Body_Die_Shut", 64, 81, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Left.bmp", L"Left_Eri_All_Body_Die_Shut", 83, 66, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Right.bmp", L"Right_Eri_All_Body_Die_Fire", 92, 115, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Left.bmp", L"Left_Eri_All_Body_Die_Fire", 115, 92, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Right.bmp", L"Right_Eri_All_Body_Die_Air", 44, 61, Ani_Time, false);
	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Left.bmp", L"Left_Eri_All_Body_Die_Air", 63, 46, Ani_Time, false);

	p_RenderBody->Set_Animation(L"Eri_All_Body_Action_Right.bmp", L"Eri_Ceremony", 84, 89, .1f, true);

	p_RenderBody->Set_TransColor(RGB(255, 105, 0));
	p_RenderLeg->Set_TransColor(RGB(255, 105, 0));
}

void Player_Eri::Update_Set_AniRender()
{
	if (One_Player::Body_Ceremony == m_Status_Body)
	{
		p_RenderBody->Change_Animation(L"Eri_Ceremony");
		p_RenderBody->Pivot({ 0, 0});
		p_RenderLeg->Change_Animation(L"Eri_Leg_None");
	}

	// 앉을 때 애니메이션
	else if (One_Player::Die_Status::Die_Sword == One_Player::m_Status_Die)
	{
		if (Vector2f::Left == m_pos_PrevDir)
		{
			p_RenderBody->Change_Animation(L"Left_Eri_All_Body_Die_Sword");
			p_RenderBody->Pivot({ 0, 25 });
		}
		else if (Vector2f::Right == m_pos_PrevDir)
		{
			p_RenderBody->Change_Animation(L"Right_Eri_All_Body_Die_Sword");
			p_RenderBody->Pivot({ 25, 25 });
		}
		p_RenderLeg->Change_Animation(L"Eri_Leg_None");
	}
	else if (One_Player::Die_Status::Die_Air == One_Player::m_Status_Die)
	{
		if (Vector2f::Left == m_pos_PrevDir)
		{
			if (TheOne::Obj_Status::Obj_Down == m_Status_Obj)
			{
				p_RenderBody->Fix_Animation(51, 51);
			}
			p_RenderBody->Change_Animation(L"Left_Eri_All_Body_Die_Air");

			// 땅에 닿았을때
			if (TheOne::Obj_Status::Obj_Stand == m_Status_Obj && 
				p_RenderBody->CurAniFrame() > 49)
			{
				p_RenderBody->CurAniFrame(49);
			}
			p_RenderBody->Pivot({ 0, 25 });
		}
		else if (Vector2f::Right == m_pos_PrevDir)
		{
			if (TheOne::Obj_Status::Obj_Down == m_Status_Obj)
			{
				p_RenderBody->Fix_Animation(56, 56);
			}

			p_RenderBody->Change_Animation(L"Right_Eri_All_Body_Die_Air");

			// 땅에 닿았을때
			if (TheOne::Obj_Status::Obj_Stand == m_Status_Obj &&
				p_RenderBody->CurAniFrame() < 58)
			{
				p_RenderBody->CurAniFrame(58);
			}
			p_RenderBody->Pivot({ 25, 25 });
		}
		p_RenderLeg->Change_Animation(L"Eri_Leg_None");
	}
	else if (One_Player::Die_Status::Die_Shut == One_Player::m_Status_Die)
	{
		if (Vector2f::Left == m_pos_PrevDir)
		{
			if (TheOne::Obj_Status::Obj_Down == m_Status_Obj)
			{
				p_RenderBody->Fix_Animation(72, 72);
			}
			p_RenderBody->Change_Animation(L"Left_Eri_All_Body_Die_Shut");
			p_RenderBody->Pivot({ 0, 25 });
		}
		else if (Vector2f::Right == m_pos_PrevDir)
		{
			if (TheOne::Obj_Status::Obj_Down == m_Status_Obj)
			{
				p_RenderBody->Fix_Animation(71, 71);
			}

			p_RenderBody->Change_Animation(L"Right_Eri_All_Body_Die_Shut");
			p_RenderBody->Pivot({ 25, 25 });
		}
		p_RenderLeg->Change_Animation(L"Eri_Leg_None");
	}
	else if (One_Player::Die_Status::Die_Fire == One_Player::m_Status_Die)
	{
		if (Vector2f::Left == m_pos_PrevDir)
		{
			if (TheOne::Obj_Status::Obj_Down == m_Status_Obj)
			{
				p_RenderBody->Fix_Animation(107, 104);
			}
			p_RenderBody->Change_Animation(L"Left_Eri_All_Body_Die_Fire");
			p_RenderBody->Pivot({ 0, 0 });
		}
		else if (Vector2f::Right == m_pos_PrevDir)
		{
			if (TheOne::Obj_Status::Obj_Down == m_Status_Obj)
			{
				p_RenderBody->Fix_Animation(100, 97);
			}

			p_RenderBody->Change_Animation(L"Right_Eri_All_Body_Die_Fire");
			p_RenderBody->Pivot({ 25, 0 });
		}
		p_RenderLeg->Change_Animation(L"Eri_Leg_None");
	}
	else if (One_Player::Die_Status::Die_Respawn == One_Player::m_Status_Die)
	{
		p_RenderBody->Change_Animation(L"Eri_Respawn");
		p_RenderLeg->Change_Animation(L"Eri_Leg_None");
		p_RenderBody->Pivot({ -10, -190 });
	}
	// 앉을 때 애니메이션
	else if (One_Player::Player_Status::Sitting == m_Status_Player)
	{
		p_RenderLeg->Change_Animation(L"Eri_Leg_None", true);

		switch (m_Status_Gun)
		{
		case One_Player::Basic:
			if (Vector2f::Left == m_pos_Dir)
			{
				p_RenderBody->Change_Animation(L"Left_Eri_All_NoGun_Body_Sitting");
				p_RenderBody->Pivot({ -5, 25 });
			}
			else if (Vector2f::Right == m_pos_Dir)
			{
				p_RenderBody->Change_Animation(L"Right_Eri_All_NoGun_Body_Sitting");
				p_RenderBody->Pivot({ -5, 25 });
			}
			break;


		case One_Player::HeavyMachine:
		case One_Player::Missile:
		case One_Player::ShotGun:
		case One_Player::Flame:
			if (Vector2f::Left == m_pos_Dir)
			{
				p_RenderBody->Change_Animation(L"Left_Eri_All_Gun_Body_Sitting");
				p_RenderBody->Pivot({ -5, 25 });
			}
			else if (Vector2f::Right == m_pos_Dir)
			{
				p_RenderBody->Change_Animation(L"Right_Eri_All_Gun_Body_Sitting");
				p_RenderBody->Pivot({ -5, 25 });
			}
			break;


		default:
			break;
		}

		// 총알 애니가 종료되면 상태를 변화시켜준다.
		if (false == p_RenderBody->IsActing())
		{
			m_Status_Player = One_Player::Player_Status::Sit;
		}
	}

	// 앉았을 때 애니메이션
	else if (One_Player::Player_Status::Sit == m_Status_Player)
	{
		p_RenderLeg->Change_Animation(L"Eri_Leg_None", true);
		if (One_Player::Fire_Status::None == m_Status_Fire)
		{
			switch (m_Status_Gun)
			{
			case One_Player::Basic:
				switch (m_Status_Body)
				{
				case One_Player::Body_Idle:
				case One_Player::Body_Look_Up:
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_LookUp:
				case One_Player::Body_Jump_LookDown:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
				case One_Player::Body_Angle_UpSide:
				case One_Player::Body_Angle_DownSide:
					if (Vector2f::Left == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_All_NoGun_Body_Sit");
						p_RenderBody->Pivot({ -5, 25 });
					}
					else if (Vector2f::Right == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_All_NoGun_Body_Sit");
						p_RenderBody->Pivot({ -5, 25 });
					}
					break;
				case One_Player::Body_Run:
					if (Vector2f::Left == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_All_NoGun_Body_Sit_Walk");
						p_RenderBody->Pivot({ -5, 25 });
					}
					else if (Vector2f::Right == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_All_NoGun_Body_Sit_Walk");
						p_RenderBody->Pivot({ -5, 25 });
					}
					break;
				case One_Player::Body_None:
					break;
				default:
					break;
				}
				break;


			case One_Player::HeavyMachine:
			case One_Player::Missile:
			case One_Player::ShotGun:
			case One_Player::Flame:
				switch (m_Status_Body)
				{
				case One_Player::Body_Idle:
				case One_Player::Body_Look_Up:
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_LookUp:
				case One_Player::Body_Jump_LookDown:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
				case One_Player::Body_Angle_UpSide:
				case One_Player::Body_Angle_DownSide:
					if (Vector2f::Left == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_All_Gun_Body_Sit");
						p_RenderBody->Pivot({ -5, 25 });
					}
					else if (Vector2f::Right == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_All_Gun_Body_Sit");
						p_RenderBody->Pivot({ -5, 25 });
					}
					break;
				case One_Player::Body_Run:
					if (Vector2f::Left == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_All_Gun_Body_Sit_Walk");
						p_RenderBody->Pivot({ -5, 25 });
					}
					else if (Vector2f::Right == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_All_Gun_Body_Sit_Walk");
						p_RenderBody->Pivot({ -5, 25 });
					}
					break;
				case One_Player::Body_None:
					break;
				default:
					break;
				}
				
				
			default:
				break;
			}
		}
		else if (One_Player::Fire_Status::Shut == m_Status_Fire)
		{
			if (true == m_b_ReAttack)
			{
				p_RenderBody->Change_ReAnimation();
			}

			switch (m_Status_Gun)
			{
			case One_Player::Basic:
				if (Vector2f::Left == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Left_Eri_All_NoGun_Body_Shut");
					p_RenderBody->Pivot({ -5, 25 });
				}
				else if (Vector2f::Right == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Right_Eri_All_NoGun_Body_Shut");
					p_RenderBody->Pivot({ -5, 25 });
				}
				break;


			case One_Player::HeavyMachine:
			case One_Player::Missile:
			case One_Player::ShotGun:
			case One_Player::Flame:
				if (Vector2f::Left == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Left_Eri_All_Gun_Body_Shut");
					p_RenderBody->Pivot({ -30, 25 });
				}
				else if (Vector2f::Right == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Right_Eri_All_Gun_Body_Shut");
					p_RenderBody->Pivot({ 30, 25 });
				}
				break;
			default:
				break;
			}


			// 총알 애니가 종료되면 상태를 변화시켜준다.
			if (false == p_RenderBody->IsActing())
			{
				m_Status_Fire = None;
			}
		}
		else if (One_Player::Fire_Status::Sword == m_Status_Fire)
		{
			switch (m_Status_Gun)
			{
			case One_Player::Basic:
				if (Vector2f::Left == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Left_Eri_All_NoGun_Body_Sword");
					p_RenderBody->Pivot({ -5, 25 });
				}
				else if (Vector2f::Right == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Right_Eri_All_NoGun_Body_Sword");
					p_RenderBody->Pivot({ -5, 25 });
				}
				break;


			case One_Player::HeavyMachine:
			case One_Player::Missile:
			case One_Player::ShotGun:
			case One_Player::Flame:
				if (Vector2f::Left == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Left_Eri_All_Gun_Body_Sword");
					p_RenderBody->Pivot({ -5, 25 });
				}
				else if (Vector2f::Right == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Right_Eri_All_Gun_Body_Sword");
					p_RenderBody->Pivot({ -5, 25 });
				}
				break;
			default:
				break;
			}


			if (false == p_RenderBody->IsActing())
			{
				m_Status_Fire = None;
			}
		}
		else if (One_Player::Fire_Status::Bomb == m_Status_Fire)
		{
			switch (m_Status_Gun)
			{
			case One_Player::Basic:
				if (Vector2f::Left == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Left_Eri_All_NoGun_Body_Bomb");
					p_RenderBody->Pivot({ -5, 25 });
				}
				else if (Vector2f::Right == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Right_Eri_All_NoGun_Body_Bomb");
					p_RenderBody->Pivot({ -5, 25 });
				}
				break;


			case One_Player::HeavyMachine:
			case One_Player::Missile:
			case One_Player::ShotGun:
			case One_Player::Flame:
				if (Vector2f::Left == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Left_Eri_All_Gun_Body_Bomb");
					p_RenderBody->Pivot({ -5, 25 });
				}
				else if (Vector2f::Right == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Right_Eri_All_Gun_Body_Bomb");
					p_RenderBody->Pivot({ -5, 25 });
				}
				break;
			default:
				break;
			}

			if (false == p_RenderBody->IsActing())
			{
				m_Status_Fire = None;
			}
		}
		else if (One_Player::Fire_Status::Kick == m_Status_Fire)
		{
			switch (m_Status_Gun)
			{
			case One_Player::Basic:
				if (Vector2f::Left == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Left_Eri_All_NoGun_Body_SitKick");
					p_RenderBody->Pivot({ -5, 25 });
				}
				else if (Vector2f::Right == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Right_Eri_All_NoGun_Body_SitKick");
					p_RenderBody->Pivot({ -5, 25 });
				}
				break;


			case One_Player::HeavyMachine:
			case One_Player::Missile:
			case One_Player::ShotGun:
			case One_Player::Flame:
				if (Vector2f::Left == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Left_Eri_All_Gun_Body_SitKick");
					p_RenderBody->Pivot({ -5, 25 });
				}
				else if (Vector2f::Right == m_pos_Dir)
				{
					p_RenderBody->Change_Animation(L"Right_Eri_All_Gun_Body_SitKick");
					p_RenderBody->Pivot({ -5, 25 });
				}
				break;
			default:
				break;
			}

			if (false == p_RenderBody->IsActing())
			{
				m_Status_Fire = None;
			}
		}
	}

	// 앉지 않았을 때 애니메이션
	else if (One_Player::Player_Status::Stand == m_Status_Player ||
		One_Player::Player_Status::Jump_Down == m_Status_Player ||
		One_Player::Player_Status::Jump_Up == m_Status_Player)
	{
		switch (m_Status_Gun)
		{
		case One_Player::Basic:
		{
			if (One_Player::Fire_Status::None == m_Status_Fire)
			{
				switch (m_Status_Body)
				{
				case One_Player::Body_Idle:

					if (Vector2f::Left == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Idle");
						p_RenderBody->Pivot({ -12, -10 });
					}
					else if (Vector2f::Right == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Idle");
						p_RenderBody->Pivot({ 0, -10 });
					}

					break;
				case One_Player::Body_Look_Up:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Look_Up_Idle", true);
						p_RenderBody->Pivot({ -12, -10 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Look_Up_Idle", true);
						p_RenderBody->Pivot({ 0, -10 });
					}
					break;
				case One_Player::Body_Jump_LookDown:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_JumpLookDown", true);
						p_RenderBody->Pivot({ 0, 0 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_JumpLookDown", true);
						p_RenderBody->Pivot({ 0, 0 });
					}
					break;
				case One_Player::Body_Run_Stop:

					if (false == p_RenderLeg->IsActing())
					{
						m_Status_Body = Body_Idle;
						m_Status_Leg = Leg_Idle;
					}

					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_RunStop", true);
						p_RenderBody->Pivot({ -12, -10 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_RunStop", true);
						p_RenderBody->Pivot({ 0, -10 });
					}
					break;
				case One_Player::Body_Jump_LookUp:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Look_Up_Idle", true);
						p_RenderBody->Pivot({ -12, -10 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Look_Up_Idle", true);
						p_RenderBody->Pivot({ 0, -10 });
					}
					break;
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Jump", true);
						p_RenderBody->Pivot({ -12, -6 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Jump", true);
						p_RenderBody->Pivot({ 0, -10 });
					}

					break;
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_RunJump", true);
						p_RenderBody->Pivot({ -12, -10 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_RunJump", true);
						p_RenderBody->Pivot({ 0, -10 });
					}

					break;
				case One_Player::Body_Run:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Run", true);
						p_RenderBody->Pivot({ -12, -10 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Run", true);
						p_RenderBody->Pivot({ 0, -10 });
					}
					break;
				default:
					break;
				}
			}
			else if (One_Player::Fire_Status::Shut == m_Status_Fire)
			{
				if (true == m_b_ReAttack)
				{
					p_RenderBody->Change_ReAnimation();
				}

				switch (m_Status_Body)
				{
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Idle:
				case One_Player::Body_Run:
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Shot_Side", true);
						p_RenderBody->Pivot({ -30, -10 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Shot_Side", true);
						p_RenderBody->Pivot({ 40, -10 });
					}
					break;

				case One_Player::Body_Jump_LookUp:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Shot_Up", true);
						p_RenderBody->Pivot({ 5, -45 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Shot_Up", true);
						p_RenderBody->Pivot({ 0, -45 });
					}
					break;
				case One_Player::Body_Look_Up:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Shot_Up", true);
						p_RenderBody->Pivot({ 5, -45 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Shot_Up", true);
						p_RenderBody->Pivot({ 0, -45 });
					}
					break;


				case One_Player::Body_Jump_LookDown:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Shot_Down", true);
						p_RenderBody->Pivot({ 0, 5 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Shot_Down", true);
						p_RenderBody->Pivot({ 0, 10 });
					}
					break;
				default:
					break;
				}

				// 총알 애니가 종료되면 상태를 변화시켜준다.
				if (false == p_RenderBody->IsActing())
				{
					m_Status_Fire = None;
				}
			}
			else if (One_Player::Fire_Status::Bomb == m_Status_Fire)
			{
				switch (m_Status_Body)
				{
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Idle:
				case One_Player::Body_Run:
				case One_Player::Body_Look_Up:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Jump_LookUp:
				case One_Player::Body_Jump_LookDown:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Bomb", true);
						p_RenderBody->Pivot({ -11, -10 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{

						p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Bomb", true);
						p_RenderBody->Pivot({ 0, -8 });

					}
					break;
				default:
					break;
				}

				// 총알 애니가 종료되면 상태를 변화시켜준다.
				if (false == p_RenderBody->IsActing())
				{
					m_Status_Fire = None;
				}
			}
			else if (One_Player::Fire_Status::Sword == m_Status_Fire)
			{
				switch (m_Status_Body)
				{
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Idle:
				case One_Player::Body_Run:
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
				case One_Player::Body_Jump_LookUp:
				case One_Player::Body_Look_Up:
				case One_Player::Body_Jump_LookDown:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						// 최초 칼질 애니
						if (true == m_b_Sword)
						{
							p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Sword2", true);
							p_RenderBody->Pivot({ -10, -10 });
						}
						else if (false == m_b_Sword)
						{
							p_RenderBody->Change_Animation(L"Left_Eri_NoGun_Body_Sword1", true);
							p_RenderBody->Pivot({ -10, -10 });
						}
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						// 최초 칼질 애니
						if (false == m_b_Sword)
						{
							p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Sword2", true);
							p_RenderBody->Pivot({ 0, -8 });
						}
						else if (true == m_b_Sword)
						{
							p_RenderBody->Change_Animation(L"Right_Eri_NoGun_Body_Sword1", true);
							p_RenderBody->Pivot({ 0, -8 });
						}
					}
					break;
				default:
					break;
				}

				// 총알 애니가 종료되면 상태를 변화시켜준다.
				if (false == p_RenderBody->IsActing())
				{
					m_Status_Fire = None;
					if (true == m_b_Sword) { m_b_Sword = false; }
					else if (false == m_b_Sword) { m_b_Sword = true; }
				}
			}
			else if (One_Player::Fire_Status::Kick == m_Status_Fire)
			{
				switch (m_Status_Body)
				{
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Idle:
				case One_Player::Body_Run:
				case One_Player::Body_Look_Up:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_All_NoGun_Body_Kick", true);
						p_RenderBody->Pivot({ 0, 20 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_All_NoGun_Body_Kick", true);
						p_RenderBody->Pivot({ 10, 20 });
					}
					break;
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
				case One_Player::Body_Jump_LookUp:
				case One_Player::Body_Jump_LookDown:
				default:
					break;
				}

				// 총알 애니가 종료되면 상태를 변화시켜준다.
				if (false == p_RenderBody->IsActing())
				{
					m_Status_Fire = None;
					m_Status_Leg = One_Player::Leg_Idle;
				}
			}

			break;
		}

		case One_Player::HeavyMachine:
		case One_Player::Missile:
		case One_Player::ShotGun:
		case One_Player::Flame:
		{
			if (m_Status_Fire == None)
			{
				switch (m_Status_Body)
				{
				case One_Player::Body_Idle:

					if (Vector2f::Left == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Idle");
						p_RenderBody->Pivot({ -30, -35 });
					}
					else if (Vector2f::Right == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Idle");
						p_RenderBody->Pivot({ 40, -37 });
					}

					break;
				case One_Player::Body_Look_Up:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Look_Up_Idle", true);
						p_RenderBody->Pivot({ -30, -35 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Look_Up_Idle", true);
						p_RenderBody->Pivot({ 40, -37 });
					}
					break;
				case One_Player::Body_Jump_LookDown:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_JumpLookDown", true);
						p_RenderBody->Pivot({ -20, 5 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_JumpLookDown", true);
						p_RenderBody->Pivot({ 40, 5 });
					}
					break;
				case One_Player::Body_Run_Stop:

					if (false == p_RenderLeg->IsActing())
					{
						m_Status_Body = Body_Idle;
						m_Status_Leg = Leg_Idle;
					}

					if (Vector2f::Left == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Idle");
						p_RenderBody->Pivot({ -25, -35 });
					}
					else if (Vector2f::Right == m_pos_Dir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Idle");
						p_RenderBody->Pivot({ 40, -37 });
					}
					break;
				case One_Player::Body_Jump_LookUp:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Look_Up_Idle", true);
						p_RenderBody->Pivot({ -25, -35 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Look_Up_Idle", true);
						p_RenderBody->Pivot({ 40, -37 });
					}
					break;
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Jump", true);
						p_RenderBody->Pivot({ -25, -35 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Jump", true);
						p_RenderBody->Pivot({ 40, -37 });
					}

					break;
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_RunJump", true);
						p_RenderBody->Pivot({ -25, -35 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_RunJump", true);
						p_RenderBody->Pivot({ 40, -37 });
					}

					break;
				case One_Player::Body_Run:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Run", true);
						p_RenderBody->Pivot({ -25, -35 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Run", true);
						p_RenderBody->Pivot({ 40, -37 });
					}
					break;
				default:
					break;
				}
			}
			else if (One_Player::Fire_Status::Shut == m_Status_Fire)
			{
				if (true == m_b_ReAttack)
				{
					p_RenderBody->Change_ReAnimation();
				}

				switch (m_Status_Body)
				{
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Idle:
				case One_Player::Body_Run:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Shot_Side", true);
						p_RenderBody->Pivot({ -30, -35 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Shot_Side", true);
						p_RenderBody->Pivot({ 40, -37 });
					}
					break;

				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Shot_Side", true);
						p_RenderBody->Pivot({ -25, -35 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Shot_Side", true);
						p_RenderBody->Pivot({ 40, -40 });
					}
					break;

				case One_Player::Body_Jump_LookUp:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Shot_Up", true);
						p_RenderBody->Pivot({ -25, -55 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Shot_Up", true);
						p_RenderBody->Pivot({ 40, -55 });
					}
					break;
				case One_Player::Body_Look_Up:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Shot_Up", true);
						p_RenderBody->Pivot({ -30, -52 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Shot_Up", true);
						p_RenderBody->Pivot({ 40, -54 });
					}
					break;


				case One_Player::Body_Jump_LookDown:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Shot_Down", true);
						p_RenderBody->Pivot({ -25, 18 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Shot_Down", true);
						p_RenderBody->Pivot({ 40, 18 });
					}
					break;
				case One_Player::Body_Angle_UpSide:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						// 업과 다운
						if (Vector2f::Up == m_pos_NextDir && Vector2f::Up != m_pos_Dir)
						{
							p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Shot_AngleUp", true);
							p_RenderBody->Pivot({ -30, -35 });
						}
						else if (Vector2f::Down == m_pos_NextDir && m_pos_PrevDir != m_pos_Dir)
						{
							p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Shot_AngleDown", true);
							p_RenderBody->Pivot({ -25, 18 });
						}
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						if (Vector2f::Up == m_pos_NextDir && Vector2f::Up != m_pos_Dir)
						{
							p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Shot_AngleUp", true);
							p_RenderBody->Pivot({ 40, -35 });
						}
						else if (Vector2f::Down == m_pos_NextDir && m_pos_PrevDir != m_pos_Dir)
						{
							p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Shot_AngleDown", true);
							p_RenderBody->Pivot({ 40, 18 });
						}
					}
				default:
					break;
				}

				// 총알 애니가 종료되면 상태를 변화시켜준다.
				if (false == p_RenderBody->IsActing())
				{
					m_Status_Fire = None;
				}
			}
			else if (One_Player::Fire_Status::Bomb == m_Status_Fire)
			{
				switch (m_Status_Body)
				{
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Idle:
				case One_Player::Body_Run:
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
				case One_Player::Body_Jump_LookUp:
				case One_Player::Body_Look_Up:
				case One_Player::Body_Jump_LookDown:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Bomb", true);
						p_RenderBody->Pivot({ -30, -15 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Bomb", true);
						p_RenderBody->Pivot({ 35, -15 });
					}
					break;
				default:
					break;
				}

				// 총알 애니가 종료되면 상태를 변화시켜준다.
				if (false == p_RenderBody->IsActing())
				{
					m_Status_Fire = None;
				}
			}
			else if (One_Player::Fire_Status::Sword == m_Status_Fire)
			{
				switch (m_Status_Body)
				{
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Idle:
				case One_Player::Body_Run:
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
				case One_Player::Body_Jump_LookUp:
				case One_Player::Body_Look_Up:
				case One_Player::Body_Jump_LookDown:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						// 최초 칼질 애니
						if (true == m_b_Sword)
						{
							p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Sword2", true);
							p_RenderBody->Pivot({ -10, -18 });
						}
						else if (false == m_b_Sword)
						{
							p_RenderBody->Change_Animation(L"Left_Eri_Gun_Body_Sword1", true);
							p_RenderBody->Pivot({ -10, -18 });
						}
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						// 최초 칼질 애니
						if (true == m_b_Sword)
						{
							p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Sword2", true);
							p_RenderBody->Pivot({ 25, -18 });
						}
						else if (false == m_b_Sword)
						{
							p_RenderBody->Change_Animation(L"Right_Eri_Gun_Body_Sword1", true);
							p_RenderBody->Pivot({ 25, -18 });
						}
					}
					break;
				default:
					break;
				}

				// 총알 애니가 종료되면 상태를 변화시켜준다.
				if (false == p_RenderBody->IsActing())
				{
					m_Status_Fire = None;
					if (true == m_b_Sword) { m_b_Sword = false; }
					else if (false == m_b_Sword) { m_b_Sword = true; }
				}
			}
			else if (One_Player::Fire_Status::Kick == m_Status_Fire)
			{
				switch (m_Status_Body)
				{
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Idle:
				case One_Player::Body_Run:
				case One_Player::Body_Look_Up:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_All_Gun_Body_Kick", true);
						p_RenderBody->Pivot({ 0, 20 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_All_Gun_Body_Kick", true);
						p_RenderBody->Pivot({ 10, 20 });
					}
					break;
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
				case One_Player::Body_Jump_LookUp:
				case One_Player::Body_Jump_LookDown:
				default:
					break;
				}

				// 총알 애니가 종료되면 상태를 변화시켜준다.
				if (false == p_RenderBody->IsActing())
				{
					m_Status_Fire = None;
					m_Status_Leg = One_Player::Leg_Idle;
				}
			}
			else if (One_Player::Fire_Status::Special == m_Status_Fire)
			{
				switch (m_Status_Body)
				{
				case One_Player::Body_Run_Stop:
				case One_Player::Body_Idle:
				case One_Player::Body_Run:
				case One_Player::Body_Look_Up:
					if (Vector2f::Left == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Left_Eri_All_Body_MoonSlasher");
						p_RenderBody->Pivot({ 0, -5 });
					}
					else if (Vector2f::Right == m_pos_PrevDir)
					{
						p_RenderBody->Change_Animation(L"Right_Eri_All_Body_MoonSlasher");
						p_RenderBody->Pivot({ 10, -5 });
					}
				case One_Player::Body_Jump_LookDown:
				case One_Player::Body_Jump_Up:
				case One_Player::Body_Jump_Down:
				case One_Player::Body_Run_Jump_Up:
				case One_Player::Body_Run_Jump_Down:
				case One_Player::Body_Jump_LookUp:
				default:
					break;
				}

				// 총알 애니가 종료되면 상태를 변화시켜준다.
				if (false == p_RenderBody->IsActing())
				{
					m_Status_Fire = None;
					m_Status_Leg = One_Player::Leg_Idle;
				}
			}

			break;
		}
		default:
			break;
		}

		switch (m_Status_Leg)
		{
		case One_Player::Leg_Idle:
			if (Vector2f::Left == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Left_Eri_Leg_Idle");
				p_RenderLeg->Pivot({ 5, -10 });
			}
			else if (Vector2f::Right == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Right_Eri_Leg_Idle");
				p_RenderLeg->Pivot({ 5, -10 });
			}
			break;
		case One_Player::Leg_Run_Stop:
			if (false == p_RenderLeg->IsActing() &&
				(p_RenderLeg->Acting_Name(L"Left_Eri_NoGun_Body_RunStop") ||
					p_RenderLeg->Acting_Name(L"Right_Eri_NoGun_Body_RunStop")))
			{
				m_Status_Body = Body_Idle;
				m_Status_Leg = Leg_Idle;
			}
			if (Vector2f::Left == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Left_Eri_Leg_RunStop", true);
				p_RenderLeg->Pivot({ 5, -10 });
			}
			else if (Vector2f::Right == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Right_Eri_Leg_RunStop", true);
				p_RenderLeg->Pivot({ 0, -10 });
			}
			break;
		case One_Player::Leg_Jump_Up:
			if (Vector2f::Left == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Eri_Leg_Left_JumpUp", true);
				p_RenderLeg->Pivot({ 5, -10 });
			}
			else if (Vector2f::Right == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Right_Eri_Leg_JumpUp", true);
				p_RenderLeg->Pivot({ 12, -10 });
			}
			break;
		case One_Player::Leg_Jump_Down:
			if (Vector2f::Left == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Left_Eri_Leg_JumpDown", true);
				p_RenderLeg->Pivot({ 5, -10 });
			}
			else if (Vector2f::Right == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Right_Eri_Leg_JumpDown", true);
				p_RenderLeg->Pivot({ 12, -10 });
			}
			break;
		case One_Player::Leg_Run_Jump_Up:
			if (Vector2f::Left == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Left_Eri_Leg_Run_JumpUp", true);
				p_RenderLeg->Pivot({ 5, -5 });
			}
			else if (Vector2f::Right == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Right_Eri_Leg_Run_JumpUp", true);
				p_RenderLeg->Pivot({ 12, -10 });
			}
			break;
		case One_Player::Leg_Run_Jump_Down:
			if (Vector2f::Left == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Left_Eri_Leg_Run_JumpDown", true);
				p_RenderLeg->Pivot({ 5, -5 });
			}
			else if (Vector2f::Right == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Right_Eri_Leg_Run_JumpDown", true);
				p_RenderLeg->Pivot({ 12, -10 });
			}
			break;
		case One_Player::Leg_Run:

			if (Vector2f::Left == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Left_Eri_Leg_Run", true);
				p_RenderLeg->Pivot({ 13, -10 });
			}
			else if (Vector2f::Right == m_pos_PrevDir)
			{
				p_RenderLeg->Change_Animation(L"Right_Eri_Leg_Run", true);
				p_RenderLeg->Pivot({ 0, -10 });
			}
			break;
		case One_Player::Leg_BodyAcition:
			p_RenderLeg->Change_Animation(L"Eri_Leg_None", true);
			break;
		default:
			break;
		}
	}
}


void Player_Eri::Update_Key()
{
	if (One_Player::Special != m_Status_Fire)
	{
		One_Player::Update_Move();
		One_Player::Update_LookUp();
		One_Player::Update_Fire();
		One_Player::Update_JumpStatus();
		One_Player::Update_Kick();
	}

	Update_Bomb();
	One_Player::Update_LookDown();
}

void Player_Eri::Update_Bomb()
{
	if (KEY_DOWN("Bomb"))
	{
		m_b_ReAttack = true;

		// 나중에 다시 열어서 처리해야징 - 폭탄 미구현
		Weapon_Bomb* NewBomb = m_MotherOfTheOne->StateOfOne_Create<Weapon_Bomb>();
		Positionf NewDirf = Vector2f::Zero;
		
		if (KEY_PRESS("Move_Left") && KEY_PRESS("Move_Up"))
		{
			NewDirf = Vector2f::Left + Vector2f::Up;
		}
		else if (KEY_PRESS("Move_Right") && KEY_PRESS("Move_Up"))
		{
			NewDirf = Vector2f::Right + Vector2f::Up;
		}
		else if (KEY_PRESS("Move_Left") && KEY_PRESS("Move_Down") 
			&& (Sit != m_Status_Player && Sitting != m_Status_Player))
		{
			NewDirf = Vector2f::Left + Vector2f::Down;
		}
		else if (KEY_PRESS("Move_Right") && KEY_PRESS("Move_Down")
			&& (Sit != m_Status_Player && Sitting != m_Status_Player))
		{
			NewDirf = Vector2f::Right + Vector2f::Down;
		}
		else if (KEY_PRESS("Move_Down")
			&& (Sit != m_Status_Player && Sitting != m_Status_Player))
		{
			NewDirf = Vector2f::Down;
		}
		else if (KEY_PRESS("Move_Left"))
		{
			NewDirf = Vector2f::Left;
		}
		else if (KEY_PRESS("Move_Right"))
		{
			NewDirf = Vector2f::Right;
		}
		else if (KEY_PRESS("Move_Up"))
		{
			NewDirf = Vector2f::Up;
		}
		else if (KEY_UNPRESS("Move_Right") && KEY_UNPRESS("Move_Left"))
		{
			NewDirf = Vector2f::Zero;
		}		

		NewBomb->Init(m_Pos, m_pos_PrevDir, NewDirf);
	}


	else if (KEY_UP("Bomb") || KEY_PRESS("Bomb"))
	{
		m_b_ReAttack = false;
	}
}
