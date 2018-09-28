#include "stdafx.h"

#include "PlayerMgr.h"
#include "Bullet_Basic.h"
#include "Bullet_Heavy.h"

#include "Core.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Animator.h"
#include "Weapon_Bomb.h"
#include "Weapon_Sword.h"

#include "Trans_Renderer.h"
#include "Animator.h"
#include "Collider.h"

One_Player::One_Player() :
	m_Run_Speed(250), m_pos_Dir_speed(5),
	m_Status_Gun(Gun_Status::Basic), m_Status_Player(Player_Status::Jump_Down),
	m_Status_Fire(Fire_Status::None), m_b_ReAttack(false),
	m_Slow_Jump_SpeedUp(200), m_Slow_Jump_SpeedDown(200), m_Sit_Speed(80),
	m_Fast_Jump_SpeedUp(250), m_Fast_Jump_SpeedDown(250), m_v_JumpDir(0),
	m_Status_JumpBody(Body_Jump_Down), m_Status_Leg(Leg_Jump_Down), p_RenderBody(nullptr), p_RenderLeg(nullptr)
{
}

One_Player::~One_Player()
{
}


void One_Player::Init()
{
	m_Heavy_Cnt = 0;
	m_Heavy_Time = .0f;
	m_Gun_Timer = .0f;

	m_b_FeverMode = false;
	m_Coll_Name = L"없음";
	m_Wchar_Enemy = L"Enemy_Person";
	m_Wchar_EnemyMachine = L"Enemy_Machine";
	m_Wchar_HeavyMachine = L"HeavyMachine";

	m_Status_Die = Die_Status::Die_None;
	m_Pos_Bottom_Check = Vector2::Zero;
	m_pos_Dir = Vector2f::Right;
	m_pos_PrevDir = m_pos_Dir;
	m_Pos = { 100,100 };
	m_pos_Respawn = m_Pos;

	m_v_Jump_Force = 800.0f;
	p_Collider = nullptr;

	Init_Collision();

	m_Time = .0f;
	m_Die_Time = 1.0f;
	m_Respawn_Time = .2f;
	m_Ceremony_Time = 3.0f;
}

void One_Player::Init_Collision()
{
	p_Collider = Create_Collider(L"Player", { 50, 80 });
	p_Collider->type(Collider::TYPE::RECT);
}

void One_Player::DebugUpdate()
{
	WCHAR Str[100] = { 0, };

	swprintf_s(Str, L"Player Pos: %3.2f %3.2f", m_Pos.X, m_Pos.Y);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X), 400, Str);

	swprintf_s(Str, L"Player Pos Dir: %3.2f %3.2f", m_pos_Dir.X, m_pos_Dir.Y);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X), 420, Str);

	swprintf_s(Str, L"Player Pos Prev Dir: %3.2f %3.2f", m_pos_PrevDir.X, m_pos_PrevDir.Y);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X), 440, Str);

	swprintf_s(Str, L"Player Pos Next Dir: %3.2f %3.2f", m_pos_NextDir.X, m_pos_NextDir.Y);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X), 460, Str);
	
	swprintf_s(Str, L"Player Gun: %d", m_Status_Gun);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X), 480, Str);

	swprintf_s(Str, L"Player Body: %d", m_Status_Body);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X), 500, Str);

	swprintf_s(Str, L"Player Leg: %d", m_Status_Leg);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X), 520, Str);

	swprintf_s(Str, L"Player Status: %d", m_Status_Player);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X), 540, Str);

	swprintf_s(Str, L"Player Fire: %d", m_Status_Fire);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X), 560, Str);

	



	swprintf_s(Str, L"Bottom Pos : %d", m_Pos_Bottom_Check.Y);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X) + 200, 400, Str);

	swprintf_s(Str, L"PartY Pos : %f", PartYSize);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X) + 200, 420, Str);

	swprintf_s(Str, L"Player Coll: %s", m_Coll_Name.c_str());
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X) + 200, 440, Str);

	swprintf_s(Str, L"Player Bottom Pos: %d, %d", m_Pos_Bottom_Check.X, m_Pos_Bottom_Check.Y);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X) + 200, 460, Str);

	swprintf_s(Str, L"Player Collider Y Color: %d", m_v_YColor);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X) + 200, 480, Str);

	swprintf_s(Str, L"Player Wall Pos: %d, %d", m_Pos_Wall_Check.X, m_Pos_Wall_Check.Y);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X) + 200, 500, Str);
	
	swprintf_s(Str, L"Player Collider X Color: %d", m_v_XColor);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X) + 200, 520, Str);

	swprintf_s(Str, L"Player Bottom Check: %d", m_b_BottomCheck);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X) + 200, 540, Str);

	swprintf_s(Str, L"Player Frame: %d", p_RenderBody->CurAniFrame());
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X) + 200, 560, Str);

	swprintf_s(Str, L"Player Respawn: %3.2f %3.2f", m_pos_Respawn.X, m_pos_Respawn.Y);
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X), 560, Str);

	if (true == m_b_FeverMode)
	{
		swprintf_s(Str, L"Fever Mode");
	}
	else
	{
		swprintf_s(Str, L"Play Mode");
	}
	TEXT_OUT((int)(m_Pos.X - m_MotherOfTheOne->CameraPos().X) + 200, 580, Str);
}


// 자동으로 체크해준다.
void One_Player::Update_Move_AddON_DirCheck()
{
	if(KEY_PRESS("Move_Right") && KEY_PRESS("Move_Left"))
	{
		return;
	}

	if (KEY_PRESS("Move_Left"))
	{
		m_pos_Dir = Vector2f::Left;
	}
	if (KEY_PRESS("Move_Right"))
	{
		m_pos_Dir = Vector2f::Right;
	}

}

