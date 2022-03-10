from collections import deque

def merge_and_count(A, B, counter):
    result = []
    i_A = i_B = 0
    while i_A < len(A) and i_B < len(B):
        if A[i_A] <= B[i_B]:
            result.append(A[i_A])
            i_A += 1
        else:
            counter += len(A) - i_A
            result.append(B[i_B])
            i_B += 1
            
    not_finished_arr, i = (A, i_A) if i_B == len(B) else (B, i_B)
    while i < len(not_finished_arr):
        result.append(not_finished_arr[i])
        i += 1
   
    return result, counter


def permutation_counter(A):
    counter = 0
    sorted_parts = deque()
    for element in A:
        sorted_parts.append([element])
    while len(sorted_parts) > 1:
        # решаем ситуацию, когда "с прошлого уровня" остался один элемент
        if len(sorted_parts[0]) < len(sorted_parts[1]):
            sorted_parts.append(sorted_parts.popleft())
        merged_arr, counter = merge_and_count(sorted_parts.popleft(), sorted_parts.popleft(), counter)
        sorted_parts.append(merged_arr)
    return counter
    
def main():
    input()  # это количество элементов. Оно не нужно. Можно было считать так: n = int(input())
    initial_array = []
    for item in map(int, input().split()):
        initial_array.append(item)
    print(permutation_counter(initial_array))
    
if __name__ == "__main__":
    main()