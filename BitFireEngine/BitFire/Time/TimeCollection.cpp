#include "TimeCollection.h"

std::chrono::steady_clock::time_point TimeCollection::_lastTimeStamp = std::chrono::high_resolution_clock::now();

double TimeCollection::ActiveTime = 0;
float TimeCollection::DeltaTime = 0;