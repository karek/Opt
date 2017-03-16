Solution for vertex cover using linear programing.

As it can be easily noticed, I use gurobi as the solver for linear program.

I create a variable x_i for every vertex in Graph.
Than for every pair of vertices (u, v) connected with an edge, I add constraint x_u + x_v >= 1, which means that at least one 
of these vertices should be found in the correct solution.


It is possible to run a program in two modes - using binary or continous variables. It is easy to notice, that the answer for binary is always larger than for continous variables. It is because continous one doesn't give us exact solution for an answer (we can't take half a human after all).  Programs with integral constraints are after all NP-hard. (The solution for vertex cover above is a reduction:)) We can use some parametrized algorithms on the LP(not MIP) results if we want to have exact solution a bit faster. 
There are also a lot of approximation algorithms if we don't care if our solution is exactly optimal. (F.E. take all variables with x_i >= 0.5 would give us 2-approx)

Example of how to run:
`make VC.o`
`./VC.o <bool if_binary>`

After running the program, you can also find the model it generated in model.lp



Disclaimer: 
I had quite big problems with compilation - I had to downgrade my compiler, because Gurobi wouldn't 
compile with gcc 5.4. (Which isn't mentioned anywhere on the internet...) Also if you would like to run it on your computer, 
you should check whether positions of your /include and /lib directory match and the version of Gurobi you have installed.