void One_Player::Update_Fever()
{
	if (KEY_DOWN("Fever"))
	{
		if (false == m_b_FeverMode)
		{
			m_b_FeverMode = true;
		}
		else if (true == m_b_FeverMode)
		{
			m_b_FeverMode = false;
		}
	}
}

void One_Player::Update_AutoMove()
{
	float posX = m_Pos.X;
	posX = m_Run_Speed * DELTATIME + m_Pos.X;

	m_Pos.X = posX;

	// 랜딩
	m_Status_Leg = One_Player::Render_Leg::Leg_Run;
	m_Status_Body = One_Player::Render_Body::Body_Run;
}

void One_Player::Update_Heavy()
{
	if (0 < m_Heavy_Cnt)
	{
		m_Gun_Timer += DELTATIME;

		if (m_Gun_Timer > m_Heavy_Time)
		{
			Bullet_Heavy* NewBullet_Heavy = MotherOfTheOne()->StateOfOne_Create<Bullet_Heavy>();
			
			float PosY = .0f;
			switch (m_Heavy_Cnt)
			{
			case 1:
				PosY = -5.0f;
				break;
			case 3:
				PosY = .0f;
				break;
			case 2:
				PosY = 5.0f;
				break;
			default:
				break;
			}
			
			NewBullet_Heavy->Init(Update_Bullet() + Positionf{ 0, PosY }, m_pos_Dir );
			m_Gun_Timer = .0f;
			m_Heavy_Cnt--;
		}
	}
	else
	{
		m_Gun_Timer = .0f;
	}
}

void One_Player::Update_Move()
{
	if (Obj_Status::Obj_Stand == m_Status_Obj)
	{
		m_pos_Respawn = m_Pos;
	}
	if (m_MotherOfTheOne->CameraIntPos().Y + CORE.GetSize().Y < m_Pos.Y + p_Collider->size().IntPartY() &&
		One_Player::Die_None == m_Status_Die)
	{
		Init_Die_Air(m_v_Jump_Force);
	}
	
	float posX = m_Pos.X;

	if (KEY_PRESS("Move_Left") || KEY_PRESS("Move_Right"))
	{
		// 공격버튼을 눌렀으면 방향 전환이 가능하다. - 점프 중, 달릴 때 모두 포함이기 때문에
		// 가정문을 하나 더 만들지 않는다.
		if (KEY_DOWN("Fire"))
		{
			Update_Move_AddON_DirCheck();
			m_pos_Jump_Dir = m_pos_Dir;
			m_pos_PrevDir = m_pos_Dir;
		}

		// 공격 버튼을 누르지 않을 시 점프 중이 아니면 방향전환이 가능하다.
		else
		{
			if ((Jump_Up != m_Status_Player && Jump_Down != m_Status_Player))
			{
				Update_Move_AddON_DirCheck();
				m_pos_Jump_Dir = m_pos_Dir;
				m_pos_PrevDir = m_pos_Dir;
			}
		}

		// 만약 예약 방향벡터가 위나 아래면 계산을 위해 m_pos_Dir은 건드리지 않는다.
		if (m_pos_NextDir != Vector2f::Up && m_pos_NextDir != Vector2f::Down)
		{
			// 위상태면 상태가 바뀌지 않는다. -> 위로 조준
			Update_Move_AddON_DirCheck();
		}


		// 점프 이동은 점프 업데이트에서 관여
		if (Stand == m_Status_Player)
		{
			posX = m_Run_Speed * DELTATIME * m_pos_Dir.X + m_Pos.X;
		}
		else if (Sit == m_Status_Player)
		{
			posX = m_Sit_Speed * DELTATIME * m_pos_Dir.X + m_Pos.X;
		}
	}
	
	Update_Wall(posX);
}

bool One_Player::Check_MachineEnemy()
{
	//  방어 코드 - 사망시 충돌체 원본이 없을 수 있음
	if (nullptr == EnemyCollider) { return false; }

	if (m_Wchar_EnemyMachine == m_Coll_Name &&
		(m_Pos.X - EnemyCollider->MotherOfTheOne_DE()->pos().X) * m_pos_Dir.X < .0f)
	{
		m_Pos.X = (EnemyCollider->MotherOfTheOne_DE()->pos().X - 
			EnemyCollider->size().PartX() - p_Collider->size().PartX()) * m_pos_Dir.X;
		return true;
	}

	return false;
}

void One_Player::Update_Wall(const float& _X)
{
	// 체크 분기점 - 화면밖막기
	if (m_MotherOfTheOne->CameraIntPos().X + CORE.GetSize().X <
		_X + p_Collider->size().X)
	{
		m_Pos.X = m_MotherOfTheOne->CameraIntPos().X + CORE.GetSize().X - p_Collider->size().X;
		return;
	}

	if (m_MotherOfTheOne->CameraIntPos().X >
		_X - p_Collider->size().X)
	{
		m_Pos.X = m_MotherOfTheOne->CameraIntPos().X + p_Collider->size().X;
		return;
	}

	// 벽에 부딛혔을 때
	if (true == TheOne::Update_Wall() || true == Check_MachineEnemy())
	{
		return;
	}

	m_Pos.X = _X;
}

