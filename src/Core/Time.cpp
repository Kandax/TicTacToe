#include "Time.h"


Time::Time()
	: frameTime(0.0)
	, sleepAdjust(0.0)
	, target(1.0 / 60.0)
	, t1(std::chrono::steady_clock::now())
	, usedTime(0.f)
	, deltaTime(0.f)
{

}

Time::Time(float fps)
	: frameTime(0.0)
	, sleepAdjust(0.0)
	, target(1.0 / fps)
	, t1(std::chrono::steady_clock::now())
	, usedTime(0.f)
	, deltaTime(0.f)
{

}


void Time::run() {
	t2 = std::chrono::steady_clock::now();
	std::chrono::duration<double> timeUsed = t2 - t1;
	deltaTime = std::chrono::duration<float>(timeUsed).count();
	usedTime = deltaTime;
	t1 = std::chrono::steady_clock::now();
}

void Time::runAtFps()
{
	t2 = std::chrono::steady_clock::now();

	std::chrono::duration<double> timeUsed = t2 - t1;
	usedTime = std::chrono::duration<float>(timeUsed).count();
	sleepTime = target - timeUsed + sleepAdjust;

	if (sleepTime > std::chrono::duration<double>(0))
	{
		std::this_thread::sleep_for(sleepTime);
	}

	t3 = std::chrono::steady_clock::now();
	frameTime = t3 - t1;
	deltaTime = std::chrono::duration<float>(frameTime).count();
	sleepAdjust = 0.9 * sleepAdjust + 0.1 * (target - frameTime);
	///////////////////
	t1 = std::chrono::steady_clock::now();
}