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
	// �浹 �ߴ�.
	if (true == CollisionCheck(_pCollider))
	{
		m_set_Other_Iter = m_set_Other.find(_pCollider);

		// ������ �浹�� ���� ��Ƶδ� set���� ã�Ҵµ� ����
		// �׷� ���� �浹 -> Enter
		if (m_set_Other.end() == m_set_Other_Iter)
		{
			m_set_Other.insert(_pCollider);
			m_MotherOfTheOne_DE->CollisionEnter(_pCollider);
		}

		// �ƴϸ� ���� �浹 -> Stay
		else
		{
			m_MotherOfTheOne_DE->CollisionStay(_pCollider);
		}
	}

	// �浹 �� �ߴ�.
	else
	{
		m_set_Other_Iter = m_set_Other.find(_pCollider);

		// ������ �浹�� ���� ��Ƶδ� set���� ã�Ҵµ� �־�
		// �׷� �浹 ���� -> Exit
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
/***************�̺κ� ������ ��ü�� ������ ���� ������ ������ ��������.*************/
// ������ �׳� Stay�� �ҽ� �浹 ó���������� �׳� true�� ��ȯ�ϵ��� �ϰԵǸ� �̺κ� ��
// set�� �˻��ϴ� ������ �ʿ� ���ԵǾ� ���곶�� ���� �� �ִ�.
// �� ������ ���ð����̱� ������ �̺κ��� �ʿ������� �����鼭 �����Ѵ�.
// ��, �� ���ӿ� �浹 ���ʽ���, ����, �浹���ᰡ ���� �ʿ����� ���ؾ��ϴ� ���̴�.


void Collider::ColliderCreateDraw()
{
	/*	HS_BDIAGONAL	������ �ٹ���
	HS_CROSS	�ٵ��� ���
	HS_DIACROSS	������ �� ������ �ٹ���
	HS_FDIAGONAL	������ �ٹ���
	HS_HORIZONTAL	����
	HS_VERTICAL	������
	*/

	// CreateSolidBrush - �ܻ� ǥ��
	// CreateHatchBrush - �ٹ��̵� ǥ��

	// ���� ��
	NewBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 0, 0));
	OldBrush = (HBRUSH)SelectObject(CORE.GetBHDC(), NewBrush);


	// �ܻ�, �뽬, ��, �뽬 + ��, �뽬 + �� + ��
	// PS_SOLID, PS_DASH, PS_DOT, PS_PS_DASHDOT, PS_DASHDOTDOT

	MyPen = CreatePen(PS_SOLID, 5, RGB(0, 160, 255));
	OldPen = (HPEN)SelectObject(CORE.GetBHDC(), MyPen);


	// ���λ��� ���ִ� �ܰ� - NULL_PEN �� �ϸ� �׵θ��� �����
	SelectObject(CORE.GetBHDC(), GetStockObject(NULL_BRUSH));
}

void Collider::ColliderDraw()
{
	Positionf RenderPos = m_Rect.Pos;

	if (true == m_MotherOfTheOne_DE->CameraMode())
	{
		RenderPos -= m_MotherOfTheOne_DE->MotherOfTheOne()->CameraPos();
	}

	// ������ ������ �°� �׷��ش�.
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
	// ���� �׸��� �������Ѵٰ� �Ѵ�. �׷��� Old�� �����ѵ�
	// �׸��� ����-?
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