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
	// ���漱��� �����带 �� ����
public:
	friend class BaseState;
	// �������������� Ư����
	friend class State_Boss;
	friend class State_Debug_SB;

	enum Obj_Status 
	{
		Obj_Stand,
		Obj_Up,
		Obj_Down,
	};

protected:
	// �ϴ� �������Ѻ���
	enum Gun_Status {
		Basic = 0,
		HeavyMachine = 1,
		Missile = 2,
		ShotGun = 3,
		Flame = 4,
	};

	Positionf	m_Pos;

	Positionf	m_PrevPos;

	// �� ������ �缱 ���� -> ���ΰ���.
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


	// ���� ���, ���� �ö� ��, ���� ������ ��, �ٴ� ����
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
	// �װų� Ȥ�� �Ϻ� ������ ��ü�� ���� �ð�1ȭ, �ֽ�ȭ�� �ʿ����� �ʰ� �ȴ�.
	// �ð�ȭ�� ���� �����Ǵ� ���� �´�. -> private���� �ϸ� ���� ���⼭ ���ϵ� �ð�ȭ��
	// �̷�����µ� ������ ��ü�� �Ȱ��� ������ �ʾ����Ƿ�
	virtual void Init() {};
	virtual void Update() {};
	virtual void DebugUpdate() {};

	virtual void Init_Render() {};
	virtual void Init_Collision() {};

private:
	virtual	void UpdateCheckLive() {};

protected:

	// ���⿡ ���� ���� �б⸦ �˷���
	// ��� ���� - ���� ����, ������ ũ��, ũ���� �� ��°
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
		// �׸��� ����.
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


	// �浹ü�� �̰��� �˾ƾ� �浹ü�� ���¸� ��ȭ��ų �� �ִ�.
public:
	// ���� �浹�ߴ��� Ȯ�� -> �ڽĵ��� Ȯ�� �Ѵ�. ��¥�� �ڽĵ��� �浹ü�� ������ ������
	// �浹 �� �� ����� �� ���� �ڽĵ��� ����
	virtual void CollisionEnter(Collider* _Other){};
	virtual void CollisionStay(Collider* _Other){};
	virtual void CollisionExit(Collider* _Other){};
	
	
	// ���� �ۿ�
public:
	virtual void Activate() {};

	// �ڽĵ鸸�� ���� �� �ִ�.
	// �ڽ��� �ݵ�� �־�� �Ѵ�.
protected:
	TheOne();
	virtual ~TheOne() = 0 ;
};
