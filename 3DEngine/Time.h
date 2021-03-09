#ifndef TIME_H
#define TIME_H

#include <chrono>

class Time
{
private:
	std::chrono::system_clock::time_point startTime;
	std::chrono::duration<float> deltaTime;

	float timeScale;

public:
	void Reset() noexcept;
	float DeltaTime() const noexcept;
	void TimeScale(float t = 1.0f) noexcept;
	float GetTimeScale() const noexcept;
	void Tick();
	Time();
};


#endif