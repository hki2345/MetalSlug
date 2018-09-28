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
	m_Coll_Name = L"����";
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


// �ڵ����� üũ���ش�.
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

	// ����
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
		// ���ݹ�ư�� �������� ���� ��ȯ�� �����ϴ�. - ���� ��, �޸� �� ��� �����̱� ������
		// �������� �ϳ� �� ������ �ʴ´�.
		if (KEY_DOWN("Fire"))
		{
			Update_Move_AddON_DirCheck();
			m_pos_Jump_Dir = m_pos_Dir;
			m_pos_PrevDir = m_pos_Dir;
		}

		// ���� ��ư�� ������ ���� �� ���� ���� �ƴϸ� ������ȯ�� �����ϴ�.
		else
		{
			if ((Jump_Up != m_Status_Player && Jump_Down != m_Status_Player))
			{
				Update_Move_AddON_DirCheck();
				m_pos_Jump_Dir = m_pos_Dir;
				m_pos_PrevDir = m_pos_Dir;
			}
		}

		// ���� ���� ���⺤�Ͱ� ���� �Ʒ��� ����� ���� m_pos_Dir�� �ǵ帮�� �ʴ´�.
		if (m_pos_NextDir != Vector2f::Up && m_pos_NextDir != Vector2f::Down)
		{
			// �����¸� ���°� �ٲ��� �ʴ´�. -> ���� ����
			Update_Move_AddON_DirCheck();
		}


		// ���� �̵��� ���� ������Ʈ���� ����
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
	//  ��� �ڵ� - ����� �浹ü ������ ���� �� ����
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
	// üũ �б��� - ȭ��۸���
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

	// ���� �ε����� ��
	if (true == TheOne::Update_Wall() || true == Check_MachineEnemy())
	{
		return;
	}

	m_Pos.X = _X;
}

