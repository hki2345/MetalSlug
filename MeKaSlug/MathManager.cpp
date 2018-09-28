#include "stdafx.h"
#include <math.h>

#include "KMacro.h"
#include "MathManager.h"


MathManager::MathManager()
{
}


MathManager::~MathManager()
{
}

// ���밪 ��ȯ
float MathManager::Absolute_Num(const float& _Num)
{
	return _Num > .0f ? _Num : _Num * (-1.0f);
}

// ���밪 ��ȯ
float MathManager::Absolute_Num(const int& _Num)
{
	return _Num > .0f ? _Num : _Num * (-1.0f);
}

// ���밪 ��ȯ - ����
Vector2f MathManager::Absolute_Vector(const Vector2f& _Vector)
{
	Vector2f Temp = _Vector;
	Temp.X > .0f ? Temp.X : Temp.X *= (-1.0f);
	Temp.Y > .0f ? Temp.Y : Temp.Y *= (-1.0f);

	return Temp;
}

// �� �� ������ �Ÿ�
float MathManager::Distance(const Positionf& _Left, const Positionf& _Right)
{
	float AbsX = Absolute_Num(_Left.X - _Right.X);
	float AbsY = Absolute_Num(_Left.Y - _Right.Y);

	return (float)sqrt((AbsX * AbsX) + (AbsY * AbsY));
}

// �� ���� �̷�� ���� - ����
// ������ 1��и��� X��
float MathManager::Radian(const Positionf& _Left, const Positionf& _Right)
{
	// �ٴ� / ����
	float Oblique = Distance(_Left, _Right);
	float Bottom = Absolute_Num(_Left.X - _Right.X);
	
	float CosX = Bottom / Oblique;
	float CosAngle = 0;

	if (_Left.X > _Right.X)
	{
		// 1��и�
		if (_Left.Y < _Right.Y)
		{
			CosAngle = acosf(CosX * 1.0f);
		}
		// 4��и� -> ���ڻ����� PI�� �Ѿ�� �Ǹ� -�� �־� ������ �����־�� �Ѵ�.
		// �̴� ���ڻ��� �׷����� ���� �� Ȯ���� �� �� �ִ�. �׷����� PI�����ۿ� ���� ������ ����
		// PI �̻��� �������� ��Ÿ���� ���� �� �� �ִ�. ���⼭ 360�� 2PI�� ���Ϸ���
		// ������ x�� �������� ��Ī���Ѿ� �ϹǷ� -1�� ���Ͽ� �����Ѵ�.
		else
		if (_Left.Y >= _Right.Y)
		{
			CosAngle = acosf(CosX * -1.0f);
			CosAngle += (float)M_PI;
		}
	}
	else
	if (_Left.X <= _Right.X)
	{
		// 2��и�
		if (_Left.Y < _Right.Y)
		{
			CosAngle = acosf(CosX * -1.0f);
		}
		else
		// 3��и�
		if (_Left.Y >= _Right.Y)
		{
			CosAngle = acosf(CosX * 1.0f);
			CosAngle += (float)M_PI;
		}
	}

	// ���ڻ��� - �ﰢ�� ������ �� ���� ���´�.
	return CosAngle;
}

// �� ���� �̷�� ���� - 360��
// ������ 1��и��� X��
float MathManager::Degree(const Positionf& _Left, const Positionf& _Right)
{
	return Radian(_Left, _Right) * (float)RadianToDegree;
}

// �� ���� �̷�� ����
// ������ ���� 1��и��� X��
Dirf MathManager::PntToPnt_Dir(const Positionf& _Left, const Positionf& _Right)
{
	return { (float)cos(Radian(_Left, _Right)), (float)-sin(Radian(_Left, _Right)) };
}

// ������ ���� ���c��
Dirf MathManager::Vector_Dir(const Positionf& _Value)
{
	return {1 / _Value.Y, 1 / _Value.X };
}

// �� ���� ������ ������ � ��Ȳ -> ��ġ���� �Ǵ��Ѵ�.
// �簢���� �簢��
bool MathManager::RectToRect(const Figure_Rect& _Left, const Figure_Rect& _Right) 
{
	// ������ ��ǥ��� Y���� ��Ī�̶� ���� ���
	if (_Left.Top() > _Right.Bottom()) { return false; }
	if (_Left.Bottom() < _Right.Top()) { return false; }
	if (_Left.Left() > _Right.Right()) { return false; }
	if (_Left.Right() < _Right.Left()) { return false; }

	return true;
}

// �簢���� ��
bool MathManager::RectToCircle(const Figure_Rect& _Left, const Figure_Circle& _Right)
{
	// �켱 ��ũ�⸸ŭ �þ �簢�� ��ŭ �˻縦 �Ѵ�.
	Figure_Rect Verticle_Rect;
	Figure_Rect Horizon_Rect;

	Verticle_Rect.Pos = Horizon_Rect.Pos = _Left.Pos;
	Verticle_Rect.Scale = Horizon_Rect.Scale = _Left.Scale;

	Verticle_Rect.Scale.Y += _Right.Diameter();
	Horizon_Rect.Scale.X += _Right.Diameter();

	if(	true == RectToPoint(Verticle_Rect, _Right) || 
		true == RectToPoint(Horizon_Rect, _Right))
	{ return true; }


	// �� �����̸� �˻��ϴ� ���� ������ �˻��Ѵ�.	
	Figure_Circle CheckCircle = _Right;
	
	CheckCircle.Pos = _Left.LeftTop();
	if (true == CircleToPoint(CheckCircle, _Right)) 
	{ return true; }

	CheckCircle.Pos = _Left.LeftBottom();
	if (true == CircleToPoint(CheckCircle, _Right)) 
	{ return true; }

	CheckCircle.Pos = _Left.RightTop();
	if (true == CircleToPoint(CheckCircle, _Right)) 
	{ return true; }

	CheckCircle.Pos = _Left.RightBottom();
	if (true == CircleToPoint(CheckCircle, _Right)) 
	{ return true; }


	return false;
}

// �簢���� ��
bool MathManager::RectToPoint(const Figure_Rect& _Left, const Figure_Point& _Right)
{
	if (_Left.Top() > _Right.Pos.Y)		{ return false; }
	if (_Left.Bottom() < _Right.Pos.Y)	{ return false; }
	if (_Left.Left() > _Right.Pos.X)	{ return false; }
	if (_Left.Right() < _Right.Pos.X)	{ return false; }

	return true;
}

// ���� �� - ������ ��ǥ���� �Ÿ��� �������� �պ��� ������ ��ġ�� �����
bool MathManager::CircleToCircle(const Figure_Circle& _Left, const Figure_Circle& _Right)
{
	if (Distance(_Left.Pos, _Right.Pos) > (_Left.Radius() + _Right.Radius()))
	{ return false; }

	return true;
}

// ���� ��
bool MathManager::CircleToPoint(const Figure_Circle& _Left, const Figure_Point& _Right)
{
	if (Distance(_Left.Pos, _Right.Pos) > _Left.Radius())
	{ return false; }

	return true;
}

// ���� ��
bool MathManager::PointToPoint(const Figure_Point& _Left, const Figure_Point& _Right)
{
	if (_Left.Pos != _Right.Pos) { return false; }
	return true;
}