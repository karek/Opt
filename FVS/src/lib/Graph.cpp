#include "Graph.h"

#include <cassert>
#include <set>
#include <iostream>
using namespace std;

Graph::Graph(): deleted(0), changeInU(true) {}

void Graph::buildGraph(int N_, int M_, vector<pair<int, int> >& edges) {
   // map<string, int> namesMap;
    vector<map<int, int> > neighMap;
    N = N_;
    M = M_;

    neighbours.resize(N);
    status.resize(N, STATUS_NONE);
    neighDouble.resize(N);
    neighMap.resize(N);
    posAtNeigh.resize(N);

    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i].first;
        int b = edges[i].second;
        if (a > b)
            swap(a, b);

        if (a == b)
            selfLoops.push_back(a);

        if (!neighMap[a].count(b)) {
            int pos = neighbours[a].size();
            posAtNeigh[b].push_back(pos);
            neighMap[a][b] = pos;
            neighbours[a].push_back(b);
            neighDouble[a].push_back(false);
            
            pos = neighbours[b].size();
            posAtNeigh[a].push_back(pos);
            neighMap[b][a] = pos;
            neighbours[b].push_back(a);
            neighDouble[b].push_back(false);
        }
        else {
            neighDouble[a][neighMap[a][b]] = true;
            neighDouble[b][neighMap[b][a]] = true;
        }
    }
}

//addVertex

void Graph::printGraph() {
    int cnt_n = 0, cnt_u = 0, cnt_d = 0, cnt_x = 0;
    for (int i = 0; i < N; i++) {
        cerr << i << " ";
        switch(getStatus(i)) {
            case STATUS_NONE: cerr << "N "; cnt_n++; break;
            case STATUS_IN_SOLUTION: cerr << "X "; cnt_x++; break;
            case STATUS_DELETED: cerr << "D "; cnt_d++; break;
            case STATUS_IN_SAFE: cerr << "U "; cnt_u++; break;
        }

        cerr << ": ";
        for (int j = 0; j < neighbours[i].size(); j++) {
            cerr << "(" << neighbours[i][j] << ", " << neighDouble[i][j] << ", " << posAtNeigh[i][j] << ") ";
        }
        cerr << "\n";
    }

    cerr << "Czy pusty: " << isEmpty() << " " << !checkCycles() << " ";
    cerr << "Num = (" << neighbours.size() << ", " << cnt_n + cnt_u + cnt_d + cnt_x << ") " <<
            "In N = " << cnt_n << " in X = (" << cnt_x   << ", " << X.size() << ") in D = (" << cnt_d <<
            ", " << deleted << ") in U = (" <<  cnt_u << ", " << U.size() << ")\n"; 

        for(int i=0; i< U.size() ;i++){
            cerr << U[i] << " ";
        }
        cerr << "=U\n";

        for(int i=0; i< X.size() ;i++){
            cerr << X[i] << " ";
        }
        cerr << "=X\n";
}

int Graph::getN() {
    return N;
}

vector<vector<int> > Graph::getNeighbours() {
    return neighbours;
}

vector<vector<bool>> Graph::getDoubles() {
    return neighDouble;
}

int Graph::degree(int v) {
    return neighbours[v].size();
}

//TODO: Take double edges under consideration
pair<int, int> Graph::getMaxDegV() {
    int deg = 0, num = -1;
    for (int i = 0; i < neighbours.size(); i++)
        if (deg < degree(i) && checkStatus(i, STATUS_NONE)) {
            deg = degree(i);
            num = i;
        }

    return make_pair(num, deg);
}

bool Graph::connected(int v, int to) {
    assert(v >= 0 && v < neighbours.size());
    for (int i = 0; i < neighbours[v].size(); i++)
        if (neighbours[v][i] == to)
            return true;

    return false;
}

bool Graph::hasSelfLoop(int v) {
    return connected(v, v);
}

bool Graph::deleteSelfLoops() {
    bool res = false;
    for(int i = 0; i < selfLoops.size(); i++) {
        int cur = selfLoops[i];
        if(isNone(cur)) {
            putInSolution(cur);
            res = true;
        }
    }

    selfLoops.clear();
    return res;
}


bool Graph::deleteDeg1Vertices() {
    bool res = false;
    for (int i = 0; i < neighbours.size(); i++)
        if (degree(i) <= 1 && isNone(i)) {
            // if (!isDoubleEdge(i, 0)) {
                deleteDeg1Chain(i);
                res = true;
            // }
            // else {

            // }
        }

    return res;
}

