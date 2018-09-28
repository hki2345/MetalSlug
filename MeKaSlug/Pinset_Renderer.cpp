#include "stdafx.h"
#include "Pinset_Renderer.h"

#include "ResourceManager.h"
#include "Core.h"


Pinset_Renderer::Pinset_Renderer() : m_Erase_Size(50), m_IsRender(true)
{
}


Pinset_Renderer::~Pinset_Renderer()
{
}


void Pinset_Renderer::Set_Pinset(const WCHAR* _pEnemySetName) {

	p_Sprite = RESOURCEMANAGER.Find_Res_Sprite(_pEnemySetName);
	KAssert(nullptr == p_Sprite);
}


// 적의 위치와 그 상태를 저장한다.
// 요부분을 고쳐야함
void Pinset_Renderer::Insert_Pinset(Position _Pos, Position _Dir, Position _Con)
{
	PinsetData newPinset( _Pos.To_Int64(), _Dir.To_Int64(), _Con.To_Int64());
	m_PinsetMap.push_back(newPinset);
}


// 요부분에서 고쳐야한다.?
void Pinset_Renderer::SetScreenToEnemy(Position _Pos, Position _Index, Position _Pos2)
{
	Positionf tempPos = _Pos;

	Insert_Pinset(_Pos, _Index, _Pos2);
}



void Pinset_Renderer::Render()
{
	if (false == CORE.Get_Value_Debeg()) { return;  }
	KAssert(nullptr == p_Sprite);


	Position StartPos =	Position();

	if (true == m_MotherOfTheOne_DE->CameraMode())
	{
		StartPos -= m_MotherOfTheOne_DE->MotherOfTheOne()->CameraPos();
	}

	m_StartIter = m_PinsetMap.begin();
	m_EndIter = m_PinsetMap.end();

	Position PinsetPos = Position();
	Position PinDirPos = Position();
	Position EnemyPos = Position();

	Position RenderPos = Position();

	WCHAR Str[100] = { 0, };
	int DebPos = 25;


	for (; m_StartIter != m_EndIter; m_StartIter++)
	{
		PinsetPos = (*m_StartIter).m_EPos;
		PinDirPos = (*m_StartIter).m_DPos;
		EnemyPos = (*m_StartIter).m_Condition;

		RenderPos.X = (PinsetPos.X + StartPos.X + CORE.GetSize().PartX());
		RenderPos.Y = (PinsetPos.Y + StartPos.Y + CORE.GetSize().PartY());

		swprintf_s(Str, L"Pinset Pos: %d %d", PinsetPos.X, PinsetPos.Y);
		TEXT_OUT((int)(RenderPos.X) + DebPos, (int)(RenderPos.Y) - DebPos, Str);

		swprintf_s(Str, L"Pinset Dir: %d %d", PinDirPos.X, PinDirPos.Y);
		TEXT_OUT((int)(RenderPos.X) + DebPos, (int)(RenderPos.Y) - DebPos + 20, Str);

		swprintf_s(Str, L"Who is Die: %d", EnemyPos.X);
		TEXT_OUT((int)(RenderPos.X) + DebPos, (int)(RenderPos.Y) - DebPos + 40, Str);

		swprintf_s(Str, L"Die Count: %d", EnemyPos.Y);
		TEXT_OUT((int)(RenderPos.X) + DebPos, (int)(RenderPos.Y) - DebPos + 60, Str);


		TransparentBlt(CORE.GetBHDC(),
			RenderPos.X - (int)(m_Size.X * 0.5f),
			RenderPos.Y - (int)(m_Size.Y * 0.5f),
			m_Size.X,
			m_Size.Y,
			p_Sprite->GetDc(),
			p_Sprite->rect().Pos.X, // 이미지의 어느점 x.
			p_Sprite->rect().Pos.Y, // 이미지의 어느점 y
			p_Sprite->rect().Size.X, // 그냥 사이즈 입니다.
			p_Sprite->rect().Size.Y, // 그냥 사이즈 입니다.
			p_Sprite->Get_Img()->Set_TransColor());
	}
}



void Pinset_Renderer::Clear()
{
	m_PinsetMap.clear();
}

std::vector<Pinset_Renderer::PinsetData> Pinset_Renderer::GetAllPinsetData()
{
	std::vector<Pinset_Renderer::PinsetData> ReturnData;

	m_StartIter = m_PinsetMap.begin();
	m_EndIter = m_PinsetMap.end();

	for (; m_StartIter != m_EndIter; m_StartIter++)
	{
		PinsetData New_EnemyData;

		New_EnemyData.m_EPos = (*m_StartIter).m_EPos;
		New_EnemyData.m_DPos = (*m_StartIter).m_DPos;
		New_EnemyData.m_Condition = (*m_StartIter).m_Condition;
		ReturnData.push_back(New_EnemyData);
	}

	return ReturnData;
}


void Pinset_Renderer::EraseScreenToPinset(Position _Pos)
{
	// 해당 반경 내에 있는 적을 지움
	std::list<PinsetData>::iterator StartIter = m_PinsetMap.begin();
	std::list<PinsetData>::iterator EndIter = m_PinsetMap.end();

	for (; StartIter != EndIter;)
	{
		Position Check_Pos = (*StartIter).m_EPos;

		Check_Pos = { Check_Pos.X + CORE.GetSize().PartX(), Check_Pos.Y + CORE.GetSize().PartY() };

		if (Check_Pos.X < _Pos.X + m_Erase_Size &&
			Check_Pos.X > _Pos.X - m_Erase_Size &&
			Check_Pos.Y < _Pos.Y + m_Erase_Size &&
			Check_Pos.Y > _Pos.Y - m_Erase_Size)
		{
			StartIter = m_PinsetMap.erase(StartIter);
		}
		else
		{
			StartIter++;
		}
	}
}