void One_Player::Update_LookUp()
{
	// 업 누를시 사선 측정
	if (KEY_PRESS("Move_Up"))
	{
		if (m_pos_NextDir != Vector2f::Down)
		{
			m_pos_NextDir = Vector2f::Up;

			// 사선 흩뿌리기 방향
			if (m_pos_Dir.Y > Vector2f::Up.Y)
			{
				m_pos_Dir.X -= m_pos_Dir_speed * DELTATIME * m_pos_PrevDir.X;
				m_pos_Dir.Y -= m_pos_Dir_speed * DELTATIME;
			}
			else
			if (m_pos_Dir.Y < Vector2f::Up.Y)
			{
				m_pos_Dir = Vector2f::Up;
			}
		}		
	}
	
	// 업 때면 사선 측정 종료
	else if((KEY_UNPRESS("Move_Up")))
	{
		// 이동키를 누른다면 -> 다음시점도 바꿔준다.
		if (KEY_PRESS("Move_Right") || KEY_PRESS("Move_Left"))
		{
			m_pos_Dir = m_pos_PrevDir;
			m_pos_NextDir = m_pos_PrevDir;
		}

		else if (m_pos_NextDir != Vector2f::Down)
		{
			// 사선 흩뿌리기 방향 
			if (m_pos_Dir.Y < 0)
			{
				m_pos_Dir.X += m_pos_Dir_speed * DELTATIME * m_pos_PrevDir.X;
				m_pos_Dir.Y += m_pos_Dir_speed * DELTATIME;
			}

			// 조건을 추가하는 이유는 잘 안 돌아오드라 -> 서있을 떄도 돌아오게끔
			else if (m_pos_Dir.Y > 0)
			{
				m_pos_Dir = m_pos_PrevDir;
				m_pos_NextDir = m_pos_PrevDir;
			}
		}
	}
}

void One_Player::Update_LookDown()
{
	if (KEY_PRESS("Move_Down"))
	{
		if (m_pos_NextDir != Vector2f::Up)
		{
			// 점프후 방향 전환은 따로 해야함
			if (Jump_Up == m_Status_Player || Jump_Down == m_Status_Player)
			{
				m_pos_NextDir = Vector2f::Down;

				// 사선 흩뿌리기 방향
				if (m_pos_Dir.Y < Vector2f::Down.Y)
				{
					m_pos_Dir.X -= m_pos_Dir_speed * DELTATIME * m_pos_PrevDir.X;
					m_pos_Dir.Y += m_pos_Dir_speed * DELTATIME;
				}
				else if (m_pos_Dir.Y > Vector2f::Down.Y)
				{
					m_pos_Dir = Vector2f::Down;
				}
			}
			
			// 점프 중이 아니면 앉기
			else if(Stand == m_Status_Player)
			{
				// 아이들 - 우선은 서있기
				m_Status_Player = Sitting;

				p_Collider->size({ 50, 40 });
				p_Collider->Pivot({ 0, 20 });

				// 앉기 캔슬
				if (None != m_Status_Fire)
				{
					m_Status_Fire = None;
					m_Status_Player = Sit;
				}
			}
		}
	}
	else if (KEY_UNPRESS("Move_Down"))
	{
		// 이동키를 누른다면 -> 다음시점도 바꿔준다.
		if (KEY_PRESS("Move_Right") || KEY_PRESS("Move_Left"))
		{
			m_pos_Dir = m_pos_PrevDir;
			m_pos_NextDir = m_pos_PrevDir;
		}

		// 역으로 도는 거 막기
		else if (m_pos_NextDir != Vector2f::Up)
		{
			if (Jump_Up == m_Status_Player || Jump_Down == m_Status_Player)
			{
				// 사선 흩뿌리기 종료
				if (m_pos_Dir.Y > 0)
				{
					m_pos_Dir.X += m_pos_Dir_speed * DELTATIME * m_pos_PrevDir.X;
					m_pos_Dir.Y -= m_pos_Dir_speed * DELTATIME;
				}
				else if (m_pos_Dir.Y < 0)
				{
					m_pos_Dir = m_pos_PrevDir;
				}
			}
			// 점프중이 아닌데 아래 키 안누르면 서잇는 거
			else
			{
				m_pos_Dir = m_pos_PrevDir;
				m_pos_NextDir = m_pos_PrevDir;
				m_Status_Player = Stand;


				p_Collider->size({ 50, 80 });
				p_Collider->Pivot({ 0, 0});
			}
		}
	}
}

void One_Player::Update_JumpStatus()
{
	if (KEY_DOWN("Jump"))
	{
		// 현재 쩜프 상황에서 다시 점프키를 누르면 점프가 실행되지 않는다.
		if (Jump_Up == m_Status_Player ||
			Jump_Down == m_Status_Player) {
			return;
		}

		m_Status_Player = Jump_Up;

		// 점프 랜더는 다르다 -> 점프 시에는 다리가 다르게 움직이기 때문에 점프 커맨드만이
		// 랜더까지 여기서 관리한다.
		if (KEY_PRESS("Move_Right") || KEY_PRESS("Move_Left"))
		{
			m_Status_Body = One_Player::Render_Body::Body_Run_Jump_Up;
			m_Status_Leg = One_Player::Render_Leg::Leg_Run_Jump_Up;
			m_Status_JumpBody = m_Status_Body;
		}

		// 제자리 점프 - 점프 방향 변수 초기화
		else if (KEY_UNPRESS("Move_Right") && KEY_UNPRESS("Move_Left"))
		{
			m_Status_Body = One_Player::Render_Body::Body_Jump_Up;
			m_Status_Leg = One_Player::Render_Leg::Leg_Jump_Up;
			m_Status_JumpBody = m_Status_Body;
			m_v_JumpDir = 0;
		}
	}
}

