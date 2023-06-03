#include "dijkstra.h"

//returns name of city based on input integer
string getCity(int i){
    switch(i){
          case 1: return "Riverside";
          case 2: return "Moreno";
          case 3: return "Hemet";
          case 4: return "Perris";
          default: return "N/A";
    }
}

void printParentPath(int parent[], int i) {
  if (parent[i] == -1) {
    return;
  }
  printParentPath(parent, parent[i]);
  cout << getCity(i + 1) << " ";
}


//print shortest path from source node to all other nodes
void printShortestPath(int src, int dist[], int parent[], int V){
    cout << "Adjacent City\t\t\tDistance\t\tPath" << endl;
    for (int i = 0; i < V; i++) {
      if(i != src){
        cout << setw(20) << left << getCity(i + 1) << "\t\t" << dist[i] << " mi\t\t\t"
          << getCity(src + 1) << "->";
      }

      printParentPath(parent, i);

      if(i != src)
        cout << endl;
      }
}

//calculates the nearest unvisited node to the source node and sets it as the minimum node and minimum distance
//returns that node represented as an integer

int getNearest(int V, bool visited[], int dist[]){
  int minValue = 9999;
  int minNode = 0;
  for(int i = 0; i < V; i++){
    if(!visited[i] && dist[i] <= minValue){     
      minValue = dist[i];                     
      minNode = i;                            
    }
  }
  return minNode;              
}


void dijkstraAlgo(int src, int V){
  int dist[4];                                    //integer array to store distances between nodes
  bool visited[4];                                //bool array to mark nodes as visited/unvisited 
  int costGraph[4][4] = {{0, 16, 33, 24}, 
                         {16, 0, 26, 18}, 
                         {33, 26, 0, 30},
                         {24, 18, 30, 0}};        //weighted matrix stored as a double array
  int parent[4];                                  //parent array to store path from source node to all other nodes
  
  //initialize all unknown nodes with "infinite" distance except for source node
  for (int i = 0; i < V; i++){
    parent[i] = -1;
    dist[i] = 9999;
    visited[i] = false;
  } 
  dist[src] = 0;                                  //set distance of source node from itself as zero

  for(int i = 0; i < V - 1; i++){
    int nearest = getNearest(V, visited, dist);     
    visited[nearest] = true;                      //sets nearest node as visited

    for(int j = 0; j < V; j++){       
      int curr_dist = dist[nearest] + costGraph[nearest][j];                
      if(!visited[j] && costGraph[nearest][j] && dist[j] > curr_dist){      //if current distance being evaluated is less than distance saved at index j
        dist[j] = curr_dist;                                                //update distance to new, shortest distance
        parent[j] = nearest;                                                //save nearest/current node to parent array
      }
    }
  } 

  printShortestPath(src, dist, parent, V);
}