#include "stdafx.h"
#include "One_Stage_CCover.h"
#include "Trans_Renderer.h"


One_Stage_CCover::One_Stage_CCover() : Speed(3200)
{												
}


One_Stage_CCover::~One_Stage_CCover()
{
}


void One_Stage_CCover::Start(const Positionf& _Value)
{
	m_PrevPos = _Value;
	Cover = Create_Renderer<Trans_Renderer>(100);
	Cover->Set_Sprite(L"Stage_Cover_Close.bmp");
	Cover->Set_TransColor(VIOLET);
	m_Pos = { m_PrevPos.X - 600, m_PrevPos.Y + 300 };
	
	m_Time = 1.0f;
	Obj_Time = .0f;

	m_CoverActing = true;
}

void One_Stage_CCover::Update()
{
	// 안전 코드
	if (m_Pos.X >= (m_PrevPos.X + 800))
	{
		m_Pos.X = (m_PrevPos.X + 800);

		if (m_Time < Obj_Time)
		{
			m_CoverActing = false;
		}
		else
		{
			Obj_Time += DELTATIME;
		}
	}
	else
	{
		m_Pos.X += Speed * DELTATIME;
	}
}
