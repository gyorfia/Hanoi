#include "Timer.h"

using namespace std::chrono;

Timer::Timer()
{
	last = steady_clock::now();
}

float Timer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

void Timer::ResetClock()
{
	last = steady_clock::now();
}

float Timer::GetTimeSinceLastRefresh()
{
	const duration<float> frameTime = steady_clock::now() - last;
	return frameTime.count();
}