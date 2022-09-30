#include "Timer.hpp"
#include <iostream>
Timer::Timer() {}

Timer::Timer(const Timer& origin) {

	this->_start = origin.get_start();
	this->_stop = origin.get_stop();
}

Timer& Timer::operator=(const Timer &origin)
{
	if (this == &origin)
		return (*this);
	this->_start = origin.get_start();
	this->_stop = origin.get_stop();
	return (*this);
}

Timer::~Timer() {}

Timer::time_type Timer::get_start() const {
	return _start;
}

Timer::time_type Timer::get_stop() const {
	return _stop;
}

double Timer::get_duration() const {
	return this->_duration;
}

void Timer::start(void)
{
	gettimeofday(&_start, NULL);
	//std::cout << _start.tv_sec * 1000000  + _start.tv_usec << std::endl;
}

void Timer::stop(void)
{
	gettimeofday(&_stop, NULL);
	//std::cout << _stop.tv_sec * 1000000  + _stop.tv_usec << std::endl;
	this->diff();
}

void Timer::diff(void) {
	
	double x_ms;
	double y_ms;

	x_ms = (double)_start.tv_sec*1000000 + (double)_start.tv_usec;
    y_ms = (double)_stop.tv_sec*1000000 + (double)_stop.tv_usec;
	this->_duration = y_ms - x_ms;
}

void Timer::diff(const time_type& entry1, const time_type &entry2) {
	
	double x_ms;
	double y_ms;

	x_ms = (double)entry1.tv_sec*1000000 + (double)entry1.tv_usec;
    y_ms = (double)entry2.tv_sec*1000000 + (double)entry2.tv_usec;
	this->_duration = y_ms - x_ms;
}

