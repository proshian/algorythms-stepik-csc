def binary_search(A, b):
    l, r = 0, len(A) - 1
    while l <= r:
        m = (l+r)//2
        if A[m] == b:
            return m
        if A[m] > b:
            r = m - 1
        else:
            l = m + 1
    return -2

def main():
    n, *A = map(int, input().split())
    k, *B = map(int, input().split())
    for b in B:
        print(binary_search(A,b) + 1, end = " ")

main()