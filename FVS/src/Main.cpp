// #include "solutions/6.75.h"
#include "lib/Graph.h"
#include "lib/Translator.h"
#include "solutions/lp_cycles.h"
#include "gurobi_c++.h"
#include <iostream>
#include <set>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define ST first
#define ND second
#define MP make_pair
#define PB push_back

typedef vector<int> VI;
typedef pair<int, int> PI;
typedef vector<PI> VPII;
typedef set<int> SI;
typedef long long LL;

#ifdef DEBUG
const bool debug = true;
#else
const bool debug = false;
#endif
int n, m, k, l, test = 1;
const int inf = 1000 * 1000 * 1000;
const int MAKSN = 1000 + 13;


int main() {
	Graph g;
	Translator t;
    t.read_input(&g);

	g.printGraph();

	// t.setGraph(&g);

	LP_Cycles s(g);
	vector<int> sol = s.solve();
	cerr << "Final solution: \n";
	cout << sol.size() << "\n";
	t.printNames(sol);



	return 0;
}