Positionf One_Player::Update_Bullet()
{
	switch (m_Status_Gun)
	{
	case TheOne::Basic:
	{
		Positionf Sit_Fix = { .0f, 20.0f };
		Positionf Right_Fix = { 40.0f, -20.0f };
		Positionf Left_Fix = { -42.0f, -15.0f };
		Positionf Up_Fix = { -4.0f, -55.0f };
		Positionf Down_Fix = { 0, 20.0f };

		// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
		if (1.0f < MATHMANAGER.Absolute_Num(m_pos_NextDir.X) ||
			1.0f < MATHMANAGER.Absolute_Num(m_pos_NextDir.Y))
		{
			return Vector2f::Zero;
		}

		if (Vector2f::Right == m_pos_NextDir)
		{
			if (Player_Status::Sit == m_Status_Player)
			{
				return m_Pos + Right_Fix + Sit_Fix;
			}
			return m_Pos + Right_Fix;
		}
		else if (Vector2f::Left == m_pos_NextDir)
		{
			if (Player_Status::Sit == m_Status_Player)
			{
				return m_Pos + Left_Fix + Sit_Fix;
			}
			return m_Pos + Left_Fix;
		}
		else if (Vector2f::Up == m_pos_NextDir)
		{
			return m_Pos + Up_Fix;
		}
		else if (Vector2f::Down == m_pos_NextDir)
		{
			// 짜증나게 아래는 또 피봇이 달라서 다르게 설정해야함
			if (Vector2f::Right == m_pos_PrevDir)
			{
				return {m_Pos.X + 0, m_Pos.Y + Down_Fix.Y};
			}
			else if (Vector2f::Left == m_pos_PrevDir)
			{
				return{ m_Pos.X + - 5.0f, m_Pos.Y + Down_Fix.Y };
			}
		}
		break;
	}
	case TheOne::HeavyMachine:
	case TheOne::Missile:
	case TheOne::ShotGun:
	case TheOne::Flame:
	{
		Positionf Right_Fix = { 40.0f, 5.0f };
		Positionf Left_Fix = { -120.0f, 5.0f };
		Positionf Up_Fix = { -40.0f, -55.0f };
		Positionf Down_Fix = { -40.0f, 65.0f };

		// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
		/*if (1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.X) ||
			1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.Y))
		{
			return Vector2f::Zero;
		}*/

		if (Vector2f::Right == m_pos_Dir)
		{
			return m_Pos + Right_Fix;
		}
		else if (Vector2f::Left == m_pos_Dir)
		{
			return m_Pos + Left_Fix;
		}
		else if (Vector2f::Up == m_pos_Dir)
		{
			return m_Pos + Up_Fix;
		}
		else if (Vector2f::Down == m_pos_Dir)
		{
			// 짜증나게 아래는 또 피봇이 달라서 다르게 설정해야함
			if (Vector2f::Right == m_pos_PrevDir)
			{
				return{ m_Pos.X - 42.5f, m_Pos.Y + Down_Fix.Y };
			}
			else if (Vector2f::Left == m_pos_PrevDir)
			{
				return{ m_Pos.X - 35.0f, m_Pos.Y + Down_Fix.Y };
			}
		}
		
		// 사 분면
		else
		{
			return { m_Pos.X - 40.0f + 90 * m_pos_Dir.X, m_Pos.Y + 90 * m_pos_Dir.Y };
		}
		break;
	}		
	default:
		break;
	}

	return Vector2f::Zero;
}

void One_Player::Update_Fire()
{
	Update_Heavy();

	// 이젠 바꿀 때
	if (KEY_DOWN("Fire"))
	{
		if (m_Status_Player == Sitting)
		{
			return;
		}
		if (m_Wchar_Enemy != m_Coll_Name)
		{
			m_b_ReAttack = true;

			switch (m_Status_Gun)
			{
			case One_Player::Basic:
			{
				RESOURCEMANAGER.Play_Sound(L"Basic_Shut.mp3", .3f);
				Bullet_Basic* NewBullet_Basic = MotherOfTheOne()->StateOfOne_Create<Bullet_Basic>();
				NewBullet_Basic->Init(Update_Bullet(), m_pos_NextDir);
				break;
			}
			case One_Player::HeavyMachine:
			{
				RESOURCEMANAGER.Play_Sound(L"Heavy_Shut.mp3", .3f);

				Bullet_Heavy* NewBullet_Heavy = MotherOfTheOne()->StateOfOne_Create<Bullet_Heavy>();
				NewBullet_Heavy->Init(Update_Bullet() + Positionf{ 0, -5.0f }, m_pos_Dir);
				m_Gun_Timer = .0f;
				m_Heavy_Time = .04f;
				m_Heavy_Cnt = 3;
				break;
			}
			case One_Player::Missile:
				break;
			case One_Player::ShotGun:
				break;
			case One_Player::Flame:
				break;
			default:
				break;
			}
		}
		else if (m_Wchar_Enemy == m_Coll_Name)
		{
			RESOURCEMANAGER.Play_Sound(L"Sword1.mp3", .3f);

			m_Status_Fire = Sword;
			Weapon_Sword* NewSword = m_MotherOfTheOne->StateOfOne_Create<Weapon_Sword>();
			NewSword->Start(m_Pos + Positionf{m_pos_Dir.X * 20.0f, 0.0f}, L"P_Sword");
		}
	}
	else if (KEY_UP("Fire") || KEY_PRESS("Fire"))
	{
		m_b_ReAttack = false;
	}
}

