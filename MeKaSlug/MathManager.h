#pragma once
#include "MatrixInfo.h"

// 난 싱글톤으로 해야지~♥
class MathManager
{
public:
	static MathManager& Inst()
	{
		static MathManager thisManager = MathManager();
		return thisManager;
	}
	
	// 여기서 구해질 값들은 실제로 많이 쓰일 예정이기에 public으로 해둔다.
public:
	float Absolute_Num		(const float& _Num);
	float Absolute_Num		(const int& _Num);
	Vector2f Absolute_Vector(const Vector2f& _Num);
	float Distance			(const Positionf& _Left, const Positionf& _Right);
	float Radian			(const Positionf& _Left, const Positionf& _Right);
	float Degree			(const Positionf& _Left, const Positionf& _Right);
	Dirf Vector_Dir			(const Positionf& _Value);
	Dirf PntToPnt_Dir		(const Positionf& _Left, const Positionf& _Right);

	bool RectToRect			(const Figure_Rect& _Left, const Figure_Rect& _Right);
	bool RectToCircle		(const Figure_Rect& _Left, const Figure_Circle& _Right);
	bool RectToPoint		(const Figure_Rect& _Left, const Figure_Point& _Right);
	bool CircleToCircle		(const Figure_Circle& _Left, const Figure_Circle& _Right);
	bool CircleToPoint		(const Figure_Circle& _Left, const Figure_Point& _Right);
	bool PointToPoint		(const Figure_Point& _Left, const Figure_Point& _Right);

private:
	MathManager();
	~MathManager();
};

