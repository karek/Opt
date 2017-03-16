/*
*   Author = Krzysztof Kiljan
*   Algorithm for finding linear optimal solution for Independent set
*   Pretty much the same as Vertex Cover - constraints are no <= 1 instead of >=
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "gurobi_c++.h"

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
int n, m, k, l, test = 1, a, b;
const int inf = 1000 * 1000 * 1000;
const int MAKSN = 1000 + 13;

VI E[MAKSN];

void readIn() {
    cin >> n >> m;
    REP(i, m) {
        cin >> a >> b;
        a--;
        b--;
        E[a].PB(b);
        E[b].PB(a);
    }
}

void solve(bool bin) {
    GRBEnv *env = new GRBEnv();
    env->set(GRB_DoubleParam_TimeLimit, 60);

    GRBModel *model = new GRBModel(*env);

    vector<GRBVar> x(n);
    REP(i, n)
    if (!bin)
        x[i] = model->addVar(0, GRB_INFINITY, 1, GRB_CONTINUOUS,
                             string("x_") + to_string(i));
    else
        x[i] = model->addVar(0, GRB_INFINITY, 1, GRB_BINARY,
                             string("x_") + to_string(i));

    GRBLinExpr obj = 0.0;
    REP(i, n)
    obj += x[i];
    model->setObjective(obj, GRB_MAXIMIZE);

    model->update();

    REP(i, n) {
        REP(j, E[i].size()) {
            int y = E[i][j];
            if (y > i)
                model->addConstr(x[i] + x[y] <= 1);
        }
    }

    model->update();

    model->write("model.lp");

    model->optimize();

    REP(i, n)
    cout << "x[" << i << "] = " << x[i].get(GRB_DoubleAttr_X) << "\n";

    delete model;
    delete env;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);
    readIn();
    if (argc > 1)
        solve(atoi(argv[1]));
    else
        solve(false);

    return 0;
}
