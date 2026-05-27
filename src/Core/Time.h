#pragma once
#include <chrono>
#include <thread>

class Time {
public:
	Time();
	Time(float fps);
	// Run timer without specific frame rate
	void run();
	// Run timer with specific frame rate. 
	// Fps at the beginning is set to 60 fps.
	void runAtFps();

	// The interval in seconds from the last frame to the current one without waiting for specific frame rate (Read Only).
	float usedTime;
	// The interval in seconds from the last frame to the current one (Read Only).
	float deltaTime;

private:
	std::chrono::steady_clock::time_point t1;
	std::chrono::steady_clock::time_point t2;
	std::chrono::steady_clock::time_point t3;
	std::chrono::duration<double> target;
	std::chrono::duration<double> sleepTime;
	std::chrono::duration<double> frameTime;
	std::chrono::duration<double> sleepAdjust;


};