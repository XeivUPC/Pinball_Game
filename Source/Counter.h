#pragma once
#include <vector>
class Counter
{
private:
	long long int _data = 0LL;
    float multiplier = 1;
    std::vector<float> multipliers;

public:
    Counter(long long int data = 0);
    ~Counter();
    long long int operator()() const;
    void Add(long long int amount);
    void AddWithoutMultipliers(long long int amount);
    void Take(long long int amount);
    void Set(long long int amount);
    void AddMultiplier(float multiplier);
    bool RemoveMultiplier(float multiplier);
    bool EditMultiplier(float multiplier, float newMultiplier);
};