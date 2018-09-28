#include "stdafx.h"
#include "TheOne.h"

#include "BaseState.h"

#include "Renderer.h"
#include "Collider.h"

#include "ResourceManager.h"

TheOne::TheOne() : m_b_Camera(true), m_v_Gravity(9.80665f),
m_f_Bottom_Space(3.0f), m_v_GravityTime(.0f), p_BottomColl(nullptr)
{
	Live(true);
	m_Status_Obj = Obj_Stand;
}

// �������� �浹ü�� ���⼭ �����. 
// ������ ����� ����Ŵϱ� ���⼭���� ����°� �°ڳ�
// �޴������� �׷��� ���� �浹ü�� �׷쿡�� �Ҹ��� �ҷ����� �ݶ��̴� ����� �׷��� ��
TheOne::~TheOne()
{
	for (size_t i = 0; i < m_Vec_Renderer.size(); i++)
	{
		NEW_DELETE(m_Vec_Renderer[i]);
	}

	for (size_t i = 0; i < m_Vec_Collider.size(); i++)
	{
		NEW_DELETE(m_Vec_Collider[i]);
	}
}

Collider* TheOne::Create_Collider(const WCHAR* _GroupName, Sizef _Size)
{
	Collider* NewCollider = new Collider();
	NewCollider->MotherOfTheOne_DE(this);
	NewCollider->size(_Size);
	NewCollider->Name(_GroupName);
	m_MotherOfTheOne->Insert_Collider(_GroupName, NewCollider);
	m_Vec_Collider.push_back(NewCollider);

	PartXSize = NewCollider->size().PartX();
	PartYSize = NewCollider->size().PartY();

	return NewCollider;
}


// ���⿡ ���� ���� �б⸦ �˷���
// ��� ���� - ���� ����, ������ ũ��, ũ���� �� ��°
bool TheOne::Render_pos_Dir_Check(Vector2f _StartPos, Vector2f _FinishPos,
	const size_t& _AngleSize, const size_t& _Check_Count)
{
	_StartPos = MATHMANAGER.Absolute_Vector(_StartPos);
	_FinishPos = MATHMANAGER.Absolute_Vector(_FinishPos);

	Dirf temp_Dir = MATHMANAGER.Absolute_Vector(m_pos_Dir);

	return
		((_StartPos.X) / _AngleSize * (_AngleSize - _Check_Count) > temp_Dir.X &&
		(_StartPos.X) / _AngleSize * (_AngleSize - (_Check_Count + 1)) <= temp_Dir.X) ||
		((_FinishPos.Y) / _AngleSize * (_Check_Count) > temp_Dir.Y &&
		(_FinishPos.Y) / _AngleSize * (_Check_Count - 1) <= temp_Dir.Y);
}


void TheOne::Update_Bottom()
{
	if (m_v_Cur_JumpForce > .0f) { return; }

	// �÷��̼����� �����Ѵ�.
	m_Pos_Bottom_Check = {(int) m_Pos.X, (int)(m_Pos.Y + (PartYSize - m_f_Bottom_Space)) }; ;
	m_b_BottomCheck = false;

	//  �ٴ� Ÿ�� ������ ���ֱ�
	if (L"Bottom" == m_Coll_Name && nullptr != p_BottomColl)
	{
		m_b_BottomCheck = true;

		m_Pos_Bottom_Check.Y = (int)(p_BottomColl->MotherOfTheOne_DE()->pos().Y - 15.0f);
		Update_BottomLine();
		return;
	}

	while (true)
	{
		// �׷��� Ż���� �ؾ���
		if (m_Pos_Bottom_Check.Y > 10000)
		{
			// �ƴ� Ż���������� �׿�������....;; ;
			// �ֳ�.. 10000 �Ѿ ��ü�� ������ ���� �״ϱ�...�װ� �÷��̾�� ����
			Death(true);
		}

		m_v_YColor = RESOURCEMANAGER.Get_PixelColor(m_MotherOfTheOne->acting_map(), m_Pos_Bottom_Check);
		
		// ���� ���� ���� 0, 255, 255 -> 16776960
		if (16776960 != m_v_YColor)
		{
			m_Pos_Bottom_Check.Y++;

			// �ʿ���� ���� ���� �� ������ �ø�
			if(m_Pos_Bottom_Check.Y > m_Pos.Y + PartYSize + m_f_Bottom_Space)
			{
				return;
			}
			continue;
		}

		else if (16776960 == RESOURCEMANAGER.Get_PixelColor(m_MotherOfTheOne->acting_map(), m_Pos_Bottom_Check))
		{
			m_b_BottomCheck = true;
			break;
		}
	}


	Update_BottomLine();
}

void TheOne::Update_BottomLine()
{
	if (true == m_b_BottomCheck)
	{
		//// ����
		m_Status_Obj = Obj_Stand;
		m_Pos.Y = (float)m_Pos_Bottom_Check.Y - PartYSize;
		m_v_Cur_JumpForce = .0f;
	}

	if (true == m_b_BottomCheck && true == m_b_JumpCheck)
	{
		m_b_JumpCheck = false;
	}
}

void TheOne::Update_Force(const float& _Force)
{
	if (false == m_b_JumpCheck)
	{
		m_v_GravityTime = .0f;
		m_b_JumpCheck = true;
		m_b_BottomCheck = false;
		m_v_Cur_JumpForce = _Force;
	}
}

void TheOne::Update_Gravity()
{
	Update_Bottom();

	// �ٴ� ���� - ����
	if(false == m_b_BottomCheck || true == m_b_JumpCheck)
	{
		// �Ʒ��� �������� 5~60 �ְ� �߷��� �����Ų��.
		// �ּ��� �� �������� �߷� - ���� �߷°����� �־���.-> ���� �ε巯�� ���� �׸��� ����
		m_Pos.Y -= m_v_Cur_JumpForce * DELTATIME;
		m_v_Cur_JumpForce -= m_v_Gravity * DELTATIME * 250;

		if (m_v_Cur_JumpForce < .0f)
		{
			m_Status_Obj = Obj_Down;
		}
		else if (m_v_Cur_JumpForce >= .0f)
		{
			m_Status_Obj = Obj_Up;
		}
	}
}

bool TheOne::Update_Wall()
{
	// �÷��̼����� �����Ѵ�.
	m_Pos_Wall_Check = { (int)m_Pos.X + (int)(PartXSize * m_pos_PrevDir.X), (int)m_Pos.Y };
	m_v_XColor = RESOURCEMANAGER.Get_PixelColor(m_MotherOfTheOne->acting_map(), m_Pos_Wall_Check);
	
	if (8443920 == m_v_XColor)
	{
		return true;
	}

	else
	{
		return false;
	}
}