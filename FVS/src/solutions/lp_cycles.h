#include "../lib/Graph.h"
#include "Solution.h"
#include "gurobi_c++.h"
#include <unordered_set>
#include <string>

using std::string;
using std::unordered_set;

class LP_Cycles : public Solution {

public:

	Graph g;
	LP_Cycles();
	LP_Cycles(Graph);
	vector<int> solve();
	vector<int> find_approx();
	vector<vector<int>> neighbours;
    vector<vector<bool>> neighDouble;
    void dfsCycles(int v, int from, vector<int>& stack, GRBModel *model);

private:
	vector<int> vis;
	vector<GRBVar> x;
	vector<int> sol;
// It worked extra slow (for example for graph 099 - 37 vertices it generated
	// Optimize a model with 12950200 rows, 37 columns and 79226024 nonzeros)
	//  So I have decided to add bitmasks to make same cycles not repeat

	//  With masks -> Optimize a model with 2332 rows, 37 columns and 23251 nonzeros
	// Quite an improvement ;)
	unordered_set<string> masks;
	int size_cap;
};