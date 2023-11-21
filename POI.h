#ifndef POI_H
#define POI_H

#include <string>
#include "road.h"
#include <vector>


//TB
struct POI
{
	std::string name;
	std::vector<std::pair<POI*, Road>> Roads;
	double lengthFromStart;
	POI* lastNode;
};



#endif