#include "Time.h"

void Time::Reset() noexcept
{
	startTime = std::chrono::system_clock::now();
}

float Time::DeltaTime() const noexcept
{
	return deltaTime.count();
}

void Time::TimeScale(float t) noexcept
{
	timeScale = t;
}

float Time::GetTimeScale() const noexcept
{
	return timeScale;
}

void Time::Tick()
{
	deltaTime = std::chrono::system_clock::now() - startTime;
}

Time::Time()
{
	Reset();
	timeScale = 1.0f;
	deltaTime = std::chrono::duration<float>(0.0f);
}
