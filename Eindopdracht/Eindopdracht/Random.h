#pragma once
#include <random>

using namespace std;

class Random
{
public:
	static Random* Instance();
	static void ResetInstance()
	{
		delete m_instance; // REM : it works even if the pointer is NULL (does nothing then)
		m_instance = NULL; // so GetInstance will still work.
	}
	default_random_engine generator;
	~Random();
private:
	static Random* m_instance;

	Random();
};

