#include "NewGraph.h"


//TB
Graph::Graph()
{
	Station.name = "Station";
	points.push_front(Station);
}

int Graph::findPOIIndex(string poiName)
{
	for(int i = 0; i < points.size(); i++)
	{
		if(points[i].name == poiName)
			return i;
	}
	cout << "POI is not in graph" << endl;
	return -1;
}

//TB
void Graph::findDistanceFromStart(vector<pair<POI*, Road>>& roads, POI point)
{
	for(auto & i : roads)
	{
		double testLength = point.lengthFromStart + i.second.length;
		POI currentNode = *(i.first);
		if(testLength < currentNode.lengthFromStart)
		{
			i.first->lengthFromStart = testLength;
			i.first->lastNode = &point;
		}
	}
}


//TB
void Graph::addRoad(const string startPOI, const string roadName, const string linkedPOI, int length)
{
	int  linkedI = findPOIIndex(linkedPOI);
	Road newRoad;
	newRoad.length = length;
	newRoad.name = roadName;
	if(linkedI >= 0)
	{
		if(startPOI == "Station")
			points[0].Roads.push_back(make_pair(&points[linkedI], newRoad));
		else
		{
			int startI = findPOIIndex(startPOI);
			if(startI >= 0)
				points[startI].Roads.push_back(make_pair(&points[linkedI], newRoad));
		}
	}
}


//TB
void Graph::getShortestPath(const string destination)
{
	int destinationI = findPOIIndex(destination);
	if(destinationI < 0)
		cout << "Invalid Destination" << endl;
	else
	{
		const double INF = 100000;
		
		points[0].lengthFromStart = 0;
		points[0].lastNode = nullptr;
		for(int i = 1; i < points.size(); i++)
		{
			points[i].lengthFromStart = INF;
			points[i].lastNode = nullptr;
		}
		
		deque<POI> unvisited(points);
		deque<POI> visited;
		
		do
		{
			
			findDistanceFromStart(unvisited.front().Roads, unvisited.front());
			visited.push_back(unvisited.front());
			unvisited.pop_front();
	
		} while(!(unvisited.empty()));
		
		//print test data
		for(int i = 0; i < visited.size(); i++)
		{
			cout << visited[i].name << ":";
			cout << visited[i].lengthFromStart << ":";
			cout << visited[i].lastNode->name << endl;
		}
		
		//almost done
		
		
	}	
	
}


