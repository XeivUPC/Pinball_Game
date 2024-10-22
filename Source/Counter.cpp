#include "Counter.h"

Counter::Counter(float data)
{
	_data = data;
}

Counter::~Counter()
{
}

float Counter::operator()() const
{
	return _data;
}

void Counter::Add(float amount, float multiplier)
{
	_data += amount * multiplier;
}

void Counter::Take(float amount, float multiplier)
{
	amount -= amount * multiplier;
}

void Counter::Set(float amount)
{
	_data = amount;
}
