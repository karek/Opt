z7.cpp contains a program for creating an auxiliary program(a program which will create some feasible solution) to a given linear program.

It is not true, that solution (0, 0, ..., 0) is a feasible solution for every LP. In such case we need some help in finding some other feasible solution.

In z7.cpp we take an LP in a normal form and based on it find a feasible solution using another LP.

Input for program is in form:

N_OF_EQUATIONS N_OF_VARS(M)
A(matrix NxM)
b(vector N x 1)
c(vector M x 1)

example input:

2 3
1 3 1 0 2 1
4 2
1 2 0

should be input for LP:

max x_0 + 2 * x_1
x_0 + 3 x_1 + x_2 = 4
    + 2 x_1 + x_2 = 2


After run we can check the auxiliary program at filer model.lp
At the output we can find the values for each variable. If value of the optimized function is > 0, than the LP has no feasible solutions. 

Example inputs and outputs:

in/1.in:

2 3
1 3 1 0 2 1
4 2
1 2 0


output: 
Optimal objective  0.000000000e+00
x[0] = 1
x[1] = 1
x[2] = 0
-- Auxiliary vars:
x[3] = 0
x[4] = 0



in/2.in 

2 4
8 3 -5 1 3 1 -2 -1
4 1
7 2 -3 -4

output: 

Optimal objective  0.000000000e+00
x[0] = 0.454545
x[1] = 0
x[2] = 0
x[3] = 0.363636
-- Auxiliary vars:
x[4] = 0
x[5] = 0


in/3.in
3 2
-1 1 1 0 0 1
1 3 2
1 1

output:
Optimal objective  2.000000000e+00    <---- which means the LP has no feasible solutions 
x[0] = 3
x[1] = 2
-- Auxiliary vars:
x[2] = 2
x[3] = 0
x[4] = 0