void Graph::deleteDeg1Chain(int v) {
    assert(isNone(v));
    if(degree(v) > 1)
        return;

    int neigh = -1;
    if (degree(v) > 0){
        neigh = neighbours[v][0];
        if(isDoubleEdge(v, 0)) {
            //is deg <= 1 and has double edge -> we delete its neighbour
            if (isNone(neigh)) {
                putInSolution(neigh);
                neigh = -1;
            }
            else {
                putInSolution(v);
                return;
            }
        }
    }

    if (!isNone(v)) // Could have got deleted by chaining after deleting double neighbour
        return;

    deleteVertex(v);
    setStatus(v, STATUS_DELETED);
    deleted++;
    
    if(neigh >= 0 && degree(neigh) <= 1 && isNone(neigh))
        deleteDeg1Chain(neigh);
}

// I will use it only in small cases (deg 2 vertices), no need to make 
// additional vector to keep it
int Graph::doubleNr(int v) {
    int res = 0;
    for(int i = 0; i < neighbours[v].size(); i++) {
        res += neighDouble[v][i];
    }
    return res;
}


int Graph::findNrInNeigh(int u, int me) {
    for(int i = 0; i < neighbours[u].size(); i++) {
        if (neighbours[u][i] == me) {
            return i;
        }
    }
    return -1;
}

void Graph::mergeDeg2Neigh(int cur) {
    // cout << cur << " " << degree(cur) << "deg \n";
    assert(degree(cur) == 2);
    int u = neighbours[cur][0], w = neighbours[cur][1];

    // We create edge now by putting w/v in u and u/v in w
    int cur_in_u = posAtNeigh[cur][0];
    int cur_in_w = posAtNeigh[cur][1];

    neighbours[u][cur_in_u] = w;
    neighbours[w][cur_in_w] = u;

    neighDouble[u][cur_in_u] = false;
    neighDouble[w][cur_in_w] = false;

    posAtNeigh[u][cur_in_u] = cur_in_w;
    posAtNeigh[w][cur_in_w] = cur_in_u;

    pureDeleteVertex(cur);    
}

bool Graph::reduceDeg2Queue() {
    bool res = false;
    while(!deg2ToReduce.empty()) {
        int cur = deg2ToReduce.front();
        deg2ToReduce.pop();

        if(!isNone(cur))
            continue;

        if(degree(cur) < 2) {
            res = true;
            deleteDeg1Chain(cur);
            continue;
        }


        int dNum = doubleNr(cur);
        // They both exist
        int u = neighbours[cur][0], w = neighbours[cur][1];

        if (dNum == 1) {
            // u is connected with a double edge
            if (neighDouble[cur][0] == false)
                swap(u, w);

            if (isNone(u)) {
                res = true;
                putInSolution(u);
                if(isNone(cur))
                    deleteDeg1Chain(cur);
            }
        }

        if (dNum == 0) {
            // Check if they are connected
            int nr_w_in_u = findNrInNeigh(u, w);
            
            // There was edge u -> w
            // Deleting v makes it double
            if(nr_w_in_u != -1) {
                if (isInU(u) && isInU(w))
                        continue;

                if (isInU(u) || isInU(w))
                    changeInU = true;

                res = true;
                neighDouble[u][nr_w_in_u] = true;
                neighDouble[w][posAtNeigh[u][nr_w_in_u]] = true;

                //REMOVE him from neighbours too
                deleteNeighbour(u, posAtNeigh[cur][0]);
                deleteNeighbour(w, posAtNeigh[cur][1]);
                pureDeleteVertex(cur);
            }
            else { // There was no edge u->w
                // We create it now by putting w/v in u and u/v in w
                if (isInU(u) || isInU(w))
                    changeInU = true;

                mergeDeg2Neigh(cur);
            }
        }
    }
    return res;
}

void Graph::putInSolution(int v) {
    setStatus(v, STATUS_IN_SOLUTION);
    deleteVertex(v);
    X.push_back(v);
}

//Maybe add merging vertices here?
void Graph::putInSafe(int v) {
    changeInU = true;
    setStatus(v, STATUS_IN_SAFE);
    U.push_back(v);
}

vector<int> Graph::getX() {
    return X;
}
vector<int> Graph::getU() {
    return U;
}

int Graph::getXSize() {
    return X.size();
}

int Graph::getUSize() {
    return U.size();
}

bool Graph::isInU(int v) {
    return checkStatus(v, STATUS_IN_SAFE);
}

bool Graph::isInX(int v) {
    return checkStatus(v, STATUS_IN_SOLUTION);
}

bool Graph::isNone(int v) {
    return checkStatus(v, STATUS_NONE);
}

bool Graph::checkStatus(int v, int status) {
    return getStatus(v) == status;
}

int Graph::getStatus(int v) {
    assert(v >= 0 && v < status.size());
    return status[v];
}

void Graph::setStatus(int v, int st) {
    assert(v >= 0 && v < status.size());
    status[v] = st;
}

//  X + U + DEL = neighbours.size()?
bool Graph::isEmpty() {
    return (X.size() + U.size() + deleted) == neighbours.size();
}


