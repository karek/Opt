import itertools
list2d = [3*[1], 15* [0]]
merged = lambda l: list(itertools.chain(*l))
print merged(list2d)


%typeset_mode True

     # A, B
A = (merged([3*[1], 15*[0]]), merged([3*[0], 2*[1], 13 * [0]]), merged([5*[0], 3*[1], 10 * [0]]) , merged([8*[0], 3*[1], 7*[0]]),
        merged([11*[0], 2*[1], 5*[0]]), merged([13*[0], 3*[1], 2*[0]]), merged([16*[0], 2*[1]]),
        merged([[1], 2*[0], [1], 4*[0], [1], 9 * [0]]), merged([[0], [1], 4*[0], [1], 9*[0], [1], [0]]),
        merged([ 2 * [0], [1], 12*[0], [1], 2*[0]]), merged([ 4 * [0], [1], 4*[0], [1], 8*[0]]),
        merged([ 5 * [0], [1], 5*[0], [1], [0], [1],  4*[0]]),
        merged([ 7 * [0], [1], 6*[0], [1], 3* [0]]),
        merged([ 10 * [0], [1], [0], [1], 4* [0], [1]])
    )
b = (14*[1])
c = tuple((18*[1]))
P = InteractiveLPProblem(A, b, c, ["xAq", "xAs","xAv", "xBq", "xBt", "xCr", "xCs", "xCu", "xDq", "xDt", "xDw",
                                  "xEr", "xEw", "xFr", "xFu", "xFv", "xGs", "xGw"],
                         constraint_type="==",variable_type=">=")

view(P)


# As we can see in dual program, every node gets its own variable, and for every E(v1, v2) y_v1 + y_v2 >= 1, 
# which is exactly the same as vertex cover formulation

view(P.dual())