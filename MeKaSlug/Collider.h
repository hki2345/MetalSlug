#pragma once
#include "TheOne_DE.h"
#include <set>

// 전반적으로 렌더러와 비슷하다 - 한 객체에게 귀속되는 형태이니까
// 충돌체는 충돌 처리를 하는 것만 다를 뿐
class Collider : public TheOne_DE
{
	// 충돌체는 사각형, 원, 점의 형태를 띈다.
	// 이 세가지만 하더라도 9가지의 경우의 수가 나오기 때문에
	// 클래스로 상속내리지 않는 것이다.
public:
	enum TYPE
	{
		RECT,
		CIRCLE,
		POINT
	};


public:
	friend class TheOne;
	friend class ColliderManager;

private:
	TYPE m_ColliderType;

	// 현재 이 충돌체의 위치와 사이즈를 담는다.
	Figure_Rect m_Rect;

	// 충돌한 것들을 잠시 담아둔다 -> enter, stay, Exit 담당
	std::set<Collider*>::iterator m_set_Other_Iter;
	std::set<Collider*> m_set_Other;

	// 그리기 위한 도구들
	// 내부 칠
	// 외부 테두리
	HBRUSH NewBrush, OldBrush;
	HPEN MyPen, OldPen;


private:
	// 충돌체는 충돌처리를 해야한다. - 충돌 검사를 해야 한다.
	void Collision(Collider* _pCollider);
	bool CollisionCheck(Collider* _pCollider);
	void ColliderCreateDraw();
	void ColliderDraw();
	void ColliderDeleteDraw();

	// Enter - Stay - Exit를 하기위한 임시 set을 해제시킨다.
	void Release();


public:
	void		size(const Sizef& _Value)	{ m_Rect.Scale = _Value; }
	Sizef&		size()						{ return m_Rect.Scale; }

	
	void		Obj_Debug_Render();

	// 충돌체의 위치를 선정한다. -> 늘 최신화 되어 강체를 만든 객체를 따라다녀야 하므로
	void		Calculate_Figure_Pos()	{ m_Rect.Pos = m_MotherOfTheOne_DE->pos() + m_Pivot; }
	void		type(TYPE _Value)		{ m_ColliderType = _Value; }


public:
	Collider();
	~Collider();
};

