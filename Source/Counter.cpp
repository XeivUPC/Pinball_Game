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

void Counter::Add(long long int amount)
{
	float totalMultiplierValue = 1;

	for (size_t i = 0; i < multipliers.size(); i++)
	{
		totalMultiplierValue *= multipliers[i];
	}

	_data += (long long int)(amount * totalMultiplierValue);
}

void Counter::AddWithoutMultipliers(long long int amount)
{
	_data += (amount);
}

void Counter::Take(long long int amount)
{
	amount -= (long long int)(amount);
}

void Counter::Set(long long int amount)
{
	_data = amount;
}

void Counter::AddMultiplier(float multiplier)
{
	multipliers.emplace_back(multiplier);
}

bool Counter::RemoveMultiplier(float multiplier)
{
	for (size_t i = 0; i < multipliers.size(); i++)
	{
		if (multipliers[i] == multiplier) {
			multipliers.erase(multipliers.begin() + i);
			return true;
		}
	} 
	return false;
}

bool Counter::EditMultiplier(float multiplier, float newMultiplier)
{
	for (size_t i = 0; i < multipliers.size(); i++)
	{
		if (multipliers[i] == multiplier) {
			multipliers[i] = newMultiplier;
			return true;
		}
	}
	return false;
}


