/*
* Author: Krzysztof Kiljan
* Solution for n queens problem using MIP.
* Two versions:
* 	v.1 Writes out whole inequalities for rows, columns and diags
*		Example: x_0_0 + x_1_1 + x_2_2 + x_3_3 <= 1 -- Only one on this
*diagonal can be in solution
*       Pros: less inequalities (May be faster for solver)
*		Cons: Generation code is worse / harder
*   v.2 Writes inequalities for every pair of positions that would check mate
*each other
*       Example: x_0_0 + x_1_1 <= 1   -- Only one in a pair can be in solution
*   	Pros: Easier generation code
*		Cons: LP may work slower
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define FOR(i, a, b) for(int i = a; i < b; i++)
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
const int MAKSN = 1000 * 1000 + 13;

void readIn() {
    cin >> n;
}

void target() {
    cout << "maximize ";
    REP(i, n) {
        REP(j, n) {
            cout << "x_" << i << "_" << j;
            if (n - 1 - j || n - 1 - i)
                cout << " + ";
        }
    }
    cout << "\nSubject to\n";
}

void row_col(bool col) {
    REP(i, n) {
        REP(j, n) {
            col ? cout << "x_" << i << "_" << j : cout << "x_" << j << "_" << i;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " <= 1\n";
    }
}

bool inBoard(int x, int y) {
    return (x >= 0 && y >= 0 && x < n && y < n);
}

void traverse(int x, int y, int dx, int dy) {
    while (inBoard(x, y)) {
        cout << "x_" << x << "_" << y;
        if (inBoard(x + dx, y + dy))
            cout << " + ";
        x += dx;
        y += dy;
    }
    cout << " <= 1\n";
}

void diags(int dx, int dy, int type) {
    REP(i, n) {
        // bleh, really not cool ;(
        int x = i, y = 0;
        if (type == 1) {
            x = 0;
            y = i;
        }
        if (type == 2) {
            x = i;
            y = n - 1;
        }
        traverse(x, y, dx, dy);
    }
}

void varRestrictions() {
    cout << "Binary\n";
    REP(i, n) {
        REP(j, n)
        cout << "x_" << i << "_" << j << "\n";
    }
}

bool oneDiag(PI a, PI b) {
    return abs(a.ST - b.ST) == abs(a.ND - b.ND);
}

bool check(PI a, PI b) {
    return (a.ST == b.ST || a.ND == b.ND) || oneDiag(a, b);
}

void pairSol() {
    REP(i, n) REP(j, n)
    FOR(ii, i, n) FOR(jj, j, n)
		if(ii != i || jj != j) 
			if(check(MP(i,j), MP(ii, jj))) 
				cout << "x_" << i << "_" << j << " + " 
					<< "x_" << ii << "_" << jj << " <= 1\n";
}

void solve(int type) {
    target();
    // v.1 -- Whole equations of rows, columns, diags

    if(!type) {
	    REP(i, 2)
	    row_col(i);

	    diags(1, 1, 0);
	    diags(1, 1, 1);
	    diags(1, -1, 1);
	    diags(1, -1, 2);
    }
    // v.2 -- Pairs
    else
    	pairSol();

    varRestrictions();
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0);
    readIn();
    if(argc > 1)
    	solve(atoi(argv[1]));
	else
		solve(0);

    return 0;
}
