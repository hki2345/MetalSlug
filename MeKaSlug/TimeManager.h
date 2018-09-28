#pragma once
#include <map>

class TimeManager
{
private:
	class Timer
	{
	public:
		friend TimeManager;

	private:
		// ����ü - �ȿ� QuadPart��� �����͸� �� ����
		LARGE_INTEGER m_CpuCount;
		LARGE_INTEGER m_NowACCTime;
		LARGE_INTEGER m_PrevACCTime;
		float m_DeltaTime;

	public:
		void Init();
		float Update();

	public:
		Timer();
		~Timer();
	};

public:
	// Ÿ�� �޴����� �̱�������
	static TimeManager& Inst()
	{
		static TimeManager OnlyTimeManger = TimeManager();
		return OnlyTimeManger;
	}

	// ��ü �������� ���. -> ���� ��� ����
	Timer FrameTimer;

	std::map<std::wstring, Timer*> m_map_Timer;

public:
	void Update();
	// �����Ϸ� ���� ���� -> �Լ��� ()�� �������ִµ� �װ� �����Ϸ� ������
	inline float DeltaTime()		{ return FrameTimer.m_DeltaTime; }

private:
	TimeManager();
	~TimeManager();
};

