#include "stdafx.h"
#include "One_Stage_SCover.h"
#include "Trans_Renderer.h"


One_Stage_SCover::One_Stage_SCover() : Speed(3200)
{												
}


One_Stage_SCover::~One_Stage_SCover()
{
}


void One_Stage_SCover::Start(const Positionf& _Value)
{
	m_PrevPos = _Value;
	Cover = Create_Renderer<Trans_Renderer>(100);
	Cover->Set_Sprite(L"Stage_Cover_Start.bmp");
	Cover->Set_TransColor(VIOLET);
	m_Pos = { m_PrevPos.X, m_PrevPos.Y + 300 };
	
	m_Time = .0f;
	Obj_Time = .0f;

	m_CoverActing = true;
}

void One_Stage_SCover::Update()
{
	if (m_Time < Obj_Time)
	{
		// 안전 코드
		if (m_Pos.X > m_PrevPos.X + 1600)
		{
			m_CoverActing = false;
			return;
		}
		m_Pos.X += Speed * DELTATIME;
	}
	else
	{
		Obj_Time += DELTATIME;
	}
}
