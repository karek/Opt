#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "Graph.h"
#include <map>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::map;
using std::pair;

class Translator {
   private:
    int N, M;
    // String representing vertex i in original input
    vector<string> names;

   public:
    void read_input(Graph* g);
    int add_vertex(string name, map<string, int>& namesMap);
    void printNames(vector<int> v);
    string getName(int v);
    vector<string> list_of_names(vector<int> v);
};

#endif  // TRANSLATOR_H
