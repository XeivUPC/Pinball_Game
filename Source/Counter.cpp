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

	for (const auto multiValue : multipliers) {
		totalMultiplierValue *= multiValue.second;
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

void Counter::AddMultiplier(float multiplier, std::string id)
{
	if (multipliers.count(id) == 0)
		multipliers[id] = multiplier;
}

float Counter::GetMultiplier(std::string id)
{
	if (multipliers.count(id) == 0)
		return 0.0f;
	else {
		return multipliers[id];
	}
}

bool Counter::RemoveMultiplier(float multiplier, std::string id)
{
	if (multipliers.count(id) != 0)
		multipliers.erase(id);
	return false;
}

bool Counter::EditMultiplier(float multiplier, float newMultiplier, std::string id)
{
	if (multipliers.count(id) != 0)
	{
		multipliers[id] = newMultiplier;
	}

	return false;
}


