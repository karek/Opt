#include "lp_cycles.h"
#include <iostream>

using namespace std;

LP_Cycles::LP_Cycles() {}

LP_Cycles::LP_Cycles(Graph g_) : g(g_) {}

void LP_Cycles::dfsCycles(int v, int from, vector<int> &stack,
                          GRBModel *model) {
    vis[v] = 1;
    stack.push_back(v);

    for (uint i = 0; i < neighbours[v].size(); i++) {
        int cur = neighbours[v][i];

        if (cur == v) {  // Self loop
            GRBLinExpr expr = x[v];
            model->addConstr(expr >= 1);
        }

        if (neighDouble[v][i]) {  // Double edge = circle
            GRBLinExpr expr = x[v] + x[cur];
            model->addConstr(expr >= 1);
        }
        else if (vis[cur] == 1 && !(cur == from)) {
            GRBLinExpr expr = 0;
            string s(neighbours.size(), 0);

            // cerr << cur << " "  << v << " " << from << "haha \n";
            s[cur] = 1;
            expr += x[cur];
            int j = stack.size() - 1;
            while (j >= 0 && stack[j] != cur) {
                expr += x[stack[j]];
                s[stack[j]] = 1;
                j--;
            }

            if (!masks.count(s)) {
            	model->addConstr(expr >= 1);
            	masks.insert(s);
            }
        }

        if (!(vis[cur] == 1)) {
            dfsCycles(cur, v, stack, model);
        }
    }

    stack.pop_back();
    vis[v] = 2;
}

vector<int> LP_Cycles::solve() {
    // g.printGraph();
    vector<int> stack;
    neighbours = g.getNeighbours();
    neighDouble = g.getDoubles();
    vis.resize(neighbours.size());
    x.resize(neighbours.size());

    int n = g.getN();

    GRBEnv *env = new GRBEnv();
    env->set(GRB_DoubleParam_TimeLimit, 600);
    GRBModel *model = new GRBModel(*env);
    model->set("LogToConsole", "0");
    model->set("LogFile", "opt.log");

    for (int i = 0; i < n; i++) {
        x[i] = model->addVar(0, 1, 1, GRB_BINARY, string("x_") + to_string(i));
    }

    GRBLinExpr obj = 0.0;
    for (int i = 0; i < n; i++) {
        obj += x[i];
    }
    model->setObjective(obj, GRB_MINIMIZE);

    model->update();

    for (uint i = 0; i < neighbours.size(); i++) {
        // if (!vis[i])
        // cerr << "START z " << i << "\n\n";
        vis.clear();
        vis.resize(n, 0);
		dfsCycles(i, -1, stack, model);
    }

    // Maybe add approx solution as start points?
    // vector<int> v = find_approx();
	// cerr << "APPROX " << v.size() << "\n";

    cerr << "Starting to calculate LP...\n";

    model->update();
    model->write("model.lp");
    model->optimize();

    // GRBModel mp = model->presolve();
	// mp.write("presolved.lp");

    // mp.optimize();

    for (int i = 0; i < n; i++) {
        cerr << "x[" << i << "] = " << x[i].get(GRB_DoubleAttr_X) << "\n";
        if(x[i].get(GRB_DoubleAttr_X) == 1)
        	sol.push_back(i);
    }


    for(int i = 0; i < sol.size(); i++) {
    	g.deleteVertex(sol[i]);
    }

    g.printGraph();

    cerr << boolalpha;  
    cerr << "Is acyclic: " << !g.checkCycles() << "\n";

    delete model;
    delete env;
    return sol;
}

vector<int> LP_Cycles::find_approx() {
    Graph gApx(g);

    while (gApx.checkCycles()) {
        pair<int, int> md = gApx.getMaxDegV();
        int v = md.first;
        gApx.putInSolution(v);
    }
    //    cerr << "Approx solution graph:\n";
    // gApx.printGraph();

    return gApx.getX();
}