bool Graph::hasDoubleToU(int v) {
    for(int i = 0; i < neighbours[v].size(); i++) {
        int cur = neighbours[v][i];
        if(isInU(cur) && neighDouble[v][i])
            return true;
    }
    return false;
}

// Deletes vertex without affecting its neighbours
void Graph::pureDeleteVertex(int v) {
    assert(isNone(v));
    assert(v >= 0 && v < neighbours.size());
    setStatus(v, STATUS_DELETED);
    deleted++;
    neighbours[v].clear();
    neighDouble[v].clear();
    posAtNeigh[v].clear();
}

// TODO:
// Status of vertex is changed by caller
void Graph::deleteVertex(int v) {
    assert(v >= 0 && v < neighbours.size());

    vector<int> d1Neighs;

    for (int i = 0; i < neighbours[v].size(); i++) {
        int cur_neigh = neighbours[v][i];
        // Deletes me at neighbour vectors
        deleteNeighbour(cur_neigh, posAtNeigh[v][i]);

        // if (neighbours[cur_neigh].size() <= 1)
        //     d1Neighs.push_back(cur_neigh);

        // if (neighbours[cur_neigh].size() == 2 && isNone(cur_neigh))
        //     deg2ToReduce.push(cur_neigh);
    }

    neighbours[v].clear();
    neighDouble[v].clear();
    posAtNeigh[v].clear();

    // for (int i = 0; i < d1Neighs.size(); i++)
    //     if (isNone(d1Neighs[i]))
    //         deleteDeg1Chain(d1Neighs[i]);
}

void Graph::deleteNeighbour(int v, int which) {
    // Self loop -> don't mess up the vectors 
    if (v == neighbours[v][which])
        return;

    assert(v >= 0 && v < neighbours.size());
    assert(which >= 0 && which < neighbours[v].size());

    int del_neigh = neighbours[v][which];
    int last_neigh = neighbours[v].back();

    neighbours[v][which] = neighbours[v].back();
    neighbours[v].pop_back();

    neighDouble[v][which] = neighDouble[v].back();
    neighDouble[v].pop_back();

    posAtNeigh[v][which] = posAtNeigh[v].back();
    posAtNeigh[v].pop_back();

    if (del_neigh != last_neigh) {
        //we need to set pos at the neighbour right
        int myPos = posAtNeigh[v][which];
        posAtNeigh[last_neigh][myPos] = which;
    }   
}


bool Graph::checkCycles() {
    vis.clear();
    vis.resize(N, 0);
    bool res = false;
    for (int i = 0; i < N; i++) {
        if(!vis[i] && !isInX(i)) {
            res |= dfsCycles(i, -1);
            if (res)
                return res;
        }
    }
    return res;
}


bool Graph::dfsCycles(int v, int from) {
    vis[v] = 1;
    bool ret = false;

    for(int i = 0; i < neighbours[v].size(); i++) {
        int akt = neighbours[v][i];

        if (vis[akt] && !(akt == from && !isDoubleEdge(v, i))) {
            return true;
        }

        if (!vis[akt] && !isInX(akt)) {
            ret |= dfsCycles(akt, v);
        }
    }

    return ret;
}

bool Graph::isDoubleEdge(int v, int pos) {
    return neighDouble[v].size() > pos && neighDouble[v][pos];
}

bool Graph::checkSameCCNeighbours() {
    bool res = false;
    if(!changeInU)
        return res;
    recalcComponentsInU();

    for(int i = 0; i < neighbours.size(); i++) {
        if (isNone(i)) {
            set<int> s;
            int uCnt = 0;
            bool put = false;
            for(int j = 0; j < neighbours[i].size(); j++) {
                int curNeigh = neighbours[i][j];

                if (isInU(curNeigh) && isDoubleEdge(i, j)) {
                    res = true;
                    put = true;
                    putInSolution(i);
                    break;
                }

                if (isInU(curNeigh)) {
                    uCnt++;
                    s.insert(ccNr[neighbours[i][j]]);
                    if (s.size() < uCnt && !put) {
                        res = true;
                        put = true;
                        putInSolution(i);
                        break;
                    }
                }
            }
            if (s.size() < uCnt && !put) {
                res = true;
                putInSolution(i);
            }
        }
    }

    changeInU = false;
    return res;
}

void Graph::recalcComponentsInU() {
    vis.clear();
    vis.resize(N, 0);
    ccNr.clear();
    ccNr.resize(N, -1);
    int nr = 0;

    for(int i = 0; i < neighbours.size(); i++) {
        if (isInU(i) && !vis[i]) {
            dfsComp(i, nr);
            nr++;
        }
    }
}

void Graph::dfsComp(int v, int nr) {
    vis[v] = 1;
    ccNr[v] = nr;

    for(int i = 0; i < neighbours[v].size(); i++) {
        int akt = neighbours[v][i];

        if (!vis[akt] && isInU(akt)) {
            dfsComp(akt, nr);
        }
    }
}