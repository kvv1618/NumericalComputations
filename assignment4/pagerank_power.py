from copy import deepcopy

def pagerankpow(G):
    n = len(G)
    L = [[] for i in range(n)]
    c = [0 for i in range(n)]
    
    for j in range(n):
        for i in range(n):
            if G[i][j] == 1:
                L[j].append(i)
        c[j] = len(L[j])
    
    p = 0.85
    delta = (1-p)/n
    x = [1/n for i in range(n)]
    z = [0 for i in range(n)]
    cnt = 0

    while max([abs(x[i]-z[i]) for i in range(n)]) > 1e-4:
        z = deepcopy(x)
        x = [0 for i in range(n)]
        for j in range(n):
            if c[j] == 0:
                for i in range(n):
                    x[i] += z[j]/n
            else:
                for i in L[j]:
                    x[i] += z[j]/c[j]
        for i in range(n):
            x[i] = p*x[i] + delta
        cnt += 1
    
    return x, cnt

G = [[0., 0., 0., 1., 0., 1.],
       [1., 0., 0., 0., 0., 0.],
       [0., 1., 0., 0., 0., 0.],
       [0., 1., 1., 0., 0., 0.],
       [0., 0., 1., 0., 0., 0.],
       [1., 0., 1., 0., 0., 0.]]

x, cnt = pagerankpow(G)

print("PageRank vector: ", x)
print("Number of iterations: ", cnt)
