import numpy as np

print("Generating matrix A...")
A = np.matrix(np.random.rand(300, 200))
with open('A.txt','wb') as f:
    for line in A:
        np.savetxt(f, line, fmt='%.10f')

print("Generating matrix B...")
B = np.matrix(np.random.rand(200, 300))
with open('B.txt','wb') as f:
    for line in B:
        np.savetxt(f, line, fmt='%.10f')