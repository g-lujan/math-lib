import numpy as np
from timeit import default_timer as timer

A = np.loadtxt('A.txt', usecols=range(200))
B = np.loadtxt('B.txt', usecols=range(300))

start = timer()
AxB = A.dot(B)
elapsed = timer() - start

print(AxB)
print(f'{elapsed * 1000} ms')

