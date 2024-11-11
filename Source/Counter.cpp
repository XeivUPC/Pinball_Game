#include "Counter.h"

Counter::Counter(long long int data)
{
	_data = data;
}

Counter::~Counter()
{
}

long long int Counter::operator()() const
{
	return _data;
}

void Counter::Add(long long int amount, float multiplier)
{
	_data += (long long int)(amount * multiplier);
}

void Counter::Take(long long int amount, float multiplier)
{
	amount -= (long long int)(amount * multiplier);
}

void Counter::Set(long long int amount)
{
	_data = amount;
}
