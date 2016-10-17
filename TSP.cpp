/* Avalg Project 1. By Alexander Janson & Andy Yousef */

#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <math.h>  


using namespace std;
//Reused parts of ADK-lab3


//This one is important!
class Node {
private:
  float _xCord;
  float _yCord;
  vector<int> _neighbor;
public:
  Node(float xCord, float yCord,int V)
    : _xCord(xCord), _yCord(yCord), _neighbor(V) {}
  float xCord() const { return _xCord; }
  float yCord() const { return _yCord; }
  vector<int> neighbors() const {return _neighbor;} 
  void addValue(int place,int cost){_neighbor[place]=cost;}
  
};

//Not so imporant. Class for edge 
//(have to use this or something similar to be able to store solution to be used by optimizer)
class Edge {
private:
  Node& _start, _end;
public:
  Edge( Node& start, Node& end)
    : _start(start), _end(end) {}
  Node start() const { return _start; }
  Node end() const { return _end; }

};

//Calculates the euclidian distance between two nodes
int euclidian(const Node& node1,const Node& node2){
	float distance;
	
	distance = pow(node1.xCord() - node2.xCord(),2) + pow(node1.yCord() - node2.yCord(),2);
	distance = sqrt(distance);
	return round(distance);
}

//This is the global variable, a bit messy but I don't feel like doing header files right now. Should actually be at start
std::vector<Node> nodes; 
vector<Edge> edges;

//Reads problem and creates a graph
void readProblem() {
  int V;
  float s,e;
  bool fileread = false; //set to false if you want to send it in to kattis
  
  if (fileread){
	  ifstream input_data;
	  input_data.open("data.in", ifstream::in); //That is, you have a file in the same folder named "test.in" containing the info

	  //read data from file and output it.
	  input_data >> V;
	  cout << V << endl;
	  
	  for (int i = 0; i < V; ++i) {
		 input_data >> s;
		 input_data >> e;
		 //add node to vector
		 nodes.push_back(Node(s, e,V));

		 
		//std::cout << s << " " << e << std::endl;
	  }
	  
  }
  
  //Used for taking input in kattis
  else{
	  std::cin >> V;
	  for (int i = 0; i < V; ++i) {
		 std::cin >> s;
		 std::cin >> e;
		 nodes.push_back(Node(s, e,V));
		
	  }
  }

    
}

void nearest_neighbor(){
	//create vector to hold all visited nodes
	vector<bool> visited(nodes.size(),false);
	//cout << visited.size() << endl;
	int viscount = 0;
	int max = nodes.size();
	int startNode;
	int currentNode;
	//start at node1
	cout << 0 << endl;
	//mark as visited
	visited[0]=true;
	currentNode = 0;
	startNode = 0; //this will not be needed for printing in kattis, but might provide insight, should also be added as edge
	++viscount;
	
	int minValue = 100000000;
	int minNode = -1;
	int cost = 100000000;
	while (viscount < max){ //will happen n times
		//calculate the next closest node
		minValue = 100000000;
		minNode = -1;
		cost = 100000000;
		for (int i = 0; i<max;++i){
			cost = euclidian(nodes.at(i),nodes.at(currentNode));
			nodes.at(currentNode).addValue(i,cost);
			if (i == currentNode){
				//add inf value to self. Overwrites V times
				nodes.at(i).addValue(i,100000000);
			}
			else if (!visited.at(i)){
				if (cost < minValue){
					minNode=i;
					minValue = cost;
				}
				
			}
		}
		edges.push_back(Edge(nodes.at(currentNode),nodes.at(minNode)));
		currentNode = minNode;
		visited[currentNode]=true;
		//cout << currentNode << endl;
		++viscount;
	}
	//Assumes we picked the first node to start at
	edges.push_back(Edge(nodes.at(currentNode),nodes.at(startNode)));
	//calculate values for the last node
	for (int i=0 ; i<max;++i){
		cost = euclidian(nodes.at(i),nodes.at(currentNode));
		nodes.at(currentNode).addValue(i,cost);
		if (i == currentNode){
			//add inf value to self. Overwrites V times
			nodes.at(i).addValue(i,100000000);
		}
	}
	/*
	for (int i=0 ; i<max;++i){
		for (int j=0;j<max;++j){
			cout << nodes.at(i).neighbors().at(j) << " ";
		}
		cout << endl;
	} */
	
}

void opt2(){
	
}

int main() {
  readProblem();
  //Now do some algorithm to solve the problem... Write algorithm above because there's no header file atm.
  nearest_neighbor();
  
  return 0;
}
