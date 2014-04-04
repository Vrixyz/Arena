#include "Utils.h"


Utils::Utils(void)
{
}


Utils::~Utils(void)
{
}


int Utils::round(double f)
{
	return (f > 0.0) ? (f + 0.5) : (f - 0.5);
}