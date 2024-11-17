#pragma once
#include <unordered_map>
#include <string>
class Counter
{
private:
	long long int _data = 0LL;

    std::unordered_map<std::string,float> multipliers;

public:

    Counter(long long int data = 0);
    ~Counter();
    long long int operator()() const;
    void Add(long long int amount);
    void AddWithoutMultipliers(long long int amount);
    void Take(long long int amount);
    void Set(long long int amount);
    void AddMultiplier(float multiplier, std::string id);
    float GetMultiplier(std::string id);
    bool RemoveMultiplier(float multiplier, std::string id);
    bool EditMultiplier(float multiplier, float newMultiplier, std::string id);
    float GetMultipliersTotalValue();
};