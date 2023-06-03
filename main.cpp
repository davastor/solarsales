#include <iostream>
#include "dijkstra.h"
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <map>
#include <list>

using namespace std;
// Easy Select to find code
// Choice1
// Choice2
// Choice3
// Choice4


// 1 Riverside to 3 Hemet 33
// 1 Riverside to 2 Moreno 16
// 1 Riverside to 4 Perris 24
// 3 Hemet to 4 Perris 30
// 3 Hemet to 2 Moreno 26
// 4 Perris to 2 Moreno 18

struct Node {
    int val, cost;
    Node* next;
};


struct Edge {
    int src, dest, weight;
};

//Main workhorse behind code, contains varibles and actually creates the "graph"

class Graph{
 // Function to make Adjacency List
  Node* getAdjListNode(int value, int weight, Node* head){
    Node* newNode = new Node;
    newNode->val = value;   
    newNode->cost = weight;  
    newNode->next = head;   
    return newNode;    
  }

  int N;  //nodes in the graph

  public:
  Node **head;

  Graph(Edge edges[], int n, int N){
    head = new Node*[N]();
    this->N = N;

    for (int i = 0; i < N; i++)
      head[i] = nullptr;

    for (unsigned i = 0; i < n; i++){
      int src = edges[i].src;  
      int dest = edges[i].dest; 
      int weight = edges[i].weight;
      Node* newNode = getAdjListNode(dest, weight, head[src]);  

      head[src] = newNode;   
                
      // Makes the graph undirected
      newNode = getAdjListNode(src, weight, head[dest]);
      head[dest] = newNode;
    }
  }
 ~Graph() {
   for (int i = 0; i < N; i++)
     delete[] head[i];
     delete[] head;
 }
};


// Choice 1
void printList(Graph& graph, int src){
  //create vector to store adjacent locations as integer
  vector<int> locations;

  //set ptr to node at location src, loop through all nodes 
  Node* ptr = graph.head[src];      
  while(ptr != nullptr){
    locations.push_back(ptr->val); 
    ptr = ptr->next;
  }

  //map of a vector of pairs to store the adjacencies between nodes
  //    
  map<int, vector<pair<int, int>>> adj;
    
  //loop through every node in the graph and assign their adjancecies and weight to a pair object
  //add each pair object to the vector
  //map a vector for each head/src node
  for(int i = 0; i <= 4; i++){
    ptr = graph.head[i];
    pair<int, int> p;
    while (ptr != nullptr){
      p.first = ptr->val;
      p.second = ptr->cost;
      adj[i].push_back(p);
      ptr = ptr->next;
    }      
  }
  //sort vector from lowest to highest number as next_permutation function finds the next highest permutation
  sort(locations.begin(), locations.end());

  do{      
    int totalDist = 0;                            //integer to store total distance traveled in each route
    int curr = src;                               //integer for traversing nodes, initialized to src to find paths starting from src node
    for(int i = 0; i < locations.size(); i++){    //loop through locations vector to print out each city
      cout << getCity(locations[i]);      
      for(int j = 0; j < 3; j++){
        if(adj[curr][j].first == locations[i]){                   //evaluates mapped nodes to the current location 
          cout << " (" << adj[curr][j].second << " mi)";          //if it matches, print out the weight (distance) of the edge
          totalDist += adj[curr][j].second;                       //add distance to totalDist
          curr = locations[i];                                    //move current to new location 
        }
      }
            
      if(i < locations.size()- 1)                                 
        cout << " --> ";
    }

    //adds distance from last node back to first node for round-trip distance
    for(int k = 0; k < 3; k++){
      if(src == adj[curr][k].first)
        totalDist += adj[curr][k].second;     
    }
    cout << "\tTotal Distance (Round-trip): " << totalDist << " mi" << endl;
  }while(next_permutation(locations.begin(), locations.end()));                 //find next permutation of locations vector, and continue looping to print out each permutation
}

//Loop through each Node ptr and print adjcent node, and distance between them
void printList(Node* ptr, int i){
  while (ptr != nullptr){
    cout << "(" << getCity(i) << ", " << getCity(ptr->val)
        << ", " << ptr->cost << " Miles) \t";

    ptr = ptr->next;
  }
  cout << endl;
}


int main(){
  int answer,
       choice;

  Edge edges[] ={
        // (x, y, w) 1st Vertex, 2nd Vertex, Weight
        { 1, 2, 16 }, { 1, 3, 33 }, { 1, 4, 24 }, { 2, 3, 26 },
        { 3, 4, 30 }, { 4, 2, 18 }
    };

  // Number of vertices
  int N = 5;

  //calculate number of edges 
  int n = sizeof(edges)/sizeof(edges[0]);

  Graph graph(edges, n, N);

  cout << "Welcome to the E-Z Route Program, please select an option below!" << endl;
  cout << " 1. Trip Planner (Trip Representation)" << endl;
  cout << " 2. Roads (Adjacencies)" << endl;
  cout << " 3. Map (Matrix)" << endl;
  cin >> choice;

  if (choice <=0 || choice >=5){
    cout << "The option you have chosen does not exist, please select another option 1-4." << endl;
    cin >> choice;
  }

  //Prints out every permutation for travel, depending on the starting location
  if (choice == 1){
    cout << "Possible Routes: " << endl << "1.Riverside, 2.Moreno, 3.Hemet, 4.Perris" << endl;
    
    for (int i = 1; i < N; i++){
        cout << "\nIf starting from " << getCity(i) << ", you can go: " << endl;
        cout << "----------------------------------------------------" << endl;
        printList(graph, i);
    }
    cin >> choice;
  }


  // Calculates adjacencies based on starting location
  if (choice == 2){
    string city;
    cout << "What is your starting location?" << endl;
  
    cout << "1.Riverside, 2.Moreno, 3.Hemet, 4.Perris" << endl;
 
  //do-while loop to validate user input for starting location
  do{
      cin >> city;
      transform(city.begin(), city.end(), city.begin(), ::toupper);   //transforms string input to all upper case for input validation
      if(city == "RIVERSIDE" || city == "1")
        dijkstraAlgo(0, 4);
      else if(city == "MORENO" || city == "2")
        dijkstraAlgo(1, 4); 
      else if(city == "HEMET" || city == "3")
        dijkstraAlgo(2, 4);
      else if(city == "PERRIS" || city == "4")
        dijkstraAlgo(3, 4);
      else{
        city = "INVALID";
        cout << "Please enter in a valid city." << endl;
      }
    }while(city == "INVALID");
    

    cin >> choice;
  }


  //Loop through each Node and pass them to printList function
  if (choice == 3){
    for (int i = 1; i < N; i++){
        printList(graph.head[i], i);
    }
  }
  

    return 0;
  }