void One_Player::Update_Bomb()
{
	if (KEY_DOWN("Bomb"))
	{
		m_b_ReAttack = true;

		// 나중에 다시 열어서 처리해야징 - 폭탄 미구현
		Weapon_Bomb* NewBomb = m_MotherOfTheOne->StateOfOne_Create<Weapon_Bomb>();

		Positionf NewDirf = Vector2f::Zero;

		if (KEY_PRESS("Move_Left"))
		{
			NewDirf = Vector2f::Left;
		}
		else if (KEY_PRESS("Move_Right"))
		{
			NewDirf = Vector2f::Right;
		}

		NewBomb->Init(m_Pos, m_pos_PrevDir, NewDirf);
	}
	else if (KEY_UP("Bomb") || KEY_PRESS("Bomb"))
	{
		m_b_ReAttack = false;
	}

}

void One_Player::Update_Jump()
{
	// 키가 눌린 경우
	if (Jump_Up == m_Status_Player)
	{
		Update_Force(m_v_Jump_Force);


		// 탈출 코드 - 내려올 때 - 랜더 포함
		if (.0f > m_v_Cur_JumpForce)
		{
			m_Status_Player = Jump_Down;

			// 점프는 랜더가 업데이트에서 관여된다. - 점프는 랜더 시에 하는 게 아니고
			// 플레이가 작동시에 랜딩된다.
			// 제자리 점프는 제자리

			// 이때 점프 변수가 하나 더 적용되는데 이는 점프 상황을 정확하게 인지하기 위함
			// -> 위 아래를 누를 때에도 점프가 지속되게 하기 위함이다.
			// 위 아래를 누르면 상판이 변하며 현재 상판으로는 검사를 할 수 없다.
			// 따라서 변수 하나를 더 둔것이다.
			if (m_Status_Body == One_Player::Render_Body::Body_Jump_Up && 
				m_Status_Leg == One_Player::Render_Leg::Leg_Jump_Up)
			{
				m_Status_Leg = One_Player::Render_Leg::Leg_Jump_Down;
				m_Status_Body = One_Player::Render_Body::Body_Jump_Down;
			}

			// 움직이는 점프는 움직이는 것에서 관여
			else if 
				(m_Status_Body == One_Player::Render_Body::Body_Run_Jump_Up &&
					m_Status_Leg == One_Player::Render_Leg::Leg_Run_Jump_Up)
			{
				m_Status_Leg = One_Player::Render_Leg::Leg_Run_Jump_Down;
				m_Status_Body = One_Player::Render_Body::Body_Run_Jump_Down;
			}
			
			// 점프 변수는 여기서 갈라져야 한다. -> 내려올때
			if (Body_Jump_Up == m_Status_JumpBody)
			{
				m_Status_JumpBody = Body_Jump_Down;
			}
			else if (Body_Run_Jump_Up == m_Status_JumpBody)
			{
				m_Status_JumpBody = Body_Run_Jump_Down;
			}
		}

		// 랜딩 - 벽막기 - 이동 순
		if (true == TheOne::Update_Wall() || true == Check_MachineEnemy()) { return; }

		
		// 상판이 점프를 하며 위를 보고 있을 때도 적용된다.
		// 위만 보고있을 때는 걸러지는데 이전 이
		if (m_Status_JumpBody == Body_Jump_Up)
		{
			// 일반 점프 시에는 느린 점프를 한다.
			if (KEY_PRESS("Move_Right"))
			{		
				m_Pos.X += m_Slow_Jump_SpeedUp * TIMEMANAGER.DeltaTime();
				m_v_JumpDir = 1;
			}
			else if (KEY_PRESS("Move_Left"))
			{
				m_Pos.X -= m_Slow_Jump_SpeedUp * TIMEMANAGER.DeltaTime();
				m_v_JumpDir = -1;
			}
			
			if (KEY_UNPRESS("Move_Right") && KEY_UNPRESS("Move_Left"))
			{
				m_Pos.X += m_Slow_Jump_SpeedUp * TIMEMANAGER.DeltaTime() * m_v_JumpDir;
			}
		}
		else if (m_Status_JumpBody == Body_Run_Jump_Up)
		{
			// 달리는 점프 시에는 빠른 점프를 한다.
			if (KEY_PRESS("Move_Right"))
			{
				m_Pos.X += m_Run_Speed * TIMEMANAGER.DeltaTime();
				m_v_JumpDir = 1;
			}
			else if (KEY_PRESS("Move_Left"))
			{
				m_Pos.X -= m_Run_Speed * TIMEMANAGER.DeltaTime();
				m_v_JumpDir = -1;
			}
			
			if (KEY_UNPRESS("Move_Right") && KEY_UNPRESS("Move_Left"))
			{
				m_Pos.X += m_Fast_Jump_SpeedUp * TIMEMANAGER.DeltaTime() * m_v_JumpDir;
			}
		}		
	}

	if (Jump_Down == m_Status_Player)
	{		
		// 아니 ㅇ왜 이러는지는 모르겠지만
		// 가정문에 넣지 않으면 점프 다운이 안됀다. ㅠㅡㅠ;;
		// 따라서 일일이 가정문에 넣어.... 조건을 체크한다. - 벽체크
		//if (true == TheOne::Update_Wall()) { return; }

		if (m_Status_JumpBody == Body_Jump_Down && false == TheOne::Update_Wall()
			&& false == Check_MachineEnemy())
		{
			// 일반 점프 시에는 느린 점프를 한다.
			if (KEY_PRESS("Move_Right"))
			{
				m_Pos.X += m_Slow_Jump_SpeedDown * TIMEMANAGER.DeltaTime();
				m_v_JumpDir = 1;
			}
			else if (KEY_PRESS("Move_Left"))
			{
				m_Pos.X -= m_Slow_Jump_SpeedDown * TIMEMANAGER.DeltaTime();
				m_v_JumpDir = -1;
			}
			
			if (KEY_UNPRESS("Move_Right") && KEY_UNPRESS("Move_Left"))
			{
				m_Pos.X += m_Slow_Jump_SpeedDown * TIMEMANAGER.DeltaTime() * m_v_JumpDir;
			}
		}
		else if (m_Status_JumpBody == Body_Run_Jump_Down && false == TheOne::Update_Wall()
			&& false == Check_MachineEnemy())
		{
			// 달리는 점프 시에는 빠른 점프를 한다.
			if (KEY_PRESS("Move_Right"))
			{
				m_Pos.X += m_Run_Speed * TIMEMANAGER.DeltaTime();
				m_v_JumpDir = 1;
			}
			else if (KEY_PRESS("Move_Left"))
			{
				m_Pos.X -= m_Run_Speed * TIMEMANAGER.DeltaTime();
				m_v_JumpDir = -1;
			}
			
			if (KEY_UNPRESS("Move_Right") && KEY_UNPRESS("Move_Left"))
			{
				m_Pos.X += m_Fast_Jump_SpeedDown * TIMEMANAGER.DeltaTime() * m_v_JumpDir;
			}
		}

		// 바닥 도착
		if (true == m_b_BottomCheck)
		{
			m_Status_Player = Stand;

			if (KEY_PRESS("Move_Down"))
			{
				m_pos_Dir = m_pos_PrevDir;
				m_pos_NextDir = m_pos_Dir;
				m_Status_Body = Body_Idle;
				m_Status_Player = Sit;
			}
		}
	}
}

