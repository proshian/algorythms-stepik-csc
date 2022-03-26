def get_pos(l, A, A_i):
    left, right = 0, len(l) - 1
    while left <= right:
        middle = (left + right) // 2
        if A[l[middle]] >= A_i:
            left = middle + 1
        else: 
            right = middle - 1
    return left

def lnis(arr):
    l = [0]
    all_preditors = [[0, 0]]
    for i in range(1, len(arr)):
        pos = get_pos(l, A, A[i])
        if pos == len(l):
            l.append(i)
        else:
            l[pos] = i
        all_preditors.append([pos, i])
        
    cur_index = len(l) - 1
    
    result = []
    for i in range(len(all_preditors) - 1, -1, -1):
        p = all_preditors[i]
        if p[0] == cur_index:
            result.append(p[1] + 1)
            cur_index -= 1
    result.reverse()
    
    return result

if __name__ == "__main__":
    input()
    A = list(map(int, input().split()))
    lnis_result = lnis(A)
    print(len(lnis_result))
    print(*lnis_result)