void One_Player::Update_LookUp()
{
	// �� ������ �缱 ����
	if (KEY_PRESS("Move_Up"))
	{
		if (m_pos_NextDir != Vector2f::Down)
		{
			m_pos_NextDir = Vector2f::Up;

			// �缱 ��Ѹ��� ����
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
	
	// �� ���� �缱 ���� ����
	else if((KEY_UNPRESS("Move_Up")))
	{
		// �̵�Ű�� �����ٸ� -> ���������� �ٲ��ش�.
		if (KEY_PRESS("Move_Right") || KEY_PRESS("Move_Left"))
		{
			m_pos_Dir = m_pos_PrevDir;
			m_pos_NextDir = m_pos_PrevDir;
		}

		else if (m_pos_NextDir != Vector2f::Down)
		{
			// �缱 ��Ѹ��� ���� 
			if (m_pos_Dir.Y < 0)
			{
				m_pos_Dir.X += m_pos_Dir_speed * DELTATIME * m_pos_PrevDir.X;
				m_pos_Dir.Y += m_pos_Dir_speed * DELTATIME;
			}

			// ������ �߰��ϴ� ������ �� �� ���ƿ���� -> ������ ���� ���ƿ��Բ�
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
			// ������ ���� ��ȯ�� ���� �ؾ���
			if (Jump_Up == m_Status_Player || Jump_Down == m_Status_Player)
			{
				m_pos_NextDir = Vector2f::Down;

				// �缱 ��Ѹ��� ����
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
			
			// ���� ���� �ƴϸ� �ɱ�
			else if(Stand == m_Status_Player)
			{
				// ���̵� - �켱�� ���ֱ�
				m_Status_Player = Sitting;

				p_Collider->size({ 50, 40 });
				p_Collider->Pivot({ 0, 20 });

				// �ɱ� ĵ��
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
		// �̵�Ű�� �����ٸ� -> ���������� �ٲ��ش�.
		if (KEY_PRESS("Move_Right") || KEY_PRESS("Move_Left"))
		{
			m_pos_Dir = m_pos_PrevDir;
			m_pos_NextDir = m_pos_PrevDir;
		}

		// ������ ���� �� ����
		else if (m_pos_NextDir != Vector2f::Up)
		{
			if (Jump_Up == m_Status_Player || Jump_Down == m_Status_Player)
			{
				// �缱 ��Ѹ��� ����
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
			// �������� �ƴѵ� �Ʒ� Ű �ȴ����� ���մ� ��
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
		// ���� ���� ��Ȳ���� �ٽ� ����Ű�� ������ ������ ������� �ʴ´�.
		if (Jump_Up == m_Status_Player ||
			Jump_Down == m_Status_Player) {
			return;
		}

		m_Status_Player = Jump_Up;

		// ���� ������ �ٸ��� -> ���� �ÿ��� �ٸ��� �ٸ��� �����̱� ������ ���� Ŀ�ǵ常��
		// �������� ���⼭ �����Ѵ�.
		if (KEY_PRESS("Move_Right") || KEY_PRESS("Move_Left"))
		{
			m_Status_Body = One_Player::Render_Body::Body_Run_Jump_Up;
			m_Status_Leg = One_Player::Render_Leg::Leg_Run_Jump_Up;
			m_Status_JumpBody = m_Status_Body;
		}

		// ���ڸ� ���� - ���� ���� ���� �ʱ�ȭ
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

		// ���� ���� 1���� ũ�� - ���� ���̶� �� - ����
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
			// ¥������ �Ʒ��� �� �Ǻ��� �޶� �ٸ��� �����ؾ���
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

		// ���� ���� 1���� ũ�� - ���� ���̶� �� - ����
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
			// ¥������ �Ʒ��� �� �Ǻ��� �޶� �ٸ��� �����ؾ���
			if (Vector2f::Right == m_pos_PrevDir)
			{
				return{ m_Pos.X - 42.5f, m_Pos.Y + Down_Fix.Y };
			}
			else if (Vector2f::Left == m_pos_PrevDir)
			{
				return{ m_Pos.X - 35.0f, m_Pos.Y + Down_Fix.Y };
			}
		}
		
		// �� �и�
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

	// ���� �ٲ� ��
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

		// ���߿� �ٽ� ��� ó���ؾ�¡ - ��ź �̱���
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
	// Ű�� ���� ���
	if (Jump_Up == m_Status_Player)
	{
		Update_Force(m_v_Jump_Force);


		// Ż�� �ڵ� - ������ �� - ���� ����
		if (.0f > m_v_Cur_JumpForce)
		{
			m_Status_Player = Jump_Down;

			// ������ ������ ������Ʈ���� �����ȴ�. - ������ ���� �ÿ� �ϴ� �� �ƴϰ�
			// �÷��̰� �۵��ÿ� �����ȴ�.
			// ���ڸ� ������ ���ڸ�

			// �̶� ���� ������ �ϳ� �� ����Ǵµ� �̴� ���� ��Ȳ�� ��Ȯ�ϰ� �����ϱ� ����
			// -> �� �Ʒ��� ���� ������ ������ ���ӵǰ� �ϱ� �����̴�.
			// �� �Ʒ��� ������ ������ ���ϸ� ���� �������δ� �˻縦 �� �� ����.
			// ���� ���� �ϳ��� �� �а��̴�.
			if (m_Status_Body == One_Player::Render_Body::Body_Jump_Up && 
				m_Status_Leg == One_Player::Render_Leg::Leg_Jump_Up)
			{
				m_Status_Leg = One_Player::Render_Leg::Leg_Jump_Down;
				m_Status_Body = One_Player::Render_Body::Body_Jump_Down;
			}

			// �����̴� ������ �����̴� �Ϳ��� ����
			else if 
				(m_Status_Body == One_Player::Render_Body::Body_Run_Jump_Up &&
					m_Status_Leg == One_Player::Render_Leg::Leg_Run_Jump_Up)
			{
				m_Status_Leg = One_Player::Render_Leg::Leg_Run_Jump_Down;
				m_Status_Body = One_Player::Render_Body::Body_Run_Jump_Down;
			}
			
			// ���� ������ ���⼭ �������� �Ѵ�. -> �����ö�
			if (Body_Jump_Up == m_Status_JumpBody)
			{
				m_Status_JumpBody = Body_Jump_Down;
			}
			else if (Body_Run_Jump_Up == m_Status_JumpBody)
			{
				m_Status_JumpBody = Body_Run_Jump_Down;
			}
		}

		// ���� - ������ - �̵� ��
		if (true == TheOne::Update_Wall() || true == Check_MachineEnemy()) { return; }

		
		// ������ ������ �ϸ� ���� ���� ���� ���� ����ȴ�.
		// ���� �������� ���� �ɷ����µ� ���� ��
		if (m_Status_JumpBody == Body_Jump_Up)
		{
			// �Ϲ� ���� �ÿ��� ���� ������ �Ѵ�.
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
			// �޸��� ���� �ÿ��� ���� ������ �Ѵ�.
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
		// �ƴ� ���� �̷������� �𸣰�����
		// �������� ���� ������ ���� �ٿ��� �ȉ´�. �ФѤ�;;
		// ���� ������ �������� �־�.... ������ üũ�Ѵ�. - ��üũ
		//if (true == TheOne::Update_Wall()) { return; }

		if (m_Status_JumpBody == Body_Jump_Down && false == TheOne::Update_Wall()
			&& false == Check_MachineEnemy())
		{
			// �Ϲ� ���� �ÿ��� ���� ������ �Ѵ�.
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
			// �޸��� ���� �ÿ��� ���� ������ �Ѵ�.
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

		// �ٴ� ����
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

	// ��ĵ��
	if (KEY_DOWN("Move_Left") || KEY_DOWN("Move_Right"))
	{
		// ���Ⱑ ��ĵ��
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
			// ����
			m_Status_Leg = One_Player::Render_Leg::Leg_Run;
			m_Status_Body = One_Player::Render_Body::Body_Run;
		}
	}
	else if (KEY_UNPRESS("Move_Left") || KEY_UNPRESS("Move_Right"))
	{
		// ���ְ� ���� �ٵ� �������� �ƴ� ���
		if (Stand == m_Status_Player && m_Status_Leg != One_Player::Leg_BodyAcition)
		{
			m_Status_Leg = One_Player::Render_Leg::Leg_Idle;
			m_Status_Body = One_Player::Render_Body::Body_Idle;
		}
	}
	// ���� ���Ϲ��̼�
	else if (KEY_UP("Move_Left") || KEY_UP("Move_Right"))
	{
		m_Status_Body = One_Player::Render_Body::Body_Run_Stop;
		m_Status_Leg = One_Player::Render_Leg::Leg_Run_Stop;

		// �� ĵ��
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

		// ���ӽŰ� ��Ȳ���� ���� ���Ⱑ �ƴ� ��Ȳ�̸� - �缱����
		if ((Vector2f::Up.Y != m_pos_Dir.Y) && m_Status_Gun == HeavyMachine)
		{
			if (Vector2f::Up == m_pos_NextDir)
			{
				m_Status_Body = One_Player::Render_Body::Body_Angle_UpSide;
			} 
		}
	}
	// ����ư �ô� ������ �ٲ��.
	else if (KEY_UP("Move_Up"))
	{
		// �ٵ� ���� �� upŰ�� ���� �� ����
		if (m_Status_Leg != Leg_Run && m_Status_Leg != Leg_BodyAcition)
		{
			// ������ �ƴ� �ÿ��� ��ȭ�ȴ�.
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


		// �ٵ𿢼� ������ ĵ�� �Ұ�
		if (m_Status_Fire != Special && m_Status_Fire != Kick)
		{
			m_Status_Fire = None;
		}
	}

	if (KEY_PRESS("Move_Down"))
	{
		// ������ ���� ��ȯ�� ���� �ؾ���
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

		// ���� ���� �ƴϸ� �ɱ�
		// �ɱ� �̵�
		else if(KEY_PRESS("Move_Right") || KEY_PRESS("Move_Left"))
		{
			m_Status_Body = One_Player::Render_Body::Body_Run;
			m_Status_Leg = One_Player::Leg_BodyAcition;
		}
		// �׳� �ɱ�
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

		// �ɱ� ĵ��
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

		// �������� �׳� ������ �Ǻ��� �ٸ���.
		if (One_Player::Body_Run_Jump_Up == m_Status_Body || One_Player::Body_Run_Jump_Down == m_Status_Body)
		{
			// ����
			m_Status_Body = One_Player::Render_Body::Body_Run_Jump_Up;
		}
		else if(Vector2f::Down != m_pos_NextDir && Vector2f::Up != m_pos_NextDir)
		{
			// ����
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
	m_Coll_Name = L"����";
	//m_Status_Gun = Gun_Status::Basic;
}