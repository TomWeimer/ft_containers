#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include "../Timer.hpp"

int main()
{
	Timer chronometer;
	chronometer.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	chronometer.stop();
	std::cout << "         " << std::fixed << std::setprecision(0) << chronometer.get_duration() << " ms"<< std::endl;
}