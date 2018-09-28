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

// �ʱ�ȭ�ϱ� ���Ž�����
void TimeManager::Timer::Init()
{
	// ���� ������ �ʴ� CPU ó����
	QueryPerformanceFrequency(&m_CpuCount);

	// ���� CPU�� ������ ���� ���� �ð�
	QueryPerformanceCounter(&m_PrevACCTime);
}

// �ֽ�ȭ�ϱ� �������
float TimeManager::Timer::Update()
{
	// ���� CPU�� ������ ���� ���� �ð�
	QueryPerformanceCounter(&m_NowACCTime);

	// ����� ������ �����ð� �� / CPU ó���� = ��ŸŸ�� -> ����ũ�μ����� ����
	// ��ŸŸ���� ���Ǵ� -> CPU�� ó���ð�
	
	//	���紩�� - ���Ŵ���				 1
	// �ѤѤѤѤѤѤѤѤѤѤ� * �ѤѤѤѤѤѤѤѤѤ�
	//	   ����ũ�μ�����			 CPU ó����
	m_DeltaTime = ((float)(m_NowACCTime.QuadPart - m_PrevACCTime.QuadPart)) / (float)m_CpuCount.QuadPart;

	// ���ſ� ���縦 �ٲ�
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