void One_Player::Update_Kick()
{
	if (KEY_DOWN("Kick"))
	{
		if (m_Wchar_Enemy == m_Coll_Name)
		{
			m_Status_Fire = Kick;
			Weapon_Sword* NewSword = m_MotherOfTheOne->StateOfOne_Create<Weapon_Sword>();
			NewSword->Start(m_Pos + Positionf{ m_pos_Dir.X * 20.0f, 0.0f }, L"P_Sword");
		}
	}
}

void One_Player::Update_Key_Render()
{
	if (KEY_DOWN("Die_Sword"))
	{
		Init_Die_Sword();
		return;
	}

	if (KEY_DOWN("Die_Shut"))
	{
		Init_Die_Shut();
		return;
	}
	if (KEY_DOWN("Die_Fire"))
	{
		Init_Die_Fire();
		return;
	}
	if (KEY_DOWN("Die_Air"))
	{
		Init_Die_Air(m_v_Jump_Force);
		return;
	}

	// 슛캔슬
	if (KEY_DOWN("Move_Left") || KEY_DOWN("Move_Right"))
	{
		// 여기가 슈캔슬
		if (None != m_Status_Fire)
		{
			p_RenderBody->Reset_Animation();
			m_Status_Fire = None;
		}
	}
	else if (KEY_PRESS("Move_Left") || KEY_PRESS("Move_Right"))
	{
		if (Jump_Up != m_Status_Player && Jump_Down != m_Status_Player)
		{
			// 랜딩
			m_Status_Leg = One_Player::Render_Leg::Leg_Run;
			m_Status_Body = One_Player::Render_Body::Body_Run;
		}
	}
	else if (KEY_UNPRESS("Move_Left") || KEY_UNPRESS("Move_Right"))
	{
		// 서있고 현재 바디 엑션중이 아닐 경우
		if (Stand == m_Status_Player && m_Status_Leg != One_Player::Leg_BodyAcition)
		{
			m_Status_Leg = One_Player::Render_Leg::Leg_Idle;
			m_Status_Body = One_Player::Render_Body::Body_Idle;
		}
	}
	// 랜딩 에니미이션
	else if (KEY_UP("Move_Left") || KEY_UP("Move_Right"))
	{
		m_Status_Body = One_Player::Render_Body::Body_Run_Stop;
		m_Status_Leg = One_Player::Render_Leg::Leg_Run_Stop;

		// 슛 캔슬
		m_Status_Fire = None;
	}



	if (KEY_PRESS("Move_Up"))
	{
		m_Status_Body = One_Player::Render_Body::Body_Look_Up;

		if ((One_Player::Player_Status::Jump_Up == m_Status_Player ||
			One_Player::Player_Status::Jump_Down == m_Status_Player))
		{
			m_Status_Body = One_Player::Render_Body::Body_Jump_LookUp;
		}

		// 헤비머신건 상황에서 수직 보기가 아닌 상황이면 - 사선보기
		if ((Vector2f::Up.Y != m_pos_Dir.Y) && m_Status_Gun == HeavyMachine)
		{
			if (Vector2f::Up == m_pos_NextDir)
			{
				m_Status_Body = One_Player::Render_Body::Body_Angle_UpSide;
			} 
		}
	}
	// 업버튼 시는 위에만 바뀐다.
	else if (KEY_UP("Move_Up"))
	{
		// 바디 엑션 간 up키를 누를 수 있음
		if (m_Status_Leg != Leg_Run && m_Status_Leg != Leg_BodyAcition)
		{
			// 점프가 아닐 시에만 변화된다.
			if (One_Player::Player_Status::Jump_Up != m_Status_Player &&
				One_Player::Player_Status::Jump_Down != m_Status_Player)
			{
				m_Status_Body = One_Player::Render_Body::Body_Idle;
				m_Status_Leg = Leg_Idle;
			}
		}

		if (One_Player::Basic != m_Status_Gun && m_pos_PrevDir != m_pos_Dir)
		{
			m_Status_Body = One_Player::Render_Body::Body_Angle_DownSide;
		}


		// 바디엑션 공격은 캔슬 불가
		if (m_Status_Fire != Special && m_Status_Fire != Kick)
		{
			m_Status_Fire = None;
		}
	}

	if (KEY_PRESS("Move_Down"))
	{
		// 점프후 방향 전환은 따로 해야함
		if ((Jump_Up == m_Status_Player || Jump_Down == m_Status_Player))
		{
			m_Status_Body = One_Player::Render_Body::Body_Jump_LookDown;


			if ((Vector2f::Down.Y != m_pos_Dir.Y) && m_Status_Gun == HeavyMachine)
			{
				if (Vector2f::Down == m_pos_NextDir)
				{
					m_Status_Body = One_Player::Render_Body::Body_Angle_UpSide;
				}
				else if (Vector2f::Down != m_pos_NextDir && m_pos_PrevDir != m_pos_Dir)
				{
					m_Status_Body = One_Player::Render_Body::Body_Angle_DownSide;
				}
			}
		}

		// 점프 중이 아니면 앉기
		// 앉기 이동
		else if(KEY_PRESS("Move_Right") || KEY_PRESS("Move_Left"))
		{
			m_Status_Body = One_Player::Render_Body::Body_Run;
			m_Status_Leg = One_Player::Leg_BodyAcition;
		}
		// 그냥 앉기
		else
		{
			m_Status_Body = One_Player::Render_Body::Body_Idle;
			m_Status_Leg = One_Player::Leg_BodyAcition;
		}
	}
	else if (KEY_UP("Move_Down"))
	{
		if (m_pos_PrevDir != m_pos_Dir)
		{
			m_Status_Body = One_Player::Render_Body::Body_Angle_DownSide;
		}
		if (Jump_Down == m_Status_Player || Jump_Up == m_Status_Player)
		{
			m_Status_Body = One_Player::Body_Jump_Down;
		}

		// 앉기 캔슬
		if (Stand == m_Status_Player)
		{
			m_Status_Fire = None;
			m_Status_Body = One_Player::Render_Body::Body_Idle;
			m_Status_Leg = One_Player::Leg_Idle;
		}
	}
	
	if (KEY_DOWN("Fire"))
	{
		m_Status_Fire = Shut;

		// 런점프와 그냥 점프의 피봇이 다르다.
		if (One_Player::Body_Run_Jump_Up == m_Status_Body || One_Player::Body_Run_Jump_Down == m_Status_Body)
		{
			// 랜딩
			m_Status_Body = One_Player::Render_Body::Body_Run_Jump_Up;
		}
		else if(Vector2f::Down != m_pos_NextDir && Vector2f::Up != m_pos_NextDir)
		{
			// 랜딩
			m_Status_Body = One_Player::Render_Body::Body_Jump_Up;
		}

		if (m_Wchar_Enemy == m_Coll_Name)
		{
			m_Status_Fire = Sword;
		}
	}

	if (KEY_DOWN("Bomb"))
	{
		m_Status_Fire = Bomb;
	}

	if (KEY_DOWN("Kick"))
	{
		m_Status_Fire = Kick;
		m_Status_Leg = One_Player::Leg_BodyAcition;
	}

}


