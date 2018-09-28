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
		// 공용체 - 안에 QuadPart라는 데이터를 쓸 거임
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
	// 타임 메니저도 싱글톤으로
	static TimeManager& Inst()
	{
		static TimeManager OnlyTimeManger = TimeManager();
		return OnlyTimeManger;
	}

	// 전체 프레임을 잰다. -> 게임 운영의 기초
	Timer FrameTimer;

	std::map<std::wstring, Timer*> m_map_Timer;

public:
	void Update();
	// 컴파일러 선택 문법 -> 함수의 ()를 생략해주는데 그건 컴파일러 마음임
	inline float DeltaTime()		{ return FrameTimer.m_DeltaTime; }

private:
	TimeManager();
	~TimeManager();
};

