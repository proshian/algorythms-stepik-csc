len_A = int(input())
A = list(map(int, input().split()))
D = [1] * len_A
for i in range(len_A):
    for j in range(i):
        if A[i] % A[j] == 0 and D[j] + 1 > D[i]:
            D[i] = D[j] + 1
print(max(D))