Linear programming (to be exact - mixed integer programming) solution for problem of finding maximum number of queens 
you can place on a n x n chessboard.

Compilation:

make hetmani.o

Usage 

`./hetmani.o <par>`

It takes one number n from stdin.

par = 0 | 1 is optional  and means the type of solution we would like to use. (There are two implemented)
0 -> Whole rows / columns /diags as inequalities
1 -> Pairs of variables as inequalities

For specifics look into the code :)


The program generates file containing lp constraints for the solution.
It matches the syntax of gurobi solver (probably others too...)

Example usage on gurobi 

./hetmani.o 0 >h4.lp
4
gurobi_cl ResultFile=h4.sol h4.lp

File h4.sol contains values found for each variable.
