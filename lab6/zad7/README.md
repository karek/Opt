z7.cpp contains a program for creating an auxiliary program(a program which will create some feasible solution) to a given linear program.

It is not true, that solution (0, 0, ..., 0) is a feasible solution for every LP. In such case we need some help in finding some other feasible solution.

In z7.cpp we take an LP in a normal form and based on it find a feasible solution using another LP.

Input for program is in form:

N_OF_EQUATIONS N_OF_VARS(M)<br />
A(matrix NxM)<br />
b(vector N x 1)<br />
c(vector M x 1)<br />

example input:

2 3<br />
1 3 1 0 2 1<br />
4 2<br />
1 2 0<br />

should be input for LP:

max x_0 + 2 * x_1<br />
x_0 + 3 x_1 + x_2 = 4<br />
    + 2 x_1 + x_2 = 2<br />


After run we can check the auxiliary program at filer model.lp
At the output we can find the values for each variable. If value of the optimized function is > 0, than the LP has no feasible solutions. 

Example inputs and outputs:

in/1.in:

2 3<br />
1 3 1 0 2 1<br />
4 2<br />
1 2 0<br />


output: 
Optimal objective  0.000000000e+00<br />
x[0] = 1<br />
x[1] = 1<br />
x[2] = 0<br />
-- Auxiliary vars:<br />
x[3] = 0<br />
x[4] = 0<br />



in/2.in: 

2 4<br />
8 3 -5 1 3 1 -2 -1<br />
4 1<br />
7 2 -3 -4<br />

output: 

Optimal objective  0.000000000e+00<br />
x[0] = 0.454545<br />
x[1] = 0<br />
x[2] = 0<br />
x[3] = 0.363636<br />
-- Auxiliary vars:<br />
x[4] = 0<br />
x[5] = 0<br />


in/3.in:<br />
3 2<br />
-1 1 1 0 0 1<br />
1 3 2<br />
1 1<br />

output:<br />
Optimal objective  2.000000000e+00    <---- which means the LP has no feasible solutions <br />
x[0] = 3<br />
x[1] = 2<br />
-- Auxiliary vars:<br />
x[2] = 2<br />
x[3] = 0<br />
x[4] = 0<br />
