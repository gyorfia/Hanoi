#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	float Mark();
	void ResetClock();
	float GetTimeSinceLastRefresh();
private:
	std::chrono::steady_clock::time_point last;
};