void One_Player::Update_Die()
{

	if (Obj_Status::Obj_Stand == m_Status_Obj)
	{
		m_pos_Respawn = m_Pos;
	}

	if (m_Pos.Y > 5000 && m_Status_Die != Die_Respawn)
	{
		Init_Respawn();
	}

	switch (m_Status_Die)
	{
	case One_Player::Die_Respawn:
		Update_Respawn();
		break;
	case One_Player::Die_None:
		return;
	case One_Player::Die_Sword:
		Update_Die_Sword();
		break;
	case One_Player::Die_Shut:
		Update_Die_Shut();
		break;
	case One_Player::Die_Air:
		Update_Die_Air();
		break;
	case One_Player::Die_Fire:
		Update_Die_Fire();
		break;
	case One_Player::Die_Laser:
		break;
	default:
		break;
	}
}

void One_Player::Sound_Die()
{
	switch (PlayerMgr::character())
	{
	case PlayerMgr::Play_Character::Eri:
		RESOURCEMANAGER.Play_Sound(L"Effect_Eri_Die.mp3", .5f);
		break;

	case PlayerMgr::Play_Character::Leona:
		RESOURCEMANAGER.Play_Sound(L"Effect_Leona_Die.mp3", .5f);
		break;

	default:
		break;
	}
}

void One_Player::Init_Die_Sword()
{
	if (One_Player::Jump_Up == m_Status_Player || One_Player::Jump_Down == m_Status_Player)
	{
		Init_Die_Air(m_v_Cur_JumpForce);
		return;
	}
	Sound_Die();
	m_Status_Die = One_Player::Die_Sword;
	m_Status_Body = One_Player::Body_Idle;
	m_Status_Leg = One_Player::Leg_BodyAcition;	
}
void One_Player::Init_Die_Air(const float& _Value)
{
	Sound_Die();
	m_v_Cur_JumpForce = _Value;
	m_Status_Die = One_Player::Die_Air;
	m_Status_Body = One_Player::Body_Idle;
	m_Status_Leg = One_Player::Leg_BodyAcition;
}
void One_Player::Init_Die_Shut()
{
	if (One_Player::Jump_Up == m_Status_Player || One_Player::Jump_Down == m_Status_Player)
	{
		Init_Die_Air(m_v_Jump_Force);
		return;
	}
	Sound_Die();
	TheOne::Update_Force(m_v_Jump_Force);
	m_Status_Die = One_Player::Die_Shut;
	m_Status_Body = One_Player::Body_Idle;
	m_Status_Leg = One_Player::Leg_BodyAcition;
}
void One_Player::Init_Die_Fire()
{
	Sound_Die();
	TheOne::Update_Force(m_v_Jump_Force);
	m_Status_Die = One_Player::Die_Fire;
	m_Status_Body = One_Player::Body_Idle;
	m_Status_Leg = One_Player::Leg_BodyAcition;
}
void One_Player::Init_Respawn()
{
	m_Status_Player = One_Player::Stand;
	m_Pos = m_pos_Respawn;	
	m_Time = .0f;
	m_Status_Die = One_Player::Die_Respawn;
	m_Status_Leg = One_Player::Leg_BodyAcition;
}

