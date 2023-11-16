#ifndef H_GRAPH
#define H_GRAPH

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct Node
{
	T ID;
	vector<pair <Node<T>, int> > edges;
};


template <typename T>
class Graph
{
	private:
		//the index for the array of vectors will be 
		Node<T>* nodes;
		int numNodes;
		//finds nodeIndex based on its ID, returns -1 if node DNE
		int findNodeIndex(T ID)
		{
			int returnValue = -1;
			for(int i = 0; i < numNodes; i++)
			{
				if(nodes[i].ID == ID)
				{
					returnValue = i;
					break;
				}
			}
			return returnValue;
		}
	
	
	public:
		/*Graph(int nNodes)
		{
			numNodes = nNodes;
			nodes =  new Node<T>[numNodes];
		}
		*/
		//values's size should be equal to nNodes!
		Graph(int nNodes, T values[])
		{
			numNodes = nNodes;
			nodes = new Node<T>[numNodes];
			for(int i = 0; i < numNodes; i++)
				nodes[i].ID = values[i];
		}
		
		void addEdge(T nodeToAddTo, T nodeToPointTo, int weight)
		{	
			//only add to this one since its directed :)
			nodes[findNodeIndex(nodeToAddTo)].edges.push_back(make_pair(nodes[findNodeIndex(nodeToPointTo)], weight));
		}
		
		//couldn't get this to work right.
		/*void printLinksMatrix() const
		{
			bool matrix[numNodes][numNodes];
			
			//initializes everything to false :)
			for(int i = 0; i < numNodes; i++)
			{
				for(int j = 0; j < numNodes; j++)
					matrix[i][j] = false;
			}
			
			for(int i = 0; i < numNodes; i++)
			{
				vector<pair <Node<T>, int> > tempVect(nodes[i].edges);
				for(int j = 0; j < tempVect.size(); j++)
				{
					matrix[i][findNodeIndex(tempVect.back().first.ID)] = true;
					tempVect.pop_back();
				}
			}
			
			cout << "  ";
			
			for(int i = 0; i < numNodes; i++)
			{
				cout << nodes[i].ID << " ";
			}
			cout << endl;
			
			for(int i = 0; i < numNodes; i++)
			{
				cout << nodes[i].ID << "[";
				for(int j = 0; j < numNodes; j++)
				{
					int val = matrix[i][j];
					cout << val << " ";
				}
				cout << "]" << endl;
			}
		}*/
		
		int allVisited(int visted[], int size)
		{
			for(int i = 0; i < size; i++)
			{
				if(visted[i] < 1)
					return false;
			}
			
			return true;
		}
		
		void findShortestPath(T nodeToFind)
		{
			const int INF = 10000;
			
			int visited[numNodes];
			int length[numNodes];
			Node<T>* lastNode[numNodes];
			
			for(int i = 0; i < numNodes; i++)
			{
				length[i] = INF;
				lastNode[i] = nullptr;
				visited[i] = false;
			}
			length[0] = 0;
			
			//look at nodes[0], go to it's neighbors
			vector<pair <Node<T>, int> > tempVect(nodes[0].edges);
			for(int i = 0; i < nodes[0].edges.size(); i++)
			{
				int q = findNodeIndex(tempVect.back().first.ID);
				length[q] = tempVect.back().second;
				lastNode[q] = &nodes[0];
				tempVect.pop_back();
			}
			visited[0] = 1;
			
			//int testTracker = 0;
			while(!(allVisited(visited, numNodes)))
			{
				for(int i = 0; i < numNodes; i++)
				{
					if(visited[i] == 1)
					{
						//cout << nodes[i].ID << endl;
						vector<pair <Node<T>, int> > tempVect1(nodes[i].edges);
						for(int j = 0; j < nodes[i].edges.size(); j++, tempVect1.pop_back())
						{
							//cout << "inside j loop" << endl;
							int index = findNodeIndex(tempVect1.back().first.ID);
							Node<T> currentNode = nodes[index];
							vector<pair <Node<T>, int> > tempVect2(currentNode.edges);
							for(int k = 0; k < currentNode.edges.size(); k++, tempVect2.pop_back())
							{
								int index2 = findNodeIndex(tempVect2.back().first.ID);
								int newLength = length[index] + tempVect2.back().second;
								
							//	cout << "inside k loop" << endl;
								
								if(length[index2] > newLength)
								{
									length[index2] = newLength;
									lastNode[index2] = &nodes[index]; 
								}
							}
							//cout << "exit k loop" << endl;
							++visited[index];
							//lastNode[index] = &nodes[i];
						}
					//	cout << "exit j loop" << endl;
					}
				}
				/*cout << "Test Tracker: " << testTracker++ << endl;
				for(int i = 0; i < numNodes; i++)
				{
					cout << visited[i] << "_";
				}
				cout << endl;*/
			}
			
			/*cout << "All distances :)" << endl;
			
			for(int i = 0; i < numNodes; i++)
				cout << nodes[i].ID << ": " << length[i] << endl;*/
			
		
			vector<T> path;
			int itemIndex = findNodeIndex(nodeToFind);
			path.push_back(nodeToFind);
			int currentIndex = itemIndex;
			while(lastNode[currentIndex] != nullptr)
			{
			//	cout << "next Node: " << lastNode[currentIndex]->ID << ":"; 
			//	cout << "Length: " << length[currentIndex] << endl;
				path.push_back(lastNode[currentIndex]->ID);
				currentIndex = findNodeIndex(lastNode[currentIndex]->ID);
			}
			
			cout << "The shortest path is ";
			
			vector<T> newVect(path);
			cout << newVect.back();
			newVect.pop_back();
			for(int i = 1; i < path.size(); i++, newVect.pop_back())
				cout << "->" << newVect.back();
				
			cout << endl;
		}
		
		
};



#endif