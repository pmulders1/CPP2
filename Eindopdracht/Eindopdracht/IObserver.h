#pragma once
class IObserver
{
public:
	IObserver();
	virtual void Update() = 0;
	virtual ~IObserver() = 0;
};

