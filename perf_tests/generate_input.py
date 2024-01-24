import numpy as np

print("Generating matrix A...")
A = np.matrix(np.random.rand(3000, 2000))
with open('A.txt','wb') as f:
    for line in A:
        np.savetxt(f, line, fmt='%.10f')

print("Generating matrix B...")
B = np.matrix(np.random.rand(2000, 3000))
with open('B.txt','wb') as f:
    for line in B:
        np.savetxt(f, line, fmt='%.10f')