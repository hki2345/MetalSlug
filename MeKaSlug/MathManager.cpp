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

// 절대값 반환
float MathManager::Absolute_Num(const float& _Num)
{
	return _Num > .0f ? _Num : _Num * (-1.0f);
}

// 절대값 반환
float MathManager::Absolute_Num(const int& _Num)
{
	return _Num > .0f ? _Num : _Num * (-1.0f);
}

// 절대값 반환 - 벡터
Vector2f MathManager::Absolute_Vector(const Vector2f& _Vector)
{
	Vector2f Temp = _Vector;
	Temp.X > .0f ? Temp.X : Temp.X *= (-1.0f);
	Temp.Y > .0f ? Temp.Y : Temp.Y *= (-1.0f);

	return Temp;
}

// 두 점 사이의 거리
float MathManager::Distance(const Positionf& _Left, const Positionf& _Right)
{
	float AbsX = Absolute_Num(_Left.X - _Right.X);
	float AbsY = Absolute_Num(_Left.Y - _Right.Y);

	return (float)sqrt((AbsX * AbsX) + (AbsY * AbsY));
}

// 두 점이 이루는 각도 - 라디안
// 기준은 1사분면의 X축
float MathManager::Radian(const Positionf& _Left, const Positionf& _Right)
{
	// 바닥 / 빗변
	float Oblique = Distance(_Left, _Right);
	float Bottom = Absolute_Num(_Left.X - _Right.X);
	
	float CosX = Bottom / Oblique;
	float CosAngle = 0;

	if (_Left.X > _Right.X)
	{
		// 1사분면
		if (_Left.Y < _Right.Y)
		{
			CosAngle = acosf(CosX * 1.0f);
		}
		// 4사분면 -> 아코사인은 PI가 넘어가게 되면 -를 넣어 역으로 구해주어야 한다.
		// 이는 아코사인 그래프를 보면 더 확실히 알 수 있다. 그래프는 PI까지밖에 없는 것으로 보아
		// PI 이상은 평행으로 나타내질 것을 알 수 있다. 여기서 360도 2PI를 구하려면
		// 평행을 x축 기준으로 대칭시켜야 하므로 -1을 곱하여 보정한다.
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
		// 2사분면
		if (_Left.Y < _Right.Y)
		{
			CosAngle = acosf(CosX * -1.0f);
		}
		else
		// 3사분면
		if (_Left.Y >= _Right.Y)
		{
			CosAngle = acosf(CosX * 1.0f);
			CosAngle += (float)M_PI;
		}
	}

	// 아코사인 - 삼각비를 넣으면 그 각이 나온다.
	return CosAngle;
}

// 두 점이 이루는 각도 - 360분
// 기준은 1사분면의 X축
float MathManager::Degree(const Positionf& _Left, const Positionf& _Right)
{
	return Radian(_Left, _Right) * (float)RadianToDegree;
}

// 두 점이 이루는 방향
// 기준은 역시 1사분면의 X축
Dirf MathManager::PntToPnt_Dir(const Positionf& _Left, const Positionf& _Right)
{
	return { (float)cos(Radian(_Left, _Right)), (float)-sin(Radian(_Left, _Right)) };
}

// 벡터의 방향 반홤ㄴ
Dirf MathManager::Vector_Dir(const Positionf& _Value)
{
	return {1 / _Value.Y, 1 / _Value.X };
}

// 두 개의 도형을 가지고 어떤 상황 -> 겹치는지 판단한다.
// 사각형대 사각형
bool MathManager::RectToRect(const Figure_Rect& _Left, const Figure_Rect& _Right) 
{
	// 윈도우 좌표계는 Y축이 대칭이란 것을 명심
	if (_Left.Top() > _Right.Bottom()) { return false; }
	if (_Left.Bottom() < _Right.Top()) { return false; }
	if (_Left.Left() > _Right.Right()) { return false; }
	if (_Left.Right() < _Right.Left()) { return false; }

	return true;
}

// 사각형대 원
bool MathManager::RectToCircle(const Figure_Rect& _Left, const Figure_Circle& _Right)
{
	// 우선 원크기만큼 늘어난 사각형 만큼 검사를 한다.
	Figure_Rect Verticle_Rect;
	Figure_Rect Horizon_Rect;

	Verticle_Rect.Pos = Horizon_Rect.Pos = _Left.Pos;
	Verticle_Rect.Scale = Horizon_Rect.Scale = _Left.Scale;

	Verticle_Rect.Scale.Y += _Right.Diameter();
	Horizon_Rect.Scale.X += _Right.Diameter();

	if(	true == RectToPoint(Verticle_Rect, _Right) || 
		true == RectToPoint(Horizon_Rect, _Right))
	{ return true; }


	// 네 귀퉁이를 검사하는 것은 원으로 검사한다.	
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

// 사각형대 점
bool MathManager::RectToPoint(const Figure_Rect& _Left, const Figure_Point& _Right)
{
	if (_Left.Top() > _Right.Pos.Y)		{ return false; }
	if (_Left.Bottom() < _Right.Pos.Y)	{ return false; }
	if (_Left.Left() > _Right.Pos.X)	{ return false; }
	if (_Left.Right() < _Right.Pos.X)	{ return false; }

	return true;
}

// 원대 원 - 서로의 좌표간의 거리가 반지름의 합보다 작으면 겹치는 경우임
bool MathManager::CircleToCircle(const Figure_Circle& _Left, const Figure_Circle& _Right)
{
	if (Distance(_Left.Pos, _Right.Pos) > (_Left.Radius() + _Right.Radius()))
	{ return false; }

	return true;
}

// 원대 점
bool MathManager::CircleToPoint(const Figure_Circle& _Left, const Figure_Point& _Right)
{
	if (Distance(_Left.Pos, _Right.Pos) > _Left.Radius())
	{ return false; }

	return true;
}

// 점대 점
bool MathManager::PointToPoint(const Figure_Point& _Left, const Figure_Point& _Right)
{
	if (_Left.Pos != _Right.Pos) { return false; }
	return true;
}