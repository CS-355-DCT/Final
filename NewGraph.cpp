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
	//poi is not in graph, return -1
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
void Graph::addPOI(const string inPOI)
{
	int inIndex = findPOIIndex(inPOI);
	if(inIndex == -1)
	{
		POI newPOI;
		newPOI.name = inPOI;
		points.push_back(newPOI);
	}
	else
		cout << "POI is already in the graph" << endl;
}


//TB
void Graph::addRoad(const string startPOI, const string roadName, const string linkedPOI, int length)
{
	int  linkedI = findPOIIndex(linkedPOI);
	int startI = findPOIIndex(startPOI);
	if(linkedI == -1)
	{
		addPOI(linkedPOI);
		//it will be the last index, so size - 1 :)
		linkedI = points.size() - 1;
	}

	if(startI == -1)
	{
		addPOI(startPOI);
		//same as before :D
		startI = points.size() - 1;
	}

	Road newRoad;
	newRoad.length = length;
	newRoad.name = roadName;

	if(startPOI == "Station")
		points[0].Roads.push_back(make_pair(&points[linkedI], newRoad));
	else
		points[startI].Roads.push_back(make_pair(&points[linkedI], newRoad));
	
}
//CM
void Graph::printShortestPath(const POI& finalDestination)
{
    const POI* curr = &finalDestination;
    cout << "Fastest Route to " << finalDestination.name << " is: ";

    
    bool isFirstNode = true;

    while (curr != nullptr)
    {
        if (!isFirstNode)
        {
            // Find the edge
            const Road& road = findRoad(*curr->lastNode, *curr);
            
            // Print the edge name
            cout << " (" << road.name << ", " << road.length << "--> ";
        }

        cout << curr->name;

        isFirstNode = false;
        curr = curr->lastNode;
    }

    cout << endl;
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
		
                for (int i =0; i< visited.size(); i++)
                 {
                         cout << visited[i].name << ": ";
                         cout << visited[i].lengthFromStart << ": ";
                         if(visited[i].lastNode != nullptr)
                                 cout << visited[i].lastNode->name <<endl;
                         else
                                 cout<< "nullptr" <<endl;
                 }

         //CM
         printShortestPath(points[destinationI]);	
	
	

		
	}	
	
}

// DC
void Graph::printNodes(){

    for(const auto& i : points){
        cout << i.name << endl;
    }
}
