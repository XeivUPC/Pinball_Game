#pragma once
class Counter
{
private:
	float _data;
public:
    Counter(float data = 0);
    ~Counter();
    float operator()() const;
    void Add(float amount, float multiplier = 1);
    void Take(float amount, float multiplier = 1);
    void Set(float amount);
};