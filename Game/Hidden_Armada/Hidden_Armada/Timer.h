#ifndef _TIMER_H_
#define _TIMER_H_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <time.h>

class Timer
{
private:
	// Data members
	int				m_FPS;
	float			m_TimeStart;
	float			m_DeltaTime;
	float			m_TimePrevious;
	float			m_TimeLastFrame;
	int				m_Frames;
	int				m_TotalFrames;
	LARGE_INTEGER	m_TickFrequency;

public:
	Timer(void);
	~Timer(void) {}

	void Init() { Reset(); }
	void Reset(void);
	void Update(void);
	float GetTime(void);
	float GetDeltaTime(void) const { return m_DeltaTime; }
	int GetFPS(void) const { return m_FPS; }
	int GetTotalFrames(void) const { return m_TotalFrames; }
};

#endif