#include "TimeController.h"
#include <cstdio>


TimeController::TimeController()
{
	_startOfDay = clock() - (SecondsPerNight / 2) * CLOCKS_PER_SEC;
	_secondsSinceDayStart = 0;
	_timeOfDay = GetCurrentTimeOfDay();
}


TimeController::~TimeController()
{
}

void TimeController::Update()
{
	_secondsSinceDayStart = (static_cast<double>(clock()) - _startOfDay) / CLOCKS_PER_SEC;
	if (_secondsSinceDayStart >= SecondsPerDay)
	{
		_startOfDay = clock();
		_secondsSinceDayStart = 0;
	}

	_timeOfDay = GetCurrentTimeOfDay();
}

TimeOfDay TimeController::GetTimeOfDay() const
{
	return _timeOfDay;
}

double TimeController::GetPercentageOfDuskCompleted() const
{
	if(_timeOfDay != TimeOfDay::Dusk)
	{
		return 0;
	}

	auto timeInDusk = _secondsSinceDayStart - DuskStartTime;
	return static_cast<double>(timeInDusk) / SecondsPerDusk;
}

double TimeController::GetPercentageOfDawnCompleted() const
{
	if (_timeOfDay != TimeOfDay::Dawn)
	{
		return 0;
	}

	auto timeInDawn = _secondsSinceDayStart - DawnStartTime;
	return static_cast<double>(timeInDawn) / SecondsPerDawn;
}

TimeOfDay TimeController::GetCurrentTimeOfDay() const
{
	auto isNighttime = _secondsSinceDayStart < (SecondsPerNight / 2) || _secondsSinceDayStart >= SecondsPerDay - (SecondsPerNight / 2);
	if (isNighttime)
	{
		return TimeOfDay::Night;
	}

	auto isDawn = _secondsSinceDayStart < (SecondsPerNight / 2) + SecondsPerDawn;
	if (isDawn)
	{
		return TimeOfDay::Dawn;
	}

	auto duskStartTime = SecondsPerDay - (SecondsPerNight / 2) - SecondsPerDusk;
	if (_secondsSinceDayStart >= duskStartTime)
	{
		return TimeOfDay::Dusk;
	}

	return TimeOfDay::Daytime;
}
