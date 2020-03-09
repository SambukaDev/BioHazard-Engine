#pragma once
#include <SDL.h>
#include "Singleton.h"

class TimeManager : public Uncopyable{

private:

	TimeManager();
	TimeManager(const TimeManager&);

	friend Singleton < TimeManager >;

	TimeManager& operator=(const TimeManager&);

	//Private function to reset alll variables
	void reset();

	//Private member variables
	bool m_isTimerRunning;
	bool m_isTimerPaused;

	double m_startTime;
	double m_lastTime;

	double m_elapsedTimeMilliseconds;
	double m_elapsedTimeSeconds;
	double m_elapsedTimeMinutes;
	double m_elapsedTimeHours;

	double m_totalTimeMilliseconds;
	double m_totalTimeSeconds;
	double m_totalTimeMinutes;
	double m_totalTimeHours;

public:

	//Public controlls
	void start();
	void pause();
	void resume();
	void stop();
	void update();
	void output();

	//Private value getters
	double GetElapsedTimeMilliseconds()  const;
	double GetElapsedTimeSeconds()       const;
	double GetElapsedTimeMinutes()       const;
	double GetElapsedTimeHours()         const;

	double GetTotalTimeMilliseconds()    const;
	double GetTotalTimeSeconds()         const;
	double GetTotalTimeMinutes()         const;
	double GetTotalTimeHours()           const;

};

typedef Singleton<TimeManager> TheTimeManager;