#pragma once
#include "TheOne_DE.h"
#include <set>

// ���������� �������� ����ϴ� - �� ��ü���� �ͼӵǴ� �����̴ϱ�
// �浹ü�� �浹 ó���� �ϴ� �͸� �ٸ� ��
class Collider : public TheOne_DE
{
	// �浹ü�� �簢��, ��, ���� ���¸� ���.
	// �� �������� �ϴ��� 9������ ����� ���� ������ ������
	// Ŭ������ ��ӳ����� �ʴ� ���̴�.
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

	// ���� �� �浹ü�� ��ġ�� ����� ��´�.
	Figure_Rect m_Rect;

	// �浹�� �͵��� ��� ��Ƶд� -> enter, stay, Exit ���
	std::set<Collider*>::iterator m_set_Other_Iter;
	std::set<Collider*> m_set_Other;

	// �׸��� ���� ������
	// ���� ĥ
	// �ܺ� �׵θ�
	HBRUSH NewBrush, OldBrush;
	HPEN MyPen, OldPen;


private:
	// �浹ü�� �浹ó���� �ؾ��Ѵ�. - �浹 �˻縦 �ؾ� �Ѵ�.
	void Collision(Collider* _pCollider);
	bool CollisionCheck(Collider* _pCollider);
	void ColliderCreateDraw();
	void ColliderDraw();
	void ColliderDeleteDraw();

	// Enter - Stay - Exit�� �ϱ����� �ӽ� set�� ������Ų��.
	void Release();


public:
	void		size(const Sizef& _Value)	{ m_Rect.Scale = _Value; }
	Sizef&		size()						{ return m_Rect.Scale; }

	
	void		Obj_Debug_Render();

	// �浹ü�� ��ġ�� �����Ѵ�. -> �� �ֽ�ȭ �Ǿ� ��ü�� ���� ��ü�� ����ٳ�� �ϹǷ�
	void		Calculate_Figure_Pos()	{ m_Rect.Pos = m_MotherOfTheOne_DE->pos() + m_Pivot; }
	void		type(TYPE _Value)		{ m_ColliderType = _Value; }


public:
	Collider();
	~Collider();
};

