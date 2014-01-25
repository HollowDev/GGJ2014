#include "Timer.h"


Timer::Timer(void)
{
	m_FPS = 0;
	m_TimeStart = 0.0f;
	m_DeltaTime = 0.0f;
	m_TimePrevious = 0.0f;
	m_TimeLastFrame = 0.0f;
	m_Frames = 0;
	m_TotalFrames = 0;
}

void Timer::Reset(void)
{
	LARGE_INTEGER ticks;

	m_TimePrevious = GetTime();
	m_TimeLastFrame = GetTime();
	m_Frames = 0;
	m_FPS = 0;
	m_TotalFrames = 0;

	QueryPerformanceCounter(&ticks);
	QueryPerformanceFrequency(&m_TickFrequency);

	m_TimeStart = (float)ticks.QuadPart / (float)m_TickFrequency.QuadPart;
}

void Timer::Update(void)
{
	float timeNow = GetTime();
	m_Frames++;
	m_TotalFrames++;

	if(timeNow - m_TimePrevious > 1.0f)
	{
		m_FPS = m_Frames / (int)(timeNow - m_TimePrevious);
		m_Frames = 0;
		m_TimePrevious = timeNow;
	}

	m_DeltaTime = (timeNow - m_TimeLastFrame);
	m_TimeLastFrame = timeNow;
}

float Timer::GetTime(void)
{
	LARGE_INTEGER ticks;
	float time;

	QueryPerformanceCounter(&ticks);

	time = (float)ticks.QuadPart / (float)m_TickFrequency.QuadPart;

	return (time - m_TimeStart);
}