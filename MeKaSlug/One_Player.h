#pragma once
#include "TheOne.h"


class Collider;
class Animator;
class One_Player : public TheOne
{
public:
	enum Die_Status
	{
		Die_Respawn = 0,
		Die_None,
		Die_Sword,
		Die_Shut,
		Die_Air,
		Die_Fire,
		Die_Laser,
	};

protected:
	enum Player_Status {
		Stand = 0,
		Jump_Up,
		Jump_Down,
		Sitting,
		Sit,
	};

	
	enum Fire_Status {
		Shut = 0,
		Sword,
		Bomb,
		Kick,
		Special,
		None,
	};

	enum Render_Leg
	{
		Leg_Idle = 0,
		Leg_Run_Stop,
		Leg_Jump_Up,
		Leg_Jump_Down,
		Leg_Run_Jump_Up,
		Leg_Run_Jump_Down,
		Leg_Run,
		Leg_BodyAcition,
	};

	enum Render_Body
	{
		Body_None = -1,
		Body_Idle = 0,
		Body_Look_Up,
		Body_Run_Stop,
		Body_Jump_Up,
		Body_Jump_LookUp,
		Body_Jump_LookDown,
		Body_Jump_Down,
		Body_Run_Jump_Up,
		Body_Run_Jump_Down,
		Body_Run,
		Body_Angle_UpSide,
		Body_Angle_DownSide,
		Body_Ceremony,
	};


	Animator* p_RenderBody;
	Animator* p_RenderLeg;

	bool		m_Auto_Move;

protected:
	std::wstring	m_Wchar_Enemy;
	std::wstring	m_Wchar_EnemyMachine;
	std::wstring	m_Wchar_HeavyMachine;



	Player_Status	m_Status_Player;
	Gun_Status		m_Status_Gun;
	Render_Leg		m_Status_Leg;
	Render_Body		m_Status_Body;
	Render_Body		m_Status_JumpBody;
	Die_Status		m_Status_Die;
	Fire_Status		m_Status_Fire;
	bool			m_b_ReAttack;
	bool			m_b_Sword;

	bool			m_b_FeverMode;

	// 점프를 누르지 않았을 때 방향 보정- JumpUpdate
	int m_v_JumpDir;

	// 방향키를 땠을 때 움직임을 자유롭게 하기 위함
	// 좌우만 측정 하기 위해 int로 받는다.
	Positionf	m_pos_Jump_Dir;

	float m_pos_Dir_speed;
	float m_Run_Speed;
	float m_Slow_Jump_SpeedUp;
	float m_Slow_Jump_SpeedDown;
	float m_Fast_Jump_SpeedUp;
	float m_Fast_Jump_SpeedDown;
	float m_Sit_Speed;


	float m_Time;
	float m_Ceremony_Time;
	float m_Die_Time;
	float m_Respawn_Time;

	// 혹시 모르니까 버출얼로
	virtual void Init_Collision();
	virtual void Init_Render() {};

	// 레오나는 특수기술을 쓴다. -> 하위 클래스에서 구현하는 것으로
	void Update_Key_Render();
	void Update_Jump();
	void Update_Fever();



	// FSM 형태만 갖추자 -> 너무 많아서 일단 함수로 찢기만 해도 됄듯
	virtual void Update_AutoMove();
	virtual void Update_Move();
	virtual void Update_Wall(const float& _X);
	virtual void Update_Move_AddON_DirCheck();
	virtual void Update_LookUp();
	virtual void Update_LookDown();
	virtual void Update_Fire();
	virtual void Update_JumpStatus();
	virtual void Update_Kick();
	virtual void Update_Bomb();
	virtual void Update_Die();

private:
	float m_Heavy_Time;
	float m_Gun_Timer;
	size_t m_Heavy_Cnt;

	void Update_Heavy();


	Positionf m_pos_Respawn;

	void Init_Die_Sword();
	void Init_Die_Air(const float& _Value);
	void Init_Die_Shut();
	void Init_Die_Fire();
	void Init_Respawn();


	void Update_Die_Sword();
	void Update_Die_Air();
	void Update_Die_Shut();
	void Update_Die_Fire();
	void Update_Respawn();

	bool Check_MachineEnemy();

	// 불렛의 시작위치를 잡아준다. -> 호출 위치 Fire
	Positionf Update_Bullet();

	
	// 바닥을 충돌시키기 위해 알아야한다.
	Collider* EnemyCollider;

public:
	void		auto_Move(const bool& _Value)	{ m_Auto_Move = _Value; }
	bool&		auto_Move()						{ return m_Auto_Move; }

	void		pos_direction(Positionf& _Value)	{ m_pos_Dir = _Value; }
	Positionf&	pos_direction()						{ return m_pos_Dir; }

	float&		run_speed()						{ return m_Run_Speed; }

	// 초기화 문 필요
	virtual void Init() override;
	virtual void Update() override {};
	virtual void DebugUpdate() override;

	virtual void CollisionEnter(Collider* _Other) override;
	virtual void CollisionStay(Collider* _Other) override;
	virtual void CollisionExit(Collider* _Other) override;
	
	/*********************** Sound ************************/
	void Sound_Die();

public:
	One_Player();
	~One_Player();
};

