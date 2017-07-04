#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <string>
#include <vector>
#include <queue>


using std::vector;
using std::string;
using std::map;
using std::pair;
using std::queue;

const int STATUS_IN_SOLUTION = -1;
const int STATUS_DELETED = -2;
const int STATUS_NONE = 0;
const int STATUS_IN_SAFE = 1;

class Graph {
   private:
    int N, M;  // number of vertices and edges
    int deleted;
    bool changeInU;
    vector<vector<int>> neighbours;
    // Information whether the edge is a double edge
    vector<vector<bool>> neighDouble;

    // Keeps the position of my vertex at the neighbour list
    // For faster deleting neighbours
    vector<vector<int>> posAtNeigh;

    // State of the given vertex
    vector<int> status;

    // String representing vertex i in original input
    // vector<string> names;

    // set<int> X, U;

    // X - Vertices in solution
    vector<int> X;

    // U - Already safe vertices
    vector<int> U;
 
    // Vertices with selfloops - have to be deleted
    vector<int> selfLoops;

    queue<int> deg2ToReduce;

    vector<int> vis;
    vector<int> ccNr;

   public:
    Graph();
    // void read_input(vector<string>& names);
    void buildGraph(int N_, int M_, vector<pair<int, int> >& edges);
    void printGraph();
    // void printNames(vector<int> v);
    // string getName(int v);
    // vector<string> list_of_names(vector<int> v);
    int getN();
    vector<vector<int> > getNeighbours();
    vector<vector<bool>> getDoubles();


    // void add_vertex(int v);
    void pureDeleteVertex(int v);
    void deleteVertex(int v);
    void deleteNeighbour(int v, int which);

 //   int add_vertex(string name, map<string, int>& namesMap, vector<string>& names);
    int degree(int v);
    bool isEmpty();

    // Returns pair <v_num, degree>, where v is not deleted nor safe vertex with max deg
    pair<int, int> getMaxDegV();

    bool connected(int v, int to);
    bool hasSelfLoop(int v);

    bool isDoubleEdge(int v, int to);
    bool hasDoubleToU(int v);

    bool deleteSelfLoops();
    //Deletes Vertices with deg <= 1
    bool deleteDeg1Vertices();
    void deleteDeg1Chain(int v);

    int doubleNr(int v);

    int findNrInNeigh(int where, int me);
    void mergeDeg2Neigh(int cur);

    // Reduce deg2 Vertices from the queue
    bool reduceDeg2Queue();


    void putInSolution(int v);
    void putInSafe(int v);

    vector<int> getX();
    vector<int> getU();

    int getXSize();
    int getUSize();

    bool isNone(int v);
    bool isInU(int v);
    bool isInX(int v);
    bool checkStatus(int v, int status);

    int getStatus(int v);
    void setStatus(int v, int st);

    bool checkCycles();
    bool dfsCycles(int v, int from);
// Looks only for vertices in None and their neighbours in U
    bool checkSameCCNeighbours();
    void recalcComponentsInU();
    void dfsComp(int v, int nr);

};

#endif  // GRAPH_H