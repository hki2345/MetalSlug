#pragma once
#include "BaseEnemy.h"
#include "FsmWorker.h"

class Enemy_Tank : public BaseEnemy
{
private:
	// WALKERSTATE m_eState;
	FsmWorker m_Work;
	size_t Fire_Count;
	float Fire_Time;
	float IntervalTime;
	float m_Time;

	int Hp;
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
	std::wstring m_s_Damage;
	std::wstring m_s_Reload;
	std::wstring m_s_Stop;
	std::wstring m_s_Wrecked;


public:
	void Init() override;
	void Update() override;

	void DebugUpdate() override;

private: /// StateFunc
	void DirCheck();
	bool StrCheck(const std::wstring _Str);

	void Move();
	void Idle();
	void Att();
	void AttackInterval();
	void Damage();
	void Reload();
	void Stop();
	void Wrecked();

public:
	virtual void CollisionEnter(Collider* _Other) override;
public:
	Enemy_Tank();
	~Enemy_Tank();
};

