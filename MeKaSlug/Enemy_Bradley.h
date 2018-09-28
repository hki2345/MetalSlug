#pragma once
#include "BaseEnemy.h"
#include "FsmWorker.h"

class Enemy_Bradley : public BaseEnemy
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

	bool Raise;

	std::wstring m_s_Acting;

	std::wstring m_s_Att;
	std::wstring m_s_Idle;
	std::wstring m_s_Interval;
	std::wstring m_s_Damage;
	std::wstring m_s_Wrecked;
	std::wstring m_s_ToRaise;
	std::wstring m_s_ToSide;


public:
	void Init() override;
	void Update() override;

	void DebugUpdate() override;

private: /// StateFunc
	void DirCheck();
	bool StrCheck(const std::wstring _Str);

	void Idle();
	void Att();
	void AttackInterval();
	void Damage();
	void Wrecked();
	void ToSide();
	void ToRaise();

public:
	virtual void CollisionEnter(Collider* _Other) override;
public:
	Enemy_Bradley();
	~Enemy_Bradley();
};

