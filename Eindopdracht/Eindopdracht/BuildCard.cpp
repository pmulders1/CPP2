#include "BuildCard.h"

using namespace std;

BuildCard::BuildCard(string name, int points, CharacterType type) : BasicCard(name, type), points(points)
{
}


BuildCard::~BuildCard()
{
}
