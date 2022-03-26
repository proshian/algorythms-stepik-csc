def get_pos_naive(l, A, A_i):
    for pos in range(len(l)):
        if A[l[pos][-1]] < A_i:
            return pos
    return len(l)
    
def get_pos(l, A, A_i):
    left, right = 0, len(l) - 1
    while left <= right:
        middle = (left + right) // 2
        if A[l[middle][-1]] >= A_i:
            left = middle + 1
        else: 
            right = middle - 1
    return left

def lnis(arr):
    l = [[0]]
    for i in range(1, len(arr)):
        pos = get_pos(l, A, A[i])
        if pos == len(l):
            l.append(l[pos - 1] + [i])
        elif pos == 0:
            l[pos] = [i]
        else:
            l[pos] = l[pos - 1] + [i]
    return l[-1]

if __name__ == "__main__":
    input()
    A = list(map(int, input().split()))
    lnis_result = lnis(A)
    print(len(lnis_result))
    for el in lnis_result:
        print(el + 1, end = " ")
