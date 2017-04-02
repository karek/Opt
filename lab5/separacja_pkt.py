# Separacja punktów prostą

# Dane problemu

W = [ (1,1), (1.5,1.5), (2,0.5)]
B = [ (1, 0.5), (0.7, 0.8)]

#Punkty
#point(W, rgbcolor=(0, 1, 0)) + point(B, rgbcolor=(1, 0, 0))

# Rozwiązanie problemu

p = MixedIntegerLinearProgram(maximization=true)
var = p.new_variable()

a, b, delta = var['a'], var['b'], var['delta']

p.set_objective(delta)



# A, B - punkty leżące na brzegu półpłaszczyzny; P - punkt leżący wewnątrz
def add_W(A):
    p.add_constraint((a*A[0] + b + delta) <= A[1])

def add_B(A):
    p.add_constraint((a*A[0] + b - delta) >= A[1])

for i in range(len(W)):
    add_W(W[i])

for i in range(len(B)):
    add_B(B[i])

p.add_constraint(delta >= 0)

p.show()

# Rozwiązanie problemu

print 'Optymalna wartość funkcji celu = ', p.solve()
print 'a=', p.get_values(a), ' b=', p.get_values(b), ' delta=', p.get_values(delta)

point(W, rgbcolor=(0, 1, 0)) + point(B, rgbcolor=(1, 0, 0)) + plot(p.get_values(a) * x + p.get_values(b), color="blue", xmin=0, xmax=3)