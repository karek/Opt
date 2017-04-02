︠e37faad5-9e73-430e-a528-8c860b5c409es︠
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

︡717543be-f517-4d4e-ad8b-0e77181c5a76︡{"done":true}︡
︠200bfdc9-945c-4b4f-b79c-1aec69cbbaa1s︠

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

︡7783615d-96ad-4ca4-9cd5-6c0f8f3bb1cf︡{"stdout":"Maximization:\n  x_2 \n\nConstraints:\n  x_0 + x_1 + x_2 <= 1.0\n  1.5 x_0 + x_1 + x_2 <= 1.5\n  2.0 x_0 + x_1 + x_2 <= 0.5\n  - x_0 - x_1 + x_2 <= -0.5\n  -0.7 x_0 - x_1 + x_2 <= -0.8\n  - x_2 <= 0.0\nVariables:\n  x_0 is a continuous variable (min=-oo, max=+oo)\n  x_1 is a continuous variable (min=-oo, max=+oo)\n  x_2 is a continuous variable (min=-oo, max=+oo)\n"}︡{"stdout":"Optymalna wartość funkcji celu =  0.25\n"}︡{"stdout":"a= -1.0  b= 1.75  delta= 0.25\n"}︡{"file":{"filename":"/projects/6770e1a8-5f05-4fdc-b27f-568429deebca/.sage/temp/compute0-us/10011/tmp_jXF7Zs.svg","show":true,"text":null,"uuid":"10567498-4959-4880-8ce5-dfd2563855c5"},"once":false}︡{"done":true}︡
︠1313f867-29b1-4ad8-b51e-6f0ec1bb0553︠









