#include "stdafx.h"
#include "Boss_Bottom.h"

#include "One_BottomEffect.h"
#include "Trans_Renderer.h"
#include "Collider.h"

Boss_Bottom::Boss_Bottom()
{
}


Boss_Bottom::~Boss_Bottom()
{
}

void Boss_Bottom::Start(const size_t& _Value, const size_t& _Size)
{
	Name(L"Bottom");
	size_t Val = _Value;
	p_Render = Create_Renderer<Trans_Renderer>(5);
	
	for (size_t i = 0; i < _Size; i++)
	{
		if (i == _Value)
		{
			if (Val > 5) { Val -= 5; }

			std::wstring temp = L"Bottom";
			WCHAR num[10];

			_itow_s(Val, num, 10);
			temp += num; temp += L".bmp";
			
			p_Render->Set_Sprite(temp.c_str());
			m_Pos = { (float)(1800 + (200 * i)), 1050.0f };
			break;
		}
	}

	p_Render->Set_TransColor(ORANGE);

	One_BottomEffect* thisEffect = m_MotherOfTheOne->StateOfOne_Create<One_BottomEffect>();
	thisEffect->Start(m_Pos);


	p_Collider = Create_Collider(L"Bottom", { 125, 10 });
	p_Collider->Pivot({ 0, -10 });
}