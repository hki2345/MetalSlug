#pragma once
class Vector2f
{
public:
	static const Vector2f Zero;
	static const Vector2f Left;
	static const Vector2f Right;
	static const Vector2f Up;
	static const Vector2f Down;
	
	float X;
	float Y;

	float PartX() const { return (X * 0.5F);}
	float PartY() const { return (Y * 0.5F);}

	int		IntX()		const { return (int)X; }
	int		IntY()		const { return (int)Y; }
	int		IntPartX()	const { return (int)PartX(); }
	int		IntPartY()	const { return (int)PartY(); }

	
	Vector2f operator+(const Vector2f& _Value) const
	{
		return{ X + _Value.X, Y + _Value.Y };
	}
	Vector2f operator-(const Vector2f& _Value) const
	{
		return{ X - _Value.X, Y - _Value.Y };
	}
	Vector2f operator*(const Vector2f& _Value) const
	{
		return {X * _Value.X, Y * _Value.Y};
	}

	Vector2f operator+(const float& _Value) const
	{
		return{ X + _Value, Y + _Value };
	}

	Vector2f operator*(const float& _Value) const
	{
		return{ X * _Value, Y * _Value };
	}
	Vector2f operator/(const float& _Value) const
	{
		return {X / _Value, Y / _Value};
	}

	Vector2f& operator-=(const Vector2f& _Value)
	{
		X -= _Value.X;
		Y -= _Value.Y;
		return *this;
	}

	Vector2f& operator+=(const Vector2f& _Value)
	{
		X += _Value.X;
		Y += _Value.Y;
		return *this;
	}

	Vector2f& operator+=(const float& _Value)
	{
		X += _Value;
		Y += _Value;
		return *this;
	}

	bool operator==(const Vector2f& _Value) const
	{
		return (X == _Value.X) && (Y == _Value.Y);
	}

	bool operator>=(const Vector2f& _Value) const
	{
		return (X == _Value.X) && (Y == _Value.Y);
	}
	bool operator!=(const Vector2f& _Value) const
	{
		return (X != _Value.X) || (Y != _Value.Y);
	}

	bool operator>(const Vector2f& _Value) const
	{
		return (X > _Value.X) && (Y > _Value.Y);
	}
	bool operator<(const Vector2f& _Value) const
	{
		return (X < _Value.X) && (Y < _Value.Y);
	}
};

typedef Vector2f Sizef;
typedef Vector2f Positionf;
typedef Vector2f Dirf;


// ��� ��(One)���� ��ǥ�� ũ�⸦ ������.
class Vector2
{
public:
	static const Vector2 Zero;
	static const Vector2 Left;
	static const Vector2 Right;
	static const Vector2 Up;
	static const Vector2 Down;

	int X;
	int Y;

	int PartX() { return (int)(X * 0.5F); }
	int PartY() { return (int)(Y * 0.5F); }

	__int64 To_Int64()
	{
		// 64int ����ȯ ����
		return *(__int64*)this;
	}

	Vector2& operator=(const Vector2f& _Value) 
	{
		X = (int)_Value.X; Y = (int)_Value.Y;
		return *this;
	}

	void operator=(__int64 _Pos)
	{
		memcpy(this, &_Pos, sizeof(__int64));
	}

	Vector2 operator*(const int& _Value)
	{
		return Vector2(X * (int)_Value, Y * (int)_Value);
	}

	Vector2 operator*(const float& _Value)
	{
		return Vector2(X * (int)_Value, Y * (int)_Value);
	}

	Vector2 operator+(const Vector2& _Value)
	{
		return Vector2(X + _Value.X, Y + _Value.Y);
	}


	Vector2 operator+(const Vector2f& _Value)
	{
		return Vector2(X + (int)_Value.X, Y + (int)_Value.Y);
	}

	bool operator !=(const Vector2& _Other)
	{
		return (this->X != _Other.X || this->Y != _Other.Y);
	}

	bool operator==(const Vector2&  _Other)
	{
		return (this->X == _Other.X && this->Y == _Other.Y);
	}

	Vector2& operator-=(Vector2 _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;

		return *this;
	}

	Vector2& operator+=(Vector2 _Other)
	{
		X += _Other.X;
		Y += _Other.Y;

		return *this;
	}

	Vector2& operator-=(Vector2f _Other)
	{
		X -= (int)_Other.X;
		Y -= (int)_Other.Y;

		return *this;
	}

	// ����ȯ - 
	operator Vector2f()
	{
		return{ (float)X, (float)Y };
	}

	Vector2() { *this = Vector2::Zero; }
	Vector2(int _X, int _Y) : X(_X), Y(_Y) {}
	Vector2(float _X, float _Y) : X((int)_X), Y((int)_Y) {}

	// ������ Pos�� �ϳ��� �ڷ������� ��Ÿ���� ���� �����
	Vector2(__int64 _Pos) { memcpy(this, &_Pos, sizeof(__int64)); }
};

typedef Vector2 Size;
typedef Vector2 Position;
typedef Vector2 Index;

// ���� �� ���� �簢���� ǥ���� �� �ִ�.
// ���۰� �� ��ǥ�� ������ �׸� -> Win���� �����ϴ� �Ͱ� ����ϰ� ����.
class Rect
{
public:
	Vector2 Pos;
	Vector2 Size;

public:
	Rect() : Pos(Vector2::Zero), Size(Vector2::Zero)
	{}

	Rect(const Rect& _Value) : Pos(_Value.Pos), Size(_Value.Size)
	{}

	Rect(Vector2 _Start, Vector2 _End) : Pos(_Start), Size(_End)
	{}
};

// ������ ��´�.
class Figure
{
public:
	Vector2f Pos;
	Vector2f Scale;

public:
	Positionf LeftTop()		const { return	{ Left(), Top() }; }
	Positionf RightTop()	const { return	{ Right(), Top() }; }
	Positionf LeftBottom()	const { return	{ Left(), Bottom() }; }
	Positionf RightBottom() const { return	{ Right(), Bottom() }; }

	// ���簢�� - Y���� window ��ǥ�踦 ����Ѵ�.
	float Left()	const { return	(Pos.X - Scale.PartX()); }
	float Right()	const { return	(Pos.X + Scale.PartX()); }
	float Top()		const { return	(Pos.Y - Scale.PartY()); }
	float Bottom()	const { return	(Pos.Y + Scale.PartY()); }

	// �� - �������� ����
	float	Radius() const			{ return Scale.PartX(); }
	void	Radius(float _Value)	{ Scale.X = _Value * 2.0f; }	
	float	Diameter() const		{ return Scale.X; }

public:
	Figure(const Figure& _Value) : Pos(_Value.Pos), Scale(_Value.Scale)
	{}

	Figure(Vector2f _Start, Vector2f _End) : Pos(_Start), Scale(_End)
	{}

	Figure() {}
};

typedef Figure Figure_Rect;
typedef Figure Figure_Circle;
typedef Figure Figure_Point;