void One_Player::Update_Die_Sword()
{

	if (true == p_RenderBody->IsActing())
	{
		m_Status_Die = One_Player::Die_Sword;
		m_Status_Leg = One_Player::Leg_BodyAcition;
	}
	else if (false == p_RenderBody->IsActing())
	{
		m_Time += DELTATIME;
		if (m_Time > m_Die_Time)
		{
			Init_Respawn();
		}
	}
}

void One_Player::Update_Die_Air()
{
	if (true != TheOne::m_b_BottomCheck)
	{
		m_Pos.X += m_pos_PrevDir.X * m_Run_Speed * -1.0f * DELTATIME;
	}

	if (true == p_RenderBody->IsActing())
	{
		m_Status_Die = One_Player::Die_Air;
		m_Status_Leg = One_Player::Leg_BodyAcition;
	}
	else if (false == p_RenderBody->IsActing())
	{
		m_Time += DELTATIME;
		if (m_Time > m_Die_Time)
		{
			Init_Respawn();
		}
	}
}

void One_Player::Update_Die_Shut()
{
	if (true != TheOne::m_b_BottomCheck)
	{
		m_Pos.X += m_pos_PrevDir.X * m_Run_Speed * -1.0f * DELTATIME;
	}

	if (true == p_RenderBody->IsActing())
	{
		m_Status_Die = One_Player::Die_Shut;
		m_Status_Leg = One_Player::Leg_BodyAcition;
	}
	else if (false == p_RenderBody->IsActing())
	{
		m_Time += DELTATIME;
		if (m_Time > m_Die_Time)
		{
			Init_Respawn();
		}
	}
}

void One_Player::Update_Die_Fire()
{
	if (true != TheOne::m_b_BottomCheck)
	{
		m_Pos.X += m_pos_PrevDir.X * m_Run_Speed * -1.0f * DELTATIME;
	}

	if (true == p_RenderBody->IsActing())
	{
		m_Status_Die = One_Player::Die_Fire;
		m_Status_Leg = One_Player::Leg_BodyAcition;
	}
	else if (false == p_RenderBody->IsActing())
	{
		m_Time += DELTATIME;
		if (m_Time > m_Die_Time)
		{
			Init_Respawn();
		}
	}
}

void One_Player::Update_Respawn()
{
	if (true == p_RenderBody->IsActing())
	{
		p_RenderBody->size({ 60, 480 });
		m_Status_Die = One_Player::Die_Respawn;
		m_Status_Leg = One_Player::Leg_BodyAcition;
	}
	else if (false == p_RenderBody->IsActing())
	{
		m_Time += DELTATIME;
		if (m_Time > m_Respawn_Time)
		{
			m_Time = .0f;
			p_RenderBody->size({ 140, 140 });
			m_Status_Die = One_Player::Die_None;
			m_Status_Body = One_Player::Body_Idle;
			m_Status_Leg = One_Player::Leg_Idle;
		}
	}
}

/********************* Collision ****************************/

void One_Player::CollisionEnter(Collider* _Other)
{
	return;
}

void One_Player::CollisionStay(Collider* _Other)
{
	EnemyCollider = nullptr;
	p_BottomColl = nullptr;
	m_Coll_Name = _Other->MotherOfTheOne_DE()->Name();

	if (m_Coll_Name == L"Bottom")
	{
		m_Coll_Name = _Other->MotherOfTheOne_DE()->Name();
		p_BottomColl = _Other;
	}

	if (m_Coll_Name == m_Wchar_HeavyMachine)
	{
		RESOURCEMANAGER.Play_Sound(L"H.mp3");
		EnemyCollider = _Other;
		m_Status_Gun = Gun_Status::HeavyMachine;
		_Other->MotherOfTheOne_DE()->Death(true);
	}

	if (m_Coll_Name == L"Enemy_Machine")
	{
		EnemyCollider = _Other;
	}

	if (true == m_b_FeverMode) { return; }

	if (m_Coll_Name == L"E_Sword" && m_Status_Die == Die_None)
	{
		Init_Die_Sword();
	}
	else if (m_Coll_Name == L"E_Explosion" && m_Status_Die == Die_None)
	{
		EnemyCollider = _Other;
		_Other->MotherOfTheOne_DE()->Activate();
		Init_Die_Shut();
	}
	else if (m_Coll_Name == L"E_Fire" && m_Status_Die == Die_None)
	{
		EnemyCollider = _Other;
		_Other->MotherOfTheOne_DE()->Activate();
		Init_Die_Fire();
	}
	else if (m_Coll_Name == L"Enemy_Boss" && m_Status_Die == Die_None)
	{
		EnemyCollider = _Other;
		_Other->MotherOfTheOne_DE()->Activate();
		Init_Die_Shut();
	}
}

void One_Player::CollisionExit(Collider* _Other)
{
	m_Coll_Name = L"없음";
	//m_Status_Gun = Gun_Status::Basic;
}