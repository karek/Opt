Solution for Independent set using linear programing.


The solution is almost the same as for Vertex Cover, which means most of its README applies here too.


I create a variable x_i for every vertex in Graph.
Than for every pair of vertices (u, v) connected with an edge, I add constraint x_u + x_v <= 1, which means that at most one 
of these vertices should be found in the correct solution.


Example of how to run:
`make IS.o`
`./IS.o <bool if_binary>`
