#include "Random.h"
#include <ctime>
#include <random>
using namespace std;

Random* Random::m_instance = nullptr;

Random* Random::Instance()
{
	if (m_instance == nullptr) m_instance = new Random();
	return m_instance;
};

Random::Random()
{
	generator.seed(time(0));
}


Random::~Random()
{
}