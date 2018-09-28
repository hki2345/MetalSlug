#pragma once
#include "BaseEnemy.h"
#include "FsmWorker.h"

class Enemy_Boss : public BaseEnemy
{
private:
	int NextStatus;

	// WALKERSTATE m_eState;
	FsmWorker m_Work;
	size_t Fire_Count;
	float Fire_Time;
	float Mode_Time;
	float m_f_Time;

	int Hp;
	float CurSpeed;
	float Speed;

	std::wstring m_s_Acting;

	std::wstring m_s_Start;
	std::wstring m_s_MagamaCannon;
	std::wstring m_s_MedicineCannon_Open;
	std::wstring m_s_MedicineCannon_Close;
	std::wstring m_s_WaveAttack;
	std::wstring m_s_RiseAttack;

	std::wstring m_s_Idle;
	std::wstring m_s_Wrecked;


public:
	bool BossDie() { if (m_s_Acting == m_s_Wrecked) { return true; } return false; }
	bool BossRise() { if (m_s_Acting == m_s_RiseAttack) { return true; } return false; }
	void Init() override;
	void Update() override;

	void DebugUpdate() override;

private: /// StateFunc
	bool StrCheck(const std::wstring _Str);
	
	void Init_Idle();


	void Start();
	void MagamaCannon();
	void MedicineCannon_Open();
	void MedicineCannon_Close();
	void WaveAttack();
	void RiseAttack();
	void Idle();
	void Wrecked();

public:
	virtual void CollisionEnter(Collider* _Other) override;

public:
	Enemy_Boss();
	~Enemy_Boss();
};

