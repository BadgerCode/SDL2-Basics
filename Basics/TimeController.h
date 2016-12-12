#pragma once
#include <ctime>

enum class TimeOfDay
{
	Night,
	Dawn,
	Daytime,
	Dusk
};

class TimeController
{
public:
	TimeController();
	~TimeController();

	void Update();
	TimeOfDay GetTimeOfDay() const;
	double GetPercentageOfDuskCompleted() const;
	double GetPercentageOfDawnCompleted() const;

	static const int SecondsPerNight = 10;
	static const int SecondsPerDawn = 2;
	static const int SecondsPerDaylight = 10;
	static const int SecondsPerDusk = 2;
	static const int SecondsPerDay = SecondsPerNight + SecondsPerDawn + SecondsPerDaylight + SecondsPerDusk;

	static const int DawnStartTime = SecondsPerNight / 2;
	static const int DawnEndTime = DawnStartTime + SecondsPerDawn;

	static const int DuskStartTime = SecondsPerNight / 2 + SecondsPerDawn + SecondsPerDaylight;
	static const int DuskEndTime = DuskStartTime + SecondsPerDusk;

private: 
	clock_t _startOfDay;
	double _secondsSinceDayStart;
	TimeOfDay _timeOfDay;

	TimeOfDay GetCurrentTimeOfDay() const;
};

