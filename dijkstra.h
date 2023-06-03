#ifndef DIJSKTRA_H
#define DIJSKTRA_H

#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;



void printParentPath(int parent[], int i);
void printShortestPath(int src, int dist[], int parent[], int V);
int getNearest(int V, bool visited[], int dist[]);
void dijkstraAlgo(int src, int V);
string getCity(int i);


#endif
