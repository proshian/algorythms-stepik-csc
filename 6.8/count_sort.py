def count_sort(arr, min_val, max_val):
    # создадим массив для подсчета элементов,
    # инициализированный нулями,
    # с длинной, равной количеству уникальных элементов, 
    b = [0] * (max_val - min_val + 1)
    
    sorted_arr = [0] * len(arr)
    
    # после выполнения цикла ниже
    # b[i] = количество раз, когда i встречается в arr
    for el in arr:
        b[el - min_val] += 1
    
    # после выполнения цикла ниже
    # b[i] = количество раз, когда в arr встречается число <= i 
    for i in range(1,len(b)):
        b[i] += b[i-1]
    
    for el in reversed(arr):
        sorted_arr[b[el - min_val] - min_val] = el
        b[el - min_val] -= 1
    return sorted_arr
    
if __name__ == '__main__':
    input()
    arr = list(map(int, input().split()))
    print(*count_sort(arr, 1, 10))