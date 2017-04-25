/* 
*	Author = Krzysztof Kiljan
*   Algorithm for finding linear optimal solution for vertex cover
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
int n, m, k, l, test = 1;
const int inf = 1000 * 1000 * 1000;
const int MAKSN = 1000 + 13;

vector<VI> A;
VI b, c;


void readIn() {
    // cout << "Format: Ile_rownan  "
    // A = ([-1, 1], [1, 0], [0,1])
// b = (1,3,2)
// c = (1,1)

    cin >> n >> m ; // n - ilość równań, m - ilość zmiennych

//A
    REP(i, n) {
        VI cur; 
        REP(j, m) {
            cin >> k;
            cur.PB(k);
        }
        A.PB(cur);
    }

// b
    REP(i, n){
        cin >> k;
        b.PB(k);
    }

// c
    REP(i, m) {
        cin >> k;
        c.PB(k);
    }
}

void printAll() {
    cout << "A = [" ;
    REP(i, A.size()) {
        cout<< "(";
        REP(j, A[i].size()) {
            if(j)
                cout << ", ";
            cout << A[i][j];
        }
        cout << ")";
        if(i + 1 < (int)A.size())
            cout << ", ";

    }
    cout <<"]\n";

    cout << "b = (";
    REP(i, b.size()) {
        cout << b[i];
        if(i + 1 < (int)b.size())
            cout << ", ";
    }
    cout << ")\n";

    cout << "c = (";
    REP(i, c.size()) {
        cout << c[i];
        if(i + 1 < (int)c.size())
            cout << ", ";
    }
    cout << ")\n";



}

void solve() {
    GRBEnv *env = new GRBEnv();
    env->set(GRB_DoubleParam_TimeLimit, 60);

    GRBModel *model = new GRBModel(*env);


    vector<GRBVar> x(n+m);
    REP(i, n+m)
        x[i] = model->addVar(0, GRB_INFINITY, 1, GRB_CONTINUOUS,
                         	string("x_") + to_string(i));


    GRBLinExpr obj = 0.0;
    REP(i, n)
   		obj += x[m+i];
  	model->setObjective(obj, GRB_MINIMIZE);

    model->update();  // bez tego constrainty nie pojda, zmiana atrybutow
                      // zmiennych tez nie



    REP(i, n) {
        GRBLinExpr expr = 0;
        expr += b[i];
        REP(j, m) {
            expr -= (A[i][j] * x[j]);
        }
        model->addConstr(expr == x[i+m]);
    }

    model->update();  // bez tego zoptymalizuje ok ale wypisze zle

    model->write("model.lp");

    model->optimize();

    REP(i, n+m)
    cout << "x[" << i << "] = " << x[i].get(GRB_DoubleAttr_X) << "\n";

    delete model;
    delete env;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);
    readIn();
    printAll();
    solve();
    return 0;
}
