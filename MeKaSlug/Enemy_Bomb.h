#pragma once
#include "BaseEnemy.h"
#include "FsmWorker.h"

class Enemy_Bomb : public BaseEnemy
{
private:
	Animator* p_Render;
	// WALKERSTATE m_eState;
	FsmWorker m_Work;
	int Hp;

	size_t Fire_Count;
	float Fire_Time;
	float IntervalTime;

	float Speed;
	float AttRange;
	float MoveRange;
	float OutRange;
	float m_Run_Speed;

	std::wstring m_s_Acting;
	std::wstring m_s_Att;
	std::wstring m_s_Move;
	std::wstring m_s_Idle;
	std::wstring m_s_Interval;

	std::wstring m_s_SDie;
	std::wstring m_s_BDie;

public:
	void Init() override;
	void Update() override;

	void DebugUpdate() override;

private: 
	void DirCheck();
	bool StrCheck(const std::wstring _Str);
	/// StateFunc
	void Move();
	void Idle();
	void Att();
	void Run();
	void AttackInterval();
	void Die();

public:
	virtual void CollisionEnter(Collider* _Other) override;

public:
	Enemy_Bomb();
	~Enemy_Bomb();
};

