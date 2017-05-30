In this task we were supposed to find a dual solution to the matching in the graph from the picture below. 
(With the weights of all of the edges were 1.)

![Bipartite Graph](https://www.mimuw.edu.pl/~henrykm/lib/exe/fetch.php?cache=&media=bipartite.png) 


After implementing it as a linear program in sage and finding the dual, it came out that in dual program, every node gets its own variable y_i.
Than for every E(v1, v2) y_v1 + y_v2 >= 1, which is exactly the same as minimum vertex cover formulation.


