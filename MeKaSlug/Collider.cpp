#include "stdafx.h"
#include "Collider.h"


Collider::Collider() : m_ColliderType(TYPE::RECT)
{
}


Collider::~Collider()
{
}

void Collider::Collision(Collider* _pCollider)
{
	// 충돌 했다.
	if (true == CollisionCheck(_pCollider))
	{
		m_set_Other_Iter = m_set_Other.find(_pCollider);

		// 이전에 충돌한 것을 담아두는 set에서 찾았는데 없어
		// 그럼 최초 충돌 -> Enter
		if (m_set_Other.end() == m_set_Other_Iter)
		{
			m_set_Other.insert(_pCollider);
			m_MotherOfTheOne_DE->CollisionEnter(_pCollider);
		}

		// 아니면 연속 충돌 -> Stay
		else
		{
			m_MotherOfTheOne_DE->CollisionStay(_pCollider);
		}
	}

	// 충돌 안 했다.
	else
	{
		m_set_Other_Iter = m_set_Other.find(_pCollider);

		// 이전에 충돌한 것을 담아두는 set에서 찾았는데 있어
		// 그럼 충돌 종료 -> Exit
		if (m_set_Other.end() != m_set_Other_Iter)
		{
			m_set_Other.erase(_pCollider);
			m_MotherOfTheOne_DE->CollisionExit(_pCollider);
		}
	}
}

bool Collider::CollisionCheck(Collider* _pCollider)
{
	switch (m_ColliderType)
	{
	case Collider::RECT:
		switch (_pCollider->m_ColliderType)
		{
		case Collider::RECT:
			return MATHMANAGER.RectToRect(m_Rect, _pCollider->m_Rect);
		case Collider::CIRCLE:
			return MATHMANAGER.RectToCircle(m_Rect, _pCollider->m_Rect);
		case Collider::POINT:
			return MATHMANAGER.RectToPoint(m_Rect, _pCollider->m_Rect);
		default:
			return false;
		}
		break;
	case Collider::CIRCLE:
		switch (_pCollider->m_ColliderType)
		{
		case Collider::RECT:
			return MATHMANAGER.RectToCircle(_pCollider->m_Rect, m_Rect);
		case Collider::CIRCLE:
			return MATHMANAGER.CircleToCircle(m_Rect, _pCollider->m_Rect);
		case Collider::POINT:
			return MATHMANAGER.CircleToPoint(m_Rect, _pCollider->m_Rect);
		default:
			return false;
		}
		break;
	case Collider::POINT:
		switch (_pCollider->m_ColliderType)
		{
		case Collider::RECT:
			return MATHMANAGER.RectToPoint(_pCollider->m_Rect, m_Rect);
		case Collider::CIRCLE:
			return MATHMANAGER.CircleToPoint(_pCollider->m_Rect, m_Rect);
		case Collider::POINT:
			return MATHMANAGER.PointToPoint(m_Rect, _pCollider->m_Rect);
		default:
			return false;
		}
		break;
	default:
		return false;
	}

	return false;
}


/************************Debug Render**************************/
/***************이부분 때문에 객체가 많아질 수록 연산은 갑절로 많아진다.*************/
// 하지만 그냥 Stay만 할시 충돌 처리구문에서 그냥 true만 반환하도록 하게되면 이부분 즉
// set을 검색하는 행위가 필요 없게되어 연산낭비를 막을 수 있다.
// 내 게임은 슈팅게임이기 때문에 이부분이 필요한지는 만들어보면서 결정한다.
// 즉, 내 게임에 충돌 최초시작, 유지, 충돌종료가 따로 필요한지 정해야하는 것이다.


void Collider::ColliderCreateDraw()
{
	/*	HS_BDIAGONAL	좌하향 줄무늬
	HS_CROSS	바둑판 모양
	HS_DIACROSS	좌하향 및 우하향 줄무늬
	HS_FDIAGONAL	우하향 줄무늬
	HS_HORIZONTAL	수평선
	HS_VERTICAL	수직선
	*/

	// CreateSolidBrush - 단색 표현
	// CreateHatchBrush - 줄무늬도 표현

	// 내부 색
	NewBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 0, 0));
	OldBrush = (HBRUSH)SelectObject(CORE.GetBHDC(), NewBrush);


	// 단색, 대쉬, 점, 대쉬 + 점, 대쉬 + 점 + 점
	// PS_SOLID, PS_DASH, PS_DOT, PS_PS_DASHDOT, PS_DASHDOTDOT

	MyPen = CreatePen(PS_SOLID, 5, RGB(0, 160, 255));
	OldPen = (HPEN)SelectObject(CORE.GetBHDC(), MyPen);


	// 내부색을 없애는 단계 - NULL_PEN 을 하면 테두리가 사라짐
	SelectObject(CORE.GetBHDC(), GetStockObject(NULL_BRUSH));
}

void Collider::ColliderDraw()
{
	Positionf RenderPos = m_Rect.Pos;

	if (true == m_MotherOfTheOne_DE->CameraMode())
	{
		RenderPos -= m_MotherOfTheOne_DE->MotherOfTheOne()->CameraPos();
	}

	// 각각의 도형에 맞게 그려준다.
	switch (m_ColliderType)
	{
	case Collider::RECT:
		Rectangle(CORE.GetBHDC(),
			RenderPos.IntX() - m_Rect.Scale.IntPartX(),
			RenderPos.IntY() - m_Rect.Scale.IntPartY(),
			RenderPos.IntX() + m_Rect.Scale.IntPartX(),
			RenderPos.IntY() + m_Rect.Scale.IntPartY()
		);
		break;
	case Collider::CIRCLE:
		Ellipse(CORE.GetBHDC(),
			RenderPos.IntX() - m_Rect.Scale.IntPartX(),
			RenderPos.IntY() - m_Rect.Scale.IntPartY(),
			RenderPos.IntX() + m_Rect.Scale.IntPartX(),
			RenderPos.IntY() + m_Rect.Scale.IntPartY()
		);
		break;
	case Collider::POINT:
		Ellipse(CORE.GetBHDC(),
			RenderPos.IntX() - 1,
			RenderPos.IntY() - 1,
			RenderPos.IntX() + 1,
			RenderPos.IntY() + 1
		);
		break;
	default:
		break;
	}
}

void Collider::ColliderDeleteDraw()
{
	// 현재 그린건 지워야한다고 한다. 그래서 Old로 지정한뒤
	// 그린건 지움-?
	SelectObject(CORE.GetBHDC(), OldBrush);
	SelectObject(CORE.GetBHDC(), OldPen);
	DeleteObject(NewBrush);
	DeleteObject(MyPen);
}

void Collider::Obj_Debug_Render()
{
	ColliderCreateDraw();
	ColliderDraw();
	ColliderDeleteDraw();
}

void Collider::Release()
{
	std::set<Collider*>::iterator StartIter = m_set_Other.begin();
	std::set<Collider*>::iterator EndIter = m_set_Other.end();

	for (; StartIter != EndIter; )
	{
		if (true == (*StartIter)->Death())
		{
			StartIter = m_set_Other.erase(StartIter);
		}
		else
		{
			StartIter++;
		}
	}
}