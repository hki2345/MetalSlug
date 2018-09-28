#include "stdafx.h"
#include "TimeManager.h"



/**********Timer*********/

TimeManager::Timer::Timer()
{
	Init();
}

TimeManager::Timer::~Timer()
{
}

// 초기화니까 과거시점임
void TimeManager::Timer::Init()
{
	// 절대 변하지 않는 CPU 처리량
	QueryPerformanceFrequency(&m_CpuCount);

	// 과거 CPU가 구동된 후의 누적 시간
	QueryPerformanceCounter(&m_PrevACCTime);
}

// 최신화니까 현재시점
float TimeManager::Timer::Update()
{
	// 현재 CPU가 구동된 후의 누적 시간
	QueryPerformanceCounter(&m_NowACCTime);

	// 현재와 과거의 누적시간 차 / CPU 처리량 = 델타타임 -> 마이크로세컨드 단위
	// 델타타임의 정의는 -> CPU당 처리시간
	
	//	현재누적 - 과거누적				 1
	// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ * ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//	   마이크로세컨드			 CPU 처리량
	m_DeltaTime = ((float)(m_NowACCTime.QuadPart - m_PrevACCTime.QuadPart)) / (float)m_CpuCount.QuadPart;

	// 과거와 현재를 바꿈
	m_PrevACCTime.QuadPart = m_NowACCTime.QuadPart;

	return m_DeltaTime;
}



/****************TimeManager*************/

TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	FrameTimer.Update();
} 