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

// 렌더러와 충돌체는 여기서 지운다. 
// 어차피 요놈이 만든거니까 여기서에서 지우는게 맞겠네
// 메니저에서 그룹을 만든 충돌체는 그룹에서 소멸자 불러질때 콜라이더 지우면 그래도 됌
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


// 방향에 따른 각도 분기를 알려줌
// 출발 각도 - 도착 각도, 나누는 크기, 크기의 몇 번째
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

	// 플레이서부터 측정한다.
	m_Pos_Bottom_Check = {(int) m_Pos.X, (int)(m_Pos.Y + (PartYSize - m_f_Bottom_Space)) }; ;
	m_b_BottomCheck = false;

	//  바닥 타일 밟으면 서있기
	if (L"Bottom" == m_Coll_Name && nullptr != p_BottomColl)
	{
		m_b_BottomCheck = true;

		m_Pos_Bottom_Check.Y = (int)(p_BottomColl->MotherOfTheOne_DE()->pos().Y - 15.0f);
		Update_BottomLine();
		return;
	}

	while (true)
	{
		// 그래도 탈출은 해야지
		if (m_Pos_Bottom_Check.Y > 10000)
		{
			// 아니 탈출하지말고 죽여벼리기....;; ;
			// 왜냐.. 10000 넘어간 객체는 보이지 않을 테니까...그게 플레이어든 뭐든
			Death(true);
		}

		m_v_YColor = RESOURCEMANAGER.Get_PixelColor(m_MotherOfTheOne->acting_map(), m_Pos_Bottom_Check);
		
		// 내가 쓰는 색상 0, 255, 255 -> 16776960
		if (16776960 != m_v_YColor)
		{
			m_Pos_Bottom_Check.Y++;

			// 필요없는 연산 없게 해 프레임 늘림
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
		//// 보정
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

	// 바닥 도착 - 안함
	if(false == m_b_BottomCheck || true == m_b_JumpCheck)
	{
		// 아래는 프레임을 5~60 주고 중력을 적용시킨다.
		// 주석된 건 인위적인 중력 - 실제 중력공식을 넣었다.-> 더욱 부드러움 ㅇㅇ 그리고 간단
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
	// 플레이서부터 측정한다.
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