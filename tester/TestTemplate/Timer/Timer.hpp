#ifndef TIMER_HPP
#define TIMER_HPP
#include <ctime>
#include <sys/time.h>
#include <map>
#include <stack>

class Timer
{

public:
	typedef struct timeval time_type;
private:
	time_type		_start;
	time_type		_stop;
	double			_duration;

public:
	Timer();
	Timer(const Timer &);
	Timer &operator=(const Timer &);
	~Timer();

	void	start(void);
	void	stop(void);
	void	diff(void);
	void	diff(const time_type& entry1, const time_type &entry2);
	

	time_type	get_start() const;
	time_type	get_stop() const;
	double		get_duration() const;
};

#endif