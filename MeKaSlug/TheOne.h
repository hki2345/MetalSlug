#pragma once
#include "Begin_DE.h"
#include "MatrixInfo.h"

#include "Core.h"

#include <vector>

class Collider;
class State_Boss;
class State_Debug_SB;
class TheOne : public Begin_DE
{
	// 전방선언과 프랜드를 한 번에
public:
	friend class BaseState;
	// 보스스테이지는 특수함
	friend class State_Boss;
	friend class State_Debug_SB;

	enum Obj_Status 
	{
		Obj_Stand,
		Obj_Up,
		Obj_Down,
	};

protected:
	// 일단 보류시켜보장
	enum Gun_Status {
		Basic = 0,
		HeavyMachine = 1,
		Missile = 2,
		ShotGun = 3,
		Flame = 4,
	};

	Positionf	m_Pos;

	Positionf	m_PrevPos;

	// 이 방향은 사선 방향 -> 따로간다.
	Dirf		m_pos_NextDir;
	Dirf		m_pos_PrevDir;
	Dirf		m_pos_Dir;
	Position	m_Pos_Bottom_Check;
	Position	m_Pos_Wall_Check;

	// Mother - State
	BaseState*	m_MotherOfTheOne;
	Collider*	p_Collider;

	float		PartYSize;
	float		PartXSize;
	float		m_f_Bottom_Space;


	// 점프 계수, 점프 올라갈 때, 점프 내려갈 때, 바닥 감지
	float	m_v_Gravity;
	float	m_v_GravityTime;
	float	m_v_Jump_Force;
	float	m_v_Cur_JumpForce;

	bool	m_b_JumpCheck;
	bool	m_b_BottomCheck;
	bool	m_b_Camera;

	int		m_v_XColor;
	int		m_v_YColor;

	Obj_Status m_Status_Obj;

	std::wstring	m_Coll_Name;
	Collider*		p_BottomColl;

public:

	void CameraMode(bool _Value)		{ m_b_Camera = _Value; }
	bool CameraMode()					{ return m_b_Camera; }

	// Mother - State
	void		MotherOfTheOne(BaseState* _Value)		{ m_MotherOfTheOne = _Value; }
	// Mother - State
	BaseState*	MotherOfTheOne()						{ return m_MotherOfTheOne; }

	void		pos(Positionf _Value)		{ m_Pos = _Value; }
	Positionf	pos()						{ return m_Pos; }
	Position	pos_int()					{ return {(int)m_Pos.X, (int)m_Pos.Y }; }

public:
	// 죽거나 혹은 일부 고정된 물체는 각각 시각1화, 최신화가 필요하지 않게 된다.
	// 시각화는 따로 관여되는 것이 맞다. -> private으로 하면 지금 여기서 통일된 시각화가
	// 이루어지는데 각각의 객체가 똑같이 생기진 않았으므로
	virtual void Init() {};
	virtual void Update() {};
	virtual void DebugUpdate() {};

	virtual void Init_Render() {};
	virtual void Init_Collision() {};

private:
	virtual	void UpdateCheckLive() {};

protected:

	// 방향에 따른 각도 분기를 알려줌
	// 출발 각도 - 도착 각도, 나누는 크기, 크기의 몇 번째
	bool Render_pos_Dir_Check(Vector2f _Left, Vector2f _Right,
		const size_t& _AngleSize, const size_t& _Check_Count);

	void Update_Bottom();
	void Update_Gravity();
	void Update_Force(const float& _Force);

	virtual void Update_BottomLine();

	bool Update_Wall();

	/************************ Renderer **********************/
private:
	std::vector<Renderer*> m_Vec_Renderer;

protected:

	// AniRenderWork;
	// SingleRenderWork;
	template<typename T>
	T* Create_Renderer(int _Order)
	{
		T* NewRender = new T();
		// 그리는 순서.
		NewRender->Order(_Order);
		NewRender->MotherOfTheOne_DE(this);
		m_MotherOfTheOne->Insert_Renderer(NewRender);
		m_Vec_Renderer.push_back(NewRender);
		return NewRender;
	}


	template<typename T>
	T* Get_Renderer(size_t _Index)
	{
		KAssert(_Index >= m_Vec_Renderer.size());

		return (T*)m_Vec_Renderer[_Index];
	}

	
	/************************ Collider **********************/
protected:
	std::vector<Collider*> m_Vec_Collider;
	Collider* Create_Collider(const WCHAR* _GroupName, Sizef _Size);


	// 충돌체가 이것을 알아야 충돌체의 상태를 변화시킬 수 있다.
public:
	// 진정 충돌했는지 확인 -> 자식들이 확인 한다. 어짜피 자식들이 충돌체를 가지고 있으니
	// 충돌 할 때 어떤짓을 할 지는 자식들이 결정
	virtual void CollisionEnter(Collider* _Other){};
	virtual void CollisionStay(Collider* _Other){};
	virtual void CollisionExit(Collider* _Other){};
	
	
	// 무기 작용
public:
	virtual void Activate() {};

	// 자식들만이 만들어낼 수 있다.
	// 자식이 반드시 있어야 한다.
protected:
	TheOne();
	virtual ~TheOne() = 0 ;
};
