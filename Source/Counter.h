#pragma once
class Counter
{
private:
	long long int _data = 0LL;
public:
    Counter(long long int data = 0);
    ~Counter();
    long long int operator()() const;
    void Add(long long int amount, float multiplier = 1);
    void Take(long long int amount, float multiplier = 1);
    void Set(long long int amount);
};